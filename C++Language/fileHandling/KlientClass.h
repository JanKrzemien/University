#include <string>
#include <iostream>

class Klient
{
    std::string imie;
    std::string nazwisko;
    std::string adres;
    
    public:
    Klient(std::string i, std::string n, std::string a): imie{i}, nazwisko{n}, adres{a} {}
    Klient() = default;

    std::string getImie() const {return imie;}
    void setImie(std::string imie_) {imie = imie_;return;}
    std::string getNazwisko() const {return nazwisko;}
    void setNazwisko(std::string nazwisko_) {nazwisko = nazwisko_;return;}
    std::string getAdres() const {return adres;}
    void setAdres(std::string adres_) {adres = adres_;return;}
};

std::ostream& operator<<(std::ostream& os, const Klient& k)
{
    os << k.getImie() << " " << k.getNazwisko() << std::endl << k.getAdres();
    return os;
}

std::istream& operator>>(std::istream& is, Klient& k)
{
    std::string imie, nazwisko, adres;

    is >> imie >> nazwisko;
    is.ignore(1);
    getline(is, adres);

    k.setImie(imie);
    k.setNazwisko(nazwisko);
    k.setAdres(adres);

    return is;
}