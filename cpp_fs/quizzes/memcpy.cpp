// #include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define WORD_SIZE (sizeof(size_t))

void *Memcpy(void *dest, const void *src, size_t n) 
{
    char *runner = (char *)dest;

    for (; 0 < n; --n)
    {
        *runner = *(char *)src;
        src = *(char **)&src + 1;
        ++runner;
    }

    return dest;
}

void *OptimalMemcpy(void *dest, const void *src, size_t n) 
{
    char *runner = (char *)dest;
    
    while ((0 < n) && (0 < (size_t)src % WORD_SIZE))
    {
        *runner = *(char *)src;
         נ מ
        ++runner;
        --n;
    }

    while (WORD_SIZE <= n)
    {
        *(size_t *)runner = *(size_t *)src;
        runner = runner + WORD_SIZE;
        src = *(char **)&src + WORD_SIZE;
        n -= WORD_SIZE;
    }

    while (0 < n)
    {
        *runner = *(char *)src;
        src = *(char **)&src + 1;
        ++runner;
        --n;
    }

    return dest;
}

void TestNotAligned();
int main()
{
    char *dest = (char *)malloc(6);
    const char *n = "hello";
    char *src = (char *)n;

    OptimalMemcpy(dest, src, 6);
    // std::cout << *dest << std::endl;
    printf("%s\n", dest);
    // printf("%s\n", src);
    // printf("%s\n", n);

    free (dest);

    char *str = (char *)malloc(20);
	char *str2 = (char *)malloc(20);
	char str3[] = "HelloHelloHello";
		
	
	OptimalMemcpy(str ,str3 ,12);
	printf("str_dest:%s \nstr_src :%s\n" ,str ,str3); 
 	printf("size: %lu\n", strlen(str));
 	free(str);
 	free(str2);   

    TestNotAligned();

    return 0;
}

void TestNotAligned()
{
    const char *src = "Khello world hello world hello world";
    char *dest = (char *)malloc(sizeof(char) * (strlen(src) + 2));
    
    dest = *(char **)&dest + 1;
    src = *(char **)&src + 1;

    dest = (char *)OptimalMemcpy(dest, src, (strlen("hello world hello world hello world") + 1));

    printf("%s\n", dest);
    /*free(dest);
*/
}