#include <math.h>

double Determinant(int n, double a[][n])
{
  int i, j, j1, j2;
  double det = 0;
  double m[n-1][n-1];
  if(n == 2)
  {
    det = a[0][0]*a[1][1] - a[1][0]*a[0][1];
  }
  else
  {
    det = 0;

    for(j1 = 0; j1 < n; j1++)
    {
	    for(i = 1; i < n; i++)
	    {
		    j2 = 0;
		    for(j = 0; j < n; j++)
		    {
			    if(j == j1) continue;

			    m[i-1][j2] = a[i][j];

			    j2++;
		    }
	    }
	    det += pow(-1.0, 1.0+j1+1.0)*a[0][j1]*Determinant(n-1,m);
    }
  }
  
  return(det);
}
