/*
 Program tworzy pamiec dzielona, semafory i dwa procesy potomne w
 ktorych uruchamia programy producenta i klienta, jest tez odpowiedzialny
 za usuniecie pamieci dzielonej i semaforow.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 26.05.2023
 ----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#include "obsluga_pamieci.h"
#include "obsluga_semaforow.h"

#define PATH "./"
#define N 100

// wskaźniki globalne służące do przekazania nazwy semaforówi pamięci dzielonej do funkcji atexitCleanUp
char * prod_sem_name = NULL;
char * kons_sem_name = NULL;
char * mem_name = NULL;

void atexitCleanUp(void)
{
    destroy_smfr(prod_sem_name);
    destroy_smfr(kons_sem_name);
    destroy_mem(mem_name);
}

void on_signal(int SIG)
{
    exit(0);
}

int main(int argc, char * argv[])
{
    // oczekiwane argumenty: nazwa obecnie wykonywanego programu, plik wykonywalny producenta, konsumenta,
    // nazwa pliku z danymi, nazwa pliku do zapisu danych, nazwa pamięci dzielonej, nazwa semafora producenta
    // nazwa semafora konsumenta
    if(argc != 8)
    {
	perror("zła ilość argumentów main.c");
	exit(1);
    }

    // łączenie stringów nazw plików i ścieżki do nich
    char pathName[4][N];
    int i, snprintfReturnVal;
    for(i = 0; i < 4; i++)
    {
	snprintfReturnVal = snprintf(pathName[i],N,"%s%s", PATH, argv[1+i]);
	if( snprintfReturnVal < 0 || snprintfReturnVal >= N )
	{
	    perror("snprintf error podczas łączenia nazwy pliku ze ścieżką do niego");
	    exit(2);
	}
    }

    // przypisanie wskaźnikom nazw semaforów i pamięci dzielonej by funkcja zarejestrowana przez
    // atexit mogła usunąć semafory i zwolnić pamięć dzieloną
    prod_sem_name = argv[6];
    kons_sem_name = argv[7];
    mem_name = argv[5];

    // stworzenie semafora producenta
    sem_t * psem = NULL;
    if( create_smfr(argv[6], &psem, NBUF) == -1 ) exit(3);

    // atexit
    if( atexit(atexitCleanUp) != 0 )
    {
        perror("atexit error");
        exit(10);
    }

    // custom signal
    if( signal(2, on_signal) == SIG_ERR )
    {
        perror("signal error");
        exit(11);
    }

    // stworzenie semafora konsumenta
    sem_t * ksem = NULL;
    if( create_smfr(argv[7], &ksem, 0) == -1 ) exit(4);

    // stworzenie pamięci dzielonej
    int desc = create_mem(argv[5]);
    if( desc == -1 ) exit(5);

    // wypisanie początkowych wartości semaforów i pamięci dzielonej
    int smfr_val = get_smfr_val(psem);
    if(smfr_val == -1) exit(6);
    printf("utworzono semafor producenta | adres: %p | wartość: %d \n", (void *)psem, smfr_val);
    smfr_val = get_smfr_val(ksem);
    if(smfr_val == -1) exit(7);
    printf("utworzono semfaro konsumenta | adres: %p | wartość: %d \n", (void *)ksem, smfr_val);
    printf("utworzono pamięć dzieloną | deskryptor: %d | rozmiar: %ld \n\n", desc, sizeof(SegmentPD));

    // zamknięcie pamięci dzielonej ponieważ określona przeze mnie w bibliotece funkcja create_mem tylko tworzy i otwiera,
    // z kolei funkcja open_mem otwiera i ustawia wskaźnik tak żeby wskazywał na obiekt dany obiekt
    if( close_mem(desc) == -1 ) exit(7);

    // wartości początkowe iteratorów wstaw i wyjmij w pamięci dzielonej
    SegmentPD * seg = NULL;
    desc = open_mem(&seg, argv[5], PROT_READ | PROT_WRITE, O_RDWR);
    if( desc == -1 ) exit(8);
    seg->wstaw = 0;
    seg->wyjmij = 0;
    if( close_maped_mem(desc, seg) == -1 ) exit(9);

    // fork
    int pidy[2];
    for(i = 0; i < 2; i++)
    {
	pidy[i] = fork();
	switch(pidy[i])
	{
	    case -1:
		perror("fork error");
		exit(12);
	    case 0:
		execlp(pathName[i], argv[1 + i], pathName[2 + i], argv[5], argv[6], argv[7], (char *) NULL);
		perror("execlp error");
		_exit(13);
	}
    }

    // czekanie na zakończenie wszystkich procesów potomnych
    for(i = 0; i < 2; i++)
    {
	if( waitpid(pidy[i], NULL, 0) == -1 )
	{
	    perror("waitpid error");
	    exit(14);
	}
    }

    // zamknij semafor producenta
    if( close_smfr(psem) == -1 ) exit(15);

    // zamknij semafor konsumenta
    if( close_smfr(ksem) == -1 ) exit(16);
}
