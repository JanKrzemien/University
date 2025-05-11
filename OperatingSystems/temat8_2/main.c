/*================================================================
 * program tworzy wątki według ilości podanej przez argumenty
 * wywołania programu i przekazuje każdemu oddzielną tablice.
 * za pomoca algorytmu piekarni kontrolowany jest dostep do sekcji krytycznej.
 * każdy wątek w swojej sekcji krytycznej zwiększa globalny licznik o 1,
 * na koniec jest sprawdzenie czy licznik jest równy oczekiwanej wartości.
 * ===============================================================
 *  Autor: Jan Krzemień				Data: 11.06.2023
 *  ==============================================================
 */

#define _REENTRANT

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#include "obsluga_watkow.h"

#define LEWY_MARGIN 10
#define GORNY_MARGIN 5
#define ODSTEP_MIEDZY_WIERSZAMI 2

// wskaźniki globalne do tablicy z numerami, tablicay z wartościami bool
volatile int * numer_ptr = NULL;
volatile bool * wybieranie_ptr = NULL;

// globalna zmienna licznikowa
int licznik = 0;

// wykonywany wątek
void * watek(void * ptr)
{
    Args * args = (Args*)ptr; // rzutowanie wskaznika typu void na strukture w ktorej sa argumenty
    int i, j, krytyczny_licznik, max_val;
    int losowa_ilosc;
    for(i = 0; i < args->ile_sekcji; i++)
    {
        printf("\033[%d;%dH\033[2K", GORNY_MARGIN + ODSTEP_MIEDZY_WIERSZAMI*args->num, LEWY_MARGIN);
        printf("watek %d | sekcja prywatna %d\n", args->num, i + 1);

	// rozpocznij wybieranie największej wartości z tablicy
	wybieranie_ptr[args->num] = true;

	// wybierz największą wartość z tablicy
	max_val = numer_ptr[0];
	for(j = 1; j < args->ile_watkow; j++)
	{
	    if( max_val < numer_ptr[j] ) max_val = numer_ptr[j];
	}
	numer_ptr[args->num] = max_val + 1;

	// zakończ wybieranie
	wybieranie_ptr[args->num] = false;

	//jeśli masz wątek nie ma najmniejszego numeru lub jeśli nie wszytskie wątki wybrały numer, czekaj
	for( j = 0; j < args->ile_watkow; j++ )
	{
	    while( wybieranie_ptr[j] );
	    while( numer_ptr[j] != 0 && (numer_ptr[j],j) < (numer_ptr[args->num], args->num) );
	}
	
        // koniec sekcji prywatnej   
	// ==========================================================
        // początek sekcji krytycznej

	// przypisanie licznikowi prywatnemu wartości licznika globalnego
        krytyczny_licznik = licznik;

	
	// poprawne wyświetlanie procesu w sekcji krytycznej
	// pętla istnieje by wymazywać linijki z poprzednich sekcji krytycznych
	for(j = 0; j < args->ile_watkow; j++)
	{
	    // ustaw odpowiednią pozycje w terminalu
	    printf("\033[%d;%dH\033[2K", GORNY_MARGIN + ODSTEP_MIEDZY_WIERSZAMI*(j + 1) + 1, 2*LEWY_MARGIN);
	    if( j+1 == args->num ) // jeżeli to aktualnie wyświetlana sekcja krytyczna wypisz co należy
                printf("watek %d | numer sekcji krytycznej %d | licznik: %d\n", args->num, i + 1, licznik);
	    else // w przeciwnym wypadku wpisz białe znaki w celu wymazania tego co było w danej linicje
	        printf("                                                   \n");
	}

	// zwiększenie licznik prywatnego
        krytyczny_licznik++;
	
	// losowe uśpienie w trakcie sekcji krytycznej
    losowa_ilosc = rand()%2 + 1;
    sleep(losowa_ilosc);

	// przypisanie zwiększonej o 1 wartości licznikowi globalenemu 
        licznik = krytyczny_licznik;

	numer_ptr[args->num] = 0;
        // koniec sekcji krytycznej
        // ===============================================================
        // początek sekcji prywatnej


	// losowe uśpienie w trakcie sekcji prywatnej
    losowa_ilosc = rand()%2 + 1;
    sleep(losowa_ilosc);

    }

    printf("\033[%d;%dH\033[2K", GORNY_MARGIN + ODSTEP_MIEDZY_WIERSZAMI*args->num, LEWY_MARGIN);
    printf("watek %d | sekcja prywatna %d | zakonczono\n",args->num, i);

    return NULL;
}

int main(int argc, char * argv[])
{
    // oczekiwano 3 argumentów: nazwy obecnie wykonywanego programu, ilości wątków, ilości sekcji krytycznych
    if( argc != 3 )
    {
	printf("error: niewlasciwa ilosc argumentow\n");
	exit(1);
    }

    // zamiana char * -> int ilości sekcji krytycznych i ilości wątków
    int sekcji_kryt , watkow;
    int correctly_assigned = sscanf(argv[1], "%d", &sekcji_kryt);
    if( correctly_assigned != 1 )
    {
	perror("sscanf error podczas zamiany char * -> int ilości sekcji krytycznych");
	exit(2);
    }
    correctly_assigned = sscanf(argv[2], "%d", &watkow);
    if( correctly_assigned != 1 )
    {
	perror("sscanf error podczas zamiany char * -> int ilości watkow");
	exit(3);
    }

    // zapoczatkowanie generatora liczb pseudolosowych
    srand(time(0));

    // stwórz tablice numer i wybieranie z domyślnymi wartościami
    volatile int numer[watkow];
    volatile bool wybieranie[watkow];
    int j = 0;
    for(j = 0; j < watkow; j++)
    {
	numer[j] = 0;
	wybieranie[j] = false;
    }
    // globalne wskaźniki wskazują na te tablice
    numer_ptr = numer;
    wybieranie_ptr = wybieranie;


    int i;
    pthread_t thread_id[watkow]; // tablica na id watkow

    Args arg[watkow]; // tablica na struktury ktore beda przekazywane do watkow jako argumenty

    //printf("\033[36m");

    // zaczekanie az uzytkownik rozpocznie program
    printf("\033[5;7m");     // Wlacz migotanie i odwrotny obraz
    printf("    ---- Nacisnij klawisz [Enter], aby wystartowac! ----   ");
    getchar();
    printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania
    // Wyczysc ekran
    if (system("clear") == -1) {
        perror("Error in call to system() function");
        exit(EXIT_FAILURE);
    }

    // utworzenie watkow z przekazaniem argumentow przez tablice
    for(i = 0; i < watkow; i++)
    {
	arg[i].ile_sekcji = sekcji_kryt;
	arg[i].ile_watkow = watkow;
	arg[i].num = i + 1;
	if( ( thread_id[i] = create_thread(watek, &(arg[i])) ) == -1 ) exit(7);
	// wypisanie id wątku i jego numer
	printf("\033[%d;0H\033[2K", i+2);
	printf("stworzono watek o id %ld i numerze %d\n", thread_id[i], i+1);
    }
    // zaczekanie na zakonczenie watkow przed koncem programu
    for(i = 0; i < watkow; i++)
	if( join_thread(thread_id[i]) == -1 ) exit(8);
   
    printf("\033[%d;0H\033[2K", GORNY_MARGIN + watkow*(ODSTEP_MIEDZY_WIERSZAMI+1));
    printf("mialo miejsce %d sekcji krytycznych; oczekiwano %d\n", licznik, watkow*sekcji_kryt);

    printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania
}
