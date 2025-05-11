/*
 Program odczytuje dane z pliku porcjami ustalonymi w pliku naglowkowym
 obsluga_pamieci.h i zapisuje je w buforze cyklicznym pamieci dzielonej
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 26.05.2023
 ----------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#include "obsluga_semaforow.h"
#include "obsluga_pamieci.h"


int main(int argc, char * argv[])
{
    // oczekiwane argumenty: nazwa programu obecnie wykonywanego, nazwa pliku z którego będą wczytywane dane,
    // nazwa pamięci dzielonej, nazwa semafora producenta, nazwa semafora konsumenta
    if( argc != 5 )
    {
	perror("niewłaściwa ilość argumentów producent");
	exit(1);
    }

    // otworzenie semafora producenta
    sem_t * psmfr = NULL;
    if( open_smfr(argv[3], &psmfr) == -1 ) exit(2);
    // otworzenie semafora konsumenta
    sem_t * ksmfr = NULL;
    if( open_smfr(argv[4], &ksmfr) == -1 ) exit(3);

    // otworzenie i odwzorowanie pamięci dzielonej
    SegmentPD * seg = NULL;
    int mem_desc = open_mem(&seg, argv[2], PROT_READ | PROT_WRITE, O_RDWR);
    if( mem_desc == -1 ) exit(4);

    // otworzenie pliku do wczytywania danych
    int f_desc = open(argv[1], O_RDONLY, 0644);
    if( f_desc == -1 )
    {
	perror("open error");
	exit(5);
    }

    int wczytano_bajtow;
    char bufor[NELE];
    int smfr_val;
    printf("rozpoczynam wczytywanie danych i zapisywanie do pamięci podręcznej\n\n");

    while( (wczytano_bajtow = read(f_desc, bufor, NELE)) > 0 ) // produkcja towaru
    {	
	// informacje o pobranych danych
	printf("wyprodukowano %d bajtów towaru\n", wczytano_bajtow);
	printf("pobrane z pliku dane: %s\n\n", bufor);
	

	// opuść semafor producenta
	if( P(psmfr) == -1 ) exit(8);

	// wartość semaforów w trakcie sekcji krytycznej
        smfr_val = get_smfr_val(psmfr);
        if(smfr_val == -1) exit(9);
        printf("semafor producenta o PID %d zmienil wartosc wartosc na %d\n", getpid(), smfr_val);
        smfr_val = get_smfr_val(ksmfr);
        if(smfr_val == -1) exit(9);
        printf("semafor konsumenta ma wartosc %d\n", smfr_val);

	// ilość wczytanych z pliku bajtów zapisana w pamięci dzielonej
	seg->bajtow[seg->wstaw] = wczytano_bajtow;

	// umieszczenie towaru w buforze
	memcpy(seg->bufor[seg->wstaw], bufor, seg->bajtow[seg->wstaw]);

	// wypisanie informacji w trakcie sekcji krytycznej
	printf("wstaw = %d; zwiększam wstaw o 1\n", seg->wstaw);
	printf("towar umieszczony w pamięci dzielonej: %s\n", seg->bufor[seg->wstaw]);

	// zwięlszenie wstaw o 1 z operacją modulo
	seg->wstaw = (seg->wstaw + 1) % NBUF;

        // wartość semaforów po sekcji krytycznej
        smfr_val = get_smfr_val(psmfr);
        if(smfr_val == -1) exit(12);
        printf("semafor producenta o PID %d ma wartosc %d\n", getpid(), smfr_val);
        smfr_val = get_smfr_val(ksmfr);
        if(smfr_val == -1) exit(12);
        printf("semafor konsumenta zmienil wartość na 1\n\n");

	// podnieś semafor konsumenta
	if( V(ksmfr) == -1 ) exit(11);

    }
    if( wczytano_bajtow == -1 ) // obsługa błędów funkcji read
    {
	perror("read error");
	exit(13);
    }

    // zamknięcie pliku do wczytywania danych
    if( close(f_desc) == -1 )
    {
	perror("close error");
	exit(16);
    }
    // zamknięcie semafora binarnego konsumenta
    if( close_smfr(ksmfr) == -1 ) exit(17);
    // zamknięcie semafora binarnego producenta
    if( close_smfr(psmfr) == -1 ) exit(18);
    // zamknięcie pamięci dzielonej z odwzorowaniem
    if( close_maped_mem(mem_desc, seg) == -1 ) exit(19);
}
