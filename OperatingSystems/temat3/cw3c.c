/* 
 Program tworzy proces potomny, ustawia go liderem swojej własnej grupy.
 Poprzez funkcję execlp uruchamia program i przekazuje mu jako
 argument wywołania funkcji nazwę programu do uruchomienia,
 numer sygnału i jak ma zareagować na dany sygnał.
 Następnie czeka na zakończenie procesu potomnego.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 05.04.2023
 ----------------------------------------------------------------------
*/

#define _POSIX_C_SOURCE 200112L
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include "funkcje.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>


#define PATH "./"
#define N 100

int main(int argc, char* argv[])
{
	// w argv powinna znajdować się nazwa uruchomionego programu,
	// nazwa programu do uruchomienia, nazwa programów do uruchomienia w procesie potomnym
	// numer sygnału i jak zareagować na dany sygnał
    if(argc != 5)
    {
        perror("niewłaściwa ilość argumentów.\n oczekiwano nazwy programu do uruchomienia w procesie potomnym, nazwy programu do przekazania do procesu potomnego, numeru sygnału do obsłużenia i znaku oznaczającego jak obsłużyć dany sygnał.\n");
		exit(1);
    }

    char pathName[N];
	// zapisanie tego co normalnie zostałoby wypisane na ekranie do tablicy pathName
    if( snprintf(pathName, N, "%s%s", PATH, argv[1]) < 0 )
    {
        perror("błąd snprintf. nie udało się zapisać dwóch ciągów znaków do tablicy wynikowej");
		exit(2);
    }

    int SIG = atoi(argv[3]);
    if(SIG == 0)
    {
        perror("nie udalo się zamienić char* na int");
	exit(9);
    }

    wypiszIDProcesu(); // wypisanie identyfikatorów procesu macierzystego

    int forkReturnVal = fork();
    int status; // zmienna w której jeśli proces potomny zostanie zakończony sygnałem znajdą się informacje o zakończeniu
	int signalNum; // jeśli proces potomny zostanie zakończony sygnałem to w signalNum będzie przechowywany numer tego sygnału uzyskany z funkcji wait

    switch(forkReturnVal)
    {
        case -1:
	    	perror("fork error");
	    	exit(3);
	case 0:
	    	if(setpgid(0,0) == -1)
	    	{
	        	perror("setpgid error");
				exit(4);
	    	}

	    	execlp(pathName, argv[1], argv[2], argv[3], argv[4], (char*) NULL);
	    	perror("execlp error");
	    	_exit(5);
	default:
		sleep(3); // oczekiwanie żeby procesy potomne na pewno sie utworzyły

		printf("sprawdzanie czy grupa o pgid %d istnieje...\n", forkReturnVal);
		if( kill(-(forkReturnVal), 0) == -1 )
		{
			perror("nie znaleziono grupy o danym pgid\n");
			exit(6);
		}
		printf("grupa istnieje\n\n");

		printf("wysyłanie sygnału do grupy...\n");
		if(kill(-(forkReturnVal), SIG) == -1)
		{
			perror("wysyłanie sygnału do grupy nie powiodło się\n");
			exit(7);
		}
		printf("sygnał wysłany, proces macierzysty czeka na zakończenie procesów potomnych\n");

		// oczekiwanie na zakończenie procesu potomnego
		if(wait(&status) == -1)
		{
			perror("wait error");
			exit(8);
		}

		// za pomocą makra WIFSIGNALED uzyskiwane są dane czy lider grupy procesów potomnych został zakończony sygnałem
		if(WIFSIGNALED(status))
		{
			signalNum = WTERMSIG(status); // makro WTERMSIG uzyskuje informacje o numerze sygnału który zakończył dany proces
			printf("lider grupy procesów potomnych został zakończony sygnałem o numerze %d (%s)\n\n", signalNum, strsignal(signalNum));
		} else
		{
			printf("lider grupy procesów potomnych zakończył się normalnie\n\n");
		}
    }

    return 0;
}
