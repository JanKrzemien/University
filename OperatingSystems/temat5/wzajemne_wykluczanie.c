/* 
 Program wykonuje n sekcji krytycznych gdzie n jest podane
 przez argument wywołania programu, w każdej sekcji krytycznej
 próbuje uzyskać dostęp do wspólnego zasobu którym jest plik z numerem
 jeśli uda się uzyskac dostęp zwiększa numer w pliku o 1, jeśli nie
 czeka aż uzyska dostęp.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 10.05.2023
 ----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "obsluga_semaforow.h"

int main(int argc, char * argv[])
{
    // oczekiwane są trzy argumenty, nazwa obecnie wykonywanego programu, ilość sekcji krytycznych do wykonania
    // nazwa semafora oraz plik do zapisania ilości sekcji krytycznych
    if( argc != 4 )
    {
	perror("niewlasciwa ilosc argumentow");
	exit(1);
    }

    // zamiana str -> int, ilość sekcji krytycznych do wykonania
    int ile_sekcji_kryt = strtol(argv[1], NULL, 10);
    if( errno == ERANGE )
    {
	perror("podczas zamiany char* -> int ilości sekcji krytycznych wartość poza zakresem typu int");
	exit(2);
    }

    // wskaźnik do semafora
    sem_t * smfr = NULL;

    // inicjuje generator liczb losowych z seedem bazującym na aktualnym czasie
    srand(time(NULL));

    // otworzenie istniejącego semafora
    if( open_smfr(argv[2], &smfr) == -1 ) exit(3);

    int desc, numer, opoznienie, snprintfReturnVal;
    char bufor[4];
    int i = 0, smfr_val;
    do
    {
	// uśpienie programu na 1 lub 2 sekundy
	opoznienie = rand()%2 + 1;
        printf("usypiam program na %d sekund\n", opoznienie);
        sleep(opoznienie);

	// wypisanie PIDu semafora i jego wartości początkowej
	smfr_val = get_smfr_val(smfr);
	if(smfr_val == -1) exit(14);
        printf("przed sekcją krytyczną | pid: %d | wartość smfra: %d \n", getpid(), smfr_val);

	// próba uzyskania dostępu do zasobu
	// if( PB(smfr) == -1 ) exit(4);

	// sekcja krytyczna
	
	// wypisanie PIDu i wartości semafora w trakcie sekcji krytycznej
	smfr_val = get_smfr_val(smfr);
	if(smfr_val == -1) exit(15);
	printf("\nsekcja krytyczna | pid: %d | wartość smfra: %d \n", getpid(), smfr_val);
	printf("czytam z pliku\n");

	// czytanie numeru z pliku
	desc = open(argv[3], O_RDONLY, 0644);
	if( desc == -1 )
	{
	    perror("open file error");
	    exit(4);
	}
	if( read(desc, bufor, 4) == -1 )
	{
	    perror("read error");
	    exit(5);
	}
	if( close(desc) == -1 )
	{
	    perror("close desc error");
	    exit(6);
	}

	// zamiana str -> int, w celu zwiększenia go o 1 i zapisania spowrotem do pliku
	numer = strtol(bufor, NULL, 10);
	if(errno == ERANGE)
	{
	    perror("wykroczono poza zakres int podczas zamiany na int numeru z pliku");
	    exit(7);
	}
	printf("z pliku przeczytałem %d zwiększam go o 1 i zapisuje spowrotem do pliku\n", numer);
	numer++;

	// uśpienie programu na 1 lub 2 sekundy
	opoznienie = rand()%2 + 1;
	printf("usypiam program na %d sekund\n", opoznienie);
	sleep(opoznienie);

	// zamiana int -> str numeru do zapisania w pliku
	snprintfReturnVal = snprintf(bufor, 4, "%d", numer);
	if(snprintfReturnVal < 0 || snprintfReturnVal >= 4)
	{
	   perror("error podczas zamiany int -> str za pomocą snprintf");
	   exit(8);
	}

	// zapisanie numeru do pliku
	desc = open(argv[3], O_WRONLY, 0644);
        if( desc == -1 )
        {
            perror("open file error");
            exit(9);
        }
        if( write(desc, bufor, 4) == -1 )
        {
            perror("write error");
            exit(10);
        }
        if( close(desc) == -1 )
        {
            perror("close desc error");
            exit(11);
        }
	
	// koniec sekcji krytycznej

	// oddanie dostepu do zasobu
	// if( VB(smfr) == -1 ) exit(12);

	// wypisanie PIDu i wartości semafora po sekcji krytycznej
	smfr_val = get_smfr_val(smfr);
	if(smfr_val == -1) exit(16);
	printf("po sekcji krytycznej | pid: %d | wartość smfra: %d \n", getpid(), smfr_val);
	
	i++;

    }while(i < ile_sekcji_kryt);



    if( close_smfr(smfr) == -1 ) exit(13);
}
