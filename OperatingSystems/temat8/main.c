/*================================================================
 * program tworzy mutex na który wskazuje globalna zmienna wskaźnikowa,
 * nastepnie tworzy wątki według ilości podanej przez argumenty
 * wywołania programu i przekazuje każdemu oddzielną tablice,
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

#include "obsluga_mutexow.h"
#include "obsluga_watkow.h"

#define LEWY_MARGIN 10
#define GORNY_MARGIN 5
#define ODSTEP_MIEDZY_WIERSZAMI 2

// globalna zmienna licznikowa
int licznik = 0;

// globalna zmienna wskaźnikowa mutexa, istnieje aby dało się usunąć mutex w funkcji zarejestrowanej przez atexit
pthread_mutex_t * mutex_ptr = NULL;

// wykonywany wątek
void * watek(void * ptr)
{
    Args * args = (Args*)ptr; // rzutowanie wskaznika typu void na strukture w ktorej sa argumenty
    int i, j, losowa_ilosc, prywatny_licznik;
    for(i = 0; i < args->ile_sekcji; i++)
    {
        printf("\033[%d;%dH\033[2K", GORNY_MARGIN + ODSTEP_MIEDZY_WIERSZAMI*args->num, LEWY_MARGIN);
        printf("watek %d | sekcja prywatna %d\n", args->num, i + 1);

	// losowe uśpienie w trakcie sekcji prywatnej
        losowa_ilosc = rand()%2 + 1;
        sleep(losowa_ilosc);


        // koniec sekcji prywatnej   
        if( lock_mutex(mutex_ptr) == -1 ) pthread_exit(NULL);
        // początek sekcji krytycznej
        
	// przypisanie licznikowi prywatnemu wartości licznika globalnego
        prywatny_licznik = licznik;

	
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
        prywatny_licznik++;

	// losowe uśpienie w trakcie sekcji krytycznej
        losowa_ilosc = rand()%2 + 1;
        sleep(losowa_ilosc);

	// przypisanie zwiększonej o 1 wartości licznikowi globalenemu 
        licznik = prywatny_licznik;

        // koniec sekcji krytycznej
        if( unlock_mutex(mutex_ptr) == -1 ) pthread_exit(NULL);
        // początek sekcji prywatnej

    }

    printf("\033[%d;%dH\033[2K", GORNY_MARGIN + ODSTEP_MIEDZY_WIERSZAMI*args->num, LEWY_MARGIN);
    printf("watek %d | sekcja prywatna %d | zakonczono\n",args->num, i);

    return NULL;
}

void atexitCleanUp(void)
{
    destroy_mutex(mutex_ptr);
    printf("\033[0m");       // Wroc do domyslnego trybu wyswietlania

}

void on_signal(int SIG)
{
    exit(0);
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

    // stworzenie mutexu
    pthread_mutex_t M;
    mutex_ptr = &M;
    if( create_mutex(mutex_ptr) == -1 ) exit(4);


    // zarejestrowanie funkcji w atexit
    if( atexit(atexitCleanUp) != 0 )
    {
	perror("atexit error");
	exit(5);
    }

    // obsługa sygnału SIG_INT
    if( signal(SIGINT, on_signal) == SIG_ERR )
    {
	perror("signal error");
	exit(6);
    }

    // zapoczatkowanie generatora liczb pseudolosowych
    srand(time(0));

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

    // wypisanie wartości mutexu
    printf("\033[1;0H\033[2K");
    printf("adres mutexu: %p\n", (void *)mutex_ptr);

    // utworzenie watkow z przekazaniem argumentow przez tablice
    for(i = 0; i < watkow; i++)
    {
	arg[i].ile_sekcji = sekcji_kryt;
	arg[i].ile_watkow = watkow;
	arg[i].num = i + 1;
	if( ( thread_id[i] = create_thread(watek, &(arg[i])) ) == -1 ) exit(7);
	printf("\033[%d;0H\033[2K", i+2);
	printf("stworzono watek o id %ld i numerze %d\n", thread_id[i], i+1);
    }
    // zaczekanie na zakonczenie watkow przed koncem programu
    for(i = 0; i < watkow; i++)
	if( join_thread(thread_id[i]) == -1 ) exit(8);
   
    printf("\033[%d;0H\033[2K", GORNY_MARGIN + watkow*(ODSTEP_MIEDZY_WIERSZAMI+1));
    printf("mialo miejsce %d sekcji krytycznych; oczekiwano %d\n", licznik, watkow*sekcji_kryt);
}
