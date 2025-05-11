/**
 * Autor: Jan Krzemień
 * Zawartość pliku:
 *  - struktura node wykorzystywana w implementacji wskaźnikowej listy jednokierunkowej
 *  - klasa ListWithPointers z zaimplementowanymi operacjami create, insert, usuń ostatnio dodany element,
 *    wykorzystywana w funkcji sortującej listy jednokierunkowe oraz w implementacji stosu
 *  - funkcja swap zamieniająca ze sobą dwa sąsiednie elementy w liście jednokierunkowej
 *  - funkcja bouble_sort implementująca sortowanie bąbelkowe dla list jednokierunkowych
 *  - klasa Kolejka implementująca kolejkę za pomocą tablicy i dwóch wskaźników 
 *  - klasa Stos implementująca stos za pomocą listy jednokierunkowej
 *  - funkcja obliczONP licząca wynik wyrażenia podanego w postaci stringa w ONP
 * 
 * Powyższe implementacje działają dla wartości typu int.
 * Nie zawierają zabezpieczeń przed wprowadzaniem niepoprawnych danych.
 * Plik nie zawiera funkcji main, a jedynie same implementacje.
*/


#include <string>

struct node {
    int value;
    node* next;
};

/**
 * lista jednokierunkowa zaimplementowana za pomocą wskaźników,
 * wykorzystywana do sortowania listy jednokierunkowej i do implementacji stosu
*/
class ListWithPointers {
    public:
    node * tail;   // wskaźnik do ostatniego elementu listy

    void create_list() {
        tail = new node;
        tail->next = nullptr;
    }
    void insert_to_list(int val) {
        node * n = new node;
        
        n->value = val;
        n->next = tail->next;

        tail->next = n;
    }
    // usuń ostatnio dodany element
    void delete_last_element() {
        node * temp = tail->next;

        tail->next = temp->next;

        delete temp;
    }
};

/**
 * funkcja swap zamienia miejscami w liście dwa sąsiadujące elementy listy
 * z
 * tail -> ... -> pToEl1 -> el1 = pToEl2 -> el2 -> ... -> null
 * na
 * tail -> ... -> pToEl1 -> el2 -> el1 -> ... -> null
 * i zwraca nowy wskaźnik pToEl2 wskazujacy na el1
*/
node * swap(node * pToEl1, node * pToEl2) {
    node * el1 = pToEl1->next;
    node * el2 = pToEl2->next;
    node * temp = el2->next;

    pToEl1->next = el2;
    el2->next = el1;
    el1->next = temp;

    return el2;
}

/**
 * sortowanie bąbelkowe zaimplementowane dla list jednokierunkowych
*/
ListWithPointers bouble_sort(ListWithPointers lista) {
    ListWithPointers posortowanaLista{};
    posortowanaLista.create_list();
    node * p1;
    node * p2;

    while(lista.tail->next != nullptr) {
        p1 = lista.tail->next;
        p2 = lista.tail;
        while(p1->next != nullptr) {
            if((p1->next)->value < (p2->next)->value) {
                p1 = swap(p2, p1);
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        // gdy element o największej wartości trafi na koniec listy przepnij go na koniec listy już posortowanych elementów
        node * temp = posortowanaLista.tail->next;
        posortowanaLista.tail->next = p1;
        p1->next = temp;
        p2->next = nullptr;
    }

    return posortowanaLista;
}

/**
 * kolejka zaimplementowana za pomocą tablicy o rozmiarze n, podawanym podczas tworzenia obiektu i dwóch wskaźników head i tail
 * 
 * nie zostały zaimplementowane zabezpieczenia przed wykonaniem push dla pełnej kolejki i dla wykonania pop dla pustej kolejki
*/
class Kolejka {
    int * kolejka;
    int n;
    int head = 0, tail = 0;
    public:
    Kolejka(int rozmiarKolejki) {
        n = rozmiarKolejki;
        kolejka = new int[n];
    }

    void push(int x) {
        kolejka[tail] = x;
        tail = (tail + 1) % n;
    }

    int pop() {
        int temp = kolejka[head];
        head = (head + 1) % n;
        return temp;
    }
};

/**
 * stos zaimplementowany za pomocą listy jednokierunkowej
 * 
 * nie zostały zaimplementowane zabezpieczenia przed wykonaniem pop dla pustego stosu
*/
class Stos {
    ListWithPointers stos{};

    public:
    Stos() {
        stos.create_list();
    }

    void push(int x) {
        stos.insert_to_list(x);
    }

    int pop() {
        int temp = (stos.tail->next)->value;

        stos.delete_last_element();

        return temp;
    }
};


/**
 * funkcja liczy wyrażenie zawierające liczby całkowite, operacje dodawania, odejmoawnia, mnożenie i dzielenia
*/
int obliczONP(std::string ONP) {
    Stos s{};

    int i = 0;
    std::string liczba = "";
    int val1, val2;
    
    // dla każdego znaku w stringu zawierającym onp
    while(i < ONP.size()) {
        switch(ONP[i]) {
            // ściągnij ze stosu dwa ostatnie elementy, wykonaj na nich operacje i włóż z powrotem na stos
            case '+':
                val1 = s.pop();
                val2 = s.pop();
                s.push(val2 + val1);
                break;
            case '-':
                val1 = s.pop();
                val2 = s.pop();
                s.push(val2 - val1);
                break;
            case '*':
                val1 = s.pop();
                val2 = s.pop();
                s.push(val2 * val1);
                break;
            case '/':
                val1 = s.pop();
                val2 = s.pop();
                s.push(val2 / val1);
                break;
            // jeżeli string zawierający zbieraną ze znaków liczbę nie jest pusty zamień ten ciąg znaków na liczbę i włóż na stos
            case ' ':
                if(liczba == "") break;
                s.push( stoi(liczba) );
                liczba = "";
                break;
            // dodawaj do ciągu znaków kolejne cyfry liczby
            default:
                liczba += ONP[i];
        }
        i++;
    }

    // na stosie zostaje jedna liczba która jest wynikiem wyrażenia podanego w onp
    return s.pop();
}
