#include <stdio.h>

double wyznacznik3x3(double[3][3]);
int uklad3(double[3][3], double[3], double[3]);
void sprawdzenie3x3(double[3][3], double[3], double[3]);

/* program rozwiązujący układ równań 3x3 */
int mainUklad3x3()
{
  double a[3][3], b[3], xyz[3], out[3];

  printf("Podaj uklad w postaci:\na11x+a12y+a13z=b1\na21x+a22y+a23z=b1\na31x+a32y+a33z=b3\n\n");
  if(scanf("%lgx%lgy%lgz=%lg", &a[0][0], &a[0][1], &a[0][2], &b[0]) < 3)
  {
    printf("input error\n");
    return -1;
  }
  if(scanf("%lgx%lgy%lgz=%lg", &a[1][0], &a[1][1], &a[1][2], &b[1]) < 3)
  {
    printf("input error\n");
    return -1;
  }
  if(scanf("%lgx%lgy%lgz=%lg", &a[2][0], &a[2][1], &a[2][2], &b[2]) < 3)
  {
    printf("input error\n");
    return -1;
  }

  int n = uklad3(a, b, xyz);
  if(n == 1)
  {
    sprawdzenie3x3(a, xyz, out);
    printf("sprawdzenie %lg=%lg %lg=%lg %lg=%lg | x=%lg y=%lg z=%lg\n", b[0], out[0], b[1], out[1], b[2], out[2], xyz[0], xyz[1],  xyz[2]);
    return 1;
  }

  printf("brak rozwiązań lub nieskończenie wiele rozwiązań\n");
  return 0;
}
