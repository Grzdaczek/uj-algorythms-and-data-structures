#include <stdexcept>
#include<cmath>

template<class T, int N>
class Queue {
private:
	T _data[N];
	int _head = 0;
	int _tail = 0;
	int _size = 0;
	const int _capacity = N;

public:
	template<class U>
	void push(U&& item) {
		if (this->_size == this->_capacity)
			throw std::out_of_range("push on full queue");
		this->_data[this->_tail] = item;
		this->_size++;
		this->_tail++;
	}

	T pop() {
		if (this->_size == 0)
			throw std::out_of_range("pop on empty queue");
		T item = this->_data[this->_head];
		this->_head++;
		this->_size--;
		return item;
	}

	T& top() {
		if (this->_size == 0)
			throw std::out_of_range("top on empty queue");
		return this->_data[this->_head];
	}

	int size() {
		return this->_size;
	}

	bool empty() {
		return this->_size == 0 ? true : false;
	}

};
