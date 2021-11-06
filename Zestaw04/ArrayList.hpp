#include <stdexcept>
#include <cstring>
#include <memory>
#include <cassert>

template<class T>
class List {
private:
	int m_size;
	int m_capacity;
	T* m_arr = nullptr;
	void allocate();
	void deallocate();

public:
	class iterator;
	class const_iterator;
	List ();
	List (const List<T>& other);
	List (List<T>&& other);
	~List ();
	List& operator=(const List<T>& other);
	List& operator=(List<T>&& other);

	// Uniwersalna referencja U&&, Wstawia element na początek listy
	template<class U>
	void push_front(U&& x);

	// Wstawia element na koniec listy
	template<class U>
	void push_back(U&& x);

	// Usuwa element z początku listy i zwraca jego wartość lub wyrzuca wyjątek gdy lista jest pusta
	T pop_front();

	// Usuwa element z końca listy i zwraca jego wartość lub wyrzuca wyjątek gdy lista jest pusta
	T pop_back();

	// Zwraca iterator wskazujący na pierwszy element
	iterator begin();

	// Zwraca const_iterator wskazujący na pierwszy element
	const_iterator begin() const;

	// Zwraca iterator wskazujący na ostatni element
	iterator end();

	// Zwraca const_iterator wskazujący na ostatni element
	const_iterator end() const;

	// Wyszukuje element o wartości "x" i zwraca jego pozycję
	iterator find(const T& x);

	// Wyszukuje element o wartości "x" i zwraca jego pozycję
	const_iterator find(const T& x) const;

	// Usuwa element wskazywany przez iterator "it" i zwraca iterator do kolejnego elementu
	iterator erase(iterator it);

	// Wstawia element "x" przed pozycję "it" i zwraca pozycję "x"
	template<class U>
	iterator insert(iterator it, U&& x);

	// Usuwa wystąpienia "x" i zwraca ich liczbę
	int remove(const T& x);

	// Zwraca liczbę elementów w liście
	int size() const;

	// Zwraca true gdy lista jest pusta
	bool empty() const;

	// Czyści listę
	void clear();

};

template<class T>
class List<T>::iterator {
protected:
	int m_index;
	const List* m_list;
	iterator() = default;
	iterator(List* list, int index);
public:
	friend List;
	T& operator*() const;
	iterator operator++();
	iterator operator--();
	bool operator==(const iterator& other) const;
	bool operator!=(const iterator& other) const;
};

template<class T>
class List<T>::const_iterator : public List<T>::iterator {
protected:
	const_iterator(const List* list, int index);
public:
	friend List;
	const T& operator*() const;
};

//-----------------------------------------------------------------------------

template<class T>
void List<T>::allocate() {
	std::cout << "-malloc" << std::endl;
	this->m_arr = (T*) std::malloc(sizeof(T) * this->m_capacity * 1000000);
	// this->m_arr = new T[this->m_capacity];
}

template<class T>
void List<T>::deallocate() {
	std::cout << "-free" << std::endl;
	std::free(this->m_arr);
	// delete this->m_arr;
}

//-----------------------------------------------------------------------------

template<class T>
List<T>::List()
	: m_size(0)
	, m_capacity(64)
	, m_arr(nullptr)
{
	std::cout << "-constructor" << std::endl;

	this->allocate();
}

template<class T>
List<T>::List(const List<T>& other)
	: m_size(0)
	, m_capacity(64)
	, m_arr(nullptr)
{
	std::cout << "-copy constructor" << std::endl;
   
	*this = other;
}

template<class T>
List<T>::List(List<T>&& other)
	: m_size(0)
	, m_capacity(64)
	, m_arr(nullptr)
{
	std::cout << "-move constructor" << std::endl;
   
	*this = std::move(other);
}

template<class T>
List<T>::~List() {
	std::cout << "-delete" << std::endl;

	this->clear();
	this->deallocate();
}

template<class T>
List<T>& List<T>::operator=(const List<T>& other) {
	this->m_capacity = other.m_capacity;
	this->m_size = other.m_size;
	this->allocate();

	for (auto el : other)
		this->push_back(el);

	return *this;
}

template<class T>
List<T>& List<T>::operator=(List<T>&& other) {
	this->clear();

	this->m_arr = other.m_arr;
	this->m_size = other.m_size;
	this->m_capacity = other.m_capacity;

	other.m_arr = nullptr;

	return *this;
}

template<class T>
template<class U>
void List<T>::push_front(U&& x) {
	auto it = this->begin();
	this->insert(it, std::forward<U>(x));
}

template<class T>
template<class U>
void List<T>::push_back(U&& x) {
	auto it = this->end();
	this->insert(it, std::forward<U>(x));
}

template<class T>
T List<T>::pop_front() {
	auto it = this->begin();
	T element = *it;
	this->erase(it);
	return element;
}

template<class T>
T List<T>::pop_back() {
	auto it = --this->end();
	T element = *it;
	this->erase(it);
	return element;
}

template<class T>
typename List<T>::const_iterator List<T>::begin() const {
	return List<T>::const_iterator(this, 0);
}

template<class T>
typename List<T>::iterator List<T>::begin() {
	return List<T>::iterator(this, 0);
}

template<class T>
typename List<T>::const_iterator List<T>::end() const {
	return List<T>::const_iterator(this, this->m_size);
}

template<class T>
typename List<T>::iterator List<T>::end() {
	return List<T>::iterator(this, this->m_size);
}

template<class T>
typename List<T>::iterator List<T>::find(const T& x) {
	for (auto it = this->begin(); it != this->end(); ++it) {
		if (*it == x)
			return it;
	}

	return this->end();
}

template<class T>
typename List<T>::const_iterator List<T>::find(const T& x) const {
	for (auto it = this->begin(); it != this->end(); ++it) {
		if (*it == x)
			return it;
	}

	return this->end();
}

template<class T>
typename List<T>::iterator List<T>::erase(List<T>::iterator it) {
	std::cout << "iterator: " << it.m_index << std::endl;

	int& index = it.m_index;
	T* ptr = &this->m_arr[index];

	(*it).~T();

	if (it != this->end())
		std::memmove(ptr, ptr + 1, sizeof(T) * (m_size - index));

	this->m_size--;
	return --it;
}

template<class T>
template<class U>
typename List<T>::iterator List<T>::insert(List<T>::iterator it, U&& x) {
	int& index = it.m_index;
	T* ptr = &this->m_arr[index];

	if (it != this->end())
		std::memmove(ptr + 1, ptr, sizeof(T) * (m_size - index));

	new (ptr) T(std::forward<U>(x));

	this->m_size++;
	return ++it;
}

template<class T>
int List<T>::remove(const T& x) {
	std::cout << "-remove" << std::endl;

	int n = 0;

	for (auto it = this->begin(); it != this->end(); ++it) {
		if (*it == x) {
			erase(it);
			n ++;
		}
	}
	
	return n;
}

template<class T>
int List<T>::size() const {
	return this->m_size;
}

template<class T>
bool List<T>::empty() const {
	return this->size() == 0;
}

template<class T>
void List<T>::clear() {
	assert(this->m_arr != nullptr);

	while (!this->empty())
		this->erase(this->end());

	assert(this->m_size == 0);
}

template<class T>
List<T>::iterator::iterator(List* list, int index) {
	this->m_list = list;
	this->m_index = index;
}

template<class T>
List<T>::const_iterator::const_iterator(const List* list, int index) {
	this->m_list = list;
	this->m_index = index;
}

template<class T>
T& List<T>::iterator::operator*() const {
	// if (...)
		// throw std::out_of_range("can't dereference out of range iterator");
	return this->m_list->m_arr[this->m_index];
}

template<class T>
const T& List<T>::const_iterator::operator*() const {
	return this->m_list->m_arr[this->m_index];
}

template<class T>
typename List<T>::iterator List<T>::iterator::operator++() {
	if (*this == this->m_list->end())
		return *this;

	this->m_index ++;
	return *this;
}

template<class T>
typename List<T>::iterator List<T>::iterator::operator--() {
	if (*this == this->m_list->begin())
		return *this;

	this->m_index --;
	return *this;
}

template<class T>
bool List<T>::iterator::operator==(const List<T>::iterator& other) const {
	return this->m_index == other.m_index;
}

template<class T>
bool List<T>::iterator::operator!=(const List<T>::iterator& other) const {
	return !(*this == other);
}
