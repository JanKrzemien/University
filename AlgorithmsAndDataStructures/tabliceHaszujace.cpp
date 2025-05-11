/**
 * Autor: Jan Krzemień
 * Zawartość pliku:
 *  - struktura node wykorzystywana w implementacji wskaźnikowej listy jednokierunkowej
 *  - klasa List z zaimplementowanymi operacjami create, insert, search, delete,
 *    wykorzystywana w klasie ListHashTable
 *  - klasa ListHashTable implementująca tablice haszującą list
 *    z operacjami create, insert, search, delete i funkcją haszującą f
 *  - klasa OpenHashTable implementująca otwartą tablice haszującą
 *    z operacjami create, insert, search, delete i funkcją haszującą f
 * 
 * Powyższe implementacje działają dla wartości typu int.
 * Nie zawierają zabezpieczeń przed wprowadzaniem niepoprawnych danych.
 * Plik nie zawiera funkcji main, a jedynie same implementacje.
*/


#include <iostream>

typedef struct node Node;
struct node {
    int val;
    Node * next;
};

class List {
    public:
    Node * tail;

    void create_list() {
        tail = new Node;
        tail->next = nullptr;
    }

    void insert_list(int x) {
        Node * n = new Node;

        n->val = x;
        n->next = tail->next;
        tail->next = n;
    }

    Node * search_list(int x) {
        Node * p = tail->next;
        Node * pToP = tail;

        while(p != nullptr && p->val != x) {
            p = p->next;
            pToP = pToP->next;
        }

        if(p == nullptr) {
            return nullptr;
        } else {
            return pToP;
        }
    }

    void delete_list(int x) {
        Node * pToDel = search_list(x);
        if(pToDel == nullptr) return;
        Node * deleted = pToDel->next;

        pToDel->next = deleted->next;

        delete deleted;
    }
};


class ListHashTable {
    public:
    List * arr;
    int arrLen;

    // funkcja haszująca
    int f(int x) {
        return x % arrLen;
    }

    void create_hashtable(int n) {
        arr = new List[n];
        for (int i = 0; i < n; i++)
        {
            arr[i].create_list();
        }
        arrLen = n;
    }

    void insert_to_hashtable(int x) {
        arr[f(x)].insert_list(x);
    }

    Node * search_hashtable(int x) {
        List temp = arr[f(x)];
        return temp.search_list(x);
    }

    void delete_from_hashtable(int x) {
        List temp = arr[f(x)];
        temp.delete_list(x);
    }
};

/**
 * -1 oznacza że dany element tablicy jest pusty
 * 0 oznacza że dany element został usunięty
*/
class OpenHashTable {
    public:
    int * arr;
    int arrLen;
    
    // funkcja haszująca
    int f(int x, int i) {
        return (x + i) % arrLen;
    }

    // stwórz tablice i ustaw wszystkie jej elementy na puste
    void create_hashtable(int n) {
        arr = new int[n];
        for (int i = 0; i < n; i++)
        {
            arr[i] = -1;
        }
        arrLen = n;
    }


    void insert_to_hashtable(int x) {
        int i = 0;
        int firstIndx = f(x, i);
        int indx = firstIndx;

        // zwiększaj i dopóki nie natrafisz na pusty element lub usunięty element
        // jeśli indeksy zatoczą koło aktualnie sprawdzany indeks będzie równy pierwszemu sprawdzonemu elementowi
        // tablica jest pełna, wyjdź z funkcji.
        while(arr[indx] != -1 && arr[indx] != 0) {
            i++;
            indx = f(x, i);
            if(indx == firstIndx) {
                std::cout << "brak wolnych miejsc w tablicy haszowanej" << std::endl;
                return;
            }
        }

        arr[indx] = x;
    }

    int search_hashtable(int x) {
        int i = 0;
        int firstIndx = f(x, i);
        int indx = firstIndx;

        // zwiększaj i dopóki nie natrafisz na pusty element lub szukany element
        // jeśli indeksy zatoczą koło aktualnie sprawdzany indeks będzie równy pierwszemu sprawdzonemu elementowi
        // tablica jest pełna, wyjdź z funkcji.
        while(arr[indx] != x && arr[indx] != -1) {
            i++;
            indx = f(x, i);
            if(indx == firstIndx) {
                std::cout << "nie znaleziono elementu" << std::endl;
                return -1;
            }
        }
        // jeśli pętla zakończyła się przez trafienie na -1 to x nie występuje w tablicy
        if(arr[indx] == -1) {
            std::cout << "nie znaleziono elementu" << std::endl;
            return -1;
        }
        // x występuje w tablicy, zwróć jego indeks
        return indx;
    }

    void delete_from_hashtable(int x) {
        int indx = search_hashtable(x);
        if(indx == -1) {
            return;
        }
        arr[indx] = 0;
    }
};