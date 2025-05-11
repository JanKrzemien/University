#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

int main()
{
    std::map<std::string, int> words{};

    std::ifstream ifs{"macbeth.txt"};

    std::string s{};

    while(ifs >> s)
    {
        ++words[s];
    }

    std::cout << "ilosc elementow w mapie: " << words.size() << std::endl;

    std::multimap<int, std::string> multi_words{};

    for(std::map<std::string, int>::iterator it = words.begin(); it != words.end(); it++)
    {
        multi_words.insert( std::pair<int, std::string>{it->second, it->first} );
    }

    std::cout << "ilosc elementow w multimapie: " << multi_words.size() << std::endl;

    for(std::multimap<int, std::string>::reverse_iterator it = multi_words.rbegin(); std::distance(multi_words.rbegin(), it) < 10; it++ )
    {
        std::cout << it->second << " " << it->first << std::endl;
    }

    ifs.close();
    return 0;
}