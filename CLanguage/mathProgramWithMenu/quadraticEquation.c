#include <stdio.h>

// funkcja rkw znajduje się w pliku funkcjaRKW.c
// kompilowac za pomoca gcc kwadratoweFunkcje.c funkcjaRKW.c -lm

/*
 * prototyp funkcji rkw służącej do znajdowania pierwiastków funkcji kwadratowej
 * funkcja zwraca liczbę całkowitą pierwiastków równania kwadratowego 0 lub 1 lub 2
 * double* oznacza wskaźnik, przy wywołaniu funkcji przekazujemy do funkcji adres zmiennej jako parametr
 */
int rkw(double, double, double, double*, double*);

int mainRowKwadratowe()
{
  double a,b,c,x1,x2;

  printf("podaj rownanie w postaci\nax2+bx+c\n");
  scanf("%lgx2%lgx%lg",&a,&b,&c);
  int n = rkw(a,b,c,&x1,&x2);

  if(n == 0)
  {
    printf("brak pierwiastkow rownania\n");
    return 0;
  }
  if(n == 1)
  {
    printf("jeden pierwiastek rownania x1 = %g\n", x1);
    return 0;
  }

  printf("dwa pierwiastki rownania x1 = %g i x2 = %g\n", x1, x2);
  return 0;
}
