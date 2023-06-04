// 2.2.21
// Sort By height
// -1 represent tree - tree can't move past
// O(n^2^num of trees)
// we should sort the array by height without move the tress between the people.
// arr is set of people with heights.


 #include <iostream>

void Swap(int *one, int *other)
{
    int tmp = *one;
    *one = *other;
    *other = tmp;
}

void SortByHeight(int *arr, size_t size) 
{
    for (; 0 < size; --size)
    {
        for (size_t i = 0, j = 1;  j < size; ++i, ++j)
        {
            while (-1 == arr[i])
            {
                ++i;
                j += i==j;
            }
            while (-1 == arr[j])
            {
                ++j;
            }

            if (arr[i] > arr[j])
            {
                Swap(&arr[i], &arr[j]);
            }
        }
    }
}


int main()
{
    int arr[] = {166,-1,152,-1,-1,155,172};

    SortByHeight(arr, 7);

    for (size_t i = 0; i < 7; ++i)
    {
        std::cout << arr[i] << "  " << std::endl;
    }
    std::cout << std::endl;
    
    return 0;
}