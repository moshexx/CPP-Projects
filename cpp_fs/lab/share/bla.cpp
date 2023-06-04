#include <iostream>
#include "moshe.h" //for implicit only

int Bla(int a)
{
    std::cout << "int Bla\n";
    return (a * a);
}

int Bla(char a)
{
    std::cout << "char Bla\n";
    return (a * a);
}

int Bla(float a)
{
    std::cout << "float Bla\n";
    return (a * a);
}
