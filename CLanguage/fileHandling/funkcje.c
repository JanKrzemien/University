#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* własne pliki nagłówkowe includujemy w "" */
#include "osoba.h"

/* funkcja wczytuje osoby typu Osoba z pliku
 * zwraca: ilość wczytanych osób
 * przyjmuje: nazwę pliku i tablice na wczytane osoby
*/
int wczytaj(char nazwaPliku[], Osoba ludzie[])
{
  FILE *fin = fopen(nazwaPliku, "r");

  if(!fin)
  {
    printf("bład otwarcia pliku\n");
    exit(-1);
  }

  int licznik = 0;
  /* fscanf będzie zwracał ilość poprawnie przypisanych elementów
   * przy tablicach znakowych nie trzeba podawać & ponieważ tablica znaków jest wskażnikiem
   * przy intach i doublach jak poniżej już trzeba
   * fscanf == 4 ponieważ za każdym razem przypisujemy 4 elementy
  */
  while( fscanf(fin, "%s %s %d %lg", ludzie[licznik].imie, ludzie[licznik].nazwisko, &ludzie[licznik].wiek, &ludzie[licznik].pensja) == 4 )
  {
    licznik++;
  }

  return licznik;
}

/* funkcja wypisuje tablice zmiennych typu Osoba */
void wypisz(Osoba ludzie[], int n)
{
  int i;
  for(i = 0; i < n; i++)
  {
    printf("%-15s %-25s %3d %10.2f\n", ludzie[i].imie, ludzie[i].nazwisko, ludzie[i].wiek, ludzie[i].pensja);
  }
  return;
}

/* porównywanie do sortowania bąbelkowego porównującą po kolei nazwisko imie wiek i pensje */
int por_niwp(Osoba os1, Osoba os2)
{
  /* strcmp(string1, string2); porównuje dwa ciągi znaków */
  int n = strcmp(os1.nazwisko, os2.nazwisko);
  if(n)
  {
    return n;
  }

  n = strcmp(os1.imie, os2.imie);
  if(n)
  {
    return n;
  }

  n = os1.wiek - os2.wiek;
  if(n)
  {
    return n;
  }

  double m = os1.pensja - os2.pensja;
  if(m > 0)
  {
    return 1;
  } else if(m < 0)
  {
    return -1;
  }

  return 0;
}

/* funkcja podana jako argument jest wskaźnikiem, stąd *porownaj, ogólnie funkcje jako parametry zapisujemy jako
 * typ_zwracanych_danych (*nazwa)(typy argumentów)
 * funkcja ta z podaną jako argument funkcją por_niwp posortuje tablice typu Osoba najpierw po nazwisku,
 * następnie po imieniach, następnie po wieku, następnie po pensjach
 * */
void bSort(Osoba tab[], int n, int (*porownaj)(Osoba, Osoba)){
  Osoba pomocnicza;
  int k, i;
  for(k = n - 1; k > 0; k--)
  {
    for(i = 0; i < k; i++)
    {
      if(porownaj(tab[i], tab[i+1]) > 0)
      {
        pomocnicza = tab[i];
	tab[i] = tab[i+1];
	tab[i+1] = pomocnicza;
      }
    }
  }
  return;
}
