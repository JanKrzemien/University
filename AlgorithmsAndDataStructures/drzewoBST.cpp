typedef struct node Node;
struct node {
    int val;
    Node * leftSubtree;
    Node * rightSubtree;
};

class BSTTree {
    public:
    Node * root;

    void create_BST() {
        root = nullptr;
    }
    void insert_to_BST(int x) {
        // stworzenie liścia
        Node * n = new Node;
        n->val = x;
        n->leftSubtree = nullptr;
        n->rightSubtree = nullptr;

        // jeśli w drzewie nie ma elementów korzeń == liść
        if (root == nullptr)
        {
            root = n;
            return;
        }

        // jeśli w drzewie są elementy
        // porównaj x z wartością węzła: jeśli x <= przejdź na lewo
        // w przeciwnym razie przejdź na prawo
        // gdy nie możesz przejść dalej wstaw tam liść i zakończ pętlę
        Node * p = root;
        while(true) {
            if (x <= p->val)
            {
                if (p->leftSubtree != nullptr)
                {
                    p = p->leftSubtree;
                } else {
                    p->leftSubtree = n;
                    break;
                }
            } else {
                if (p->rightSubtree != nullptr) 
                {
                    p = p->rightSubtree;
                } else {
                    p->rightSubtree = n;
                    break;
                }
            }
        }
    }

    Node * search_BST(int x) {
        // jeśli drzewo jest puste zwróć null
        if(root == nullptr) {
            return nullptr;
        }
        // jeśli x jest w root zwróć wskaźnik do root
        if(root->val == x) {
            return root;
        }

        // jeśli w drzewie są elementy
        // chce zwrócić wskaźnik, wskazujący na węzeł o poziom wyżej od szukanego, żeby potem łatwiej się usuwało
        //
        // porównaj x z wartością węzła: jeśli x <= i istnieje poddrzewo na lewo,
        // jeśli węzeł lewego poddrzewa nie ma wartości x przejdź do lewego poddrzewa
        // w przeciwnym razie
        // jeśli węzeł prawego poddrzewa nie ma wartości x przejdź do prawego poddrzewa
        //
        // jeśli węzeł lewego lub prawego poddrzewa ma wartość równą x zwróć wskaźnik, wskazujący na węzeł o poziom wyżej od szukanego
        //
        // jeśli x jest mniejszy od wartości węzła ale nie można iść w lewo
        // lub jeśli x jest większy od węzła ale nie można iść w prawo
        // zwróć null
        Node * p = root;
        while(true) {
            if (x < p->val && p->leftSubtree != nullptr)
            {
                if((p->leftSubtree)->val != x) p = p->leftSubtree;
                else return p;
            }
            else if(x > p->val && p->rightSubtree != nullptr)
            {
                if((p->rightSubtree)->val != x) p = p->rightSubtree;
                else return p;
            }
            else
            {
                return nullptr;
            }
        }
    }

    void delete_from_BST(int x) {
        // szukaj czy x jest w drzewie
        Node * higherNode = search_BST(x);
        Node * toBeDeleted;
        bool left = false;

        // jeśli nie znaleziono x w drzewie
        if(higherNode == nullptr) return;

        // jeśli trzeba usunąć korzeń
        if(root->val == x) {
            toBeDeleted = root;
            Node * pointerToP = root;
            Node * p = root->leftSubtree;
            while(p->rightSubtree != nullptr) {
                pointerToP = p;
                p = p->rightSubtree;
            }

            p->rightSubtree = root->rightSubtree;

            if (pointerToP != root)
            {
                pointerToP->rightSubtree = p->leftSubtree;
                p->leftSubtree = root->leftSubtree;
            }

            root = p;

            delete toBeDeleted;

            return;
        }
        
        // gdy po wyszukaniu zwrócony jest wskaźnik węzła wyżej trzeba sprawdzić
        // czy węzeł do usunięci jest w lewym czy prawym poddrzewie
        if (x <= higherNode->val) {
            toBeDeleted = higherNode->leftSubtree;
            left = true;
        }
        else toBeDeleted = higherNode->rightSubtree;
        
        // przypadek gdy węzeł do usunięcia jest liściem, nie ma żadnego potomka
        if (toBeDeleted->leftSubtree == nullptr && toBeDeleted->rightSubtree == nullptr)
        {
            if (left) higherNode->leftSubtree = nullptr;
            else higherNode->rightSubtree = nullptr;

            delete toBeDeleted;
            
            return;
        }

        // przypadek gdy węzeł do usunięcia ma prawego potomka ale nie ma lewego
        if (toBeDeleted->leftSubtree == nullptr)
        {
            if (left) higherNode->leftSubtree = toBeDeleted->rightSubtree;
            else higherNode->rightSubtree = toBeDeleted->rightSubtree;

            delete toBeDeleted;
            
            return;
        }

        // przypadek gdy węzeł do usunięcia ma lewego potomka ale nie ma prawego
        if (toBeDeleted->rightSubtree == nullptr)
        {
            if (left) higherNode->leftSubtree = toBeDeleted->leftSubtree;
            else higherNode->rightSubtree = toBeDeleted->leftSubtree;
            
            delete toBeDeleted;
            
            return;
        }

        // gdy węzeł do usunięcia ma i lewy i prawy węzeł
        // wyznaczenie wskaźnika do elementu który powinien zastąpić usuwany węzeł
        // przejdź do węzła o jeden niżej w lewym poddrzewie i idź w prawo dopóki nie trafisz na null
        /**                      
         *                      pointerToP
         *                    /             \
         *                  coś               p
         *                                  /    \
         *                     lewe poddrzewo p    null
         */
        Node * pointerToP = toBeDeleted;
        Node * p = toBeDeleted->leftSubtree;
        while(p->rightSubtree != nullptr) {
            pointerToP = p;
            p = p->rightSubtree;
        }

        // niech higherNode wskazuje na wyznaczony element
        if (left) higherNode->leftSubtree = p;
        else higherNode->rightSubtree = p;

        // przepnij do wyznaczonego elementu niezmienione poddrzewo
        p->rightSubtree = toBeDeleted->rightSubtree;

        /**
         * pointerToP == toBeDeleted odpowiada przypadkowi gdy toBeDeleted->leftSubTree jest
         * największym elementem spośród mniejszych od usuwanego węzła więc nie trzeba nic więcej zmieniać
         * 
         * w przeciwnym razie lewe poddrzewo p jest przepinane do prawego poddrzewa pointerToP a do lewego poddrzewa p
         * podpinane jest lewe poddrzewo toBeDeleted
        */
        if (pointerToP != toBeDeleted)
        {
            pointerToP->rightSubtree = p->leftSubtree;
            p->leftSubtree = toBeDeleted->leftSubtree;
        }

        delete toBeDeleted;
    }
};