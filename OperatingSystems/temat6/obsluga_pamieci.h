#ifndef OBSLUGA_PAMIECI_H
#define OBSLUGA_PAMIECI_H

#define NELE 25 // rozmiar elementu bufora (jednostki towaru) w bajtach
#define NBUF 4  // liczba elementów bufora

// SegmentPD struct
typedef struct {
  char bufor[NBUF][NELE];
  int wstaw;
  int wyjmij;
  int bajtow[NBUF];
} SegmentPD;

// utworzenie pamięci dzielonej i nadanie jej rozmiaru sizeof(SegmentPD)
int create_mem(char * name);

// otworzenie i odwzorowanie pamięci dzielonej
int open_mem(SegmentPD ** pt, char * name, int prot, int flags);

// zamknięcie pamięci dzielonej bez odwzorowania
int close_mem(int desc);

// zamyka pamięć dzieloną z odwzorowaniem pamięci
int close_maped_mem(int desc, SegmentPD * pt);

// usunięcie pamięci dzielonej
int destroy_mem(char * name);

#endif
