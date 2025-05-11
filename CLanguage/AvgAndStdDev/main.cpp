#include <iostream>
#include <ctime>
#include <cmath>


int main()
{
    srand( time(0) );

    double num, sum = 0, stdD, avg;
    int count = 0;

    for (int i = 0; i < 1000; i++, count++)
    {
        num = (double)rand() / (RAND_MAX + 1.0);
        sum += num;
        stdD += pow(num - 0.5, 2);
    }

    avg = sum / count;
    stdD /= count;
    stdD = sqrt(stdD);

    std::cout << "average is " << avg << " standard deviation is " << stdD << std::endl;
    
}