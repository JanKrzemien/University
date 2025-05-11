typedef struct node Node;
struct node {
    int val;
    Node * left;
    Node * right;
    Node * parent;
};

class Splay {
    public:
    Node * root;
    void create() {
        root = nullptr;
    }
    void rotateLeft(Node * node) {
        Node * parent = node->parent;

        node->parent = parent->parent;
        if(node->parent != nullptr) {
            if(node->parent->right == parent)
                node->parent->right = node;
            else 
                node->parent->left = node;
        }
        parent->parent = node;

        Node * leftSubtree = node->left;
        node->left = parent;

        parent->right = leftSubtree;
        if(leftSubtree != nullptr)
            leftSubtree->parent = parent;
    }
    void rotateRight(Node * node) {
        Node * parent = node->parent;
        node->parent = parent->parent;
        if(node->parent != nullptr) {
            if(node->parent->right == parent)
                node->parent->right = node;
            else
                node->parent->left = node;
        }
        parent->parent = node;

        Node * rightSubtree = node->right;
        node->right = parent;
        
        parent->left = rightSubtree;
        if(rightSubtree != nullptr)
            rightSubtree->parent = parent;
    }
    void splay(Node * futureRoot) {
        // dopóki futureRoot ma rodzica nie dotarł jeszcze do korzenia drzewa
        while(futureRoot->parent != nullptr) {
            
            if (futureRoot->parent->left == futureRoot && futureRoot->parent->parent == nullptr) {
                // zig
                rotateRight(futureRoot);
            } else if (futureRoot->parent->right == futureRoot && futureRoot->parent->parent == nullptr) {
                // zag
                rotateLeft(futureRoot);
            } else if (futureRoot->parent->left == futureRoot && futureRoot->parent->parent->left == futureRoot->parent) {
                // zig zig
                rotateRight(futureRoot->parent);
                rotateRight(futureRoot);
            } else if (futureRoot->parent->right == futureRoot && futureRoot->parent->parent->right == futureRoot->parent) {
                // zag zag
                rotateLeft(futureRoot->parent);
                rotateLeft(futureRoot);
            } else if (futureRoot->parent->right == futureRoot && futureRoot->parent->parent->left == futureRoot->parent) {
                // zag zig
                rotateLeft(futureRoot);
                rotateRight(futureRoot);
            } else if (futureRoot->parent->left == futureRoot && futureRoot->parent->parent->right == futureRoot->parent) {
                // zig zag
                rotateRight(futureRoot);
                rotateLeft(futureRoot);
            }
        }
        root = futureRoot;
    }
    void insert(int x) {
        // normal BST insert
        Node * node = root;
        Node * parent = nullptr;
        while(node != nullptr) {
            parent = node;
            if(x <= node->val)
                node = node->left;
            else
                node = node->right;
        }
        Node * n = new Node;
        n->val = x;
        n->left = nullptr;
        n->right = nullptr;
        n->parent = parent;
        if(parent != nullptr) {
            if(x <= parent->val)
                parent->left = n;
            else
                parent->right = n;
        }

        // splay to bring node to root
        splay(n);
    }
    void search(int x) {
        // normal BST search
        Node * node = root;
        Node * parent = nullptr;
        while(node != nullptr) {
            parent = node;
            if (x < node->val)
                node = node->left;
            else if (x > node->val)
                node = node->right;
            else {
                // if node with value x is found bring it to root
                splay(node);
                return;
            }
        }
        // if node with value x is not in the tree bring to root node with closest value
        if (parent != nullptr)
            splay(parent);
    }
    void del(int x) {
        // there is nothing to search
        if(root == nullptr) return;

        // bring node with value x to the root
        search(x);

        // node with value x not found
        if (root->val != x)
            return;
        
        // node with value x found, normal BST remove root
        if (root->left == nullptr) {
            Node * node = root->right;
            delete root;
            if(node != nullptr) {
                node->parent = nullptr;
            }
            root = node;
            return;
        }
        if (root->right == nullptr) {
            Node * node = root->left;
            delete root;
            node->parent = nullptr;
            root = node;
            return;
        }
        Node * node = root->left;
        while(node->right != nullptr) node = node->right;

        if(node == root->left) {
            node->parent = nullptr;
            node->right = root->right;
            root->right->parent = node;
        } else {
            node->parent->right = node->left;
            if (node->left != nullptr)
                node->left->parent = node->parent;
            node->parent = nullptr;
            node->left = root->left;
            node->right = root->right;
            root->left->parent = node;
            root->right->parent = node;
        }

        delete root;
        root = node;
    }

};
