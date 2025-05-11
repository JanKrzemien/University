
#include "complex.h"

class Rkw
{
private:
    complex a,b,c,x1,x2;
public:
    Rkw(complex a_, complex b_ = 0, complex c_ = 0): a{a_}, b{b_}, c{c_} {}

    void solve();
    void const print();
    void const check();
};

void Rkw::solve()
{
    complex deltaSqrt = sqrt(b*b - 4.0*a*c);

    x1 = (-b - deltaSqrt)/(2.0*a);
    x2 = (-b + deltaSqrt)/(2.0*a);

    return;
}

void const Rkw::print()
{
    std::cout << x1 << " " << x2 << std::endl;
    return;
}

void const Rkw::check()
{
    std::cout << "sprawdzenie dla x1: " << x1*x1*a + x1*b + c << std::endl;
    std::cout << "sprawdzenie dla x2: " << x2*x2*a + x2*b + c << std::endl;
    return;
}