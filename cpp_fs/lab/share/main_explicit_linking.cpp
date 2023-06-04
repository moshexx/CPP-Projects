#include <stdlib.h>
#include <iostream>
#include <dlfcn.h>



int main(int argc, char **argv)
{
    int a = 4;
    void *handle;
    int (*ptr)(int);
    char *error = NULL;

    handle = dlopen ("./lib.so", RTLD_LAZY);
    if (!handle)
    {
        std::cerr << error << std::endl;
        exit(1);
    }
    *(void **)(&ptr)  = dlsym(handle, argv[1]);
    if ((error = dlerror()) != NULL)
    {
        std::cerr << error << std::endl;
        exit(1);
    }
    a = ptr(a);
    std::cout << "explicit:" << std::endl;
    std::cout << "Foo(a) =" << a << std::endl;
    dlclose(handle);

    (void)argc;
    return 0;
}