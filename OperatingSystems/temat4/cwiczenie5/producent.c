/* 
 Program wczytuje dane z pliku podanego przez argument wywołania programu
 porcjami po SIZE bajtów i zapisuje je do potoku.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 26.04.2023
 ----------------------------------------------------------------------
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

#define SIZE 20

int main(int argc, char *argv[])
{
    // producent powinien otrzymać przez argumenty wywołania programu nazwe programu wykonywanego, ścieżka do potoku, ścieżka do pliku z danymi
    if( argc != 3 )
    {
        perror("niewłaściwa ilość argumentów");
        exit(1);
    }

    // otworzenie pliku do czytania danych i potoku do zapisywania danych
    int readDesc = open(argv[2], O_RDONLY, "rw-r--r--");
    int writeDesc = open(argv[1], O_WRONLY, "rw-r--r--");
    if( readDesc == -1 || writeDesc == -1 )
    {
        perror("open function error");
        exit(3);
    }

    // odczyt z pliku i zapis do potoku
    int wczytanychBajtow, zapisanychBajtow;
    char bufor[SIZE];
    printf("rozpoczynam odczyt z pliku i zapis do potoku\n");
    while( (wczytanychBajtow = read(readDesc, bufor, SIZE)) > 0 )
    {
        printf("\nodczytano %d bajtow\n", wczytanychBajtow);
        printf("odczytane dane: ");

        if( write(1, bufor, wczytanychBajtow) == -1 )
        {
            perror("error while trying to write in terminal");
            exit(5);
        }

        if( (zapisanychBajtow = write(writeDesc, bufor, wczytanychBajtow)) == -1 )
        {
            perror("error while trying to write to named pipe");
            exit(6);
        }

        printf("\nzapisano do potoku %d bajtow\n", zapisanychBajtow);
    }
    if( wczytanychBajtow == -1 )
    {
        perror("read error");
        exit(4);
    }
    printf("zakończono odczytywanie z pliku i zapisywanie w potoku\n");

    if( close(readDesc) == -1 || close(writeDesc) == -1 )
    {
        perror("error while closing descriptors");
        exit(7);
    }

    return 0;
}
