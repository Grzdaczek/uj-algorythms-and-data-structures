#include "iterator.hpp"

#include <stdexcept>
#include <cassert>

template<class T>
class CursorList {
public:
	class List;

private:
	typedef typename CursorList<T>::List::m_Node m_Node;
	m_Node* m_data;
	List m_empty;
	int m_capacity;

	m_Node* m_alloc() {
		// TODO: check for free space
		m_Node* ptr = m_empty.m_head;
		m_empty.m_head = m_empty.m_head->next;

		// TODO: fix memmory leak, m_empty node value never gets destroyed
		return ptr;
	}

	void m_free(m_Node* node) {

	}

public:
	#define __DEFAULT_SIZE 10
	CursorList()
		: m_data(new m_Node[__DEFAULT_SIZE])
		, m_empty(List(this))
		, m_capacity(__DEFAULT_SIZE)
	{
		for (int i = 0; i < m_capacity - 1; ++i)
			m_data[i].next = &m_data[i + 1];
		
		for (int i = 0; i < m_capacity; ++i)
			m_data[i].value = i;

		m_empty.m_head = &m_data[0];
		m_empty.m_tail = &m_data[m_capacity - 1];
	}

	List create() {
		return List(this);
	}

#if !NDEBUG
	List __emptyList() { return m_empty; }
#endif

};

template<class T>
class CursorList<T>::List {
private:
	class m_Node {
	public:
		T value;
		m_Node* next;
		m_Node() : value(T()), next(nullptr) {};
		m_Node(const T& x) : value(x), next(nullptr) {};
		m_Node(T&& x) : value(std::move(x)), next(nullptr) {};
	};

	class m_Iterator {
	private:
		m_Node* m_nodeptr;

	public:
		friend CursorList;
		
		m_Iterator() = default;

		m_Iterator(m_Node* nodeptr)
			: m_nodeptr(nodeptr)
		{}

		T& operator*() const {
			return m_nodeptr->value;
		}

		m_Iterator& operator++() {
			this->m_nodeptr = this->m_nodeptr->next;
			return *this;
		}

		bool operator==(const m_Iterator& other) const {
			return m_nodeptr == other.m_nodeptr;
		}
	};
	
	CursorList* const m_parent;
	int m_size;
	m_Node* m_head;
	m_Node* m_tail;
	
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

	constexpr ConstIterator begin() const {
		return ConstIterator(m_Iterator(m_head));
	}

	constexpr Iterator begin() {
		return Iterator(m_Iterator(m_head));
	}

	constexpr ConstIterator end() const {
		return ConstIterator(m_Iterator(nullptr));
	}

	constexpr Iterator end() {
		return Iterator(m_Iterator(nullptr));
	}

	constexpr ConstIterator last() const {
		return ConstIterator(m_Iterator(m_tail));
	}
	
	constexpr Iterator last() {
		return Iterator(m_Iterator(m_tail));
	}

	template<typename U>
	Iterator insert(Iterator it, U&& x) {
		std::cout << "-insert" << std::endl;

		m_Node* nodeptr = new (m_parent->m_alloc()) m_Node(std::forward<U>(x));
		
		if (!m_size) {
			// When list is empty, these should be nullptr
			assert(m_head == nullptr);
			assert(m_tail == nullptr);
			
			m_head = nodeptr;
			m_tail = nodeptr;
		}
		else {
			// When list is NOT empty, these CAN'T be nullptr
			assert(m_head != nullptr);
			assert(m_tail != nullptr);

			if (it == end()) {
				m_tail->next = nodeptr;
			}
			else if (it == begin()) {
				nodeptr->next = m_head;
				m_head = nodeptr;
			}
			else {
				// Worst case; the previous element must be found
				auto prev = begin();
				while (	prev.unwrap().m_nodeptr && 
						prev.unwrap().m_nodeptr->next == it.unwrap().m_nodeptr)
				{
					++prev;
				}

				m_Node* prevptr = it.unwrap().m_nodeptr;
				nodeptr->next = prevptr->next;
				prevptr->next = nodeptr;
			}
		}

		m_size++;
		return Iterator(m_Iterator(nodeptr));
	}

	Iterator erase(Iterator it) {
		
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