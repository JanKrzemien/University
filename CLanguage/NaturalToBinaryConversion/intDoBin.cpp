#include <iostream>

#define N 300
#define END_OF_STRING '\0'

int Konwersja_Dec_Bin_a(unsigned dec, char * bin);
int Konwersja_Dec_Bin_b(unsigned dec, char * bin);

int main()
{
    char bin[N];
    unsigned int dec;
    std::cout << "podaj liczbe naturalna: ";
    std::cin >> dec;

    std::cout << "number of digits in binary representation: " << Konwersja_Dec_Bin_b(dec, bin) << std::endl;
    std::cout << bin << std::endl;

    return 0;
}

int Konwersja_Dec_Bin_a(unsigned dec, char * bin)
{
    // conversion dec to bin
    int i = 0;
    while( dec != 0 )
    {
        if( dec % 2 == 1 )
            bin[i] = '1';
        else
            bin[i] = '0';
        
        dec = dec / 2;
        i++;
    }
    bin[i] = END_OF_STRING;

    // reversing order of the bin array
    char temp;
    for (int j = i - 1, k = 0; j >= i/2 && k < i/2; j--, k++)
    {
        temp = bin[j];
        bin[j] = bin[k];
        bin[k] = temp;
    }

    return i;
}

int Konwersja_Dec_Bin_b(unsigned dec, char * bin)
{
        // conversion dec to bin
    int i = 0;
    while( dec != 0 )
    {
        if( dec % 2 == 1 )
            bin[i] = '1';
        else
            bin[i] = '0';
        
        dec = dec >> 1;
        i++;
    }
    bin[i] = END_OF_STRING;

    // reversing order of the bin array
    char temp;
    for (int j = i - 1, k = 0; j >= i/2 && k < i/2; j--, k++)
    {
        temp = bin[j];
        bin[j] = bin[k];
        bin[k] = temp;
    }

    return i;
}