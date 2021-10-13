#include <stdexcept>

class Node {
public:
	Node(int item, Node* prevNode) {
		this->item = item;
		this->prevNode = prevNode;
	}	
	Node* prevNode = nullptr;
	int item;

};

class Stack {
public:
	Stack(int capacity) {
	   this->_capacity = capacity;
	}

	~Stack() {
		while (_top != nullptr) {
			Node* n = this->_top;
			_top = this->_top->prevNode;
			delete n;
		}
	}

	void push(int item) {
	   if (this->_size == this->_capacity) throw std::out_of_range("push on full stack");
		Node* n = new Node(item, this->_top);
		this->_top = n; 
		this->_size++;
	}

	int pop() {
		if (this->_top == nullptr) throw std::out_of_range("pop from empty stack");
		int item = this->_top->item;
		this->_top = this->_top->prevNode;
		this->_size--;
		return item;
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
	Node* _top = nullptr;

};
