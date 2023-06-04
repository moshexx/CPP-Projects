#include<iostream>
#include<fstream>

size_t IKEA(const int *arr, const size_t size) 
{
	size_t count0 = 0;	//010101
	size_t count1 = 0;	//101010
	
	// arr[0] == 0 ? ++count0:++count1;

	for (size_t i = 0; i < size; ++i)
	{
		if (i % 2 == 0)
		{
			arr[i] == 0 ? ++count0:++count1;
		}
		else // if(i % 2 == 1)
		{
			arr[i] == 0 ? ++count1:++count0;
		}
	}

	if (count0 < count1)
	{
		return count0;
	}

	return count1;
}

int main()
{
	int arr[10] = {1, 1, 0, 1, 0, 1, 0, 1, 0, 1};


	size_t count = IKEA(arr, 10);

	std::cout << count << std::endl;


	return 0;
}
