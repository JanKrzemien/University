// kompiluj komendą gcc sumaAB.c funkcje.c -lm
#include <stdio.h>

double fL(double, double, int);
double fR(double, double, int);
double silnia(unsigned);
double sn(unsigned, unsigned); //sumbol newtona

int mainSumaAB()
{
  double a,b;
  int n;
  
  printf("podaj a, b, n: ");
  scanf("%lg %lg %d", &a, &b, &n);

  double wynikL = fL(a, b, n);
  double wynikR = fR(a, b, n);

  if(wynikL > wynikR)
  {
    printf("wynik po lewej stronie jest wiekszy\n");
    printf("roznica wynikow wynosi: %g\n", (wynikL - wynikR));
    return 0;
  }
  if(wynikL < wynikR)
  {
    printf("wynik po prawej stronie jest wiekszy\n");
    printf("roznica wynikow wynosi: %g\n", (wynikR - wynikL));
    return 0;
  }

  printf("wyniki sa sobie rowne, wynik = %g\n", wynikL);

  return 0;
}

