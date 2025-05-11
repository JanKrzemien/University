/**
 * Autor: Jan Krzemień
 * Zawartość pliku:
 *  - sortowanie przez wstawianie zaimplementowane w funkcji insertion_sort
 *  - sortowanie przez wybieranie zaimplementowane w funkcji selection_sort
 *  - sortowanie bąbelkowe zaimplementowane w funkcji bouble_sort
 *  - sortowanie szybkie zaimplementowane w funkcji quicksort
 *  - sortowanie przez scalanie zaimplementowane w funkcji mergesort
 *  - sortowanie przez kopcowanie zaimplementowane w funkcji heapsort
 * 
 * Wszystkie powyższe implementacje działają dla tablicy liczb całkowitych o długości n >= 2.
 * Nie zawierają zabezpieczeń przed wprowadzaniem niepoprawnych danych.
 * Plik nie zawiera funkcji main, a jedynie same implementacje
*/

/**
 * implementacja sortowania przez wstawianie
 * tab - tablica do posortowania
 * n - długość tablicy tab
*/
void insertion_sort(int tab[], int n){
    int temp;  // przechowuje wartości podczas zamiany miejscami elementów tablicy
    int j;     // index wykorzystywany przy przesuwaniu elementów tablicy

    for (int i = 1; i < n; i++)
    {
        temp = tab[i];
        // przesuwaj elementy tablicy aż natrafisz na element niewiększy
        // od danego sortowanego elementu
        j = i - 1;
        while(j > -1 && tab[j] > temp){
            tab[j + 1] = tab[j];
            j--;
        }
        // wpisz sortowany element w miejsce powstałe przez przesuwanie elementów większych
        tab[j + 1] = temp;
    }
}

/**
 * implementacja sortowania przez wybieranie
 * tab - tablica do posortowania
 * n - długość tablicy tab
*/
void selection_sort(int tab[], int n){
   int temp;            // zmienna używana do zamiany miejscami elementów tablicy
   int min, minIndx;

   for (int i = 1; i < n; i++)
   {
        // jako minimum pierwszy fragment nie posortowanej części tablicy
        min = tab[i - 1];
        minIndx =  i - 1;
        
        // znajdź minimum w nieposortowanej tablicy
        for (int j = i; j < n; j++)
        {
            if( min > tab[j] ){
                min = tab[j];
                minIndx = j;
            }
        }

        // zamień miejscami minimum z pierwszym elementem nieposortowanej tablicy        
        temp = tab[i - 1];
        tab[i - 1] = min;
        tab[minIndx] = temp;
   }
}

/**
 * implementacja sortowania bąbelkowego
 * tab - tablica do posortowania
 * n - długość tablicy tab
*/
void bouble_sort(int tab[], int n){
    int temp;
    
    int j; 
    int i = n;

    // i zmniejsza się od n do 0 żeby w kolejnej pętli warunek j < i
    // zapewniał że nie będzie porównań z już posortowanymi elementami
    while( i > 0 ){

        j = 1;
        while( j < i ){
            if( tab[j] < tab[j - 1] ){
                temp = tab[j];
                tab[j] = tab[j - 1];
                tab[j - 1] = temp;
            }

            j++;
        }

        i--;
    }
}


/**
 * implementacja sortowania szybkiego
 * tab - tablica do posortowania
 * poczatekTablicy - index pierwszego elementu sortowanej tablicy
 * koniecTablicy - index ostatniego elementu tablicy plus jeden
*/
void quicksort(int tab[], int poczatekTablicy, int koniecTablicy) {
    int temp;  // zmienna do zamiany elementów tablicy

    // jeśli tablica jest dwuelementowa zamiana elementów jeśli konieczna i wyjdź z rekurencji
    if (koniecTablicy - poczatekTablicy == 2) {
        if (tab[poczatekTablicy] > tab[poczatekTablicy + 1]) {
            temp = tab[poczatekTablicy];
            tab[poczatekTablicy] = tab[poczatekTablicy + 1];
            tab[poczatekTablicy + 1] = temp;
        }
        return;
    }
    // jeśli tablica jest jednoelementowa to jest już posortowana
    if (koniecTablicy - poczatekTablicy < 2) return;

    int srodek = (poczatekTablicy + koniecTablicy) / 2;   // środkowy indeks tablicy
    int pivot = tab[srodek];                              // wartość elementu środkowego
    int wskL = poczatekTablicy, wskP = koniecTablicy - 1; // wskaźniki lewy i prawy

    while(wskL < wskP) {
        // przesuwaj lewy wskaźnik aż nie trafi na element większy od pivota lub koniec tablicy
        while(tab[wskL] <= pivot && wskL < koniecTablicy)
            wskL++;
        
        // przesuwaj prawy wskaźnik aż nie trafi na element mniejszy od pivota lub początek tablicy
        while(tab[wskP] >= pivot && wskP > poczatekTablicy)
            wskP--;

        // jeśli wskaźniki się nie minęły zamień elementy miejscami
        if(wskL < wskP){
            temp = tab[wskL];
            tab[wskL] = tab[wskP];
            tab[wskP] = temp;
        }
    }

    // ustaw pivot między wskaźnikami

    /**
     * przypadek gdy np.
     * ..., 3, ..., 1, 3, 3, 4
     * gdzie pierwsze 3 od lewej to pivot, wskL jest na elemencie o wartości 4, wskP na elemencie o wartości 1
     * to powinno przejść w
     * ..., 1, ..., 3, 3, 3, 4
    */
    if(wskL > srodek && wskP > srodek) {
        temp = tab[wskP];
        tab[wskP] = pivot;
        tab[srodek] = temp;
        srodek = wskP;
    }
    /**
     * przypadek gdy np.
     * 1, 2, 2, 4, ..., 3, ...
     * gdzie 3 to pivot, wskL jest na elemencie o wartości 4, wskP na elemencie o wartości 1
     * to powinno przejść w
     * 1, 2, 2, 3, ..., 4, ...
    */
    if(wskL < srodek && wskP < srodek) {
        temp = tab[wskL];
        tab[wskL] = pivot;
        tab[srodek] = temp;
        srodek = wskL;
    }


    quicksort(tab, poczatekTablicy, srodek);
    quicksort(tab, srodek + 1, koniecTablicy);
}

/**
 * implementacja sortowania przez scalanie
 * tab - tablica do posortowania
 * poczatekTablicy - index pierwszego elementu sortowanej tablicy
 * koniecTablicy - index ostatniego elementu tablicy plus jeden
*/
void mergesort(int tab[], int poczatekTablicy, int koniecTablicy) {
    int temp;                                   // zmienna służąca do zamiany elementów tablicy
    int n = koniecTablicy - poczatekTablicy;    // długość tablicy
    
    // jeśli dwa elementy w tablicy zamień jeśli trzeba i wyjdź z rekurencji
    if (n == 2){
        if (tab[poczatekTablicy] > tab[poczatekTablicy + 1])
        {
            temp = tab[poczatekTablicy];
            tab[poczatekTablicy] = tab[poczatekTablicy + 1];
            tab[poczatekTablicy + 1] = temp;
        }
        return;
    }
    // tablica jednoelementowa jest już posortowana
    if (n == 1) return;
    
    int srodek = (poczatekTablicy + koniecTablicy) / 2;   // środkowy indeks tablicy

    /**
     * podziel tablice na dwie podtablice
     * pierwsza o indeksach od poczatekTablicy do srodek - 1
     * drugą o indeksach od srodek do koniecTablicy - 1
    */
    mergesort(tab, poczatekTablicy, srodek);
    mergesort(tab, srodek, koniecTablicy);

    int *tablicaPomocnicza = new int[n];

    int wskL = poczatekTablicy, wskP = srodek, indexTablicyPomocniczej = 0;
    
    // porównuj elementy z dwóch podtablic i dopisuj mniejszy do tablicy pomocniczej
    // do momentu wykorzystania wszystkich elementów z jednej z podtablic
    while(wskL < srodek && wskP < koniecTablicy) {
        if (tab[wskL] <= tab[wskP]) {
            tablicaPomocnicza[indexTablicyPomocniczej] = tab[wskL];
            wskL++;
        } else {
            tablicaPomocnicza[indexTablicyPomocniczej] = tab[wskP];
            wskP++;
        }
        indexTablicyPomocniczej++;
    }

    // w jednej z podtablic pozostaną elementy

    // jeśli w lewej podtablicy pozostały jakieś elementy przepisz je do tablicy pomocniczej
    while(wskL < srodek) {
        tablicaPomocnicza[indexTablicyPomocniczej] = tab[wskL];
        wskL++;
        indexTablicyPomocniczej++;
    }
    // jeśli w prawej podtablicy pozostały jakieś elementy przepisz je do tablicy pomocniczej
    while(wskP < koniecTablicy) {
        tablicaPomocnicza[indexTablicyPomocniczej] = tab[wskP];
        wskP++;
        indexTablicyPomocniczej++;
    }

    // przepisz tablice pomocniczą do oryginalnej tablicy
    indexTablicyPomocniczej = 0;
    wskL = poczatekTablicy;
    while(indexTablicyPomocniczej < n) {
        tab[wskL] = tablicaPomocnicza[indexTablicyPomocniczej];
        wskL++;
        indexTablicyPomocniczej++;
    }

    // zwolnij zaalokowaną na tablice pomocniczą pamięć
    delete[] tablicaPomocnicza;
}

/**
 * implementacja sortowania przez kopcowanie
 * tab - tablica do posortowania
 * n - długość tablicy tab
*/
void heapsort(int tab[], int n) {

    // budowanie kopca
    int temp;
    int wsk = 1, k, indexWezlaWyzej;
    while(wsk < n) {
        // jeśli trzeba popraw kopiec
        /**
         * mechanizm poprawiania kopca podczas jego budowy,
         * index nowo dodanego liścia to 2*p = 2*p + 1 lub + 2
         *              p
         *             /\
         *            /  \
         *       2p + 1   2p + 2
         * żeby dostać p odejmuje jeden i dziele na dwa a zapisywanie
         * do zmiennej całkowitej integer sprawia że dostaje liczbę całkowitą p
         * 
         * wsk to index nowododanego liścia
         * k to index nowododanej wartości, początkowy równy wsk
         * indexWezlaWyzej to index węzła który jest rodzicem węzła o indeksie k
         * 
         * dopóki węzeł wyżej ma mniejszą wartość lub dopóki nowododana wartość
         * nie stała się korzeniem zamieniaj ich wartości
         * k staje się indeksem węzła wyżej,
         * indexWezlaWyzej staje się indeksem węzła wyżej
        */
        k = wsk;                                // index nowododanego liścia
        indexWezlaWyzej = (k - 1) / 2;          // index węzła nad liściem
        
        // dopóki nie dotrze do korzenia wykonuj
        while(k > 0) {
            // jeśli nowa wartość jest większa od wartości węzła nad nią zamień je miejscami
            if (tab[k] > tab[indexWezlaWyzej]) {
                temp = tab[k];
                tab[k] = tab[indexWezlaWyzej];
                tab[indexWezlaWyzej] = temp;
            }
            // jeśli nowa wartość jest mniejsza od wartości węzła wyżej kopiec jest poprawny, zakończ poprawianie go
            else {
                break;
            }
            // przejdź indeksami o poziom wyżej w drzewie
            k = indexWezlaWyzej;
            indexWezlaWyzej = (indexWezlaWyzej - 1) / 2;
        }

        // dodaj element na koniec kopca
        wsk++;
    }

    wsk--;  // żeby wskaźnik był indeksem ostatniego elementu

    // rozbieranie kopca
    while(wsk > 0) {
        // ściągnij największy element i zamień go z ostatnim elementem kopca
        temp = tab[0];
        tab[0] = tab[wsk];
        tab[wsk] = temp;

        // ilość elementów kopca mniejsza o 1, wsk dalej jest inedksem ostatniego elementu kopca
        wsk--;

        // jeśli trzeba popraw kopiec
        /**
         * mechanizm poprawiania kopca podczas jego rozbierania
         * (różni się od mechanizmu poprawiania kopca podczas jego budowy ponieważ
         * podczas budowy sprawdzanie było przeprowadzane od liścia do korzenia
         * podczas rozbierania sprawdzanie przeprowadzam od korzenia do liścia)
         * 
         * wsk to indeks ostatniego elementu kopca
         * k to index węzła, początkowo równy 0 co jest równoważne korzeniowi kopca
         * dzieci węzła o indeksie k będą miały indeksy 2*k + 1 i 2*k + 2
         *              k
         *             /\
         *            /  \
         *       2k + 1   2k + 2
         * 
         * w każdej iteracji sprawdzam w który potomek jest większy,
         * a następnie czy węzeł o indeksie k jest mniejszy,
         * jeśli węzeł o indeksie k jest większy lub równy to nie trzeba dalej poprawiać kopca,
         * jeśli jest mniejszy to wartości są zamieniane i index k jest równy indeksowi
         * potomka z którym zamienił się wartością.
         * 
         * pętla zakończy się gdy węzeł o indeksie k będzie większy lub równy swojemu
         * największemu potomkowi lub gdy dojdzie do jednej z poniższych sytuacji
         * 
         *    a)        k           b)     k
         *             / \                / \
         *            /   \              /   \
         * 2k + 1 == wsk   brak       brak    brak
         * 
         * w obu przypadkach pętla się zakończy i zostanie sprawdzony warunek w instrukcji if
         * w przypadku a) jeśli wartość węzła o indeksie k będzie mniejsza od wartości węzła 2k + 1
         * ich wartości zostaną zamienione, w przypadku b) warunek instrukcji if nie zostanie
         * spełniony, kopiec będzie już poprawny
        */
        k = 0;
        while(2*k + 2 <= wsk) {
            if(tab[2*k + 1] > tab[2*k + 2]) {
                if(tab[k] < tab[2*k + 1]) {
                    temp = tab[k];
                    tab[k] = tab[2*k + 1];
                    tab[2*k + 1] = temp;
                }
                else {
                    break;
                }
                k = 2*k + 1;
            } else {
                if(tab[k] < tab[2*k + 2]) {
                    temp = tab[k];
                    tab[k] = tab[2*k + 2];
                    tab[2*k + 2] = temp;
                } else {
                    break;
                }
                k = 2*k + 2;
            }
        }
        if(2*k + 1 <= wsk && tab[k] < tab[2*k + 1]) {
            temp = tab[k];
            tab[k] = tab[2*k + 1];
            tab[2*k + 1] = temp;
        }

    }
}
