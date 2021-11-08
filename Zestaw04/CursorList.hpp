#include <stdexcept>
#include <cassert>

template<class T>
class List {
private:
	int m_size;
	int m_capacity;

public:

	class iterator {
	protected:
		int m_ptr;
		const List* m_list;
		iterator() = default;
		
		iterator(List* list, int ptr) {
			this->m_list = list;
			this->m_ptr = ptr;
		}

	public:
		friend List;
	
		T& operator*() const {
			// if (...)
			// 	throw std::out_of_range("can't dereference out of range iterator");
			// TODO: implement
		}

		iterator operator++() {
			// TODO: implement
		}

		iterator operator--() {
			// TODO: implement
		}

		bool operator==(const List<T>::iterator& other) const {
			return this->m_ptr == other.m_ptr;
		}

		bool operator!=(const List<T>::iterator& other) const {
			return !(*this == other);
		}
	};

	class const_iterator : public iterator {
	protected:
		const_iterator(const List* list, int index) {
			// TODO: implement
		}

	public:
		friend List;
		
		const T& operator*() const {
			// if (...)
			// 	throw std::out_of_range("can't dereference out of range iterator");
			// TODO: implement
		}
	};

	List() {
		// TODO: implement
	}

	List(const List<T>& other) {
		// TODO: implement
	}

	List(List<T>&& other) {
		// TODO: implement
	}

	~List() {
		// TODO: implement
	}

	List<T>& operator=(const List<T>& other) {
		// TODO: implement
	}

	List<T>& operator=(List<T>&& other) {
		// TODO: implement
	}

	// Uniwersalna referencja U&&, Wstawia element na początek listy
	template<class U>
	void push_front(U&& x) {
		auto it = this->begin();
		this->insert(it, std::forward<U>(x));
	}

	// Wstawia element na koniec listy
	template<class U>
	void push_back(U&& x) {
		auto it = this->end();
		this->insert(it, std::forward<U>(x));
	}

	// Usuwa element z początku listy i zwraca jego wartość lub wyrzuca wyjątek gdy lista jest pusta
	T pop_front() {
		auto it = this->begin();
		T element = *it;
		this->erase(it);
		return element;
	}

	// Usuwa element z końca listy i zwraca jego wartość lub wyrzuca wyjątek gdy lista jest pusta
	T pop_back() {
		auto it = --this->end();
		T element = *it;
		this->erase(it);
		return element;
	}

	// Zwraca const_iterator wskazujący na pierwszy element
	const_iterator begin() const {
		// TODO: implement
	}

	// Zwraca iterator wskazujący na pierwszy element
	iterator begin() {
		// TODO: implement
	}

	// Zwraca const_iterator wskazujący na ostatni element
	const_iterator end() const {
		// TODO: implement
	}

	// Zwraca iterator wskazujący na ostatni element
	iterator end() {
		// TODO: implement
	}

	// Wyszukuje element o wartości "x" i zwraca jego pozycję
	iterator find(const T& x) {
		for (auto it = this->begin(); it != this->end(); ++it) {
			if (*it == x)
				return it;
		}

		return this->end();
	}

	const_iterator find(const T& x) const {
		for (auto it = this->begin(); it != this->end(); ++it) {
			if (*it == x)
				return it;
		}

		return this->end();
	}

	// Usuwa element wskazywany przez iterator "it" i zwraca iterator do kolejnego elementu
	iterator erase(iterator it) {
		// TODO: implement
	}

	// Wstawia element "x" przed pozycję "it" i zwraca pozycję "x"
	template<class U>
	iterator insert(iterator it, U&& x) {
		// TODO: implement
	}

	// Usuwa wystąpienia "x" i zwraca ich liczbę
	int remove(const T& x) {
		// TODO: implement
	}

	// Zwraca liczbę elementów w liście
	int size() const {
		return this->m_size;
	}

	// Zwraca true gdy lista jest pusta
	bool empty() const {
		return this->size() == 0;
	}

	// Czyści listę
	void clear() {
		// TODO: implement
		// assert(this->m_size == 0);
	}

};
