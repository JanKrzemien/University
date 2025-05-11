#include <string>
#include <vector>
#include <sstream> // string stream
#include "KlientClass.h"
#include "DateClass.h"
#include <iostream>

class Book
{
    private:
        std::string title;
        int amount;
        double price;
    public:
        Book() = default;

        bool operator<(const Book& bk)
        {
            return this->title < bk.title;
        }
        bool operator==(const Book& bk)
        {
            return this->title == bk.title;
        }

        friend std::ostream& operator<<( std::ostream& os, const Book& b)
        {
            os << b.title << "| " << b.price << " | " << b.amount;
            return os;
        }

        friend std::istream& operator>>(std::istream& is, Book& b)
        {
            getline(is, b.title, '|');
            is >> b.price;
            char znak;
            is >> znak;
            is >> b.amount;
            
            is.ignore(1);

            return is;
        }
};

class Zamowienie
{
    private:
        Klient klient;
        std::vector<Book> ksiazki;
        Date data;
    
    public:
    
    std::vector<Book>& get_ksiazki()
    {
        return ksiazki;
    }

    friend std::istream& operator>>(std::istream& is, Zamowienie& z)
    {
        is >> z.klient;
        is >> z.data;

        is.ignore(1);

        z.ksiazki.clear();

        Book ks{};
        std::string line;

        while( getline(is, line) && line != "" )
        {
            // utworzenie ze stringa strumienia i działanie na nim jak na strumieniu
            std::istringstream iss{line};
            iss >> ks;
            z.ksiazki.push_back(ks);
        }

        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Zamowienie& z)
    {
        os << z.klient << std::endl;

        os << z.data << std::endl;

        for(int i = 0; i < z.ksiazki.size(); i++)
            os << z.ksiazki[i];

        // for(std::vector<Book>::iterator it = z.ksiazki.begin(); it != z.ksiazki.end(); ++it)
        //     os << *it << std::endl;

        return os;
    }
};