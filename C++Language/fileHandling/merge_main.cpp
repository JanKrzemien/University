#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include "KlientClass.h"

int main()
{
    std::ifstream fin1{"./out1.txt"};
    std::ifstream fin2{"./out2.txt"};

    if(!fin1 || !fin2)
    {
        std::cerr << "file error";
        return -1;
    }

    std::vector<Klient> klienci1{};
    std::vector<Klient> klienci2{};

    Klient k1{}, k2{};

    while(fin1 >> k1)
    {
        klienci1.push_back(k1);
    }

    while(fin2 >> k2)
    {
	klienci2.push_back(k2);
    }

    fin1.close();
    fin2.close();

    std::sort(klienci1.begin(), klienci1.end(), [](Klient k1, Klient k2) -> bool {return k1.getNazwisko() < k2.getNazwisko();});
    std::sort(klienci2.begin(), klienci2.end(), [](Klient k1, Klient k2) -> bool {return k1.getNazwisko() < k2.getNazwisko();});

    // std::for_each(klienci1.begin(), klienci1.end(), [&](Klient k){std::cout << k << std::endl;});
    // std::for_each(klienci2.begin(), klienci2.end(), [&](Klient k){std::cout << k << std::endl;});

    std::vector<Klient> vec(klienci1.size() + klienci2.size());

    std::merge(klienci1.begin(), klienci1.end(), klienci2.begin(), klienci2.end(), vec.begin(), [](Klient k1, Klient k2) -> bool {return k1.getNazwisko() < k2.getNazwisko();});

    std::cout << "rozmiar vec po merge ale przed unique: " << vec.size() << std::endl;    
    std::cout << "vec merge =============================" << std::endl;

    std::for_each(vec.begin(), vec.end(), [&](Klient k){std::cout<<k<<std::endl;});

    std::vector<Klient>::iterator it = std::unique(vec.begin(), vec.end(), [](Klient k1, Klient k2) -> bool {return (k1.getImie() == k2.getImie() && k1.getNazwisko() == k2.getNazwisko()) ;});

    vec.resize(std::distance(vec.begin(), it));

    std::cout << "rozmiar vec po unique: " << vec.size() << std::endl;

    // wersja 1
    // strumień do wypisywania pliku
    std::ofstream fout{"out3.txt"};
    // iterator ofstream
    std::ostream_iterator<Klient> ostr_it{fout, "\n"};
    // skopiowanie vectora, iterator ostream zapisuje w strumieniu dane z vectora
    std::copy(vec.begin(), vec.end(), ostr_it);

    // wersja 2
    // std::ofstream fout{"out3.txt"};
    // for(int i = 0; i < vec.size(), i++)
    // {
    //     fout << vec[i] << std::endl;
    // }

    fout.close();

    return 0;
}
