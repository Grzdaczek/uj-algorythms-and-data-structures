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

		m_HollowNode* new_hollow = reinterpret_cast<m_HollowNode*>(node);
		new_hollow->next = m_hollow;
		m_hollow = new_hollow;
	}

public:
	#define __DEFAULT_SIZE 10
	CursorList()
		: m_capacity(__DEFAULT_SIZE)
		, m_nsize(m_capacity)
		, m_hollow(nullptr)
		, m_data(reinterpret_cast<m_Node*>(new m_HollowNode[m_nsize]))
	{
		for (int i = 0; i < m_nsize - 1; ++i)
			m_data[i].as_hollow.next = reinterpret_cast<m_HollowNode*>(&m_data[i+1]);

		m_hollow = &m_data[0].as_hollow;
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

		m_ValueNode* nodeptr = new (m_parent->m_alloc()) m_ValueNode(std::forward<U>(x));
		
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

				m_ValueNode* prevptr = it.unwrap().m_nodeptr;
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
			std::cout << n.m_value << " ";

		std::cout << "]" << std::endl;
	}
#endif

};