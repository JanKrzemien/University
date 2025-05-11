#ifndef OBSLUGA_KOLEJEK_H
#define OBSLUGA_KOLEJEK_H

#include <mqueue.h>

#define ZNAK_POPRZEDZAJACY "/"
#define N 100

#define SERWER_MQ "/serwer_mq"

// tworzy kolejke i zwraca jej deskryptor
int create_mq(char name[], int flags);

// usuwa kolejke
int destroy_mq(char name[]);

// otwiera kolejke i zwraca jej deskryptor
int open_mq(char name[], int flags);

// zamyka kolejke
int close_mq(int desc);

// ustawia wskaźnik mq_attr na strukture w której znajdują się atrybuty kolejki
int get_mq_attr(int desc, struct mq_attr * attr);

// wysłanie komunikatu
int send_mq(int desc, const char * msg_ptr, int msg_len);

// odebranie komunikatu
int receive_mq(int desc, char * msg_ptr, int msg_len);

#endif
