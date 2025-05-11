#define _DEFAULT_SOURCE || _XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED || _POSIX_C_SOURCE >= 200112L

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#include "obsluga_pamieci.h"

// utworzenie pamięci dzielonej i nadanie jej rozmiaru
int create_mem(char * name)
{
    int desc = shm_open(name, O_RDWR | O_EXCL | O_CREAT, 0644);
    if( desc == -1 )
    {
	perror("shm_open error w funkcji create_mem");
	return -1;
    }
    if( ftruncate(desc, sizeof(SegmentPD)) == -1 )
    {
	destroy_mem(name);
	perror("ftruncate error");
	return -1;
    }
    return desc;
}
// otworzenie i odwzorowanie pamięci dzielonej
int open_mem(SegmentPD ** pt, char * name, int prot, int flags)
{
    // otworzenie pamięci dzielonej
    int desc = shm_open(name, flags, 0644);
    if( desc == -1 )
    {
	perror("shm_open error w funkcji open_mem");
	return -1;
    }
    // odwzorowanie pamięci dzielonej
    *pt = (SegmentPD *) mmap(NULL, sizeof(SegmentPD), prot, MAP_SHARED, desc, 0);
    if( *pt == MAP_FAILED )
    {
	perror("mmap error");
	return -1;
    }
    return desc;
}
// zamknięcie pamięci dzielonej bez odwzorowania
int close_mem(int desc)
{
    if( close(desc) == -1 )
    {
	perror("close error");
	return -1;
    }
    return 0;
}
// zamyka pamięć dzieloną z odwzorowaniem pamięci
int close_maped_mem(int desc, SegmentPD * pt)
{
    if( munmap((void *)pt, sizeof(SegmentPD)) == -1 )
    {
	perror("munmap error");
	return -1;
    }
    if( close(desc) == -1 )
    {
        perror("close error in overloaded func");
        return -1;
    }
    return 0;
}
// usunięcie pamięci dzielonej
int destroy_mem(char * name)
{
    if( shm_unlink(name) == -1 )
    {
	perror("shm_unlink error");
	return -1;
    }
    return 0;
}
