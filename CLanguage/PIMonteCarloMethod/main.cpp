#include <iostream>
#include <ctime>
#include <cstdlib>

int main()
{
    double d,x,y; 
    long int n = 100; // number of random points on xy plane in 1 by 1 square
    long int k = 0; // number of points that hit unit circle

    srand( time(NULL) );

    for( int i = 0; i < 8; i++, n*=10, k=0 )
    {
        for( int j = 0; j < n; j++ )
        {
            // random (x,y) point
            x = (double)rand() / RAND_MAX;
            y = (double)rand() / RAND_MAX;

            d = x*x + y*y ; // distance from point (0,0)
        
            if( d <= 1 ) k++;
        }

        std::cout << "dla " << n << " punktow pi jest " << k << " sukcesow, pi jest rowne " << 4*((double)k/(double)n) << std::endl;
    }

    return 0;
}