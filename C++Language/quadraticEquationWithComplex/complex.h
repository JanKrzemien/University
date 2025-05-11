#include <cmath>
#include <iostream>
#include <string>

class complex
{
//private:
// domyślnie jest private
    double re, im;
public:
    // konstuktory
    /* konstruktorów może być więcej niż jeden
    *  w zależności od ilości podanych argumentów zostanie
    *  użyty odpowiedni kontruktor
    */
    // po dwukropku następuje przypisanie do zmiennych re i im wartości paramentrów
    complex(double r, double i) : re{r}, im{i} {};
    complex(double r) : re{r}, im{0} {};
    complex() : re{0}, im{0} {};

    // w zależności od ilości argumentów zostanie użyta taka funkcja
    double real() const { return re; }
    void real(double d) { re=d; }
    double imag() const { return im; }
    void imag(double d) { im=d; }

    // definicja operatorów += oraz -=, zwracana jest referencja
    complex& operator+=(complex z) {re+=z.re, im+=z.im; return *this;}
    complex& operator-=(complex z) {re-=z.re, im-=z.im; return *this;}

    // prototyp funkcji operatorów
    complex& operator*=(complex z);
    complex& operator/=(complex z);


};

complex& complex::operator*=(complex z)
{
    double a, b;
    a = (re*z.re) - (im*z.im);
    b = (re*z.im) + (im*z.re);
    re = a;
    im = b;
    return *this;
}

complex& complex::operator/=(complex z)
{
    double a,b;
    a = (re*z.re + im*z.im)/(z.re*z.re + z.im*z.im);
    b = (im*z.re - re*z.im)/(z.re*z.re + z.im*z.im);
    re = a;
    im = b;
    return *this;
}

complex operator+(complex a, complex b) {return a+=b;}
complex operator*(complex a, complex b) {return a*=b;}
complex operator-(complex a, complex b) {return a-=b;}
// return {,} wywołuje konstruktor dla dwóch argumentów
complex operator-(complex a) {return{-a.real(), -a.imag()};}
complex operator/(complex a, complex b) {return a/=b;}

complex sqrt(complex z)
{
    double u,v;

    double a = z.real();
    double b = z.imag();
 
    u = sqrt((a + sqrt(a*a + b*b))/2.0);
    if(u != 0.0)
    {
        v = b/(2.0*u);
    } else
    {
        v = sqrt(-a);
    }

    return complex{u,v};
}

std::ostream& operator<<(std::ostream& os, complex z)
{
    os << '(' << z.real() << ',' << z.imag() << ')';
    return os;    
}

std::istream& operator>>(std::istream& is, complex& z) // wskaźnik żeby można było zmieniać z a nie jego kopię
{
    double a, b;
    char znak[3];
    is >> znak[0] >> a >> znak[1] >> b >> znak[3];

    if(znak[0] != '(' || znak[1] != ',' || znak[2] != ')')
    {
        // strumienie błędu cerr oraz clog
        std::cerr << "błędny format wpisywanej liczby zespolonej,\n poprawny format to (real,imag).\n";
        return is;
    }

    z.real(a);
    z.imag(b);

    return is;
}