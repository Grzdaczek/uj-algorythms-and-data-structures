#include "iterator.hpp"

#include <stdexcept>
#include <cassert>

template<class T>
class CursorList {
public:
	class List;

private:
	class m_ValueNode {
	public:
		m_ValueNode* next;
		T value;
		m_ValueNode() :				next(nullptr), value(T()) {};
		m_ValueNode(const T& x) :	next(nullptr), value(x) {};
		m_ValueNode(T&& x) :		next(nullptr), value(std::move(x)) {};
	};

	class m_HollowNode {
	public:
		m_HollowNode* next;
		m_HollowNode() : next(nullptr) {};
	};

	union m_Node {
		m_HollowNode as_hollow;
		m_ValueNode as_value;
		m_Node() { as_hollow.next = nullptr; };
		~m_Node() {};
	};
	
	int m_capacity;
	int m_nsize;
	m_HollowNode* m_hollow;
	m_Node* m_data;

	m_ValueNode* m_alloc() {
		if (full())
			throw new std::out_of_range("can't alloc, list is full");

		m_Node* node = reinterpret_cast<m_Node*>(m_hollow);
		m_hollow = m_hollow->next;
		m_nsize--;

		// Different union members should have the same raw address
		assert((void*)node == (void*)&(node->as_value));
		assert((void*)node == (void*)&(node->as_hollow));

		return &node->as_value;
	}

	void m_free(m_ValueNode* node) {
		if (empty())
			throw new std::out_of_range("can't free, list is empty");

		m_HollowNode* new_hollow = new (node) m_HollowNode;
		new_hollow->next = m_hollow;
		m_hollow = new_hollow;
		m_nsize++;
	}

public:
	#define __DEFAULT_SIZE 1024
	CursorList()
		: m_capacity(__DEFAULT_SIZE)
		, m_nsize(m_capacity)
		, m_hollow(nullptr)
		, m_data(new m_Node[m_nsize])
	{
		for (int i = 0; i < m_nsize - 1; ++i)
			m_data[i].as_hollow.next = reinterpret_cast<m_HollowNode*>(&m_data[i+1]);

		m_hollow = &m_data[0].as_hollow;
	}

	~CursorList() {
		delete[] m_data;
	}

	List create() {
		return List(this);
	}

	int size() {
		return m_capacity - m_nsize;
	}

	bool empty() {
		return m_nsize == m_capacity;
	}

	bool full() {
		assert(m_nsize == 0 ? (m_hollow == nullptr) : true);
		return m_nsize == 0;
	}

#if !NDEBUG
	void __print_hollow() {
		m_HollowNode* n = m_hollow;
		std::cout << "[ ";
		while (n) {
			std::cout << __addr_to_index((m_Node*)n) << " ";
			n = n->next;
		}

		std::cout << "]" << std::endl;
	}

	void* __addr_to_index(void* ptr) {
		int a = reinterpret_cast<uint64_t>(ptr);
		int b = reinterpret_cast<uint64_t>(m_data);
		return (void*)((a-b) / sizeof(m_Node));
	}
#endif

};

template<class T>
class CursorList<T>::List {
private:
	class m_Iterator {
	private:
		m_ValueNode* m_nodeptr;

	public:
		friend CursorList;
		
		m_Iterator() = default;

		m_Iterator(m_ValueNode* nodeptr)
			: m_nodeptr(nodeptr)
		{}

		T& operator*() const {
			if (!m_nodeptr)
				throw new std::out_of_range("can't derefrence out of range iterator");
			return m_nodeptr->value;
		}

		m_Iterator& operator++() {
			if (m_nodeptr)
				m_nodeptr = m_nodeptr->next;

			return *this;
		}

		bool operator==(const m_Iterator& other) const {
			return m_nodeptr == other.m_nodeptr;
		}
	};

	CursorList* const m_parent;
	int m_size;
	m_ValueNode* m_head;
	m_ValueNode* m_tail;
	
public:
	friend CursorList;
	typedef nsd::ConstIterator<m_Iterator, T> ConstIterator;
	typedef nsd::Iterator<m_Iterator, T> Iterator;

	List() = delete;

	List(CursorList* const parent)
		: m_parent(parent)
		, m_size(0)
		, m_head(nullptr)
		, m_tail(nullptr)
	{}

	// Zwraca ConstIterator wskazujący na pierwszy element
	constexpr ConstIterator begin() const {
		return ConstIterator(m_Iterator(m_head));
	}

	// Zwraca Iterator wskazujący na pierwszy element
	constexpr Iterator begin() {
		return Iterator(m_Iterator(m_head));
	}

	// Zwraca ConstIterator wskazujący za ostatni element
	constexpr ConstIterator end() const {
		return ConstIterator(m_Iterator(nullptr));
	}

	// Zwraca Iterator wskazujący za ostatni element
	constexpr Iterator end() {
		return Iterator(m_Iterator(nullptr));
	}

	// Zwraca ConstIterator wskazujący na ostatni element
	constexpr ConstIterator last() const {
		return ConstIterator(m_Iterator(m_tail));
	}
	
	// Zwraca Iterator wskazujący na ostatni element
	constexpr Iterator last() {
		return Iterator(m_Iterator(m_tail));
	}

	// Wstawia element "x" przed pozycję "it" i zwraca pozycję "x"
	template<typename U>
	Iterator insert(Iterator it, U&& x) {
		m_ValueNode* nodeptr = new (m_parent->m_alloc()) m_ValueNode(std::forward<U>(x));

		if (m_size == 0) {
			m_head = nodeptr;
			m_tail = nodeptr;
		}
		else if (it == end()) {
			m_tail->next = nodeptr;
			m_tail = nodeptr;
		}
		else {
			m_ValueNode** indirect = &m_head;

			while (*indirect != it.unwrap().m_nodeptr)
				indirect = &(*indirect)->next;

			nodeptr->next = *indirect;
			*indirect = nodeptr;
		}

		m_size++;
		return Iterator(m_Iterator(nodeptr));
	}

	// Usuwa element wskazywany przez iterator "it" i zwraca iterator do kolejnego elementu
	Iterator erase(Iterator it) {
		m_ValueNode* nodeptr = it.unwrap().m_nodeptr;
		Iterator next = Iterator(m_Iterator(nodeptr->next));

		if (m_size == 1) {
			m_head = nullptr;
			m_tail = nullptr;
		}
		else {
			m_ValueNode** indirect = &m_head;

			while (*indirect != nodeptr)
				indirect = &(*indirect)->next;

			// HACK, works because address of m_ValueNode is the same as it's memeber "next"
			if (nodeptr == m_tail)
				m_tail = (m_ValueNode*)indirect;

			*indirect = nodeptr->next;
		}
		
		nodeptr->value.~T();
		m_parent->m_free(nodeptr);

		m_size--;
		return next;
	}

	// Uniwersalna referencja U&&, Wstawia element na początek listy
	template<class U>
	void push_front(U&& x) {
		auto it = begin();
		insert(it, std::forward<U>(x));
	}

	// Wstawia element na koniec listy
	template<class U>
	void push_back(U&& x) {
		auto it = end();
		insert(it, std::forward<U>(x));
	}

	// Usuwa element z początku listy i zwraca jego wartość lub wyrzuca wyjątek gdy lista jest pusta
	T pop_front() {
		auto it = begin();
		T element = *it;
		erase(it);
		return element;
	}

	// Usuwa element z końca listy i zwraca jego wartość lub wyrzuca wyjątek gdy lista jest pusta
	T pop_back() {
		auto it = last();
		T element = *it;
		erase(it);
		return element;
	}

	// Wyszukuje element o wartości "x" i zwraca jego pozycję
	Iterator find(const T& x) {
		for (auto it = begin(); it != end(); ++it) {
			if (*it == x)
				return it;
		}

		return end();
	}

	// Wyszukuje element o wartości "x" i zwraca jego pozycję
	ConstIterator find(const T& x) const {
		for (auto it = begin(); it != end(); ++it) {
			if (*it == x)
				return it;
		}

		return end();
	}

	// Usuwa wystąpienia "x" i zwraca ich liczbę
	int remove(const T& x) {
		if (empty())
			return 0;

		int n = 0;
		auto it = begin();
		while (it != end()) {
			if (*it == x) {
				it = erase(it);
				++n;
			}
			else {
				++it;
			}
		}

		return n;
	}

	int size() {
		return m_size;
	}

	bool empty() {
		return m_size == 0;
	}

	bool full() {
		return m_parent->full();
	}

#if !NDEBUG
	void __print() {
		std::cout << "[ ";
		for (const auto& n : *this)
			std::cout << n << " ";

		std::cout << "]" << std::endl;
	}
#endif

};