#ifndef OBSLUGA_SEMAFOROW_H
#define OBSLUGA_SEMAFOROW_H

#include <semaphore.h>

#define PATH "./"
#define N 100

// tworzy semafor binarny i sprawia że wskaźnik sem wskazuje na niego
int create_smfr(char name[], sem_t ** sem);

// usuwa semafor binarny
int destroy_smfr(char name[]);

// otwiera semafor binarny i sprawia że wskaźnik sem wskazuje na niego
int open_smfr(char name[], sem_t ** sem);

// zamyka semafor binarny
int close_smfr(sem_t * sem);

// zwraca wartość semafora
int get_smfr_val(sem_t * sem);

// opuszcza semafor
int PB(sem_t * sem);

// podnosi semafor
int VB(sem_t * sem);

#endif
