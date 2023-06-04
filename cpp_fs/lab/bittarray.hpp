#ifndef __ILRD_RD96_BITTARRAY_HPP__
#define __ILRD_RD96_BITTARRAY_HPP__ 

#include <array> // std::array
#include <cstddef>  // size_t
#include <climits> // CHAR_BIT
#include <iostream>
#include <iterator>

#include <string>
#include <algorithm>


// typedef struct Bit Bit;
namespace ilrd 
{

class BitArray
{
public:
    BitArray();
    ~BitArray();

    struct Bit
    {
        bool b : 1;
    };
    Bit& operator[](size_t index);

private:
    static const size_t Bit_Array_Size = sizeof(size_t) * CHAR_BIT;
    std::array<int, Bit_Array_Size> m_arr;
};




} // end of namespace ilrd

 #endif   /*__ILRD_RD96_BITTARRAY_HPP__ */
