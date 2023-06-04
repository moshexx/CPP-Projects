// אתה מקבל מערך ממוין, שיכול להחזיק בתוכו כפילויות של מספרים
// לדוגמה
// 1 1 2 2 3 3 3
// לבנות פונקציה שמוחקת כפילויות של מספרים כך שיכולות להישאר עד 2 חזרות של כל מספר
// ערך החזרה - אורך המערך החדש
// 1 1 2 2 3 3 או 1 1 2 2 3 
// inplace

#include <iostream>     // std::cout
#include <cstring>      // memset 


void RemoveElementInArray(size_t *arr, size_t index, size_t size)
{
    for (size_t i = index; i < size; ++i)
    {
        arr[i] = arr[i+1];
    }
}

size_t Yoni(size_t arr[], size_t size)
{
    size_t new_size = size;

    for (size_t i = 1; i < size - 1; ++i)
    {
        if (arr[i] == arr[i + 1] && arr[i] == arr[i - 1])
        {
            RemoveElementInArray(arr, i, new_size);
            --new_size;
            if (arr[i] == arr[i - 1])
            {
                RemoveElementInArray(arr, i, new_size);
                --new_size;
            }
        }
    }

    return new_size;
}

int main()
{
    size_t arr[] = {0,1,1,2,2,3,3,3,6};
    size_t size = sizeof(arr)/sizeof(arr[0]);

    size_t new_size = Yoni(arr, size);

    std::cout << "new size: " << new_size << std::endl;

    for (size_t i = 0; i < new_size; ++i)
    {
        std::cout << arr[i] << std::endl;
    }

    return 0;
}