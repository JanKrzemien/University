/* 
 Program wypisuje identyfikatory UID, GID, PID, PPID, PGID
 dla danego procesu.
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 17.03.2023
 ----------------------------------------------------------------------
*/ 

#include "funkcje.h"
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    printf("Podstawowe identyfikatory dla danego procesu:\n");
    wypiszIDProcesu(); // wypisuje identyfikatory procesu

    return 0;
}
