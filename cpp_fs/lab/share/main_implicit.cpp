#include <stdlib.h>
#include <iostream>
#include <dlfcn.h>

#include "moshe.h"
// must have h file
// compile: gd -shared -fpic bla.cpp foo.cpp -o lib.so
//          gd+ main_implicit.cpp lib.so -Wl,-rpath=$PWD

int main()
{
    
    float a = 4;
    int b = 4;
    char c = 4;

    std::cout << "implicit:" << std::endl;
    std::cout << Foo(a) << std::endl;
    std::cout << Foo(b) << std::endl;
    std::cout << Foo(c) << std::endl;
    std::cout << Bla(a) << std::endl;
    std::cout << Bla(b) << std::endl;
    std::cout << Bla(c) << std::endl;

}