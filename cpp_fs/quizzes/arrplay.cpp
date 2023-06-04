// 9.2.2021
/* Given an array of scores that are positive integers.
   Player 1 picks one of the numbers from either end of
   the array followed by player 2 and then player 1 and so on.
    Each time a player picks a number, that number will not be
    available for the next player. This continues until all the
    scores have been chosen. The player with the maximum score wins.

    ניתן לבחור משני צידי המערך בכל סיבוב. */

#include <iostream>     // std::size_t, 

template<class T>
inline T Max(T min, T max)
{
    return min < max ?  max : min;
}

// return 1 or 2
int Play(const int *arr, size_t size)
{
    size_t l = 0;
    size_t r = size - 1;
    int score1 = 0;
    int score2 = 0;

    while (2 < (r - l))
    {
        int leftChoise = arr[l] - arr[l + 1];
        int rightChoise = arr[r] - arr[r - 1];
         
        if (leftChoise == Max(leftChoise, rightChoise))
        {
            score1 += arr[l];
            ++l;
        }
        else
        {
            score1 += arr[r];
            --r;
        }

        leftChoise = arr[l] - arr[l + 1];
        rightChoise = arr[r] - arr[r - 1];
        
        if (leftChoise == Max(leftChoise, rightChoise))
        {
            score2 += arr[l];
            ++l;
        }
        else
        {
            score2 += arr[r];
            --r;
        }
    }

    while (1 < r - l)
    {
        if (arr[l] == Max(arr[l], arr[r]))
        {
            score1 += arr[l];
            ++l;
        }
        else
        {
            score1 += arr[r];
            --r;
        }

        if (arr[l] == Max(arr[l], arr[r]))
        {
            score2 += arr[l];
            ++l;
        }
        else
        {
            score2 += arr[r];
            --r;
        }
    }

     if (1 == r - l)
    {
        if (arr[l] == Max(arr[l], arr[r]))
        {
            score1 += arr[l];
            ++l;
        }
        else
        {
            score1 += arr[r];
            --r;
        }
    }
    if (score2 <= score1)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}



// another solution 

bool IsPlayer1Win(int *arr, size_t size)
{
    size_t left = 0;
    size_t right = size - 1;
    size_t sum1 = 0;
    size_t sum2 = 0;
    int chosen = 0;

    for (size_t i = 0; i < size; ++i)
    {
        if (arr[left] - arr[right] - arr[left + 1]) < 
            arr[right] - arr[left] - arr[right - 1]
        {
            chosen = arr[right];
            --right;
        }
        else
        {
            chosen = arr[left];
            ++left;
        }
        if ((i % 2) == 0)
        {
            sum1 += chosen;
        }
        else
        {
            sum2 += chosen;
        }
    }
    return (sum2 <= sum1);
}

int main()
{
    int arr1[8] = {5, 9, 2, 1, 20, 10, 13, 15};
    int arr2[3] = {1, 6, 2};
    int arr3[4] = {1, 20, 300, 10};

    std::cout << "result 1 = (1)" << IsFirstWin(arr1, 8) << std::endl;
    std::cout << "result 2 = (0)" << IsFirstWin(arr2, 3) << std::endl;
    std::cout << "result 3 = (1)" << IsFirstWin(arr3, 4) << std::endl;
    
}


int main()
{
    int arr1[] = {1, 20, 300, 10};
    int arr2[] = {1, 6, 2};
    int arr3[] = {1, 20, 1000 ,300 ,10};

    if (1 == Play(arr1, 4))
    {
        std::cout << "SUCCESS - Player1 won" << std::endl;
    }

    if (2 == Play(arr2, 3))
    {
        std::cout << "SUCCESS - Player2 won" << std::endl;
    }
    if (2 == Play(arr2, 5))
    {
        std::cout << "SUCCESS - Player2 won" << std::endl;
    }

    return 0;
}