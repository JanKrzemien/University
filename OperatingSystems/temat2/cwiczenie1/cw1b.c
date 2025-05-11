/* 
 Program wywołuje trzy razy w pętli funkcje fork i wypisuje
 identyfikatory UID, GID, PID, PPID, PGID procesu macierzystego oraz
 wszystkich procesów potomnych.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 17.03.2023
 ----------------------------------------------------------------------
*/ 

#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "funkcje.h"

int main()
{
    unsigned int i;
    printf("id procesu macierzystego:\n");
    wypiszIDProcesu(); // wypisuje identyfikatory procesu macierzystego

    for(i = 1; i < 4; i++)
    {
        printf("---------------------------------------\n");
        // funkcja fork towrzy identyczną kopie procesu macierzystego
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                printf("id procesu potomnego:\n");
                wypiszIDProcesu(); // wypisuje identyfikatory procesu potomnego
                break;
            default:
                if(wait(NULL) == -1) // sprawia że proces macierzysty czeka na koniec procesu potomnego
                {
                    perror("wait error");
                    exit(2);
                }
        }
    }

    return 0;
}
