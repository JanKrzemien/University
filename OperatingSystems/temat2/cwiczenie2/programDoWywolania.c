/* 
 Program wywoływany w proceach potomych, przez argumenty programu jest
 przekazywany ciąg znaków wypisywany w terminalu
 razem z identyfikatorami procesu
 ----------------------------------------------------------------------
 Autor: Jan Krzemień,                               Krakow, 24.03.2023
 ----------------------------------------------------------------------
*/ 
#include "funkcje.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        perror("niewlasciwa ilosc argumentow");
        exit(1);
    }

    printf("\nwywolano program %s o id: \n", argv[1]); // wypisanie argumentu podanego do programu
    wypiszIDProcesu(); // wypisuje identyfikatory wywołanego procesu
    return 0;
}
