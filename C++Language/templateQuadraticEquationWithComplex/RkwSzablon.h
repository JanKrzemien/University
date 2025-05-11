
#include "complexKopia.h"

template <class T> // to samo co <typename T>
class Rkw
{
private:
    T a,b,c,x1,x2;
public:
    Rkw(T a_, T b_ = T{}, T c_ = T{}): a{a_}, b{b_}, c{c_} {}

    void solve();
    void const print();
    void const check();
};

template <class T>
void Rkw<T>::solve()
{
    T deltaSqrt = sqrt(b*b - T{4}*a*c);

    x1 = (-b - deltaSqrt)/(T{2}*a);
    x2 = (-b + deltaSqrt)/(T{2}*a);

    return;
}

template <class T>
void const Rkw<T>::print()
{
    std::cout << x1 << " " << x2 << std::endl;
    return;
}

template <class T>
void const Rkw<T>::check()
{
    std::cout << "sprawdzenie dla x1: " << x1*x1*a + x1*b + c << std::endl;
    std::cout << "sprawdzenie dla x2: " << x2*x2*a + x2*b + c << std::endl;
    return;
}