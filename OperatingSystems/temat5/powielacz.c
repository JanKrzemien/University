/* 
 Program powielacz tworzy n procesów potomnych, gdzie n jest podane
 przez argumenty wywołania programu, w każdym procesie uruchamiany jest
 program podany przez argument wywołania, w powielacz.c znajduje się
 funkcja zarejestrowana w atexit, obsługa sygnału 2, wpisanie do pliku
 numer.txt początkowej wartości 0, stworzenie i usunięcie semaforów.
 program czeka na zakończenie wszystkich procesów potomnych.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 10.05.2023
 ----------------------------------------------------------------------
*/

#include "obsluga_semaforow.h"

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

// globalna zmienna wskaźnikowa stworzona by mieć dostęp do nazwy semafora w funkcji atexitCleanUp
char *pt = NULL;

void atexitCleanUp(void)
{
    destroy_smfr(pt);
}

void on_signal(int sig)
{
    exit(0);
}

int main(int argc, char* argv[])
{
    // program oczekuje 3 argumentów: nazwe pliku wykonywalnego programu do uruchomienia w procesie potomnym,
    // ile procesów utworzyć, ile sekcji krytycznych każdy program powinien mieć, nazwa semafora nazwanego
    if(argc != 6)
    {
	perror("niewłaściwa ilość argumentów");
	exit(1);
    }

    // wskaźnik pt wskazuje na element tablicy w którym znajduje się nazwa semafora
    pt = argv[5];

    // wskaźnik do semafora
    sem_t * smfr = NULL;

    // utworzenie i zainicjowanie semafora
    if( create_smfr(argv[5], &smfr) == -1 ) exit(2);

    int smfr_val = get_smfr_val(smfr);
    if(smfr_val == -1) exit(16);
    printf("semafor stworzony.\n adres semafora: %p  wartość początkowa semafora: %d \n", (void *)smfr, smfr_val);
    // zarejestrowanie funkcji sprzątającej przy zakończeniu programu
    if( atexit(atexitCleanUp) != 0 )
    {
	perror("atexit init error");
	exit(3);
    }

    // usuwanie semafora gdy zostanie odebrany sygnał SIGINT
    if( signal(2, on_signal) == SIG_ERR )
    {
	perror("signal error");
	exit(4);
    }

    // połączenie nazwy programu do wywołania w procesie potomnym ze ścieżką
    char pathName[2][N];
    int char_count = snprintf(pathName[0], N, "%s%s", PATH, argv[1]);
    if( char_count < 0 || char_count >= N )
    {
	perror("error podczas snprintf pathName[0]");
	exit(5);
    }
    char_count = snprintf(pathName[1], N, "%s%s", PATH, argv[4]);
    if( char_count < 0 || char_count >= N )
    {
	perror("error podczas snprintf pathName[1]");
	exit(5);
    }

    // zamiana ciągu znaków na int
    int ile_procesow = strtol(argv[2], NULL, 10);
    if( errno == ERANGE )
    {
	perror("przy zamianie argv[2] char* -> int wartość poza zakresem typu int");
	exit(6);
    }
    int ile_sekcji_kryt = strtol(argv[3], NULL, 10);
    if( errno == ERANGE )
    {
	perror("przy zamianie argv[3] char* -> int wartość poza zakresem typu int");
	exit(6);
    }

    // otworzenie pliku numer.txt i wpisanie do niego 0
    int desc = open(pathName[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    char numer[4];
    numer[0] = '0';
    if( write(desc, &numer, sizeof(char)) == -1 )
    {
	perror("write error");
	exit(7);
    }
    if( close(desc) == -1 )
    {
	perror("close error");
	exit(8);
    }

    // tworzenie procesów potomnych
    int pidy[ile_procesow];
    int i;
    for(i = 0; i < ile_procesow; i++)
    {
	// zbieranie pidów procesów potomnych w celu czekania na nie
	pidy[i] = fork();
	switch(pidy[i])
	{
	    case -1:
	        perror("fork error");
		exit(9);
	    case 0:
		execlp(pathName[0], argv[1], argv[3], argv[5], pathName[1], (void*)NULL);
		perror("execlp error");
		_exit(10);
	}
    }

    // czekanie aż wszystkie procesy się zakończą
    for(i = 0; i < ile_procesow; i++)
    {
        if( waitpid(pidy[i], NULL, 0) == 0 )
        {
            perror("waitpid error");
            exit(11);
        }
    }

    // sprawdzenie czy wpisany numer do pliku numer.txt zgadza się z oczekiwanym numerem
    // oczekiwany numer to ilość procesów razy ilość sekcji krytycznych
    desc = open(pathName[1], O_RDONLY, 0644);
    if( read(desc, numer, sizeof(numer)) == -1 )
    {
	    perror("read error");
	    exit(12);
    }
    if( close(desc) == -1 )
    {
	    perror("close read only desc");
	    exit(13);
    }
    printf("oczekiwano %d wykonanych sekcji krytycznych\n", ile_procesow*ile_sekcji_kryt);
    printf("zostało wykonane %s sekcji krytycznych\n", numer);

    if( close_smfr(smfr) == -1 ) exit(14);
}
