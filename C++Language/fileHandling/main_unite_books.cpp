#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>

#include "ZamowienieClass.h"

int main()
{
    std::ifstream ifs1{"in1 copy.txt"};
    std::ifstream ifs2{"in2 copy.txt"};

    std::vector<Book> bks1{};
    std::vector<Book> bks2{};
    Book bk{};

    std::istream_iterator<Book> it1{ifs1};
    std::istream_iterator<Book> it2{ifs2};
    std::istream_iterator<Book> eos{};

    std::back_insert_iterator< std::vector<Book> > back_it1{bks1};
    std::back_insert_iterator< std::vector<Book> > back_it2{bks2};
    std::copy(it1, eos, back_it1);
    std::copy(it2, eos, back_it2);
    
    ifs1.close();
    ifs2.close();

    std::sort(bks1.begin(), bks1.end());

    std::sort(bks2.begin(), bks2.end());

    std::vector<Book> merged_books{};
    merged_books.resize(bks1.size() + bks2.size());

    //std::vector<Book>::iterator it = std::set_union(bks1.begin(), bks1.end(), bks2.begin(), bks2.end(), merged_books.begin());
    std::merge(bks1.begin(), bks1.end(), bks2.begin(), bks2.end(), merged_books.begin());
    //merged_books.resize(std::distance(merged_books.begin(), it));

    std::sort(merged_books.begin(), merged_books.end());

    std::vector<Book>::iterator it = std::unique(merged_books.begin(), merged_books.end());
    merged_books.resize(std::distance(merged_books.begin(), it));

    for(auto x : merged_books)
    {
        std::cout << x << std::endl;
    }

    std::cout << "książek w pliku: " << merged_books.size() << std::endl;

    std::ofstream ofs{"ksiazki.txt"};
    std::ostream_iterator<Book> oit{ofs, ""};

    std::copy(merged_books.begin(), merged_books.end(), oit);

    ofs.close();
}