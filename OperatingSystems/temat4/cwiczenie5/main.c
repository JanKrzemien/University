/* 
 Program tworzacy dwa procesy potomne z odpowiednimi argumentami wywołania programu,
 znajduje sie tam funkcja atexit oraz obsługa sygnału SIGINT
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 26.04.2023
 ----------------------------------------------------------------------
*/ 

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define PATH "./"
#define N 100

// pathName jest zmienną globalną żeby wewnątrz funkcji removePipe był dostęp do nazwy potoku do usunięcia
char pathName[5][N];

// funkcja do robienia porządków w przypadku błędu
// usuwa nazwany potok
void removePipe(void)
{
    if( unlink(pathName[4]) != 0 )
    {
	perror("unlink error");
	_exit(4);
    }
}

void signalHandler(int sig)
{
    exit(0);
}

int main(int argc, char *argv[])
{
    // program oczekuje nazwy uruchomionego pliku, nazwy plików wykonywalnych producenta i konsumenta,
    // nazwy potoku, nazw plików do odczytu i zapisu danych
    if(argc != 6)
    {
	puts("wrong number of arguments");
	exit(1);
    }


    // łączenie nazw plików ze ścieżką
    int i, wczytano;
    for(i = 0; i < 5; i++)
    {
	wczytano = snprintf(pathName[i], N, "%s%s", PATH, argv[i+1]);
	if(wczytano < 0 || wczytano >= N)
	{
	    perror("snprintf error");
	    exit(2);
	}
    }

    // tworzenie potoku
    if( mkfifo(pathName[4], 0644) == -1 )
    {
        perror("mkfifo error");
        exit(3);
    }

    if( setpgid(0,0) == -1 )
    {
        perror("setpgid error");
        exit(9);
    }

    // ustawienie funkcji która usunie potok przy wywołaniu funkcji exit
    if( atexit(removePipe) != 0 )
    {
	perror("atexit error");
	exit(5);
    }

    // obsługa sygnału SIGINT
    // po odebraniu sygnału SIGINT wywołaj funkcje exit
    // ktora usunie potok nazwany
    if( signal(2, signalHandler) == SIG_ERR )
    {
	perror("error while setting reaction to signal SIGINT");
	exit(10);
    }

    int pidy[2];
    int forkReturnVal;

    for(i = 0; i < 2; i++)
    {
	forkReturnVal = fork();
	switch(forkReturnVal)
	{
	    case -1:
            perror("fork error");
            exit(6);
	    case 0:
            execlp(pathName[i], argv[i + 1], pathName[4], pathName[2 + i], (void*)NULL);
	        perror("execlp error");
            _exit(7);
        default:
            pidy[i] = forkReturnVal;
    }
    }

    for(i = 0; i < 2; i++)
    {
        if(waitpid(pidy[i], NULL, 0) == -1)
        {
            perror("waitpid error");
            exit(8);
        }
    }

}
