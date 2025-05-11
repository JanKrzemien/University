#include "RkwSzablon.h"

#include <complex>

int main()
{
    ::complex a1{}, b1{}, c1{};
    std::complex<long double> a2{}, b2{}, c2{};
    
    std::cout << "podaj liczby dla ::complex" << std::endl;
    std::cin >> a1 >> b1 >> c1;

    std::cout << "podaj liczby dla std::complex" << std::endl;
    std::cin >> a2 >> b2 >> c2;

    Rkw<::complex> rkw1{a1,b1,c1};

    Rkw<std::complex<long double>> rkw2{a2,b2,c2};

    rkw1.solve();
    rkw1.print();
    rkw1.check();

    rkw2.solve();
    rkw2.print();
    rkw2.check();

    return 0;
}
