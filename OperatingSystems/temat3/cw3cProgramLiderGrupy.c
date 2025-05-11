/* 
 Program w pętli poprzez funkcję execlp uruchamia 3 programy i przekazuje mu jako
 argument wywołania funkcji nazwę programu do uruchomienia,
 numer sygnału i jak ma zareagować na dany sygnał.
 Następnie sprawia że proces potomny staje się liderem swojej własnej grupy.
 Sprawdza czy proces potomny istnieje i wysyła do procesu potomnego sygnał.
 Program czeka na zakończenie procesu potomnego, jeśli został zakończony przez sygnał
 wypisuje numer sygnału i jego nazwe.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 05.04.2023
 ----------------------------------------------------------------------
*/

#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>


#define PATH "./"
#define N 100

int main(int argc, char* argv[])
{
    // w argv powinna znajdować się nazwa uruchomionego programu,
	// nazwa programów do uruchomienia w procesie potomnym
	// numer sygnału i jak zareagować na dany sygnał
    if(argc != 4)
    {
        perror("niewłaściwa ilość argumentów.\n oczekiwano nazwy programu do uruchomienia w procesie potomnym, numeru sygnału do obsłużenia i znaku oznaczającego jak obsłużyć dany sygnał.\n");
	    exit(1);
    }

    char pathName[N];
    // zapisanie tego co normalnie zostałoby wypisane na ekranie do tablicy pathName
    if( snprintf(pathName, N, "%s%s", PATH, argv[1]) < 0 )
    {
        perror("błąd snprintf. nie udało się zapisać dwóch ciągów znaków do tablicy wynikowej");
	    exit(2);
    }

    wypiszIDProcesu(); // wypisanie identyfikatorów lidera grupy procesów potomnych
   
    int SIG = atoi(argv[2]);
    if(SIG == 0)
    {
        perror("nie udało się zamienić char* na int");
	    exit(8);
    }
    if( signal(SIG, SIG_IGN) == SIG_ERR ) // ustawienie domyślnej reakcji na sygnał dla lidera grupy na ignorowanie
    {
        perror("error in signal function");
        exit(9);
    }

    int forkReturnVal;
    int status; // zmienna w której jeśli proces potomny zostanie zakończony sygnałem znajdą się informacje o zakończeniu
    int pidy[3]; // tablica na numery pid procesów potomnych

    for(int i = 0; i < 3; i++)
    {
        forkReturnVal = fork();
        switch(forkReturnVal)
        {
            case -1:
                perror("fork error");
                exit(3);
            case 0:
                execlp(pathName, argv[1], argv[2], argv[3], (char*) NULL);
                perror("execlp error");
                _exit(4);
            default:
                pidy[i] = forkReturnVal;
        }
    }

    // dla każdego procesu potomnego ich proces macierzysty czeka na zakończenie.
    // po zakończeniu jeśli zostały zakończone sygnałem wypisuje informacje o zakończeniu
    int i;
    for(i = 0; i < 3; i++)
    {
        // oczekiwanie na zakończenie procesu potomnego
	    if(waitpid(pidy[i], &status, 0) == -1)
	    {
			perror("wait error");
			exit(7);
	    }

        printf("status : %d\n", status);

		// za pomocą makra WIFSIGNALED uzyskiwane są dane czy lider grupy procesów potomnych został zakończony sygnałem
        if(WIFSIGNALED(status))
        {
            // makro WTERMSIG uzyskuje informacje o numerze sygnału który zakończył dany proces
            printf("proces potomny o pid %d zakończono sygnałem %d (%s)\n", pidy[i], WTERMSIG(status), strsignal(WTERMSIG(status)));
        } else
        {
            printf("proces potomny o pid %d zakończony normalnie\n", pidy[i]);
        }
    }

    return 0;
}
