#include <stdexcept>

template<class T, int N>
class Stack {
public:
	~Stack() {
		while (this->_top != nullptr) {
			Node* n = this->_top;
			this->_top = this->_top->prev;
			delete n;
		}
	}

	void push(T item) {
		if (this->_size == this->_capacity) throw std::out_of_range("push on full stack");
		this->_top = new Node(this->_top, item);
		this->_size++;
	}

	T pop() {
		if (this->_top == nullptr) throw std::out_of_range("pop from empty stack");
		int item = this->_top->item;
		Node* n = this->_top;
		this->_top = this->_top->prev;
		this->_size--;
		delete n;
		return item;
	}

	T& top() {
		if (this->_top == nullptr) throw std::out_of_range("top on empty stack");
		return this->_top->item; 
	}

	int size() {
		return this->_size;
	}

	bool empty() {
		return this->_size == 0;
	}

private:
	class Node {
		public:
		Node(Node* p, T i): prev(p), item(i) {}
		Node* prev;
		T item;
	};

	unsigned int _size = 0;
	unsigned int _capacity = N;
	Node* _top = nullptr;

};
