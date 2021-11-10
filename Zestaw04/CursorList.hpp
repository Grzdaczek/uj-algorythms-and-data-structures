#include "iterator.hpp"

#include <stdexcept>
#include <cassert>

template<class T>
class CursorList {
private:
	class List;
	typedef typename CursorList<T>::List::m_Node m_Node;

	m_Node* m_data;
	List m_empty;
	int m_capacity;

public:
	#define __DEFAULT_SIZE 10
	CursorList()
		: m_data(new m_Node[__DEFAULT_SIZE])
		, m_empty(List(this))
		, m_capacity(__DEFAULT_SIZE)
	{
		for (int i = 0; i < m_capacity - 1; ++i)
			m_data[i].next = &m_data[i + 1];
		
		m_empty.m_head = &m_data[0];
		m_empty.m_tail = &m_data[m_capacity - 1];
	}

	List create() {
		return List(this);
	}

	// DEBUG
	List __emptyList() { return m_empty; }
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
	
	friend CursorList;
	CursorList* const m_parent;
	int m_size;
	m_Node* m_head;
	m_Node* m_tail;
	
public:
	typedef nsd::ConstIterator<m_Iterator, T> ConstIterator;
	typedef nsd::Iterator<m_Iterator, T> Iterator;

	List() = delete;

	List(CursorList* const parent)
		: m_parent(parent)
		, m_size(0)
		, m_head(nullptr)
		, m_tail(nullptr)
	{}

	constexpr Iterator begin() const {
		return ConstIterator(m_Iterator(m_head));
	}

	constexpr Iterator begin() {
		return Iterator(m_Iterator(m_head));
	}

	constexpr Iterator end() const {
		return ConstIterator(m_Iterator(nullptr));
	}

	constexpr Iterator end() {
		return Iterator(m_Iterator(nullptr));
	}

};