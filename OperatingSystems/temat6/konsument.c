/*
 Program odczytuje z bufora cyklicznego w pamieci podrecznej dane porcjami
 ustalonymi w pliku naglowkowym obsluga_pamieci.h i zapisuje je w pliku
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 26.05.2023
 ----------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include "obsluga_semaforow.h"
#include "obsluga_pamieci.h"


int main(int argc, char * argv[])
{
    // oczekiwane argumenty: nazwa programu obecnie wykonywanego, nazwa pliku z którego będą wczytywane dane,
    // nazwa pamięci dzielonej, nazwa semafora producenta, nazwa semafora konsumenta
    if( argc != 5 )
    {
	perror("niewłaściwa ilość argumentów konsument");
	exit(1);
    }

    // otworzenie semafora producenta
    sem_t * psem = NULL;
    if( open_smfr(argv[3], &psem) == -1 ) exit(2);

    // otworzenie semafora konsumenta
    sem_t * ksem = NULL;
    if( open_smfr(argv[4], &ksem) == -1 ) exit(3);

    // otworzenie i odwzorowanie pamięci dzielonej
    SegmentPD * seg = NULL;
    int mem_desc = open_mem(&seg, argv[2], PROT_READ | PROT_WRITE, O_RDWR);
    if( mem_desc == -1 ) exit(4);

    // otworzenie pliku do zapisywania danych
    int f_desc = open(argv[1], O_WRONLY | O_TRUNC, 0644);
    if( f_desc == -1 )
    {
	perror("open error");
	exit(5);
    }

    // wczytywanie danych z pamięci dzielonej i zapisywanie do pliku
    // sleep żeby upewnić się że producent zaczął pierwszy przesyłanie towaru
    char bufor[NELE];
    int zapisano_bajtow, smfr_val;
    printf("rozpoczynam pobieranie danych z pamięci dzielonej i zapisywanie do pliku\n\n");
    while( 1 )
    {

	// opuszczenie semafora konsumenta
	if( P(ksem) == -1 ) exit(6);	

	// wartość semaforów w sekcji krytycznej
        smfr_val = get_smfr_val(psem);
        if(smfr_val == -1) exit(7);
        printf("semafor producenta ma wartość: %d\n", smfr_val);
        smfr_val = get_smfr_val(ksem);
        if(smfr_val == -1) exit(7);
        printf("semafor konsumenta o PID  %d zmienil wartosc na %d\n", getpid(), smfr_val);

	// skopiowanie z pamięci dzielonej do lokalnego bufora
	memcpy(bufor, seg->bufor[seg->wyjmij], seg->bajtow[seg->wyjmij]);

	// wypisanie informacji o pobranych danych
	printf("z pamięci podręcznej do bufora pobrano: %s\n", bufor);	
	printf("wyjmij jest równe %d, zwiększam wyjmij o 1\n", seg->wyjmij);

	// uśpienie programu na sekundę
	printf("usypiam program na 1 sekundę\n");
	sleep(1);

        // wartość semaforów po sekcji krytycznej
        smfr_val = get_smfr_val(psem);
        if(smfr_val == -1) exit(11);
        printf("semafor producenta zmienia wartosc na 1\n");
        smfr_val = get_smfr_val(ksem);
        if(smfr_val == -1) exit(11);
        printf("semafor konsumenta o PID  %d zmienia wartosc na %d\n\n", getpid(), smfr_val);
	// podniesienie semafora producenta
	if( V(psem) == -1 ) exit(9);


	// zapisanie danych z bufora do pliku
	if( (zapisano_bajtow = write(f_desc, bufor, seg->bajtow[seg->wyjmij])) == -1 )
        {
            perror("write error");
            exit(10);
        }

        printf("w pliku zapisano %d bajtów\n\n", seg->bajtow[seg->wyjmij]);

	// if( seg->bajtow[seg->wyjmij] < NELE ) break;
	// wydaje mi się że producent produkował dane o wiele szybciej od konsumenta, po tym jak konsument
	// podniósł semafor producenta, producent nadpisał ilość bajtów jeszcze przed sprawdzeniem przez konsumenta
	// poniższego warunku końca pętli
	if( zapisano_bajtow < NELE ) break;

	// zwiększenie wyjmij o 1
        seg->wyjmij = ( seg->wyjmij + 1 ) % NBUF;

    }

    printf("zakończono pobieranie danych z pamięci dzielonej i zapisywanie w pliku\n");

    // zamknięcie pliku do wczytywania danych
    if( close(f_desc) == -1 )
    {
	perror("close error");
	exit(12);
    }
    // zamknięcie semafora binarnego konsumenta
    if( close_smfr(ksem) == -1 ) exit(13);
    // zamknięcie semafora binarnego producenta
    if( close_smfr(psem) == -1 ) exit(14);
    // zamknięcie pamięci dzielonej z odwzorowaniem
    if( close_maped_mem(mem_desc, seg) == -1 ) exit(15);
}
