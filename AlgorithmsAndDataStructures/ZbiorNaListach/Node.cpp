template<class T>
class Node {
    public:
    T data;
    Node * next;
    Node * prev;
    Node() {
        next = nullptr;
    }
    Node(T _data) {
        this.data = _data;
        this.next = nullptr;
        this.prev = nullptr;
    }
};
