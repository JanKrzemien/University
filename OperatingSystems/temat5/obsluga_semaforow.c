#include "obsluga_semaforow.h"

#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

// tworzy semafora binarnego i sprawia że podany przez argument wskaźnik wskazuje na niego
int create_smfr(char name[], sem_t ** sem)
{
    *sem = sem_open(name, O_EXCL | O_CREAT, 0644, 1);
    if(*sem == SEM_FAILED)
    {
	perror("error podczas tworzenia semafora binarnego");
	return -1;
    }
    return 0;
}

// otwiera semafor binarny i sprawia że podany przez argument wskaźnik wskazuje na niego
int open_smfr(char name[], sem_t ** sem)
{
    *sem = sem_open(name, 0);
    if( *sem == SEM_FAILED )
    {
	perror("nie udało się otworzyć semafora binarnego");
	return -1;
    }
    return 0;
}

// usuwa semafor binarny
int destroy_smfr(char name[])
{
    if( sem_unlink(name) == -1 )
    {
	perror("error podczas usuwania semafora");
	return -1;
    }
    return 0;
}

// zamyka semafor binarny
int close_smfr(sem_t * sem)
{
    if( sem_close(sem) == -1 )
    {
	perror("nie udało się zamknąć semafora");
	return -1;
    }
    return 0;
}

// funkcja zwraca wartość dla wskazanego przez wskaźnik semafora
int get_smfr_val(sem_t * sem)
{
    int sval;
    if( sem_getvalue(sem, &sval) == -1 )
    {
	perror("sem_getvalue error");
	return -1;
    }
    return sval;
}


// jeśli semafor binarny jest równy 1 to zmniejsza te wartość o 1 i od razu wraca do wykonywania kodu
// jeśli semafor binarny < 1 to sprawia że proces czeka
int PB(sem_t * sem)
{
    if( sem_wait(sem) == -1 )
    {
	 perror("sem_wait error");
         return -1;
    }
    return 0;
}

// zwiększa wartość semafora binarnego o 1
int VB(sem_t * sem)
{
    if( sem_post(sem) == -1 )
    {
	perror("sem_post error");
	return -1;
    }
    return 0;
}
