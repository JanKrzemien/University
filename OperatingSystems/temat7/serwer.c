/*==============================================================================
 * Program serwer.c po utworzeniu swojej kolejki czeka na komunikaty oczekujac
 * dzialan matematycznych. Gdy sie pojawia odsyla wynik do klienta ktory wyslal
 * komunikat, w przypadku dzielenia przez zero odsyla zero.
 * W celu zakonczenia programu serwera nalezy podac z klawiatury ctrl-c
 *==============================================================================
 * Autor: Jan Krzemień					Data: 07.06.2023
 *==============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

#include "obsluga_kolejek.h"

// funkcja rejestrowana przez atexit
void atexitCleanUp(void)
{
    destroy_mq(SERWER_MQ);
}

// obsługa signału SIG_INT
void on_signal(int SIG)
{
    exit(0);
}

int main(void)
{
    // utworzenie kolejki do odbierania komunikatów
    int serwer_desc = create_mq(SERWER_MQ, O_RDONLY);
    if( serwer_desc == -1 ) exit(2);

	// informacje o kolejce serwera
	struct mq_attr que_attr;
	get_mq_attr(serwer_desc, &que_attr);
	printf("informacje o kolejce serwera:\n");
	printf("deskryptor: %d | nazwa: %s | max ilosc wiadomosci: %ld | max dlugosc wiadomosci: %ld\n", serwer_desc, SERWER_MQ, que_attr.mq_maxmsg, que_attr.mq_msgsize);

    // atexit, zarejestrowanie funkcji która usunie kolejki po zakończeniu programu
    if( atexit(atexitCleanUp) != 0 )
    {
	perror("atexit error");
	exit(3);
    }

    // obsługa sygnału SIG_INT, po otrzymaniu zakończenie programu i usunięcie kolejek
    if( signal(SIGINT, on_signal) == SIG_ERR )
    {
	perror("signal error");
	exit(4);
    }

    // losowość generowanych liczb
    srand( time(NULL) );

    // obsługa odebranych komunikatów
    char bufor[N], operacja = 'd', adres_klienta[8];
    int correctly_assigned, klient_desc, mq_receive_error;
    double num1 = 0,num2 = 0,wynik;
    // wczytanie komunikatu do zmiennej bufor
    while( ( mq_receive_error = receive_mq(serwer_desc, bufor, N) ) != -1 )
    {
		// wypisanie otrzymanego komunikatu
		printf("otrzymany komunikat: %s", bufor);

		// wyciągnięcie z komunikatu informacji
		correctly_assigned = sscanf(bufor, "%s %lf %c %lf", adres_klienta, &num1, &operacja, &num2);
		if( correctly_assigned < 4 )
		{
			printf("sscanf error przeczytano: %s %lf %c %lf\n", adres_klienta, num1, operacja, num2);
			exit(6);
		}

		// wykonanie operacji z komunikatu
		switch(operacja)
		{
			case '+':
			wynik = num1 + num2;
			break;
			case '-':
			wynik = num1 - num2;
			break;
			case '*':
			wynik = num1 * num2;
			break;
			case '/':
			if ( num2 == 0 )
			{
				printf("dzielenie przez 0, odsyłam w komunikacie 0\n");
				wynik = 0;
			}
			else
				wynik = num1 / num2;
			break;
			default:
				printf("nieznana operacja, odsyłam w komunikacie 0\n");
				wynik = 0;
		}

		// stworzenie komunikatu z wyniku działania
		correctly_assigned = snprintf(bufor, N, "%lg", wynik);
		if(correctly_assigned < 0 || correctly_assigned > N)
		{
			perror("snprintf error podczas zapisywania zmiennej double do tablicy char");
			exit(8);
		}

		// otworzenie kolejki klienta
		klient_desc = open_mq(adres_klienta, O_WRONLY);
		if(klient_desc == -1) exit(9);

		// uśpienie serwera na 1 lub 2 sekundy
		printf("usypiam serwer na 1 lub 2 sekundy\n");
		sleep(rand()%2 + 1);

		// odesłanie komunikatu
		if( send_mq(klient_desc, bufor, N) == -1 ) exit(10);

		// zamknięcie kolejki klienta
		if(close_mq(klient_desc) == -1) exit(11);
    }
    if( mq_receive_error == -1 ) exit(12);

    printf("zakonczono dzialanie serwera\n");

    // zamknięcie kolejki do odbierania komunikatów
    if( close_mq(serwer_desc) == -1 ) exit(13);
}
