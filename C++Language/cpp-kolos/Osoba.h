#include <iostream>
#include <string>

// imie1 < imie2, if imie1 == imie2 then wiek1 < wiek2

class Osoba
{
    private:
        std::string imie;
        int wiek;
    public:

        bool operator<(Osoba os2)
        {
            if(imie != os2.imie)
            {
                return imie < os2.imie;
            }
            return wiek < os2.wiek;
        }
        bool operator==(Osoba os2)
        {
            if(imie != os2.imie)
            {
                return false;
            }
            if(wiek != os2.wiek)
            {
                return false;
            }
            return true;
        }

        friend std::istream& operator>>(std::istream &is, Osoba& o)
        {

            is >> o.imie >> o.wiek;

            //o.imie = o.imie.substr(0, o.imie.size() - 1);

            return is;
        }

        friend std::ostream& operator<<(std::ostream &os, const Osoba& o)
        {
            os << o.imie << " " << o.wiek;

            return os;
        }
};