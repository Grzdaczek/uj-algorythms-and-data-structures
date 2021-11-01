// std::farward: TODO
#include "AbstractList.hpp"

template<class T>
class List : public AbstractList<T> {
private:
    struct Node {
        T item;
        Node* prev;
        Node* next;
    };

    struct Iterator {
        Node* ptr;
        Iterator operator*();
        Iterator operator++();
        Iterator operator--();
        Iterator operator==(Iterator& other);
        Iterator operator!=(Iterator& other);
    };

    Node m_guard;
    int m_size;

public:
    List ();
    List (const List<T>& other);
    List (List<T>&& other);
    List operator=(const List<T>& other);
    List operator=(List<T>&& other);

    template<class U>
    void push_front(U&& item);
    T pop_front();
};

template<class T>
List<T>::List() {
    m_guard.next = nullptr;
    m_guard.prev = nullptr;
    m_size = 0;
}
