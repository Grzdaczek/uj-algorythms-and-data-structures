template<class T> // std::farward: TODO
class List {
private:
	struct Node {
		T item;
		Node* prev;
		Node* next;
	};

	Node m_guard;
	int m_size;

public:
	List () = default;
	List (const List<T>& other);
	List (List<T>&& other);
	List operator=(const List<T>& other);
	List operator=(List<T>&& other);

	struct iterator {
		Node* ptr;
		iterator operator*();
		iterator operator++();
		iterator operator--();
		bool operator==(const iterator& other);
		bool operator!=(const iterator& other);
	};

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
	int size();

	// Zwraca true gdy lista jest pusta
	bool empty();

	// Czyści listę
	void clear();

};

//-----------------------------------------------------------------------------

template<class T>
List<T>::List(const List<T>& other) {

}

template<class T>
List<T>::List(List<T>&& other) {

}

template<class T>
List<T> List<T>::operator=(const List<T>& other) {

}

template<class T>
List<T> List<T>::operator=(List<T>&& other) {

}

template<class T>
template<class U>
void List<T>::push_front(U&& x) {

}

template<class T>
template<class U>
void List<T>::push_back(U&& x) {

}

template<class T>
T List<T>::pop_front() {

}

template<class T>
T List<T>::pop_back() {

}

template<class T>
typename List<T>::iterator List<T>::begin() {
	List<T>::iterator it;
	it.ptr = this->m_guard.next;
	return it;
}

template<class T>
typename List<T>::iterator List<T>::end() {
	List<T>::iterator it;
	it.ptr = this->m_guard.prev;
	return it;
}

template<class T>
typename List<T>::iterator List<T>::find(const T& x) {

}

template<class T>
typename List<T>::iterator List<T>::erase(List<T>::iterator it) {

}

template<class T>
template<class U>
typename List<T>::iterator List<T>::insert(List<T>::iterator it, U&& x) {

}

template<class T>
int List<T>::remove(const T& x) {

}

template<class T>
typename List<T>::iterator List<T>::iterator::operator*() {

}

template<class T>
typename List<T>::iterator List<T>::iterator::operator++() {

}

template<class T>
typename List<T>::iterator List<T>::iterator::operator--() {

}

template<class T>
bool List<T>::iterator::operator==(const List<T>::iterator& other) {

}

template<class T>
bool List<T>::iterator::operator!=(const List<T>::iterator& other) {

}