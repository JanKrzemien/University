
template<class T>
class Node {
    T data;
    int priorytet;
};

// TODO zrób z kopca osobną klasę, kolejka niech dziedziczy po kopcu

template<class T>
class Kolejka {
    Node<T> * kopiec;
    unsigned int ostatniElementKopca;

    void dodajDoKopca(Node<T> element) {
        if ( ostatniElementKopca + 1 >= kopiec.size() ) return;

        ostatniElementKopca++;
        kopiec[ostatniElementKopca] = element;
    }
    Node<T> usunKorzen() {
        if (ostatniElementKopca == -1) return nullptr;
        if (ostatniElementKopca == 0) {
            ostatniElementKopca--;
            return kopiec[0];
        }

        Node<T> temp = kopiec[0];
        kopiec[0] = kopiec[ostatniElementKopca];
        ostatniElementKopca--;
        return temp;
    }
    // przebuduj kopiec po dodaniu nowego elementu (od nowo dodanego liscia)
    void przebudujKopiecOdLiscia() {
        unsigned int p = ostatniElementKopca;
        unsigned int rodzicP = (ostatniElementKopca - 1) / 2; // jeżeli p to indeks 2*n + 1 lub 2*n + 2 to rodzic p ma indeks (int)((p - 1) / 2)
        int wynikPorownania;
        while (rodzicP != 0) {
            wynikPorownania = porownajElementy(kopiec[p], kopiec[rodzicP]);
            if (wynikPorownania > 0) {
                swap(p, rodzicP);
            } else if (wynikPorownania == 0) {
                
            } else {

            }
        }
    }
    // przebuduj kopiec po usunieciu korzenia i zastapieniu go korzeniem
    void przebudujKopiecOdKorzenia() {

    }
    /**
     * zwraca wartosc
     * > 0 gdy el1 jest wiekszy od el2
     * < 0 gdy el1 jest mniejszy od el2
     * == 0 gdy el1 jest rowny el2
    */
    int porownajElementy(Node<T> el1, Node<T> el2) {

    }
    void swap(unsigned int indeksEl1, unsigned int indeksEl2) {
        Node<T> temp = kopiec[indeksEl1];
        kopiec[indeksEl1] = kopiec[indeksEl2];
        kopiec[indeksEl2] = temp;
    }

    public:
    Kolejka(unsigned int rozmiar) {
        kopiec = new Node<T>[rozmiar];
        ostatniElementKopca = -1;
    }

    void dodaj(T element, int priorytet) {
        
    }

    T pobierz() {
        return kopiec[0];
    }
};

int main() {

}
