#include <iostream>
#include <stack>
#include <string>

class MacierzSasiedztwa {
    bool ** macierz;
    unsigned int rozmiarMacierzy;
    bool skierowany;

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

    int stopien(bool wchodzacy, int wezel) {
        int stopien = 0;
        for (int i = 0; i < rozmiarMacierzy; i++) {
            if (wchodzacy) stopien += macierz[i][wezel];
            else stopien += macierz[wezel][i];
        }
        return stopien;
    }

    int * listaSasiadow(bool wchodzacych, int wezel) {
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

    bool getSkierowany() {
        return skierowany;
    }

    int getLiczbaWierzcholkow() {
        return rozmiarMacierzy;
    }

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

    void print() {
        for (int i = 0; i < rozmiarMacierzy; i++) {
            for (int j = 0; j < rozmiarMacierzy; j++)
                std::cout << macierz[i][j] << " ";
            std::cout << std::endl;
        }
    }
};

#define SKIEROWANY      true
#define WIERZCHOLKOW    6
#define KRAWEDZI        9

int KRAWEDZIE[KRAWEDZI][2] = {{0,1}, {1,2}, {2,1}, {2,2}, {1,3}, {2,4}, {3,4}, {3,5}, {4,5}};

void process(int node) {
    std::cout << node << std::endl;
}

bool DFS(MacierzSasiedztwa graph, bool visited[], int start_node) {

}

bool findCycle(MacierzSasiedztwa graph, bool visited[], int start_node) {
    std::stack<int> stack{};

    stack.push(start_node);
    visited[start_node] = true;

    int * neighbours;
    int arr_length;

    if(graph.getSkierowany()) {
        neighbours = graph.getListaWychodzacych(start_node);
        arr_length = graph.getStopienWychodzacy(start_node);
    } else {
        neighbours = graph.getListaSasiadow(start_node);
        arr_length = graph.getStopien(start_node);
    }

    for (int i = 0; i < arr_length; i++) {
        if (!visited[neighbours[i]])
        {
            stack.push(neighbours[i]);
            visited[neighbours[i]] = true;
        } else return true;
    }
    delete[] neighbours;
}

// void DFS(MacierzSasiedztwa graph, bool visited[], int start_node) {
//     std::stack<int> stack{};

//     stack.push(start_node);
//     visited[start_node] = true;

//     int node;
//     int * neighbours;
//     int arr_length;
//     while(!stack.empty()) {
//         node = stack.top();
//         stack.pop();
//         process(node);
//         if(graph.getSkierowany()) {
//             neighbours = graph.getListaWychodzacych(node);
//             arr_length = graph.getStopienWychodzacy(node);
//         } else {
//             neighbours = graph.getListaSasiadow(node);
//             arr_length = graph.getStopien(node);
//         }

//         for (int i = 0; i < arr_length; i++) {
//             if (!visited[neighbours[i]])
//             {
//                 stack.push(neighbours[i]);
//                 visited[neighbours[i]] = true;
//             }
//         }
//         delete[] neighbours;
//     }
// }

int main() {
    MacierzSasiedztwa graf_skierowany{SKIEROWANY, WIERZCHOLKOW, KRAWEDZI, KRAWEDZIE};
    MacierzSasiedztwa graf_nieskierowany{!SKIEROWANY, WIERZCHOLKOW, KRAWEDZI, KRAWEDZIE};
    
    bool odwiedzone[graf_skierowany.getLiczbaWierzcholkow()] = {false};

    std::cout << findCycle(graf_skierowany, odwiedzone, 0) << std::endl;

    // graf_skierowany.print();
}
