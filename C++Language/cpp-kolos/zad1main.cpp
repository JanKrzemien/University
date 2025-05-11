#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>

#include "Osoba.h"

int main()
{
    std::ifstream fsos1{"osoby1.txt"};
    std::ifstream fsos2{"osoby2.txt"};

    std::vector<Osoba> os1{};
    std::vector<Osoba> os2{};


    std::istream_iterator<Osoba> iis1{fsos1};
    std::istream_iterator<Osoba> iis2{fsos2};
    std::istream_iterator<Osoba> eos{};

    std::back_insert_iterator< std::vector<Osoba> > back_it1{os1};
    std::back_insert_iterator< std::vector<Osoba> > back_it2{os2};

    std::copy(iis1, eos, back_it1);
    std::copy(iis2, eos, back_it2);

    std::sort(os1.begin(), os1.end(), [&](Osoba o1, Osoba o2)->bool {return o1 < o2;});
    std::sort(os2.begin(), os2.end(), [&](Osoba o1, Osoba o2)->bool {return o1 < o2;});

    //std::for_each(os1.begin(), os1.end(), [&](Osoba os){std::cout << os << std::endl;});
    //std::cout << std::endl;
    //std::for_each(os2.begin(), os2.end(), [&](Osoba os){std::cout << os << std::endl;});

    // ==================================
    std::vector<Osoba> vec1{os1.size() + os2.size()};

    std::vector<Osoba>::iterator set_union_it = std::set_union(os1.begin(), os1.end(), os2.begin(), os2.end(), vec1.begin());
    vec1.resize(std::distance(vec1.begin(), set_union_it));

    //std::for_each(vec1.begin(), vec1.end(), [&](Osoba os){std::cout << os << std::endl;});
    std::cout << "po set_union rozmiar to " << vec1.size() << std::endl;

    // ================================

    // ================================

    std::vector<Osoba> vec2{os1.size() + os2.size()};
    std::merge(os1.begin(), os1.end(),os2.begin(), os2.end(), vec2.begin());
    std::vector<Osoba>::iterator merge_it = std::unique(vec2.begin(), vec2.end());
    vec2.resize(std::distance(vec2.begin(), merge_it));
    //std::for_each(vec2.begin(), vec2.end(), [&](Osoba os){std::cout << os << std::endl;});
    std::cout << "po merge + unique rozmiar to " << vec2.size() << std::endl;

    // ================================

    // ================================

    std::vector<Osoba> vec3{};
    vec3.insert(vec3.begin(), os1.begin(), os1.end());
    vec3.insert(vec3.begin() + 5, os2.begin(), os2.end());
    std::sort(vec3.begin(), vec3.end(), [&](Osoba o1, Osoba o2)->bool {return o1 < o2;});
    std::vector<Osoba>::iterator insert_it = std::unique(vec3.begin(), vec3.end());
    vec3.resize(std::distance(vec3.begin(), insert_it));
    //std::for_each(vec3.begin(), vec3.end(), [&](Osoba os){std::cout << os << std::endl;});
    std::cout << "po insert + unique rozmiar to " << vec3.size() << std::endl;

    // ================================

    std::ofstream out1{"out1.txt"};
    std::ofstream out2{"out2.txt"};
    std::ofstream out3{"out3.txt"};
    std::ostream_iterator<Osoba> oit1{out1, "\n"};
    std::ostream_iterator<Osoba> oit2{out2, "\n"};
    std::ostream_iterator<Osoba> oit3{out3, "\n"};

    std::copy(vec1.begin(), vec1.end(), oit1);
    std::copy(vec2.begin(), vec2.end(), oit2);
    std::copy(vec3.begin(), vec3.end(), oit3);

    out1.close();
    out2.close();
    out3.close();
    fsos1.close();
    fsos2.close();

    return 0;
}