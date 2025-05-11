#include <math.h>

double silnia(unsigned n)
{
  if(n == 0) return 1.0;

  double silnia = 1;
  while(n > 1)
  {
    silnia *= n;
    n--;
  }
  
  return silnia;
}

double sn(unsigned n, unsigned k)
{
  if(k == 0 || k == n) return 1.0;

  return (silnia(n)) / (silnia(k)*silnia(n - k));
}

double fL(double a, double b, int n)
{
  double sumaL = a + b;
  sumaL = pow(sumaL, n);
  return sumaL;
}

double fR(double a, double b, int n)
{
  int k = 0;
  double sumaR = 0;
  while(k <= n)
  {
    sumaR += sn(n,k)*pow(a, n-k)*pow(b,k);
    k++;
  }
  return sumaR;
}
