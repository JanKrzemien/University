#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char Osoba[2][18];

void wypisz(int, Osoba[]);
int wczytaj(Osoba[50], char[]);
int compar(const void *, const void *);

int main()
{
  Osoba osoby[50];
  int n = wczytaj(osoby, "osoby");
  wypisz(n, osoby);

  qsort(osoby, n, sizeof(Osoba), compar);

  printf("\n");

  wypisz(n, osoby);
}

int wczytaj(Osoba osoby[50], char plik[])
{
  int licznik = 0;
  FILE *fin = fopen(plik, "r");
  while(fscanf(fin, "%s %s", osoby[licznik][0], osoby[licznik][1]) == 2)
  {
    licznik++;
  }

  fclose(fin);
  return licznik;
}

void wypisz(int n, Osoba osoby[n])
{
  int i;
  for(i = 0; i < n; i++)
  {
    printf("%-18s %-18s\n", osoby[i][0], osoby[i][1]);
  }
}

int compar(const void * o1, const void * o2)
{
  Osoba * os1 = (Osoba *)o1;
  Osoba * os2 = (Osoba *)o2;

  const char * os1I = (const char *) os1[0];
  const char * os2I = (const char *) os2[0];
  const char * os1N = (const char *) os1[1];
  const char * os2N = (const char *) os2[1];

  if(strcmp(os1I, os2I))
	  return strcmp(os1I, os2I);
  return -strcmp(os1N, os2N);
}
