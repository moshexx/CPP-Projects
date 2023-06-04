#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

int main()
{
    float *f = (float *)malloc(15 * sizeof(float));
    size_t i = 0;

    for (i = 0; i < 15; i++)
    {
        f[i] = i;
        printf("%lu\n", i);
    }
    printf("%f\n", f[i]);
    
    return 0;
}
