#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        std::cout << "wrong number of arguments" << std::endl;
        return -1;
    }

    std::string pass;

    std::cout << "type password to cipher: ";
    std::cin >> pass;

    FILE * file;

    if(NULL == (file = fopen(argv[1], "rb"))) return 1;

    FILE * file_temp;
    char temp_name[20];
    tmpnam(temp_name);

    if(NULL == (file_temp = fopen(temp_name, "wb"))) return 1;

    int pass_len = pass.size();
    char znak;
    long int j = 0;
    while(znak=getc(file))
    {
        znak = pass[j % pass_len];
        putc(znak, file_temp);
    }

    unlink(argv[1]);
    rename(temp_name, argv[1]);

    return 0;
}