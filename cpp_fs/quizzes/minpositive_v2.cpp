#include <bits/stdc++.h>
using namespace std;

void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

int segregate(int arr[], int size)
{
	int j = 0;

    // o(n)
	for (int i = 0; i < size; ++i) 
    {
		if (arr[i] <= 0) 
        {
			swap(&arr[i], &arr[j]);
			++j; 
		}
	}

	return j;
}

int findMissingPositive(int arr[], int size)
{
	int i;

	for (i = 0; i < size; i++) 
    {
		if (abs(arr[i]) - 1 < size && arr[abs(arr[i]) - 1] > 0)
		{
            arr[abs(arr[i]) - 1] = -arr[abs(arr[i]) - 1];
		}
	}

	for (i = 0; i < size; i++)
		if (arr[i] > 0)
        {
			return i + 1;
        }

	return size + 1;
}

int findMissing(int arr[], int size)
{
	int shift = segregate(arr, size);

	return findMissingPositive(arr + shift, size - shift);
}

const size_t SIZE = 4;
const size_t SIZE2 = 5;

int main()
{
	// int arr[] = { 0, 10, 2, -10, -20 };
	// int arr_size = sizeof(arr) / sizeof(arr[0]);
	// int missing = findMissing(arr, arr_size);

	// cout << "The smallest positive missing number is " << missing;


    int arr[] = {10, -10, 1, 3};
    int arr2[] = {1, 2, 4, 3};
    int arr3[] = {-1, -2, -4, -3, -2};

    int min1 = findMissing(arr, SIZE);  // 2
    int min2 = findMissing(arr2, SIZE); // 5
    int min3 = findMissing(arr3, SIZE2); // 1

    std::cout << min1 << std::endl;
    std::cout << min2 << std::endl;
    std::cout << min3 << std::endl;
    
	return 0;
}
