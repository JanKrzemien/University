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

    std::string line, word;
    int i;
    while(getline(ifs, line))
    {
        if(line == "")
            continue;
        
        std::istringstream ss{line};
        while(ss >> word)
        {
            // if(word.size() == 1)
            // {
            //     if( words.find(word) == words.end() )
            //         words.insert( std::pair<std::string, int>(word, 1) );
            //     else
            //         words.at(word)++;
            //     continue;
            // }
            // i = 0;
            // while( !( ( (int)word[i] >= 65 && (int)word[i] <= 90 ) || ( (int)word[i] >= 97 && (int)word[i] <= 122 ) ) )
            //         i++;
            // if(i >= word.size())
            //     continue;
            // word = word.substr(i, word.size());

            // i = 0;
            // while( !( ( (int)word[word.size() - i] >= 65 && (int)word[word.size() - i] <= 90 ) || ( (int)word[word.size() - i] >= 97 && (int)word[word.size() - i] <= 122 ) ) )
            //         i++;
            // if(i >= word.size())
            //     continue;
            // word = word.substr(0, word.size() - i + 1);

            if( words.find(word) == words.end() )
                words.insert( std::pair<std::string, int>(word, 1) );
            else
                words.at(word)++;
        }
        

    }

    std::vector< std::pair<std::string, int> > vec{};

    for (auto x : words)
    {
        vec.push_back(x);
    }

    std::sort(vec.begin(), vec.end(), [&](std::pair<std::string, int> w1, std::pair<std::string, int> w2)->bool{return w2.second < w1.second;});

    i = 0;
    for(auto x : vec)
    {
        if(i == 10)
        {
            break;
        }
        std::cout << x.first << " " << x.second << std::endl;
        i++;
    }

    ifs.close();
    return 0;
}