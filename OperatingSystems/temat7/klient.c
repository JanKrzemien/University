/*========================================================================
 * Program klient tworzy kolejke o nazwie bedacej numerem PID procesu klienta,
 * prosi o podanie dzialania arytmetycznego przez uzytkownika. Nastepnie
 * wysyla dzialanie poprzedzone nazwa swojej kolejki do serwera i czeka na
 * odpowiedz. Wypisuje odpowiedz i prosi o podanie dzialania az nie otrzyma
 * od uzytkownika ctrl-d.
 *========================================================================
 * Autor: Jan Krzemień					Data: 07.06.2023
 * =======================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

#include "obsluga_kolejek.h"

// zmienna wskaźnikowa której celem jest usunięcie kolejek wewnątrz atexitCleanUp
char * mq_ptr = NULL;

// funkcja rejestrowana przez atexit która usuwa kolejki
void atexitCleanUp(void)
{
    destroy_mq(mq_ptr);
}

// funkcja do obsługi sygnału SIG_INT, kończy program i usuwa kolejki
void on_signal(int SIG)
{
    exit(0);
}

int main(void)
{
   // pid klienta do użycia w nazwie skrzynki
   int pid = getpid();

   char mq_name[N];

   // stworzenie nazwy kolejki do odbierania komunikatów
   int printed_count = snprintf(mq_name, N, "%s%d", ZNAK_POPRZEDZAJACY, pid);
   if( printed_count < 0 || printed_count > N )
   {
	perror("snprintf error podczas łączneia / z pidem klienta");
	exit(1);
   }
   mq_ptr = mq_name;

   // stworzenie kolejki do odbierania komunikatów
   int klient_desc = create_mq(mq_name, O_RDONLY);
   if( klient_desc == -1 ) exit(2);

   // informacje o kolejce klienta
   struct mq_attr que_attr;
   get_mq_attr(klient_desc, &que_attr);
   printf("informacje o kolejce klienta:\n");
   printf("deskryptor: %d | nazwa: %s | max ilosc wiadomosci: %ld | max dlugosc wiadomosci: %ld\n", klient_desc, mq_name, que_attr.mq_maxmsg, que_attr.mq_msgsize);


   // zarejestrowanie funkcji usuwającej kolejke podczas końca programu
   if( atexit(atexitCleanUp) != 0 )
   {
	perror("atexit klient error");
	exit(3);
   }

   // obsługa sygnału SIG_INT
   if( signal(SIGINT, on_signal) == SIG_ERR )
   {
	perror("signal klient error");
	exit(4);
   }

   // uśpienie klienta na pół sekundy by upewnić się że utworzył swoją kolejkę
   printf("usypiam klienta na 1 sekunde\n");
   sleep(1);

   // otworzenie kolejki serwera 
   int serwer_desc = open_mq(SERWER_MQ, O_WRONLY);
   if(serwer_desc == -1) exit(5);

   // wczytuj dane z klawiatury i wysyłaj jako komunikaty do wczytania EOF z klawiatury lub do wystąpienia błędu
   char bufor[N];
   char komunikat[N];
   printf("podaj nowy komunikat do wyslania\n");
   while( fgets(bufor, N, stdin) != NULL )
   {
      // połącz adres kolejki klienta z wiadomością w jeden komunikat
      printed_count = snprintf(komunikat, N, "%s %s", mq_name, bufor);
      if(printed_count < 0 || printed_count > N)
      {
         perror("snprintf error podczas laczenia nazwy kolejki klienta i tresci komunikatu do wyslania do serwera");
         exit(6);
      }

      // wysłanie komunikatu do serwera
      if( send_mq(serwer_desc, komunikat, N) == -1 ) exit(7);

      // odebranie komunikatu z serwera
      if( receive_mq(klient_desc, komunikat, N) == -1 ) exit(8);

      // wypisanie odpowiedzi serwera
      printf("wynik z serwera: %s\n", komunikat);

      // wiadomość podaj nowy komunikat do wysłania
      printf("podaj nowy komunikat do wyslania\n");
   }

   printf("zakonczono dzialanie klienta\n");

   if( close_mq(serwer_desc) == -1 ) exit(9);
   if( close_mq(klient_desc) == -1 ) exit(10);
}

