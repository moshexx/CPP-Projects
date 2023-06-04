// 23.02.2021
/* 
You are given an array data structure. Implement the following functions in O(1):
void SetVal(int index, int val);
int GetVal(int index);
void SetAll(int val); //no memset!
*/

#include <iostream>     // std::cout
#include <cstring>      // memset 

const int SIZE = 100;

enum {I_VAL = 0, I_COUNT = 1};

class Array
{
public:
    Array(): m_count_set_all(0)
    {
        memset(m_arr, 0, sizeof(m_arr));
    }

    void SetVal(int index, int val)
    {
        m_arr[index][I_VAL] = val;
        m_arr[index][I_COUNT] = m_count_set_all;
    }

    int GetVal(int index)
    {
        if (m_count_set_all <= m_arr[index][I_COUNT])
        {
            return m_arr[index][I_VAL];
        }
        else
        {
            return update;
        }
    }

    void SetAll(int val)
    {
        update = val;
        ++m_count_set_all;
    }

private:
    int update;
    int m_count_set_all;
    int m_arr[SIZE][2];
};


int main() 
{
    Array array;
    array.SetVal(0, 1);
    array.SetVal(1, 2);
    array.SetVal(2, 3);
    array.SetVal(3, 4);
    array.SetVal(4, 5);

    std::cout << "SetVal (1 - 5):\n";
    std::cout << array.GetVal(0) << std::endl;
    std::cout << array.GetVal(1) << std::endl;
    std::cout << array.GetVal(2) << std::endl;
    std::cout << array.GetVal(3) << std::endl;
    std::cout << array.GetVal(4) << std::endl;

    std::cout << "SetAll(9):\n";
    array.SetAll(9);
    std::cout << array.GetVal(0) << std::endl;
    std::cout << array.GetVal(1) << std::endl;
    std::cout << array.GetVal(2) << std::endl;
    std::cout << array.GetVal(3) << std::endl;
    std::cout << array.GetVal(4) << std::endl;

    std::cout << "setVal: arr[3] = 4, arr[4] = 5:\n";
    array.SetVal(3, 4);
    array.SetVal(4, 5);
    std::cout << array.GetVal(0) << std::endl;
    std::cout << array.GetVal(1) << std::endl;
    std::cout << array.GetVal(2) << std::endl;
    std::cout << array.GetVal(3) << std::endl;
    std::cout << array.GetVal(4) << std::endl;

    std::cout << "SetAll(122):\n";
    array.SetAll(122);
    std::cout << array.GetVal(0) << std::endl;
    std::cout << array.GetVal(1) << std::endl;
    std::cout << array.GetVal(2) << std::endl;
    std::cout << array.GetVal(3) << std::endl;
    std::cout << array.GetVal(4) << std::endl;

    return 0;
}
