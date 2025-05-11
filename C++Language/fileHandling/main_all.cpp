#include <iostream>
#include <vector>
#include <fstream>
#include "ZamowienieClass.h"
#include <algorithm>

int main()
{
    std::vector<Zamowienie> zamow{};
    Zamowienie zam{};

    std::ifstream fin1{"in1.txt"};
    std::ifstream fin2{"in2.txt"};
    std::ofstream fout{"out4.txt"};

    if(!fout || !fin1 || !fin2)
    {
        std::cerr << "file error";
        return -1;
    }

    while(fin1 >> zam)
        // fout << zam << std::endl;
        zamow.push_back(zam);

    while(fin2 >> zam)
        // fout << zam << std::endl;
        zamow.push_back(zam);


    // for(int i = 0; i < zamow.size(); i++)
    // {
    //     fout << zamow[i] << std::endl;
    // }

    // for( std::vector<Zamowienie>::iterator it = zamow.begin(); it != zamow.end(); ++it)
    // {
    //     fout << *it << std::endl;
    // }

    std::for_each(zamow.begin(), zamow.end(), [&fout](Zamowienie z){fout << z << std::endl;});


    fin1.close();
    fin2.close();
    fout.close();

    return 0;
}