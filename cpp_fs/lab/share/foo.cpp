#include <iostream>
#include "moshe.h" //for implicit only

int Foo(char a)
{
    std::cout << "char Foo\n";
    return (a + 10);
}

int Foo(int a)
{
    std::cout << "int Foo\n";
    return (a + 10);
}

int Foo(float a)
{
    std::cout << "float Foo\n";
    return (a + 10);
}
