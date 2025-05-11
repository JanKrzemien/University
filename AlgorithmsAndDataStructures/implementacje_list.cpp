/**
 * Autor: Jan Krzemień
 * Zawartość pliku:
 *  - struktura node wykorzystywana w implementacji wskaźnikowej listy
 *  - operacje słownikowe create, insert, search, delete zaimplementowane w klasie ListWithPointers
 *    za pomocą listy w implementacji wskaźnikowej
 *  - operacje słownikowe create, insert, search, delete zaimplementowane w klasie ListWithArray
 *    za pomocą listy w implementacji kursorowej
 * 
 * Powyższe implementacje przechowują wartości typu int.
 * Nie zawierają zabezpieczeń przed wprowadzaniem niepoprawnych danych.
 * Plik nie zawiera funkcji main, a jedynie same implementacje.
*/

struct node {
    int value;
    node* next;
};

class ListWithPointers {
    node * tail;   // wskaźnik do ostatniego elementu listy
    
    public:

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

    // wyszukaj pierwszy element w liście o danej wartości
    node* search_list(int x) {
        /**
         * pToP - pointerToPointer, przy przeszukiwaniu listy wygodniej było zwracać wskaźnik do poprzedniego elementu
         * żeby przy usuwaniu mieć dostęp do elementu przed usuwanym, usuwanego i po usuwanym
         * pToP jest wskaźnikiem którt wskazuje na element listy przed przeszukiwanym
        */
        node * p = tail->next;
        node * pToP = tail;

        while(p != nullptr && p->value != x) {
            p = p->next;
            pToP = pToP->next;
        }

        return pToP;
    }

    // usuń pierwszy element w liście o takiej wartości
    void delete_from_list(int x) {
        node * p = search_list(x);

        // jeżeli element o danej wartości istnieje w liście, usuń go
        if(p->next != nullptr) {
            node * nodeToBeDeleted = p->next;
            p->next = nodeToBeDeleted->next;
            delete nodeToBeDeleted;
        }
    }
};

/**
 * w tej implementacji listy za pomocą tablicy puste elementy tablicy w miejscu indeksu
 * kolejnego elementu listy mają -2.
 * 
 * podczas dodawania elementu tablica jest przeszukiwana aż do znalezienia pierwszego pustego miejsca.
 * zwiększa to złożoność obliczeniową do O(n) dla każdej z poniższych operacji ale pozwala uniknąć
 * pozostawiania pustych wierszy tablicy po usunięciu elementu
 * 
 * zaimplementowana jest również funkcja void resize_array(int n) która w przypadku gdy tablica będzie pełna
 * stworzy większą, skopiuje do niej elementy i usunie poprzednią.
*/
class ListWithArray {
    int arrayLength;        // rozmiar tablicy
    int numberOfElements;   // liczba elementów w liście
    int ** array;           // wskaźnik do tablic wskaźników, tablica w której będą elementy listy
    int indexOfLastElem;    // indeks ostatniego elementu w tablicy    

    public:
    void create_list(int n = 1) {
        array = new int*[n];            // nowa tablica wskaźników o rozmiarze n
        
        /** do każdego elementu tablicy przypisywany jest wskaźnik do tablicy dwuelementowej.
          * następnie drugi element tej tablicy jest równy -2 co będzie oznaczało że
          * element listy który znajdowałby się pod danym indeksem jest pusty
        */
        for (int i = 0; i < n; i++){
            array[i] = new int[2];
            array[i][1] = -2;
        }
        arrayLength = n;
        numberOfElements = 0;
        indexOfLastElem = -1;
    }

    void insert_to_list(int x) {
        // jeśli tablica jest pełna, rozszerz tablice żeby miała dwa razy więcej elementów
        if (numberOfElements == arrayLength) {
            resize_array(2*arrayLength);
        }

        // znalezienie pierwszego pustego elementu i wstawienie tam nowego elementu listy
        for (int i = 0; i < arrayLength; i++)
        {
            if (array[i][1] == -2)
            {
                array[i][0] = x;
                array[i][1] = indexOfLastElem;
                indexOfLastElem = i;
                break;
            }
        }

        numberOfElements++;
    }

    int search_list(int x) {
        /**
         * temp - przy przeszukiwaniu listy wygodniej było zwracać indeks do poprzedniego elementu
         * żeby przy usuwaniu mieć dostęp do elementu przed usuwanym, usuwanego i po usuwanym
         * temp to zmienna jest która przechowuje indeks elementu listy przed przeszukiwanym
         * dla ostatniego elementu listy nie ma elementu przed przeszukiwanym więc początkowo temp == i
        */
        int i = indexOfLastElem;
        int temp = indexOfLastElem;
        while(i != -1 && array[i][0] != x) {
            temp = i;
            i = array[i][1];
        }

        return temp;
    }

    void delete_from_list(int x) {
        int pos = search_list(x);
        
        // jeżeli nie znaleziono elementu o danej wartości zakończ usuwanie
        if (array[pos][1] == -1)
            return;

        // jeżeli usuwany element jest ostatnim elementem listy nie ma elementu który na niego wskazuje
        // usuń go i zmień indeks ostaniego elementu
        if (pos == indexOfLastElem && array[pos][0] == x)
        {
            indexOfLastElem = array[pos][1];
            array[pos][1] = -2;
            return;
        }
        
        // jeżeli usuwany element nie jest ostatnim elementem listy, niech poprzedni element wskazuje
        // na element na który wskazuje usuwany element. Usuń znaleziony element
        int temp = array[pos][1];
        array[pos][1] = array[temp][1];
        array[temp][1] = -2;
    }

    /**
     * metoda tworzy tablice o danym rozmiarze kopiuje do tej tablicy elementy tablicy array.
     * pozostałe puste miejsca zapisuje przez -2 co oznacza w implementacji że są one puste.
     * następnie usuwa tablice array i sprawia że jej wskaźnik wskazuje na nową tablice.
    */
    void resize_array(int n) {
        int ** temp = new int*[n];
        for (int i = 0; i < n; i++)
        {
            temp[i] = new int[2];
            temp[i][1] = -2;
        }
             
        for (int i = 0; i < arrayLength; i++)
        {
            temp[i][0] = array[i][0];
            temp[i][1] = array[i][1];

            delete array[i];
        }

        delete array;

        array = temp;
        temp = nullptr;

        arrayLength = n;
    }
};
