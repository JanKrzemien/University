#ifndef OBSLUGA_WATKOW_H
#define OBSLUGA_WATKOW_H

#include <pthread.h>

struct args
{
    int num;
    int ile_sekcji;
    int ile_watkow;
};

typedef struct args Args;


// tworzy wątek wykonujący funkcję func
pthread_t create_thread(void * (*func)(void *), Args * args);

// nakazuje procesowi czekać na zakończenie wątku o danym ID
int join_thread(pthread_t TID);

#endif
