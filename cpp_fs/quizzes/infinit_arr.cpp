#include <iostream>     // std::cout
#include <cstring>      // memset 


size_t Find(size_t *arr, size_t num, size_t jump)
{
    size_t i = 0;

    for (i = 0; arr[i] <= num; i += jump)
    {
        if (num == arr[i])
        {
            return i;
        }
        //else if  num < arr[i]
    }

    if (num < arr[i])
    {
        i += Find(&arr[i - jump], num, jump / 2) - jump;
    }

    return i;
}


int main()
{
    size_t arr[2000] = {0};

    for (size_t i = 1; i < 2000; i++)
    {
        arr[i] = i;
        // std::cout << arr[i] << " ";
    }
    std::cout << "somtething happen..." << std::endl;
    size_t index = Find(arr, 1022, 50);

    std::cout << index << std::endl;

    return 0;
}