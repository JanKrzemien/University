#include <iostream>
#include "KlientClass.h"
#include <fstream>
#include <vector>
#include <algorithm>

int main()
{
    std::ifstream ifs{"in1.txt"};

    std::ifstream ifs2{"in2.txt"};

    if(!ifs || !ifs2)
    {
        std::cerr <<  "błąd otwarcia pliku";
        return -1;
    }

    std::vector<Klient> klienci{};
    std::vector<Klient> klienci2{};
    Klient klient{};
    std::string smieci;

    while(ifs >> klient)
    {
        klienci.push_back(klient);
        while(getline(ifs, smieci) && smieci != "");
    }

    while(ifs2 >> klient)
    {
        klienci2.push_back(klient);
        while(getline(ifs2, smieci) && smieci != "");
    }

    std::cout << "wczytano " << klienci.size() << " elementów" << std::endl;
    std::cout << "wczytano " << klienci2.size() << " elementów" << std::endl;


    ifs.close();
    ifs2.close();

    std::ofstream ofs{"out1.txt"};
    std::ofstream ofs2{"out2.txt"};
    if(!ofs || !ofs2)
    {
        std::cerr << "bład otwarcia pliku do zapisu";
        return -2;
    }

    // czwarty sposób
    // #include <algorithm>
    // pętla for_each z wykorzystaniem funkcji lambda
    // równie dobrze można zdefiniować funkcje na boku i jej użyć
    std::for_each(klienci.begin(),klienci.end(),[&](Klient k){ofs << k << std::endl;});

    std::for_each(klienci2.begin(), klienci2.end(), [&](Klient k){ofs2 << k << std::endl;});


    // trzeci sposób też używający iteratora ale nie jawnie
    // for(klient k : klienci)
    //     ofs << k << std::endl << std::endl;
    // tak samo możemy użyć auto zamiast klient k zrobić auto k

    // drugi sposób
    // for(std::vector<Klient>::iterator it = klienci.begin() ; it != klienci.end() ; ++it)
    //     ofs << *it << std::endl << std::endl;

    // std::vector<Klient>::iterator można zastąpić typem automatycznym auto

    // for(auto it = klienci.begin() ; it != klienci.end() ; ++it)
    //     ofs << *it << std::endl << std::endl;

    // pierwszy sposób
    // for(int i = 0 ; i < klienci.size() ; i++)
    //     ofs << klienci[i] << std::endl << std::endl;

    ofs.close();
    ofs2.close();

    return 0;
}