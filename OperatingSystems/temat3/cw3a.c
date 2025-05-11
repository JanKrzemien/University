/* 
 Program w zależności od podanej przez argumenty wywołania programu litery
 odpowiednio obsługuje sygnał, również podany przez argument wywołania funkcji.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 05.04.2023
 ----------------------------------------------------------------------
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "funkcje.h"

// funkcja z reakcją na sygnał w przypadku podania przez argument programu
// litery c
void signal_handler(int SIG)
{
    printf("\nreakcja dla sygnału %d\n", SIG);
    return;
}

int main(int arg, char *argv[])
{
    // w argv powinna się znajdować nazwa programu, numer sygnału, znak oznaczający reakcje na sygnał
    if(arg != 3)
    {
        perror("nieprawidlowa ilosc argumentow.\n oczekiwano nazwy programu do uruchomienia w procesie potomnym, numeru sygnału do obsługiwania i znaku oznaczającego jak proces potomny powinien zareagować na dany sygnał\n");
	    exit(1);
    }

    int SIG = atoi(argv[1]); // zamiana char na int
    if(SIG == 0)
    {
        perror("nie udało się zamienić char na int");
	exit(4);
    }

    wypiszIDProcesu(); // wypisanie identyfikatorów procesu oczekującego na sygnał

    // w zależności od znaku podanego przez argument wywołania programu ustaw reakcje na sygnał
    switch(argv[2][0])
    {
        case 'd':
            printf("\ndomyślna reakcja na sygnał\n");
            if( signal(SIG, SIG_DFL) == SIG_ERR )
            {
                perror("error funkcji signal");
                exit(EXIT_FAILURE);
            }
            break;
        case 'i':
            printf("\nignorowanie sygnału\n");
            if( signal(SIG, SIG_IGN) == SIG_ERR )
            {
                perror("error funkcji signal");
                exit(EXIT_FAILURE);
            }
            break;
        case 'c':
            printf("\ncustomowa reakcja na sygnał\n");
            if( signal(SIG, signal_handler) == SIG_ERR )
            {
                perror("error funkcji signal");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            perror("nieznana reakcja na sygnał");
            exit(3);
    }

    // pause oczekuje na sygnał, jeśli proces nie zostanie zakończony przez sygnał
    // tylko na wskutek sygnału zostanie wykonana funkcja i program będzie kontynuowany
    // zostanie wypisane zareagowano na sygnał...
    if(pause() == -1)
    {
        printf("zareagowano na sygnał, program jest kontynuowany\n");
    }

    return 0;
}
