// pancake "sort" = Flip the arr from arr[0] until arr[index]
// 22.2.21

#include <iostream>     // std::cout, size_t

void Swap(int *one, int *two) 
{
    int tmp = *one;
    *one = *two;
    *two = tmp;
}

int *Flip(int *arr, size_t index)
{
    for(size_t i = 0; i < index; ++i, --index)
    {
        Swap(&arr[i], &arr[index]);
    }

    return arr;
}

int FindMax(int *arr, size_t n)
{
    size_t i = 0;
    size_t maxIndex = 0;

    for (maxIndex = 0, i = 0; i < n; ++i)
    {
        if (arr[maxIndex] < arr[i])
        {
            maxIndex = i;
        }
    }

    return maxIndex;
}

// simalar to isretion sort - take the max num to the end of the array
// after each iteration reduce the size of the array by 1 
// (to ignore the sorted elements in the Flip operation).
void pancakeSort(int *arr, size_t size)
{
    for (; 1 < size; --size) 
    {
        size_t maxIndex= FindMax(arr, size);
 
        if (maxIndex != size - 1) // if maxIndex isn't the last index already
        {
            // To move to the end,
            // first move max num to the beginning
            Flip(arr, maxIndex); 
            Flip(arr, size - 1);
        }
    }
}

int main()
{
    int arr[5] = {1, 3, 54, 24, 15};

    pancakeSort(arr, 5);

    for (int i = 0; i < 5; ++i)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}