#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
#include <iostream>

#include "ZamowienieClass.h"

int main()
{
    std::ifstream fin1{"in1.txt"};
    std::ifstream fin2{"in2.txt"};
    std::istream_iterator<Zamowienie> it1{fin1};
    std::istream_iterator<Zamowienie> it2{fin2};
    std::istream_iterator<Zamowienie> eos;
    std::vector<Zamowienie> vec1{};
    std::vector<Zamowienie> vec2{};

    // kopiowanie z pliku do wektora
    std::copy(it1, eos, std::back_inserter(vec1));
    std::copy(it2, eos, std::back_inserter(vec2));


    // wypisanie wartości wektora bk
    // std::for_each(bk.begin(), bk.end(), [&](Book b){std::cout << b << std::endl;});

    std::ofstream fout{"zakupy1.txt"};
    std::ofstream fout2{"zakupy2.txt"};

    // kopiowanie z wektora do pliku
    // std::ostream_iterator<Zamowienie> oit{fout, "\n\n"};
    // std::copy(vec.begin(), vec.end(), std::ostream_iterator<Zamowienie>{fout, "\n\n"});

    // wyłuskanie książek i książki do pliku
    std::vector<Book> bk1{};
    std::vector<Book> bk2{};

    for(auto &x : vec1)
    {
        // żeby to zakomentowane zadziałało zmień w klasie Zamowienie na std::vector<Book> get_ksiazki() const
        // std::vector<Book> ks{x.get_ksiazki()};
        // std::copy(ks.begin(), ks.end(), std::back_inserter(bk));
        std::copy(x.get_ksiazki().begin(), x.get_ksiazki().end(), std::back_inserter(bk1));
    }
    for(auto &x : vec2)
    {
        // żeby to zakomentowane zadziałało zmień w klasie Zamowienie na std::vector<Book> get_ksiazki() const
        // std::vector<Book> ks{x.get_ksiazki()};
        // std::copy(ks.begin(), ks.end(), std::back_inserter(bk));
        std::copy(x.get_ksiazki().begin(), x.get_ksiazki().end(), std::back_inserter(bk2));

    }

    std::cout << "w in1 jest " << bk1.size() << " książek" << std::endl;
    std::cout << "w in2 jest " << bk2.size() << " książek" << std::endl;

    std::ostream_iterator<Book> bit{fout, "\n\n"};
    std::ostream_iterator<Book> bit2{fout2, "\n\n"};
    std::copy(bk1.begin(), bk1.end(), bit);
    std::copy(bk2.begin(), bk2.end(), bit2);

    fin1.close();
    fin2.close();
    fout.close();
}