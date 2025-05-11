/* 
 Program tworzy proces potomny, wczytuje dane z pliku podanego przez argument wywołania programu
 porcjami po DATA_RATE bajtów i zapisuje je do potoku.
 Proces potomny, odczytuje dane z potoku i zapisuje do pliku.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 14.04.2023
 ----------------------------------------------------------------------
*/ 

#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/param.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#define PATH "./"
#define N 100

#define DATA_RATE 32
#define DATA_RATE_POTOMNY 20

int main(int argc, char *argv[])
{
    // oczekiwane są 2 argumenty:
    // nazwa pliku do pobrania danych i nazwa pliku do zapisania danych
    if(argc != 3)
    {
        perror("niewłaściwa ilość argumentów wywołania programu\n");
	    exit(1);
    }

    // łączenie nazw plików ze ścieżkami w pętli, dla każdego z 3 plików
    // przekazanych przez argumenty wywołania programu
    char pathName[2][N];
    int i;
    int iloscZnakow;
    for(i = 0; i < 2; i++)
    {
        iloscZnakow = snprintf(pathName[i], N, "%s%s", PATH, argv[1 + i]);
    	if( iloscZnakow < 0 || iloscZnakow >= N )
	    {
	        perror("nie udało się zapisać ciągów znaków do jednej tablicy za pomocą funkcji snprintf\n");
	        exit(2);
    	}
    }


    // otworzenie pliku i przypisanie jego deskryptora do zmiennej
    printf("Otwieranie plikow...\n");
    int deskryptorOdczyt = open(pathName[0], O_RDONLY, "rw-r--r--");
    int deskryptorZapis = open(pathName[1], O_WRONLY | O_TRUNC | O_CREAT, "rw-r--r--");
    if( deskryptorOdczyt == -1 || deskryptorZapis == -1 )
    {
	perror("nie udało się otworzyć pliku, porażka funkcji open\n");
        exit(3);
    }
    printf("Pliki otworzone\n\n");

    printf("Tworzenie potoku...\n");
    // utworzenie potoku, jego deskryptory są zapisane w tablicy potok
    int potok[2];
    if(pipe(potok) == -1)
    {
        perror("błąd nie udało się otworzyć potoku funkcją pipe\n");
	    exit(4);
    }
    printf("Potok utworzony\n\n");

    // zmienne odczyt z pliku i wysłanie do potoku
    int odczytanoBajtowZPliku, zapisanoBajtowWPotoku, odczytanoBajtowZPotoku, zapisanoBajtowDoPliku;
    char bufferZPliku[DATA_RATE], bufferDoPliku[DATA_RATE_POTOMNY];

    unsigned int opoznienie;

    // ustawienie seed'a dla funkcji rand,
    // time(0) jako argument zagwarantuje że liczby wylosowane będą
    // się różniły pomiędzy wywołaniami programu
    srand( time(0) );


    // stworzenie procesu potomnego i wywołanie w nim programu
    switch(fork())
    {
        case -1:
	    perror("fork error");
	    exit(8);
	case 0: // konsument
	    if( close(potok[1]) == -1 || close(deskryptorOdczyt) == -1 )
	    {
			perror("close pipe error");
			exit(14);
	    }

		printf("rozpoczynam odczyt z potoku...\n");
		// odczyt danych z potoku tak długo jak z potoku można odczytać porcje DATA_RATE danych
		// lub aż do napotkania błędu lub końca pliku
		while( ( odczytanoBajtowZPotoku = read(potok[0], (void*)bufferDoPliku, DATA_RATE_POTOMNY) ) > 0 )
		{
			printf("odczytano %d bajtów z potoku...\n", odczytanoBajtowZPotoku);
			
			// usypianie programu na ilość losową sekund
			opoznienie = rand()%3;
			printf("usypiam program na %d sekund\n", opoznienie);
			sleep(opoznienie);

			// zapis danych do pliku połączony z obsługą błędów funkcji write
			if( ( zapisanoBajtowDoPliku = write(deskryptorZapis, (void*)bufferDoPliku, odczytanoBajtowZPotoku) ) == -1 )
			{
				perror("błąd podczas zapisywania danych w pliku za pomocą funkcji write\n");
				exit(4);
			}
			printf("zapisano %d bajtów w pliku...\n", zapisanoBajtowDoPliku);
			printf("zapisane do pliku: ");
			// wypisanie danych na ekranie za pomocą funkcji write
			if( write(1, (void*)bufferDoPliku, zapisanoBajtowDoPliku) == -1 )
			{
					perror("wypisanie danych standardowym wyjściem nie powiodło się, funkcja write zwróciła -1\n");
					exit(8);
			}
			printf("\n");

		}
		if( odczytanoBajtowZPotoku == -1 ) // obsługa błędów dla funkcji read znajdującej się w warunku pętli while
		{
			perror("błąd podczas odczytu danych z potoku za pomocą funkcji read");
			exit(5);
		}

		printf("zakończono pobieranie z potoku i zapisywanie do pliku\n");

		// zamknięcie potoku
		if( close(potok[0]) == -1 || close(deskryptorZapis) == -1 )
		{
			perror("nie udało się zamknąć pliku za pomocą funkcji close w procesie potomnym\n");
			exit(6);
	    }

	    break;
	default: // producent
	    if( close(potok[0]) == -1 || close(deskryptorZapis) == -1)
	    {
            perror("close pipe error");
			exit(10);
	    }

	    	printf("Rozpoczynam przesyłanie danych do potoku...\n\n");
    	    // funkcja read odczytuje z pliku dane w porcjach określonych przez DATA_RATE
            // jeśli zostaną odczytane wszystkie dane odczytanoBajto będzie równe 0,
    	    // w przypadku błędu odczytanoBajtow będzie równe -1 i po zakończeniu pętli błąd zostanie obsłużony
    	    while( ( odczytanoBajtowZPliku = read(deskryptorOdczyt, (void*)bufferZPliku, DATA_RATE) ) > 0)
    	    {
                printf("odczytano %d bajtów z pliku...\n", odczytanoBajtowZPliku);
                // zapisanie do potoku, połączone z obsługą błędów funkcji write
             	if( ( zapisanoBajtowWPotoku = write(potok[1], (void*)bufferZPliku, odczytanoBajtowZPliku) ) == -1)
            	{
                    perror("zapisanie danych do potoku nie powiodło się, funkcja write zwróciła -1\n");
                    exit(5);
            	}

            	printf("zapisano %d bajtów w potoku...\n", zapisanoBajtowWPotoku);
				printf("zapisano do potoku: ");
            	// wypisanie danych na ekranie za pomocą funkcji write
            	if( write(1, (void*)bufferZPliku, zapisanoBajtowWPotoku) == -1 )
       	    	{
           	    perror("wypisanie danych standardowym wyjściem nie powiodło się, funkcja write zwróciła -1\n");
            	    exit(13);
        	}
        	printf("\n");

    	    }
    	    if(odczytanoBajtowZPliku == -1) // obsługa błędów funkcji read
    	    {
        		perror("odczytanie danych z pliku nie powiodło się, funkcja read zwróciła -1\n");
        		exit(6);
    	    }
    	    printf("przesyłanie danych do potoku zakończone\n\n");

	    // zamknięcie pliku do odczytu danych
		if( close(potok[1]) == -1 || close(deskryptorOdczyt) == -1 )
		{
        	perror("błąd podczas zamknięcia pliku funkcją close w procesie macierzystym\n");
           	exit(12);
   	    }

	    if(wait(NULL) == -1 )
	    {
			perror("wait error");
			exit(15);
	    }

    }

    return 0;
}
