#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

// no need in h file
// compile acording the instruction in readme file

int main(int argc, char **argv)
{
    void *handle;
    int a = 4;
    int (*ptr)();
    char *error;

    handle = dlopen ("./lib.so", RTLD_LAZY);
    if (!handle)
    {
        fputs (dlerror(), stderr);
        exit(1);
    }
    *(void **)(&ptr)  = dlsym(handle, argv[1]);
    if ((error = dlerror()) != NULL)
    {
        fputs(error, stderr);
        exit(1);
    }
    a = ptr(a);
    printf ("Foo(a) = %d\n", a);
    dlclose(handle);

    return 0;
}