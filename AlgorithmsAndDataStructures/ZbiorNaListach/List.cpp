#include "Node.cpp"

// lista wiązana dwukierunkowa

template<class T>
class List {
    public:
    Node<T> * tail;

    void insert(T data) {
        Node<T> n{data};
        n.next = tail->next;
        n.prev = tail;
        tail->next = n;
    }

    Node<T> * search(T data) {
        Node<T> * p = tail->next;
        while(p != nullptr && p->data != data)
            p = p->next;
        return p;
    }

    List() {
        tail = new Node<T>();
    }
};