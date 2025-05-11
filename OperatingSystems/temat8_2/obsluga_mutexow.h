#ifndef OBSLUGA_MUTEXOW_H
#define OBSLUGA_MUTEXOW_H

#include <pthread.h>

// tworzy mutex z domyślnymi ustawieniami i ustawia wskaźnik pmutex żeby wskazywał na nowo utworzony mutex
int create_mutex(pthread_mutex_t  * pmutex);

// usuwa mutex na który wskazuje przekazany przez argument wskaźnik
int destroy_mutex(pthread_mutex_t * pmutex);

// zamyka dostęp do mutexu
int lock_mutex(pthread_mutex_t * pmutex);

// otwiera dostęp do mutexu
int unlock_mutex(pthread_mutex_t * pmutex);

#endif
