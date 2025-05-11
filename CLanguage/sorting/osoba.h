/* na dwa sposoby typ złożony
 * struktura i inna nazwa tego typu
*/

/* definicja struktury jest definicją typu */
/* stworzenie struktury */
struct osoba
{
  char imie[15];
  char nazwisko[25];
  int wiek;
  double pensja;
};

/* zdefiniowanie typu, nadanie strukturze nowej nazwy */
typedef struct osoba Osoba;

/* zmienne możemy definiować jako
 * struct osoba osoba1;
 * Osoba osoba2;
 * */
