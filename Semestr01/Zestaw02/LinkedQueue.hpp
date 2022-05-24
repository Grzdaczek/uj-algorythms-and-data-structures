#include <stdexcept>

template<class T, size_t N>
class Queue {
private:
	struct Node {
		Node* next;
		T item;
	};

	size_t m_size = 0;
	// unsigned int m_capacity = N;
	Node* m_head = nullptr;
	Node* m_tail = nullptr;

	template<class U>
	void enqueue(U&& item) {
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

	void dequeue() {
		Node* new_head = m_head->next;
		delete m_head;
		m_head = new_head;
		m_size --;
	}

public:
	~Queue() {
		while (m_size != 0) dequeue();
	}

	void push(const T& item) {
		// if (m_size == m_capacity)
			// throw std::out_of_range("push on full queue");
		enqueue(item);
	}

	void push(T&& item) {
		// if (m_size == m_capacity)
			// throw std::out_of_range("push on full queue");
		enqueue(std::move(item));
	}

	void pop() {
		if (m_size == 0)
			throw std::out_of_range("pop called on empty queue");
		dequeue();
	}

	T& top() {
		if (m_size == 0)
			throw std::out_of_range("top called on empty queue");
		return m_head->item;
	}

	const T& top() const {
		if (m_size == 0)
			throw std::out_of_range("top called on empty queue");
		return m_head->item;
	}

	size_t size() const {
		return m_size;
	}

	bool empty() const {
		return m_size == 0;
	}

};