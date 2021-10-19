#include <stdexcept>

/*
template<class T>
class Node {
public:
	Node(T, Node* prevNode) {
		this->item = item;
		this->prevNode = prevNode;
	}	
	Node* prevNode = nullptr;
	T&& item;

};
*/

template<class T, int N>
class Stack {
public:
	~Stack() {
		while (_top != nullptr) {
			Node* n = this->_top;
			_top = this->_top->prev;
			delete n;
		}
	}

    template<class U>
	void push(U&& item) {
	   if (this->_size == this->_capacity) throw std::out_of_range("push on full stack");
		Node* n = new Node(this->_top, item);
		this->_top = n; 
		this->_size++;
	}

	T pop() {
		if (this->_top == nullptr) throw std::out_of_range("pop from empty stack");
		int item = this->_top->item;
		this->_top = this->_top->prev;
		this->_size--;
		return item;
	}

    T& top() {
       return &(this->_top->item); 
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
        Node(Node* p, T& i): item(i), prev(p) {}
        Node* prev = nullptr;
        T& item;
    };

	unsigned int _size = 0;
	unsigned int _capacity = N;
	Node* _top = nullptr;

};
