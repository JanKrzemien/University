/* 
 Program wywołuje trzy razy w pętli funkcje fork i podczas ostatniej
 iteracji pętli usypia procesy potomne przez co proces macierzysty się
 kończy a procesy potomne są adoptowane
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 17.03.2023
 ----------------------------------------------------------------------
*/ 
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "funkcje.h"

int main()
{
    unsigned int i;
    printf("id procesu macierzystego:\n");
    wypiszIDProcesu(); // wypisuje identyfikatory procesu macierzystego
    printf("---------------------------------------\n");
    for(i = 1; i < 4; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                sleep(1);
                wypiszIDProcesu(); // wypisuje identyfikatory procesu potomnego
        }
    }

    return 0;
}
