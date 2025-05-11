
#include "obsluga_kolejek.h"

#include <mqueue.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>

// tworzy kolejke i zwraca jej deskryptor
int create_mq(char name[], int flags)
{
    struct mq_attr atr = {0, 10, 100, 0};
    int desc = mq_open(name, flags | O_EXCL | O_CREAT, 0644, &atr);
    if(desc == -1)
	perror("error podczas tworzenia kolejki, desc == -1");
    return desc;
}

// otwiera kolejke i zwraca jej deskryptor
int open_mq(char name[], int flags)
{
    int desc = mq_open(name, flags);
    if( desc == -1 )
	perror("nie udało się otworzyć kolejki, desc == -1");
    return desc;
}

// usuwa kolejke
int destroy_mq(char name[])
{
    if( mq_unlink(name) == -1 )
    {
	perror("error podczas usuwania kolejki");
	return -1;
    }
    return 0;
}

// zamyka kolejke
int close_mq(int desc)
{
    if( mq_close(desc) == -1 )
    {
	perror("nie udało się zamknąć kolejki");
	return -1;
    }
    return 0;
}


// ustawia wskaźnik attr na strukture w której znajdują się atrybuty skrzynki
int get_mq_attr(int desc, struct mq_attr * attr)
{
    if( mq_getattr(desc, attr) == -1 )
    {
	perror("mq_getattr error");
	return -1;
    }
    return 0;
}

// wysłanie komunikatu do kolejki
// w zadaniu nie ma mowy o priorytetach stąd wszystkie komunikaty będą miały priorytet 0
int send_mq(int desc, const char * msg_ptr, int msg_len)
{
    if( mq_send(desc, msg_ptr, msg_len, 0) == -1 )
    {
	 perror("nie udało się wysłać komunikatu");
         return -1;
    }
    return 0;
}

// odebranie komunikatu
int receive_mq(int desc, char * msg_ptr, int msg_len)
{
    if( mq_receive(desc, msg_ptr, msg_len, 0) == -1 )
    {
	perror("nie udało się odebrać komunikatu");
	return -1;
    }
    return 0;
}
