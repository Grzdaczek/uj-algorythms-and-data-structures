#include <stdexcept>
#include<cmath>

template<class T, int N>
class Queue {
private:
	struct Node {
		Node* next;
		T item;
	};

	unsigned int m_size = 0;
	// unsigned int m_capacity = N;
	Node* m_head = nullptr;
	Node* m_tail = nullptr;

	template<class U>
	void enque(U&& item) {
		// if (m_size == m_capacity)
			// throw std::out_of_range("push on full queue");
		Node* new_node = new Node();
		new_node->item = std::move(item);
		new_node->next = nullptr;

		if (m_size == 0)
			m_head = new_node;
		else
			m_tail->next = new_node;

		m_tail = new_node;
		m_size ++;
	}

public:
	~Queue() {
		while (m_size != 0) pop();
	}

	void push(const T& item) {
		enque(item);
	}

	void push(T&& item) { 
		enque(std::move(item));
	}

	void pop() {
		if (m_size == 0)
			throw std::out_of_range("pop on empty queue");
		Node* new_head = m_head->next;
		delete m_head;
		m_head = new_head;
		m_size --;
	}

	T& top() {
		if (m_size == 0)
			throw std::out_of_range("top on empty queue");
		return m_head->item;
	}

	int size() {
		return m_size;
	}

	bool empty() {
		return m_size == 0 ? true : false;
	}

};