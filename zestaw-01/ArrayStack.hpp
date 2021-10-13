#include <stdexcept>

// capacity może być przekazywane jako parametr w template
class Stack {
public:
	Stack(int capacity) {
	   this->_data = new int[capacity];
	   this->_capacity = capacity;
	}

	~Stack() {
		delete this->_data;
	}

	void push(int item) {
	   if (this->_size == this->_capacity) throw std::out_of_range("push on full stack");
	   this->_data[++this->_size] = item;
	}

	int pop() {
		if (this->_size == 0) throw std::out_of_range("pop from empty stack");
		return this->_data[this->_size--];
	}

	int size() {
		return this->_size;
	}

	bool empty() {
		return this->_size == 0;
	}

private:
	unsigned int _size = 0;
	unsigned int _capacity;
	int* _data;

};
