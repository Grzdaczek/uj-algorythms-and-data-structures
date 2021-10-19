#include <stdexcept>

template<class T, int N>
class Stack {
public:
	Stack() {
	   this->_data = new int[N];
	}

	~Stack() {
		delete this->_data;
	}

    template<class U>
	void push(U&& item) {
	   if (this->_size == this->_capacity) throw std::out_of_range("push on full stack");
	   this->_data[++this->_size] = item;
	}

	T pop() {
		if (this->_size == 0) throw std::out_of_range("pop from empty stack");
		return this->_data[this->_size--];
	}

    T& top() {
        return this->size == 0 ? &this->_data[this->_size] : nullptr;
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
	int* _data;

};
