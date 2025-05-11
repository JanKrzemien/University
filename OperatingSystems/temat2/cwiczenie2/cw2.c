/* 
 Przez argumenty programu przekazywana jest nazwa pliku wykonywalnego do inicjowania w procesach.
 Program wywołuje trzy razy w pętli funkcje fork, podczas każdej iteracji.
 W procesie potomnym inicjowany jest nowy program, do inicjowanego programu przekazywana
 jest za pomocą argumentów programu informacja o numerze iteracji w której został zainicjowany
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 24.03.2023
 ----------------------------------------------------------------------
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "funkcje.h"

#define PATH "./" // ścieżka do pliku podawanego poprzez argument wywołania programu
#define N 100  // ilość znaków na nazwę pliku który wywołujemy w execlp

int main(int arg, char *argv[])
{
    if(arg != 2)
    {
        perror("nieprawidlowa ilosc argumentow.\n oczekiwano nazwy programu do uruchomienia w procesie potomnym.\n");
	    exit(3);
    }

    unsigned int i;
    char pathName[N];

    // snprintf łączy dwie tablice charów w jedną o maksymalnej długości N
    // nie ma możliwości wyjścia poza zakres tablicy pathName
    if(snprintf(pathName, N, "%s%s", PATH, argv[1]) < 0)
    {
        perror("snprintf error");
	    exit(4);
    }

    char numerProgramu[2] = {'0', '\0'}; // tablica charów służąca do przekazywania ciągu znaków jako argumentu wywoływanego programu
    
    printf("id procesu macierzystego:\n");
    wypiszIDProcesu(); // wypisuje identyfikatory procesu macierzystego
    
    for(i = 1; i < 4; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                numerProgramu[0] = i + '0';
                // wywołanie programu z numerem iteracji pętli w której był wywołany jako argumentem
                execlp(pathName, argv[1], numerProgramu ,(char*) NULL);
		        perror("execlp error"); // jeśli funkcja dojdzie do tego momentu znaczy że execlp się nie powiódł i należy zakończyć program
                _exit(2);
            default:
                if(wait(NULL) == -1) 
                {
                    perror("wait error");
                    exit(5);
                }
        }
    }

    return 0;
}
