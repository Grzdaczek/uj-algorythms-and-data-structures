#include <stdexcept>
#include <cstring>
#include <memory>
#include <cassert>

#include "iterator.hpp"

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

	struct m_ListIterator {
		const List* m_list;
		int m_index;

		m_ListIterator() = default;

		m_ListIterator(const List* list, int index)
			: m_list(list)
			, m_index(index)
		{}

		T& operator*() const {
			return this->m_list->m_arr[this->m_index];
		}

		m_ListIterator& operator++() {
			this->m_index ++;
			return *this;
		}

		m_ListIterator& operator--() {
			this->m_index --;
			return *this;
		}

		bool operator==(const m_ListIterator& other) const {
			return m_index == other.m_index;
		}
	};

public:
	typedef nsd::Iterator<m_ListIterator, T> iterator;
	typedef nsd::ConstIterator<m_ListIterator, T> const_iterator;

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

	// Uniwersalna referencja U&&, Wstawia element na pocz??tek listy
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

	// Usuwa element z pocz??tku listy i zwraca jego warto???? lub wyrzuca wyj??tek gdy lista jest pusta
	T pop_front() {
		auto it = this->begin();
		T element = *it;
		this->erase(it);
		return element;
	}

	// Usuwa element z ko??ca listy i zwraca jego warto???? lub wyrzuca wyj??tek gdy lista jest pusta
	T pop_back() {
		auto it = --this->end();
		T element = *it;
		this->erase(it);
		return element;
	}

	// Zwraca const_iterator wskazuj??cy na pierwszy element
	const_iterator begin() const {
		auto it = m_ListIterator(this, 0);
		return const_iterator(it);
	}

	// Zwraca iterator wskazuj??cy na pierwszy element
	iterator begin() {
		auto it = m_ListIterator(this, 0);
		return iterator(it);
	}

	// Zwraca const_iterator wskazuj??cy na ostatni element
	const_iterator end() const {
		auto it = m_ListIterator(this, this->m_size);
		return const_iterator(it);
	}

	// Zwraca iterator wskazuj??cy na ostatni element
	iterator end() {
		auto it = m_ListIterator(this, this->m_size);
		return iterator(it);
	}

	// Wyszukuje element o warto??ci "x" i zwraca jego pozycj??
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
		int index = it.unwrap().m_index;
		T* ptr = &this->m_arr[index];

		(*it).~T();

		if (it != this->end())
			std::memmove(ptr, ptr + 1, sizeof(T) * (m_size - index));

		this->m_size--;
		return --it;
	}

	// Wstawia element "x" przed pozycj?? "it" i zwraca pozycj?? "x"
	template<class U>
	iterator insert(iterator it, U&& x) {
		int index = it.unwrap().m_index;
		T* ptr = &this->m_arr[index];

		if (it != this->end())
			std::memmove(ptr + 1, ptr, sizeof(T) * (m_size - index));

		new (ptr) T(std::forward<U>(x));

		this->m_size++;
		return ++it;
	}

	// Usuwa wyst??pienia "x" i zwraca ich liczb??
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

	// Zwraca liczb?? element??w w li??cie
	int size() const {
		return this->m_size;
	}

	// Zwraca true gdy lista jest pusta
	bool empty() const {
		return this->size() == 0;
	}

	// Czy??ci list??
	void clear() {
		while (!this->empty())
			this->erase(--this->end());

		assert(this->m_size == 0);
	}

};
