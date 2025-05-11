/* 
 Program wczytuje dane z potoku podanego przez argument wywołania programu
 porcjami po SIZE bajtów i zapisuje je do pliku.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 26.04.2023
 ----------------------------------------------------------------------
*/ 

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

#define SIZE 15

int main(int argc, char *argv[])
{
    // producent powinien otrzymać przez argumenty wywołania programu nazwe programu wykonywanego, ścieżka do potoku, ścieżka do pliku do zapisu
    if( argc != 3 )
    {
        perror("niewłaściwa ilość argumentów konsument");
        exit(1);
    }

    // otworzenie pliku do czytania danych i potoku do zapisywania danych
    int writeDesc = open(argv[2], O_WRONLY | O_TRUNC, "rw-r--r--");
    int readDesc = open(argv[1], O_RDONLY, "rw-r--r--");
    if( readDesc == -1 || writeDesc == -1 )
    {
        perror("open function error");
        exit(3);
    }

    // ustawienie seed'a dla funkcji rand,
    // time(0) jako argument zagwarantuje że liczby wylosowane będą
    // się różniły pomiędzy wywołaniami programu
    srand( time(0) );


    // odczyt z pliku i zapis do potoku
    int wczytanychBajtow, zapisanychBajtow;
    int opoznienie;
    char bufor[SIZE];
    printf("rozpoczynam odczyt z potoku i zapis do pliku\n");
    while( (wczytanychBajtow = read(readDesc, bufor, SIZE)) > 0 )
    {
        printf("odczytano z potoku %d bajtow\n", wczytanychBajtow);
        printf("odczytano dane: ");
        if( write(1, bufor, wczytanychBajtow) == -1 )
        {
            printf("nastąpił error przy wypisywaniu na ekran\n\n\n");
            perror("error while writing to screen");
            exit(5);
        }

        if( (zapisanychBajtow = write(writeDesc, bufor, wczytanychBajtow)) == -1 )
        {
            printf("nastąpił error przy zapisywaniu do pliku\n\n\n");
            perror("error while writing to file");
            exit(6);
        }

        printf("zapisano w pliku %d bajtow\n", zapisanychBajtow);
        
        // uśpienie procesu na 0 1 lub 2 sekundy
        opoznienie = rand()%3;
        printf("\nusypiam program na %d sekund\n", opoznienie);
        sleep(opoznienie);

    }
    if( wczytanychBajtow == -1 )
    {
	perror("error while reading from named pipe");
	exit(4);
    }
    printf("zakończono odczyt z potoku i zapis do pliku\n");

    if( close(readDesc) == -1 || close(writeDesc) == -1 )
    {
	perror("error while closing descriptor");
	exit(7);
    }

    return 0;
}
