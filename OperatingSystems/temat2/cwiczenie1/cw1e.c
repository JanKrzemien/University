/* 
 Program wywołuje trzy razy w pętli funkcje fork, podczas każdej iteracji
 procesy potomne stają się liderami swoich własnych grup a proces macierzysty
 czeka na ich zakończenie.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 17.03.2023
 ----------------------------------------------------------------------
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "funkcje.h"

int main()
{
    unsigned int i;
    printf("id procesu macierzystego:\n");
    wypiszIDProcesu(); // wypisuje identyfikatory procesu maceirzystego

    for(i = 1; i < 4; i++)
    {
        printf("---------------------------------------\n");
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                if(setpgid(0,0) == -1)
                {
                    perror("setpgid error");
                    exit(2);
                }
                wypiszIDProcesu(); // wypisuje identyfikatory procesu potomnego
                break;
            default:
                if(wait(NULL) == -1)
                {
                    perror("wait error");
                    exit(3);
                }
        }
    }

    return 0;
}
