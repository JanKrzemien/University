#include <iostream>

// TODO zrobić to na listach posortowanych, zrobić operacje union, intersection, difference rekurencyjnie

// L: 1 -> 2 -> 3
// M: 1 -> 2 -> 4
/**
  first: 1
  L: 2 -> 3
  M: 2 -> 4

  first: 2
  L: 3
  M: 4

  first: 3
  L: NULL
  M: 4

  first: 4
  L: NULL
  M: NULL

  first: NULL

  1 -> 2 -> 3 -> 4
*/

template<class T>
class Node {
    public:
    T data;
    Node * next;
    Node * prev;
    Node() {
        this->next = nullptr;
        this->prev = nullptr;
    }
    Node(T _data) {
        this->data = _data;
        this->next = nullptr;
        this->prev = nullptr;
    }
};

// lista wiązana dwukierunkowa
template<class T>
class List {
    public:
    Node<T> * tail;
    unsigned int count;

    void insert(T data) {
        Node<T> * n = new Node<T>(data);

        Node<T> * pp = tail;
        Node<T> * p = tail->next;
        while(p != nullptr && p->data < data) {
            pp = p;
            p = p->next;
        }

        if(p == nullptr) {
            n->next = nullptr;
            n->prev = pp;
            pp->next = n;
        } else {
            n->next = p;
            pp->next = n;
            n->prev = pp;
            pp->next = n;
        }

        count++;
    }

    Node<T> * search(T data) {
        Node<T> * p = tail->next;
        while(p != nullptr && p->data < data)
            p = p->next;
        
        if(p != nullptr && p->data == data) return p;
        return nullptr;
    }

    bool lookup(T data) {
        return search(data) != nullptr;
    }

    void remove(Node<T> * p) {
        if(p == nullptr || p == tail) return;

        if(p->next == nullptr) {
            p->prev->next = nullptr;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }

        delete p;

        count--;
    }

    void print() {
        Node<T> * p = tail->next;
        while(p != nullptr) {
            std::cout << p->data << " ";
            p = p->next;
        }
    }

    List() {
        tail = new Node<T>();
        count = 0;
    }
};

template <class T>
class Set {
    public:
    List<T> container{};

    void insert(T data) {
        if(!container.lookup(data))
            container.insert(data);
    }

    bool lookup(T data) {
        return container.lookup(data);
    }

    void remove(T data) {
        container.remove( container.search(data) );
    }

    void print() {
        container.print();
    }

    unsigned int length() {
        return container.count;
    }
};

template<class T>
class SetOperations {
    public:
    Node<T> * assemble(T data, Node<T> * LTail, Node<T> * MTail) {
        Node<T> * n = new Node<T>(data);
        n->next = setUnion(LTail, MTail);
        return n;
    }

    void link_back(Node<T> * tail, Node<T> * tailNext) {
        if(tailNext != nullptr) {
            tailNext->prev = tail;
            link_back(tailNext, tailNext->next);
        }
    }

    unsigned int count_list_elements(Node<T> * tail) {
        unsigned int count = 0;
        Node<T> * p = tail;
        while(p->next != nullptr) {
            p = p->next;
            count++;
        }

        return count;
    }

    Node<T> * setUnion(Node<T> * LTail, Node<T> * MTail) {
        if(LTail == nullptr && MTail == nullptr) {
            return nullptr;
        } else if (LTail == nullptr) {
            return assemble(MTail->data, nullptr, MTail->next);
        } else if (MTail == nullptr) {
            return assemble(LTail->data, nullptr, LTail->next);
        } else if (LTail->data == MTail->data) {
            return assemble(LTail->data, LTail->next, MTail->next);
        } else if (LTail->data < MTail->data) {
            return assemble(LTail->data, LTail->next, MTail);
        } else {
            return assemble(MTail->data, LTail, MTail->next);
        }
    }

    Set<T> Union(Set<T> s1, Set<T> s2) {
        Set<T> res{};

        Node<T> * tail = setUnion(s1.container.tail, s2.container.tail);

        link_back(tail, tail->next);
        res.container.tail = tail;
        res.container.count = count_list_elements(tail);

        return res;
    }

    Set<T> difference(Set<T> s1, Set<T> s2) {
        Set<T> res{};
        Node<T> * p = s1.container.tail->next;
        while(p != nullptr) {
            if(!s2.lookup(p->data)) {
                res.container.insert(p->data); // List<T>::insert
            }
            
            p = p->next;
        }

        return res;
    }

    Set<T> intersection(Set<T> s1, Set<T> s2) {
        Set<T> res{};

        Node<T> * p = s1.container.tail->next;
        while(p != nullptr) {
            if(s2.lookup(p->data)) {
                res.container.insert(p->data); // List<T>::insert
            }

            p = p->next;
        }

        return res;
    }
};

#define DATA_TYPE int

int main() {
    Set<DATA_TYPE> s1{};

    s1.insert(1);
    s1.insert(2);
    s1.insert(4);
    s1.print(); std::cout << std::endl;
    
    Set<DATA_TYPE> s2{};

    s2.insert(1);
    s2.insert(2);
    s2.insert(3);
    s2.print(); std::cout << std::endl;

    Set<DATA_TYPE> result;

    SetOperations<DATA_TYPE> op{};

    std::cout << "union: " << std::endl;
    result = op.Union(s1, s2);
    result.print(); std::cout << std::endl;

    std::cout << "intersection: " << std::endl;
    result = op.intersection(s1, s2);
    result.print(); std::cout << std::endl;

    std::cout << "difference s1 \\ s2: " << std::endl;
    result = op.difference(s1, s2);
    result.print(); std::cout << std::endl;
}