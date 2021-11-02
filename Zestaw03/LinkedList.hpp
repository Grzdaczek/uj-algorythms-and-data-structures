#include <stdexcept>

template<class T> // std::farward: TODO
class List {
private:
	class Node {
	public:
		T value;
		Node* prev;
		Node* next;
	};

	Node m_guard;
	int m_size = 0;

public:
	List ();
	List (const List<T>& other);
	List (List<T>&& other);
	~List ();

	class iterator {
	private:
		Node* m_guard;
		Node* m_ptr;
		iterator() = delete;
		iterator(List* list, Node* m_ptr) : m_guard(&list->m_guard), m_ptr(m_ptr) {};
	public:
		friend List;
		T& operator*() const;
		iterator operator++();
		iterator operator--();
		bool operator==(const iterator& other) const;
		bool operator!=(const iterator& other) const;
	};

	List operator=(const List<T>& other);

	List operator=(List<T>&& other);

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

	// Zwraca iterator wskazujący na ostatni element
	iterator end();

	// Wyszukuje element o wartości "x" i zwraca jego pozycję
	iterator find(const T& x);

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

//-----------------------------------------------------------------------------

template<class T>
List<T>::List() {
	this->m_guard.next = &this->m_guard;
	this->m_guard.prev = &this->m_guard;
}

template<class T>
List<T>::List(const List<T>& other) {
	*this = other;
}

template<class T>
List<T>::List(List<T>&& other) {
	*this = std::move(other);
}

template<class T>
List<T>::~List() {
	this->clear();
}

template<class T>
List<T> List<T>::operator=(const List<T>& other) {
	if (&other == this)
		return *this;

	this->clear();
	for(const auto& value : other)
		this->push_back(value);

	return *this;
}

template<class T>
List<T> List<T>::operator=(List<T>&& other) {
	if (&other == this)
		return *this;

	this->clear();
	this->m_size = other.m_size;
	this->m_guard = other.m_guard;

	other.m_size = 0;
	other.m_guard.next = nullptr;
	other.m_guard.prev = nullptr;

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
typename List<T>::iterator List<T>::begin() {
	return List<T>::iterator(this, this->m_guard.next);
}

template<class T>
typename List<T>::iterator List<T>::end() {
	return List<T>::iterator(this, &this->m_guard);
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
typename List<T>::iterator List<T>::erase(List<T>::iterator it) {
	if (it.m_ptr == it.m_guard)
		return it;
	
	auto n = it.m_ptr;
	n->next->prev = n->prev;
	n->prev->next = n->next;
	this->m_size --;

	delete n;
	++it;
	return it;
}

template<class T>
template<class U>
typename List<T>::iterator List<T>::insert(List<T>::iterator it, U&& x) {
	auto n = new List<T>::Node();
	n->value = x;
	n->next = it.m_ptr;
	n->prev = it.m_ptr->prev;

	n->next->prev = n;
	n->prev->next = n;
	this->m_size ++;

	return it;
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
	for (auto it = this->begin(); it != this->end(); ++it) {
		erase(it);
	}
}

template<class T>
T& List<T>::iterator::operator*() const {
	if (this->m_guard == this->m_ptr)
		throw std::out_of_range("can't dereference out of range iterator");

	return this->m_ptr->value;
}

template<class T>
typename List<T>::iterator List<T>::iterator::operator++() {
	if (this->m_ptr == this->m_guard)
		return *this;

	this->m_ptr = this->m_ptr->next;
	return *this;
}

template<class T>
typename List<T>::iterator List<T>::iterator::operator--() {
	if (this->m_ptr == this->m_guard->next)
		return *this;

	this->m_ptr = this->m_ptr->prev;
	return *this;
}

template<class T>
bool List<T>::iterator::operator==(const List<T>::iterator& other) const {
	return this->m_ptr == other.m_ptr;
}

template<class T>
bool List<T>::iterator::operator!=(const List<T>::iterator& other) const {
	return !(*this == other);
}