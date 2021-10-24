#include <stdexcept>

template<class T, size_t N>
class Queue {
private:
	T m_data[N];
	size_t m_head = 0;
	size_t m_tail = 0;
	size_t m_size = 0;

	template<class U>
	void enque(U&& item) {
		m_data[m_tail] = std::move(item);
		m_size ++;	
		m_tail = modulo_increment(m_tail);
	}

	void dequeue() {
		m_head = modulo_increment(m_head);
		m_size --;
	}

	size_t modulo_increment(size_t x) {
		if constexpr ((N & (N-1)) == 0) // check if N is power of 2
			return (x+1) & (N-1); // do some bit manipulation, as it is faster that way
		else
			return (x+1) % N; // resort to modulo division
	}

public:
	void push(const T& item) {
		if (m_size == N)
			throw std::out_of_range("push called on full queue");
		enque(item);
	}

	void push(T&& item) {
		if (m_size == N)
			throw std::out_of_range("push called on full queue");
		enque(std::move(item));
	}

	void pop() {
		if (m_size == 0)
			throw std::out_of_range("pop called on empty queue");
		dequeue();
	}

	T& top() {
		if (m_size == 0)
			throw std::out_of_range("top called on empty queue");
		return m_data[m_head];
	}

	const T& top() const {
		if (m_size == 0)
			throw std::out_of_range("top called on empty queue");
		return m_data[m_head];
	}

	size_t size() const {
		return m_size;
	}

	bool empty() const {
		return m_size == 0;
	}

};
