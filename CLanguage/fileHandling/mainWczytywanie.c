/* kompiluj za pomocą gcc mainWczytywanie.c funkcje.c osoba.h */
#include <stdio.h>

/* własne pliki nagłówkowe includujemy w "" */
#include "osoba.h"

int wczytaj(char[], Osoba[]);
void wypisz(Osoba[], int);
int por_niwp(Osoba, Osoba);
/* przekazujemy do funkcji funkcję jako jeden z argumentów a więc przekazujemy wskaźnik do tej funkcji
 * i musimy podać typy argumentów jakie przyjmuje */
void bSort(Osoba[], int, int (*)(Osoba, Osoba));

int main()
{
  char nazwaPliku[30] = {"ludzieDB"};
  Osoba ludzie[20];

  int wczytanoLinijek = wczytaj(nazwaPliku, ludzie);

  printf("poprawnie wczytanych %d osób\n", wczytanoLinijek);

  bSort(ludzie, wczytanoLinijek, por_niwp);

  wypisz(ludzie, wczytanoLinijek);
}
