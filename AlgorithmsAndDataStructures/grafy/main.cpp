/***
 * problemy i rozwiązania:
 *  - w jakiej postaci przyjąć i przechowywać węzły grafu - przyjąłem że węzły są numerowane zaczynając od 0.
 *  - w reprezentacji za pomocą list sąsiedztwa w jaki sposób zaimplementować pętle - pętla występuje jeśli w zbiorze pod danym indeksem znajduje się element o takim samym indeksie.
 *  - w reprezentacji za pomocą list sąsiedztwa w jaki sposób uniknąć powtórzonych wartości dla grafów nieskierowanych - wykorzystałem zbiory implementowane za pomocą posortowanych list dwukierunkowych.
 *  - w reprezentacji za pomocą macierzy incydencji w jaki sposób zaimplementować pętle - krawędź będąca pętlą będzie miała element o wartości większej od 1.
 *  - w reprezentacji za pomocą macierzy incydencji w jaki sposób uniknąć powtórzonych wartości dla grafów nieskierowanych - dla grafu nieskierowanego tworzę kopie tablicy krawędzi, następnie usuwam z niej powtarzające się krawędzie
 *   i dla tak stworzonej tablicy krawedzi tworze macierz.
*/

#include <iostream>

class reprezentacjaGrafu {
    protected:
    bool skierowany;

    virtual int stopien(bool wchodzacy, int wezel) {return -1;}
    virtual int * listaSasiadow(bool wchodzacy, int wezel) {return nullptr;}

    public:
    int getStopienWchodzacy(int wezel) {
        if(!skierowany) return -1;
        return stopien(true, wezel);
    }

    int getStopienWychodzacy(int wezel) {
        if(!skierowany) return -1;
        return stopien(false, wezel);
    }

    int getStopien(int wezel) {
        if(skierowany) return -1;
        return stopien(false, wezel);
    }

    int * getListaWychodzacych(int wezel) {
        if(!skierowany) return nullptr;
        return listaSasiadow(false, wezel);
    }

    int * getListaWchodzacych(int wezel) {
        if(!skierowany) return nullptr;
        return listaSasiadow(true, wezel);
    }

    int * getListaSasiadow(int wezel) {
        if(skierowany) return nullptr;
        return listaSasiadow(true, wezel);
    }

    virtual void print() {}
};

class MacierzSasiedztwa : public reprezentacjaGrafu {
    bool ** macierz;
    unsigned int rozmiarMacierzy;

    void stworzMacierz() {
        macierz = new bool*[rozmiarMacierzy];
        for (int i = 0; i < rozmiarMacierzy; i++)
            macierz[i] = new bool[rozmiarMacierzy];
    }

    void wyzerujMacierz() {
        for (int i = 0; i < rozmiarMacierzy; i++)
            for (int j = 0; j < rozmiarMacierzy; j++)
                macierz[i][j] = false;
    }

    void wpiszKrawedzie(int liczbaKrawedzi, int krawedzie[][2]) {
        for (int i = 0; i < liczbaKrawedzi; i++) {
            macierz[krawedzie[i][0]][krawedzie[i][1]] = true;
        }

        // jeśli graf jest nieskierowany jest macierz sąsiedztwa jest symetryczna
        if(!skierowany)
            for (int i = 0; i < liczbaKrawedzi; i++)
                macierz[krawedzie[i][1]][krawedzie[i][0]] = true;
    }

    int stopien(bool wchodzacy, int wezel) override {
        int stopien = 0;
        for (int i = 0; i < rozmiarMacierzy; i++) {
            if (wchodzacy) stopien += macierz[i][wezel];
            else stopien += macierz[wezel][i];
        }
        return stopien;
    }

    int * listaSasiadow(bool wchodzacych, int wezel) override {
        int * sasiedzi;
        if(!skierowany) sasiedzi = new int[ getStopien(wezel) ];
        else sasiedzi = new int[ wchodzacych ? getStopienWchodzacy(wezel) : getStopienWychodzacy(wezel) ];
        int ostatniSasiad = -1;
        for(int i = 0; i < rozmiarMacierzy; i++)
            if( (!wchodzacych && macierz[wezel][i]) || (wchodzacych && macierz[i][wezel]) ) {
                ostatniSasiad++;
                sasiedzi[ostatniSasiad] = i;
            }
        
        return sasiedzi;
    }

    public:

    MacierzSasiedztwa(bool skierowany_, int liczbaWierzcholkow, int liczbaKrawedzi, int krawedzie[][2]) {
        rozmiarMacierzy = liczbaWierzcholkow;
        skierowany = skierowany_;
        stworzMacierz();
        wyzerujMacierz();
        wpiszKrawedzie(liczbaKrawedzi, krawedzie);
    }

    void print() override {
        for (int i = 0; i < rozmiarMacierzy; i++) {
            for (int j = 0; j < rozmiarMacierzy; j++)
                std::cout << macierz[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

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

class ListaSasiedztwa : public reprezentacjaGrafu {
    Set<int> * listaOdchodzacych;
    Set<int> * listaDochodzacych;
    int rozmiar;

    void printListaSasiedztwa(Set<int> * l) {
        for (int i = 0; i < rozmiar; i++)
        {
            std::cout << i << ": ";
            l[i].print();
            std::cout << std::endl;
        }
    }

    int stopien(bool wchodzacy, int wezel) override {
        if(wchodzacy) return listaDochodzacych[wezel].length();
        else return listaOdchodzacych[wezel].length();
    }

    int * listaSasiadow(bool wchodzacych, int wezel) override {
        int * sasiedzi;
        Node<int> * tail;
        if(!skierowany) {
            sasiedzi = new int[ getStopien(wezel) ];
            tail = listaOdchodzacych[wezel].container.tail->next;
        } else {
            sasiedzi = new int[ wchodzacych ? getStopienWchodzacy(wezel) : getStopienWychodzacy(wezel) ];
            tail = wchodzacych ? listaDochodzacych[wezel].container.tail->next : listaOdchodzacych[wezel].container.tail->next;
        }             
        int ostatniSasiad = -1;
        while(tail != nullptr) {
            ostatniSasiad++;
            sasiedzi[ostatniSasiad] = tail->data;
            tail = tail->next;
        }
        return sasiedzi;
    }

    void stworzListy() {
        listaOdchodzacych = new Set<int>[rozmiar];
        listaDochodzacych = new Set<int>[rozmiar];
        for (int i = 0; i < rozmiar; i++) {
            listaOdchodzacych[i] = Set<int>();
            listaDochodzacych[i] = Set<int>();
        }
    }

    public:
    ListaSasiedztwa(bool skierowany_, int liczbaWierzcholkow, int liczbaKrawedzi, int krawedzie[][2]) {
        skierowany = skierowany_;
        rozmiar = liczbaWierzcholkow;

        stworzListy();

        if(skierowany) {
            for (int i = 0; i < liczbaKrawedzi; i++)
            {
                listaOdchodzacych[krawedzie[i][0]].insert(krawedzie[i][1]);
                listaDochodzacych[krawedzie[i][1]].insert(krawedzie[i][0]);
            }

            return;
        }

        for (int i = 0; i < liczbaKrawedzi; i++)
        {   
            listaOdchodzacych[krawedzie[i][0]].insert(krawedzie[i][1]);
            if(krawedzie[i][1] != krawedzie[i][0])
                listaOdchodzacych[krawedzie[i][1]].insert(krawedzie[i][0]);
        }
    }

    void print() override {
        if(skierowany) {
            std::cout << "lista odchodzacych:" << std::endl;
            printListaSasiedztwa(listaOdchodzacych);
            
            std::cout << "lista dochodzacych:" << std::endl;
            printListaSasiedztwa(listaDochodzacych);

            return;
        }

        std::cout << "lista sasiadow:" << std::endl;
        printListaSasiedztwa(listaOdchodzacych);
    }
};

class MacierzIncydencji : public reprezentacjaGrafu {
    unsigned int iloscWezlow;
    unsigned int iloscKrawedzi;
    short ** macierzIncydencji;


    int stopien(bool wchodzacy, int wezel) override {
        int s = 0;
        for (int i = 0; i < iloscKrawedzi; i++) {
            if ((wchodzacy || !skierowany) && macierzIncydencji[i][wezel] > 0)
                s += 1;
            else if ((!wchodzacy && skierowany) && (macierzIncydencji[i][wezel] == -1 || macierzIncydencji[i][wezel] == 2))
                s += 1;
        }

        return s;
    }

    int * listaSasiadow(bool wchodzacych, int wezel) override {
        int * sasiedzi;
        if(!skierowany) sasiedzi = new int[ getStopien(wezel) ];
        else sasiedzi = new int[ wchodzacych ? getStopienWchodzacy(wezel) : getStopienWychodzacy(wezel) ];
        int ostatniSasiad = -1;
        for(int i = 0; i < iloscKrawedzi; i++) {
            if(!wchodzacych && skierowany) {
                if (macierzIncydencji[i][wezel] == 2) {
                    ostatniSasiad++;
                    sasiedzi[ostatniSasiad] = wezel;
                } else if (macierzIncydencji[i][wezel] == -1) {
                    for (int j = 0; j < iloscWezlow; j++) {
                        if (macierzIncydencji[i][j] == 1) {
                            ostatniSasiad++;
                            sasiedzi[ostatniSasiad] = j;
                            break;
                        }
                    }
                }
            } else if (wchodzacych && !skierowany) {
                if (macierzIncydencji[i][wezel] == 2) {
                    ostatniSasiad++;
                    sasiedzi[ostatniSasiad] = wezel;
                } else if (macierzIncydencji[i][wezel] == 1) {
                    for (int j = 0; j < iloscWezlow; j++) {
                        if (macierzIncydencji[i][j] == 1 && wezel != j) {
                            ostatniSasiad++;
                            sasiedzi[ostatniSasiad] = j;
                            break;
                        }
                    }
                }
            } else if (wchodzacych) {
                if (macierzIncydencji[i][wezel] == 2) {
                    ostatniSasiad++;
                    sasiedzi[ostatniSasiad] = wezel;
                } else if (macierzIncydencji[i][wezel] == 1) {
                    for (int j = 0; j < iloscWezlow; j++) {
                        if (macierzIncydencji[i][j] == -1) {
                            ostatniSasiad++;
                            sasiedzi[ostatniSasiad] = j;
                            break;
                        }
                    }
                }
            }
        }
        
        return sasiedzi;
    }

    public:

    MacierzIncydencji(bool skierowany_, int liczbaWierzcholkow, int liczbaKrawedzi, int krawedzie[][2]) {
        iloscWezlow = liczbaWierzcholkow;
        iloscKrawedzi = liczbaKrawedzi;
        skierowany = skierowany_;

        // stwórz macierz incydencji
        macierzIncydencji = new short*[iloscKrawedzi];
        for (int i = 0; i < iloscKrawedzi; i++) {
            macierzIncydencji[i] = new short[iloscWezlow];
        }
           
        // wypelnij macierz incydencji zerami
        for (int i = 0; i < iloscWezlow; i++)
            for (int j = 0; j < iloscKrawedzi; j++)
                macierzIncydencji[i][j] = 0;

        if(!skierowany) {
            int k[liczbaKrawedzi][2];
            // jeśli graf nieskierowany skopiuj tablice krawędzi
            for (int i = 0; i < liczbaKrawedzi; i++)
            {
                k[i][0] = krawedzie[i][0];
                k[i][1] = krawedzie[i][1];
            }
            // usuń powtarzające się krawędzie
            for (int i = 0; i < iloscKrawedzi - 1; i++)
                for (int j = i + 1; j < iloscKrawedzi; j++)
                    if (k[i][0] == k[j][1] && k[i][1] == k[j][0])
                        k[j][0] = -1;
            // wpisz unikatowe krawędzie
            for (int i = 0; i < iloscKrawedzi; i++)
                if (k[i][0] != -1) {
                    macierzIncydencji[i][krawedzie[i][1]] += 1;
                    macierzIncydencji[i][krawedzie[i][0]] += 1;
                }
        } else {
            // wpisz krawędzie dla grafu skierowanego
            for (int i = 0; i < iloscKrawedzi; i++)
            {
                macierzIncydencji[i][krawedzie[i][1]] += 1;
                if (krawedzie[i][0] != krawedzie[i][1]) macierzIncydencji[i][krawedzie[i][0]] += -1;
                else macierzIncydencji[i][krawedzie[i][0]] += 1;
            }
        }
    }

    void print() override {
        for (int i = 0; i < iloscKrawedzi; i++) {
            for (int j = 0; j < iloscWezlow; j++)
                std::cout << macierzIncydencji[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

#define SKIEROWANY      true
#define WIERZCHOLKOW    6
#define KRAWEDZI        9

int KRAWEDZIE[KRAWEDZI][2] = {{0,1}, {1,2}, {2,1}, {2,2}, {1,3}, {2,4}, {3,4}, {3,5}, {4,5}};

void test(reprezentacjaGrafu * graf, int wezel, bool skierowany) {
    int * sasiedzi;
    int sasiadow;

    graf->print();

    if(skierowany) {
        std::cout << graf->getStopienWchodzacy(wezel) << std::endl;
        std::cout << graf->getStopienWychodzacy(wezel) << std::endl;

        sasiedzi = graf->getListaWychodzacych(wezel);
        sasiadow = graf->getStopienWychodzacy(wezel);
        for (int i = 0; i < sasiadow; i++)
            std::cout << sasiedzi[i] << " ";
        std::cout << std::endl;

        sasiedzi = graf->getListaWchodzacych(wezel);
        sasiadow = graf->getStopienWchodzacy(wezel);
        for (int i = 0; i < sasiadow; i++)
            std::cout << sasiedzi[i] << " ";
    } else {
        std::cout << graf->getStopien(wezel) << std::endl;

        sasiedzi = graf->getListaSasiadow(wezel);
        sasiadow = graf->getStopien(wezel);
        for (int i = 0; i < sasiadow; i++)
            std::cout << sasiedzi[i] << " ";
    }

    std::cout << std::endl;
    std::cout << std::endl;
}

int main() {
    test( new MacierzSasiedztwa(SKIEROWANY, WIERZCHOLKOW, KRAWEDZI, KRAWEDZIE), 2, true);
    
    test( new MacierzSasiedztwa(!SKIEROWANY, WIERZCHOLKOW, KRAWEDZI, KRAWEDZIE), 2, false);

    test( new ListaSasiedztwa(SKIEROWANY, WIERZCHOLKOW, KRAWEDZI, KRAWEDZIE), 2, true);

    test( new ListaSasiedztwa(!SKIEROWANY, WIERZCHOLKOW, KRAWEDZI, KRAWEDZIE), 2, false);

    test( new MacierzIncydencji(SKIEROWANY, WIERZCHOLKOW, KRAWEDZI, KRAWEDZIE), 2, true);

    test( new MacierzIncydencji(!SKIEROWANY, WIERZCHOLKOW, KRAWEDZI, KRAWEDZIE), 2, false);
}
