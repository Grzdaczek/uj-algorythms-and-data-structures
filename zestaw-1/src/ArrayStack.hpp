#include <stdexcept>

// capacity może być przekazywane jako parametr w template

class Stack {

    public:

    Stack(int capacity) {
       this->_data = new int[capacity];
       this->_size = -1;
       this->_capacity = capacity;
    }

    ~Stack() {
        delete this->_data;
    }

    void push(int item) {
       if (this->_size == this->_capacity) throw std::out_of_range("stack is full");
       this->_data[++this->_size] = item;
    }

    int pop() {
        if (this->_size == -1) throw std::out_of_range("stack is empty");
        return this->_data[this->_size--];
    }

    int size() {
        return this->_size;
    }

    bool empty() {
        return this->_size == -1;
    }

    private:
    
    int _size;
    int _capacity;
    int* _data;

};
