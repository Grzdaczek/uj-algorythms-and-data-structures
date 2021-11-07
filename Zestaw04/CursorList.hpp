#include <stdexcept>
#include <cassert>

template<class T>
class List {
private:
	class Node;

public:
	class iterator;
	class const_iterator;
	List();
	List(const List<T>& other);
	List(List<T>&& other);
	~List();
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
class List<T>::Node {
protected:
	Node() = default;
	Node(const T& v) : value(v) {}
	Node(T&& v) : value(std::move(v)) {}
public:
	friend List;
	T value;
	Node next;
};

template<class T>
class List<T>::iterator {
protected:
	List* m_list;
	Node* m_ptr;
	iterator() = default;
	iterator(List* list, Node* ptr);
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
	const_iterator(const List* list, const Node* ptr);
public:
	friend List;
	const T& operator*() const;
};

//-----------------------------------------------------------------------------

template<class T>
List<T>::List() {
	// TODO: implement
}

template<class T>
List<T>::List(const List<T>& other) {
	// TODO: implement
}

template<class T>
List<T>::List(List<T>&& other) {
	// TODO: implement
}

template<class T>
List<T>::~List() {
	// TODO: implement
}

template<class T>
List<T>& List<T>::operator=(const List<T>& other) {
	// TODO: implement
}

template<class T>
List<T>& List<T>::operator=(List<T>&& other) {
	// TODO: implement
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
	// TODO: implement
}

template<class T>
typename List<T>::iterator List<T>::begin() {
	// TODO: implement
}

template<class T>
typename List<T>::const_iterator List<T>::end() const {
	// TODO: implement
}

template<class T>
typename List<T>::iterator List<T>::end() {
	// TODO: implement
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
	// TODO: implement
}

template<class T>
template<class U>
typename List<T>::iterator List<T>::insert(List<T>::iterator it, U&& x) {
	// TODO: implement
}

template<class T>
int List<T>::remove(const T& x) {
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
	// TODO: implement
}

template<class T>
List<T>::iterator::iterator(List* list, Node* ptr)
	: m_list(list)
	, m_ptr(ptr)
{}

template<class T>
List<T>::const_iterator::const_iterator(const List* list, const Node* ptr) {
	// TODO: implement
}

template<class T>
T& List<T>::iterator::operator*() const {
	// if (...)
	// 	throw std::out_of_range("can't dereference out of range iterator");

	// TODO: implement
}

template<class T>
const T& List<T>::const_iterator::operator*() const {
	// if (...)
	// 	throw std::out_of_range("can't dereference out of range iterator");

	// TODO: implement
}

template<class T>
typename List<T>::iterator List<T>::iterator::operator++() {
	// TODO: implement
}

template<class T>
typename List<T>::iterator List<T>::iterator::operator--() {
	// TODO: implement
}

template<class T>
bool List<T>::iterator::operator==(const List<T>::iterator& other) const {
	return this->m_ptr == other.m_ptr;
}

template<class T>
bool List<T>::iterator::operator!=(const List<T>::iterator& other) const {
	return !(*this == other);
}
