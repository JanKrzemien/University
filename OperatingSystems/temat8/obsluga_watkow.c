#include "obsluga_watkow.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// tworzy wątek ze standardowymi atrybutami i przekazaną przez argumenty funkcji
// funkcją i tablicą argumentów
pthread_t create_thread(void * (*func)(void *), Args * args)
{
    pthread_t id;
    int errnum = pthread_create(&id, NULL, func, args);
    if( errnum != 0 )
    {
	printf("pthread_create error: %s\n", strerror(errnum));
	return -1;
    }
    return id;
}

// sprawia że proces czeka na zakończenie wątku o danym id
int join_thread(pthread_t TID)
{
    int errnum = pthread_join(TID, NULL);
    if( errnum != 0 )
    {
        printf("pthread_join error: %s\n", strerror(errnum));
        return -1;
    }
    return 0;

}
