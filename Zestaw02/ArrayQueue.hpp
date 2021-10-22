#include <stdexcept>
#include<cmath>

template<class T, int N>
class Queue {
private:
	T m_data[N];
	int m_head = 0;
	int m_tail = 0;
	int m_size = 0;
	const int m_capacity = N;

	template<class U>
	void enque(U&& item) {
		if (m_size == m_capacity)
			throw std::out_of_range("push on full queue");
		m_data[m_tail] = std::move(item);
		m_size ++;
		m_tail += (m_tail + 1) % m_capacity;
	}

public:

	void push(const T& item) {
		enque(item);
	}

	void push(T&& item) { 
		enque(std::move(item));
	}

	void pop() {
		if (m_size == 0)
			throw std::out_of_range("pop on empty queue");
		m_head += (m_head + 1) % m_capacity;
		m_size --;
	}

	T& top() {
		if (m_size == 0)
			throw std::out_of_range("top on empty queue");
		return m_data[m_head];
	}

	int size() {
		return m_size;
	}

	bool empty() {
		return m_size == 0 ? true : false;
	}

};
