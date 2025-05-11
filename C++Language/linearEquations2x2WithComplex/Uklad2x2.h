#include <iostream>

template<class T>
class Uklad2x2
{
private:
    T a[2][2]; // wspolczynniki
    T b[2]; // wyrazy wolne
    T xy[2]; // xy po rozwiązaniu ukladu, xy[0] to x xy[1] to y
    int n; // ilość rozwiązań
public:
    Uklad2x2(T[2][2], T[2]);
    Uklad2x2() = default;

    void solve();
    void const print();
    void const check();
};

template<class T>
Uklad2x2<T>::Uklad2x2(T a_[2][2], T b_[2])
{
    a[0][0] = a_[0][0];
    a[0][1] = a_[0][1];
    a[1][0] = a_[1][0];
    a[1][1] = a_[1][1];

    b[0] = b_[0];
    b[1] = b_[1];
}

template<class T>
void Uklad2x2<T>::solve()
{
    T wyznacznikG = a[0][0]*a[1][1] - a[0][1]*a[1][0];

    T wyznacznikX = b[0]*a[1][1] - b[1]*a[0][1];

    T wyznacznikY = a[0][0]*b[1] - b[0]*a[1][0];

    if(wyznacznikG != T{}) // dwa rozwiązania
    {
        xy[0] = wyznacznikX/wyznacznikG;
        xy[1] = wyznacznikY/wyznacznikG;
        n = 1;
        return;
    }

    if(wyznacznikY == T{} && wyznacznikX == T{}) // nieskończenie wiele rozwiązań
    {
        n = 1000;
        return;
    }

    // brak rozwiązań
    // wyznacznik główny równy 0 i wyznaczniki x i y nie są równocześnie równe 0
    n = 0;
    return;
}

template<class T>
void const Uklad2x2<T>::print()
{
    if(n == 1)
    {
        std::cout << "dwa rozwiązania: " << xy[0] << ", " << xy[1] << std::endl;
        return;
    }
    if(n == 1000)
    {
        std::cout << "nieskończenie wiele rozwiązań" << std::endl;
        return;
    }

    std::cout << "brak rozwiązań" << std::endl;
    return;
}

template<class T>
void const Uklad2x2<T>::check()
{
    std::cout << "sprawdzenie dla równania 1: " << a[0][0]*xy[0] + a[0][1]*xy[1] << " = " << b[0] << std::endl;
    std::cout << "sprawdzenie dla równania 2: " << a[1][0]*xy[0] + a[1][1]*xy[1] << " = " << b[1] << std::endl;
    return;
}