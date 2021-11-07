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

	void m_alloc() {
		this->m_arr = (T*) std::malloc(sizeof(T) * this->m_capacity);
	}

	void m_free() {
		std::free(this->m_arr);
	}

public:

	class iterator {
	protected:
		int m_index;
		const List* m_list;
		iterator() = default;
		
		iterator(List* list, int index) {
			this->m_list = list;
			this->m_index = index;
		}

	public:
		friend List;
	
		T& operator*() const {
			if (this->m_index < 0 || this->m_index >= this->m_list->m_size)
				throw std::out_of_range("can't dereference out of range iterator");

			return this->m_list->m_arr[this->m_index];
		}

		iterator operator++() {
			if (this->m_index >= this->m_list->m_size)
				return this->m_list->end();

			this->m_index ++;
			return *this;
		}

		iterator operator--() {
			if (this->m_index <= 0)
				return this->m_list->begin();

			this->m_index --;
			return *this;
		}

		bool operator==(const List<T>::iterator& other) const {
			return this->m_index == other.m_index;
		}

		bool operator!=(const List<T>::iterator& other) const {
			return !(*this == other);
		}
	};

	class const_iterator : public iterator {
	protected:
		const_iterator(const List* list, int index) {
			this->m_list = list;
			this->m_index = index;
		}

	public:
		friend List;
		
		const T& operator*() const {
			if (this->m_index < 0 || this->m_index >= this->m_list->m_size)
				throw std::out_of_range("can't dereference out of range iterator");

			return this->m_list->m_arr[this->m_index];
		}
	};

	List()
		: m_size(0)
		, m_capacity(1024)
	{
		this->m_alloc();
	}

	List(const List<T>& other)
		: m_size(0)
		, m_capacity(other.m_capacity)
	{
		this->m_alloc();
		
		for (const auto& el : other)
			this->push_back(el);
	}

	List(List<T>&& other)
		: m_size(other.m_size)
		, m_capacity(other.m_capacity)
		, m_arr(other.m_arr)
	{
		other.m_arr = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;
	}

	~List() {
		if (this->m_arr == nullptr)
			return;

		this->clear();
		this->m_free();
	}

	List<T>& operator=(const List<T>& other) {
		this->clear();

		if (this->m_capacity != other.m_capacity) {
			this->m_free();
			this->m_capacity == other.m_capacity;
			this->m_alloc();
		}

		for (const auto& el : other)
			this->push_back(el);

		return *this;
	}

	List<T>& operator=(List<T>&& other) {
		this->m_free();
		this->clear();

		this->m_arr = other.m_arr;
		this->m_size = other.m_size;
		this->m_capacity = other.m_capacity;

		other.m_arr = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;

		return *this;
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
		return const_iterator(this, 0);
	}

	// Zwraca iterator wskazujący na pierwszy element
	iterator begin() {
		return iterator(this, 0);
	}

	// Zwraca const_iterator wskazujący na ostatni element
	const_iterator end() const {
		return const_iterator(this, this->m_size);
	}

	// Zwraca iterator wskazujący na ostatni element
	iterator end() {
		return iterator(this, this->m_size);
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
		int& index = it.m_index;
		T* ptr = &this->m_arr[index];

		(*it).~T();

		if (it != this->end())
			std::memmove(ptr, ptr + 1, sizeof(T) * (m_size - index));

		this->m_size--;
		return --it;
	}

	// Wstawia element "x" przed pozycję "it" i zwraca pozycję "x"
	template<class U>
	iterator insert(iterator it, U&& x) {
		int& index = it.m_index;
		T* ptr = &this->m_arr[index];

		if (it != this->end())
			std::memmove(ptr + 1, ptr, sizeof(T) * (m_size - index));

		new (ptr) T(std::forward<U>(x));

		this->m_size++;
		return ++it;
	}

	// Usuwa wystąpienia "x" i zwraca ich liczbę
	int remove(const T& x) {
		if (this->empty())
			return 0;

		int n = 0;
		auto it = this->end();
		do {
			--it;
			if (*it == x) {
				erase(it);
				n++;
			}
		} while (it != this->begin());

		return n;
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
		while (!this->empty())
			this->erase(--this->end());

		assert(this->m_size == 0);
	}

};
