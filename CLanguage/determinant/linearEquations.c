#include <stdio.h>
#include <stdlib.h>

double Determinant(int n, double a[][n]);
void kopiujTablice(int n, double a[][n], double b[][n]);
void podmienKolumne(int n, double a[][n], double b[n], int indexKolumny);

int main()
{
  int n, nrSerii;
  printf("podaj n: \n");
  scanf("%d", &n);
  printf("podaj numer seri: \n");
  scanf("%d", &nrSerii);

  double uklad[n][n];
  
  srand(nrSerii);
  int i, j;
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < n; j++)
    {
      uklad[i][j] = (double)rand()/RAND_MAX;
    }
  }

  double rozwiazania[n];
  for(i = 0; i < n; i++)
  {
    rozwiazania[i] = (double)rand()/RAND_MAX;
  }

  double wyznaczniki[n];
  double kolumnaTemp[n];
  double kopiaUklad[n][n];
  double wspolczynniki[n];

  for(i = 0; i < n; i++)
  {
    kopiujTablice(n, uklad, kopiaUklad);

    for(j = 0; j < n; j++)
    {
      kolumnaTemp[j] = kopiaUklad[j][i];
    }

    podmienKolumne(n, kopiaUklad, rozwiazania, i);

    wyznaczniki[i] = Determinant(n, kopiaUklad);
  }

  double wyznacznikG = Determinant(n, uklad);

  for(i = 0; i < n; i++)
  {
    wspolczynniki[i] = wyznaczniki[i]/wyznacznikG;
    printf("x%d = %lg\n", i, wspolczynniki[i]);
  }

  printf("sprawdzenie: \n");
  double spr;
  for(i = 0; i < n; i++)
  {
    spr = 0.0;
    for(j = 0; j < n; j++)
    {
      spr += uklad[i][j]*wspolczynniki[j];
    }
    printf("lewa strona: %lg | prawa strona: %lg | dokladnosc: %lg\n", spr, rozwiazania[i], spr-rozwiazania[i]);
  }

}

void podmienKolumne(int n, double a[][n], double r[n], int indexKolumny)
{
  int i;
  for(i = 0; i < n; i++)
  {
    a[i][indexKolumny] = r[i];
  }
}

void kopiujTablice(int n, double a[n][n], double b[n][n])
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
		b[i][j]=a[i][j];
		}
	}
}
