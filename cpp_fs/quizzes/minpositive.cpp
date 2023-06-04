// 26.1.2021
//find the minimum positive number which doesn't apear in the arr.

#include <iostream>     // std::cout
#include <new>          // ::operator new[]
#include <cstring>      // memset

const size_t SIZE = 4;
const size_t SIZE2 = 5;

// time worst O(2n) = O(n)
// space O(n)
int FindMinPositiveMissing(const int *arr, size_t size) 
{
    int *histogram = new int[1 + size];
    size_t i = 0;

    memset(histogram, 0, (1 + size) * sizeof(int));

    for (i = 0; i < size; ++i)
    {
        if (0 < arr[i] && arr[i] <= size)
        {
            histogram[arr[i]-1] = 1;
        }
    }

    for (i = 0; i < size; ++i)
    {
        if (0 == histogram[i])
        {
            break;
        }
    }

    int winner = i + 1;
    delete[] histogram;
    
    return winner;
}

int main()
{
    int arr[] = {10, -10, 1, 3};
    int arr2[] = {1, 2, 4, 3};
    int arr3[] = {-1, -2, -4, -3, -2};

    int min1 = FindMinPositiveMissing(arr, SIZE);   // 2
    int min2 = FindMinPositiveMissing(arr2, SIZE);  // 5
    int min3 = FindMinPositiveMissing(arr3, SIZE2); // 1

    std::cout << min1 << std::endl;
    std::cout << min2 << std::endl;
    std::cout << min3 << std::endl;

    return 0;
}