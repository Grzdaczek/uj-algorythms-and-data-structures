#include <stdexcept>

template<class T, int N>
class Stack {
public:
	Stack() {
		this->_data = new T[N];
	}

	~Stack() {
		delete this->_data;
	}

	void push(T item) {
		if (this->_size == this->_capacity) throw std::out_of_range("push on full stack");
		this->_data[++this->_size] = item;
	}

	T pop() {
		if (this->_size == 0) throw std::out_of_range("pop from empty stack");
		return this->_data[this->_size--];
	}

	T& top() {
		if (this->_size == 0) throw std::out_of_range("top on epmpy stack");
		return this->_data[this->_size];
	}


	int size() {
		return this->_size;
	}

	bool empty() {
		return this->_size == 0;
	}

private:
	unsigned int _size = 0;
	unsigned int _capacity = N;
	T* _data;

};
