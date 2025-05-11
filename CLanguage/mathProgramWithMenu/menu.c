#include <stdio.h>
#include <stdlib.h>

char menu();
int mainRowKwadratowe();
int mainSumaAB();
int mainUklad3x3();
int mainUkladRownan();

int main()
{
  while(1)
  {
    switch( menu() )
    {
      case '0':
        printf("kończe program\n");
        exit(0);
      case '1':
        printf("wybrano równanie kwadratowe\n");
        mainRowKwadratowe();
        break;
      case '2':
        printf("wybrano dwumian newtona\n");
        mainSumaAB();
	break;
      case '3':
        printf("wybrano uklad 2x2\n");
        mainUkladRownan();
        break;
      case '4':
        printf("wybrano uklad 3x3\n");
        mainUklad3x3();
        break;
      default:
        printf("nie ma takiej opcji\n");
    }
  }

  return 0;
}

char menu()
{
  printf("1. równanie kwadratowe\n");
  printf("2. dwumian newtona\n");
  printf("3. uklad 2x2\n");
  printf("4. uklad 3x3\n");
  printf("0. zakończenie programu\n");
  char wybor;
  /* %c wczytuje jeden znak ale enter zostaje w buforze co jest problemem */
  scanf("%s", &wybor);
  return wybor;
}
