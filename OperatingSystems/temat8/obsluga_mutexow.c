#include "obsluga_mutexow.h"

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// tworzy mutex z domyślnymi ustawieniami i ustawia wskaźnik pmutex żeby wskazywał na nowo utworzony mutex
int create_mutex(pthread_mutex_t  * pmutex)
{
    int errnum = pthread_mutex_init(pmutex, NULL);
    if( errnum != 0 )
    {
	printf("error podczas mutex_init: %s\n", strerror(errnum));
	return -1;
    }
    return 0;
}

// usuwa mutex na który wskazuje przekazany przez argument wskaźnik
int destroy_mutex(pthread_mutex_t * pmutex)
{
    int errnum = pthread_mutex_destroy(pmutex);
    if( errnum != 0 )
    {
	printf("error podczas mutex_destroy: %s\n", strerror(errnum));
	return -1;
    }
    return 0;
}

// zamyka dostęp do mutexu
int lock_mutex(pthread_mutex_t * pmutex)
{
    int errnum = pthread_mutex_lock(pmutex);
    if( errnum != 0 )
    {
        printf("error podczas mutex_lock: %s\n", strerror(errnum));
        return -1;
    }
    return 0;
}

// otwiera dostęp do mutexu
int unlock_mutex(pthread_mutex_t * pmutex)
{
    int errnum = pthread_mutex_unlock(pmutex);
    if( errnum != 0 )
    {
        printf("error podczas mutex_unlock: %s\n", strerror(errnum));
        return -1;
    }
    return 0;
}


