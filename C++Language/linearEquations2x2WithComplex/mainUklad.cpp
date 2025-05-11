#include "Uklad2x2.h"
#include "complexUklad.h"
#include "Rational.h"

#define TYPE Rational

int main()
{

    TYPE a[2][2] = {{{1,2},{3,4}},{{5,6},{7,8}}};
    TYPE b[2] = {{1,2},{3,4}};
    Uklad2x2<TYPE> ukl{a,b};

    ukl.solve();
    ukl.check();
    ukl.print();

    return 0;
}