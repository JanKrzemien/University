/* 
 Program poprzez funkcję execlp uruchamia program i przekazuje mu jako
 argument wywołania funkcji numer sygnału i jak ma zareagować na dany sygnał.
 Następnie sprawdza czy proces potomny istnieje i wysyła do procesu potomnego sygnał.
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
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

#define PATH "./"
#define N 100

int main(int argc, char *argv[])
{
    // w argv powinny się znajdować nazwa uruchomionego programu, nazwa programu do uruchomienia za pomocą execlp
    // numer sygnału i jak zareagować na ten sygnał
    if(argc != 4)
    {
        perror("nieprawidłowa ilość argumentów.\nWymagana jest nazwa pliku wykonywalnego jako argument, numer sygnału i sposób zachowania się wywołanej funkcji\n");
		exit(1);
    }

    char pathName[N];
    // zapisanie tego co normalnie zostałoby wypisane na ekranie do tablicy pathName
    if( snprintf(pathName, N, "%s%s", PATH, argv[1]) < 0 )
    {
        perror("błąd snprintf. nie udało się zapisać dwóch ciągów znaków do tablicy wynikowej");
		exit(2);
    }

    int SIG = atoi(argv[2]);
    if(SIG == 0)
    {
        perror("nie udało się przekonwertować ciągu znaków na int");
	exit(8);
    }

    int forkReturnVal = fork();
    int statusPotomka; // zmienna będzie przekazana do funkcji wait i będzie się w niej znajdował status zakończenia procesu potomnego
    int signalNum; // jeśli proces potomny zostanie zakończony sygnałem to w signalNum będzie przechowywany numer tego sygnału uzyskany z funkcji wait

    switch(forkReturnVal)
    {
	case -1:
	    perror("fork error");
	    exit(3);
	case 0:
	    execlp(pathName, argv[1], argv[2], argv[3], (char*)NULL);
	    perror("execlp error");
	    _exit(4);
	default:
	    sleep(1.5); // sleep żeby proces potomny na pewno się utworzył
		
	    printf("sprawdzam czy proces potomny istnieje...\n");
	    if(kill(forkReturnVal, 0) == -1)
	    {
			perror("proces nie istnieje");
			exit(5);
	    }
	    printf("proces istnieje\n\n");

	    printf("wysyłam sygnał %c do procesu o pid %d\n", SIG, forkReturnVal);
	    if(kill(forkReturnVal, SIG) == -1)
	    {
			perror("operacja wysłania sygnału do procesu potomnego nie powidodła się");
			exit(6);
	    }
	    printf("sygnał wysłany, proces macierzysty zaczyna czekać na zakończenie procesu potomnego\n\n");

		// oczekiwanie na zakończenie procesu potomnego
	    if(wait(&statusPotomka) == -1)
	    {
			perror("wait error");
			exit(7);
	    }

		// za pomocą makra WIFSIGNALED uzyskiwane są dane czy proces potomny został zakończony sygnałem
	    if(WIFSIGNALED(statusPotomka))
	    {
			signalNum = WTERMSIG(statusPotomka); // makro WTERMSIG uzyskuje informacje o numerze sygnału który zakończył dany proces
			printf("proces potomny został zakończony sygnałem o numerze %d (%s)\n\n", signalNum, strsignal(signalNum));
	    } else
	    {
			printf("proces potomny zakończył się normalnie\n\n");
	    }
    }

    return 0;
}
