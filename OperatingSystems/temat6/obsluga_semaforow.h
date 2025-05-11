#ifndef OBSLUGA_SEMAFOROW_H
#define OBSLUGA_SEMAFOROW_H

#include <semaphore.h>

// tworzy semfaro binarny i sprawia że wskaźnik sem wskazuje na niego
int create_smfr(char name[], sem_t ** sem, int val);

// usuwa semafor binarny
int destroy_smfr(char name[]);

// otwiera semafor binarny i sprawia że wskaźnik sem wskazuje na niego
int open_smfr(char name[], sem_t ** sem);

// zamyka semafor binarny
int close_smfr(sem_t * sem);

// zwraca wartość semafora
int get_smfr_val(sem_t * sem);

// opuszcza semafor
int P(sem_t * sem);

// podnosi semafor
int V(sem_t * sem);

#endif
