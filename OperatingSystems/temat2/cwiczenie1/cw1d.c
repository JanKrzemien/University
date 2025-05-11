/* 
 Program wywołuje trzy razy w pętli funkcje fork, podczas każdej iteracji
 wypisuje identyfikatory procesów dla danego pokolenia, następnie usypia je
 na sekudne, w ostatniej iteracji procesy macierzyste są uśpione o pół sekundy
 dłużej dla pewności że skończą się po procesach potomnych
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 17.03.2023
 ----------------------------------------------------------------------
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "funkcje.h"

int main()
{
    unsigned int i;
    printf("identyfikatory procesu macierzystego: \n");
    wypiszIDProcesu(); // wypisuje identyfikatory procesu macierzystego

    printf("------------------------------\n");

    for(i = 1; i < 4; i++)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                wypiszIDProcesu(); // wypisuje identyfikatory procesu potomnego w danym pokoleniu
                sleep(1);
        }
    }

    sleep(4);
    return 0;
}
