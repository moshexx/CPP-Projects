//*****************************************************************************
//*		Descriptions - bitarray		      				 					   
//*		Date: Sun 07 Mar 2021					     								   
//*		Group: RD96						      								   
//******************************************************************************

#ifndef ILRD_RD96_BITARRAY_HPP
#define ILRD_RD96_BITARRAY_HPP

#include <string>       // std::string
#include <climits>     // CHAR_BIT
#include <algorithm>   // fill, transform, equal, fill, for_each

namespace ilrd
{

template<size_t N>
class BitArray 
{
    class BitArrayProxy;

public:
    explicit BitArray();
    // ~BitArray(); - default
    //BitArray(const BitArray& other_); - default
    //BitArray& operator=(const BitArray& other_); - default

    BitArrayProxy operator[](size_t index);
    bool operator[](size_t index) const;

    BitArray& operator|=(const BitArray& other_);
    BitArray& operator&=(const BitArray& other_);
    BitArray& operator^=(const BitArray& other_);

    bool operator==(const BitArray& other_) const;
    bool operator!=(const BitArray& other_) const;

    bool Get(size_t index) const;
    BitArray& Set(bool val, size_t index);
    BitArray& Set(bool val);
    BitArray& Flip(size_t index);
    BitArray& Flip();
    size_t Count() const;
    std::string ToString() const;   // throw: bad_alloc

private:
    static const size_t WORD_SIZE_BITS = (sizeof(size_t) * CHAR_BIT);
    static const size_t ARRAY_SIZE = ((N - 1) / WORD_SIZE_BITS) + 1;
    size_t m_array[ARRAY_SIZE];

    void InitBitArray();
    void CleanUpPadding(size_t &last_index);

    class BitArrayProxy
    {
    public:
        explicit BitArrayProxy(BitArray& bit_array, size_t index);
        // ~BitArrayProxy(); - default

        BitArrayProxy& operator=(bool val);
        BitArrayProxy& operator=(const BitArrayProxy& other);
        operator bool() const;

    private:
        BitArray& m_bit_array;
        size_t m_index;
    }; // end of class BitArrayProxy
}; // end of class BitArray

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ implementation ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    namespace detail
	{
	static const size_t one = 1;
	static const size_t zero = 0;
    
    inline size_t GetElement(size_t index)
    {
        return (index / (sizeof(size_t) * CHAR_BIT));
    }

    inline size_t GetBitInElement(size_t index)
    {
        return(index % (sizeof(size_t) * CHAR_BIT));
    }

	inline void SetBit(size_t &bitarray, size_t index, size_t val)
	{
		bitarray ^= (-val ^ bitarray) & (detail::one << index);
	}
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~ FunctorCount ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        enum { OPTIONS = 256};
        static const unsigned char s_lut_count[OPTIONS] = 
            {0x0, 0x1, 0x1, 0x2, 0x1, 0x2, 0x2, 0x3, 0x1, 0x2,0x2, 0x3, 0x2, 0x3, 0x3, 0x4, 0x1, 0x2, 0x2, 0x3, 0x2, 0x3, 0x3, 0x4,
            0x2, 0x3, 0x3, 0x4, 0x3, 0x4, 0x4, 0x5,0x1, 0x2, 0x2, 0x3, 0x2, 0x3, 0x3, 0x4, 0x2, 0x3, 0x3, 0x4, 0x3, 0x4, 0x4, 0x5, 0x2, 0x3, 0x3, 0x4, 0x3, 0x4, 0x4, 0x5,
            0x3, 0x4, 0x4, 0x5, 0x4, 0x5, 0x5, 0x6, 0x1, 0x2, 0x2, 0x3, 0x2, 0x3, 0x3, 0x4, 0x2, 0x3, 0x3, 0x4, 0x3, 0x4, 0x4, 0x5, 0x2, 0x3, 0x3, 0x4, 0x3, 0x4, 0x4, 0x5, 
            0x3, 0x4, 0x4, 0x5, 0x4, 0x5, 0x5, 0x6, 0x2, 0x3, 0x3, 0x4, 0x3, 0x4, 0x4, 0x5, 0x3, 0x4, 0x4, 0x5, 0x4, 0x5, 0x5, 0x6, 0x3, 0x4, 0x4, 0x5, 0x4, 0x5, 0x5, 0x6, 
            0x4, 0x5, 0x5, 0x6, 0x5, 0x6, 0x6, 0x7, 0x1, 0x2, 0x2, 0x3, 0x2, 0x3, 0x3, 0x4, 0x2, 0x3, 0x3, 0x4, 0x3, 0x4, 0x4, 0x5, 0x2, 0x3, 0x3, 0x4, 0x3, 0x4, 0x4, 0x5, 
            0x3, 0x4, 0x4, 0x5, 0x4, 0x5, 0x5, 0x6, 0x2, 0x3, 0x3, 0x4, 0x3, 0x4, 0x4, 0x5, 0x3, 0x4, 0x4, 0x5, 0x4, 0x5, 0x5, 0x6, 0x3, 0x4, 0x4, 0x5, 0x4, 0x5, 0x5, 0x6,
            0x4, 0x5, 0x5, 0x6, 0x5, 0x6, 0x6, 0x7, 0x2, 0x3, 0x3, 0x4, 0x3, 0x4, 0x4, 0x5, 0x3, 0x4, 0x4, 0x5, 0x4, 0x5, 0x5, 0x6, 0x3, 0x4, 0x4, 0x5, 0x4, 0x5, 0x5, 0x6,
            0x4, 0x5, 0x5, 0x6, 0x5, 0x6, 0x6, 0x7, 0x3, 0x4, 0x4, 0x5, 0x4, 0x5, 0x5, 0x6, 0x4, 0x5, 0x5, 0x6, 0x5, 0x6, 0x6, 0x7, 0x4, 0x5, 0x5, 0x6, 0x5, 0x6, 0x6, 0x7,
            0x5, 0x6, 0x6, 0x7, 0x6, 0x7, 0x7, 0x8};

    class FunctorCount
    {
    public:
        FunctorCount(size_t &_count):count(_count) {}
        void operator()(const unsigned char& byte) 
        {
            count += s_lut_count[byte];
        }

    private:
        size_t& count;
    }; // end of class FunctorCount

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~ FunctorString ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    static const char *s_lut_string[OPTIONS] = 
    {"00000000", 
    "10000000", "01000000", "11000000", "00100000", "10100000", "01100000", 
    "11100000", "00010000", "10010000", "01010000", "11010000", "00110000", 
    "10110000", "01110000", "11110000", "00001000", "10001000", "01001000", 
    "11001000", "00101000", "10101000", "01101000", "11101000", "00011000", 
    "10011000", "01011000", "11011000", "00111000", "10111000", "01111000", 
    "11111000", "00000100", "10000100", "01000100", "11000100", "00100100", 
    "10100100", "01100100", "11100100", "00010100", "10010100", "01010100", 
    "11010100", "00110100", "10110100", "01110100", "11110100", "00001100", 
    "10001100", "01001100", "11001100", "00101100", "10101100", "01101100", 
    "11101100", "00011100", "10011100", "01011100", "11011100", "00111100", 
    "10111100", "01111100", "11111100", "00000010", "10000010", "01000010", 
    "11000010", "00100010", "10100010", "01100010", "11100010", "00010010", 
    "10010010", "01010010", "11010010", "00110010", "10110010", "01110010", 
    "11110010", "00001010", "10001010", "01001010", "11001010", "00101010", 
    "10101010", "01101010", "11101010", "00011010", "10011010", "01011010", 
    "11011010", "00111010", "10111010", "01111010", "11111010", "00000110", 
    "10000110", "01000110", "11000110", "00100110", "10100110", "01100110", 
    "11100110", "00010110", "10010110", "01010110", "11010110", "00110110", 
    "10110110", "01110110", "11110110", "00001110", "10001110", "01001110", 
    "11001110", "00101110", "10101110", "01101110", "11101110", "00011110", 
    "10011110", "01011110", "11011110", "00111110", "10111110", "01111110", 
    "11111110", "00000001", "10000001", "01000001", "11000001", "00100001", 
    "10100001", "01100001", "11100001", "00010001", "10010001", "01010001", 
    "11010001", "00110001", "10110001", "01110001", "11110001", "00001001", 
    "10001001", "01001001", "11001001", "00101001", "10101001", "01101001", 
    "11101001", "00011001", "10011001", "01011001", "11011001", "00111001", 
    "10111001", "01111001", "11111001", "00000101", "10000101", "01000101", 
    "11000101", "00100101", "10100101", "01100101", "11100101", "00010101", 
    "10010101", "01010101", "11010101", "00110101", "10110101", "01110101", 
    "11110101", "00001101", "10001101", "01001101", "11001101", "00101101", 
    "10101101", "01101101", "11101101", "00011101", "10011101", "01011101", 
    "11011101", "00111101", "10111101", "01111101", "11111101", "00000011", 
    "10000011", "01000011", "11000011", "00100011", "10100011", "01100011", 
    "11100011", "00010011", "10010011", "01010011", "11010011", "00110011", 
    "10110011", "01110011", "11110011", "00001011", "10001011", "01001011", 
    "11001011", "00101011", "10101011", "01101011", "11101011", "00011011", 
    "10011011", "01011011", "11011011", "00111011", "10111011", "01111011", 
    "11111011", "00000111", "10000111", "01000111", "11000111", "00100111", 
    "10100111", "01100111", "11100111", "00010111", "10010111", "01010111", 
    "11010111", "00110111", "10110111", "01110111", "11110111", "00001111", 
    "10001111", "01001111", "11001111", "00101111", "10101111", "01101111", 
    "11101111", "00011111", "10011111", "01011111", "11011111", "00111111", 
    "10111111", "01111111", "11111111" };

    class FunctorString
    {
    public:
        FunctorString(std::string& _str): str(_str) {}
        void operator()(const unsigned char& byte)
        {
            str += s_lut_string[byte];
        }

    private:
        std::string& str;
    }; // end of class FunctorString

	} //end namespace detail 

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ BitArray ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<size_t N>
BitArray<N>::BitArray()
{   
    std::fill(m_array, m_array + sizeof(m_array) / sizeof(size_t), 0);
}

template<size_t N>
typename BitArray<N>::BitArrayProxy BitArray<N>::operator[](size_t index)
{
	return BitArrayProxy(*this, index); // no Ctor() will be called
}

template<size_t N>
bool BitArray<N>::operator[](size_t index) const
{
    size_t specificIndex = detail::GetElement(index);
    size_t bitIndex = detail::GetBitInElement(index);

	return ((m_array[specificIndex] >> bitIndex) & detail::one);
}

// BitArrayProxy
template<size_t N>
BitArray<N>::BitArrayProxy::BitArrayProxy(BitArray& bit_array, size_t index):
m_bit_array(bit_array), m_index(index)
{	// empty
}

template<size_t N>
typename BitArray<N>::BitArrayProxy& BitArray<N>::BitArrayProxy::operator=(bool val)
{
    size_t specificIndex = detail::GetElement(m_index);
    size_t bitIndex = detail::GetBitInElement(m_index);

	detail::SetBit(m_bit_array.m_array[specificIndex], bitIndex, val); 

	return *this;
}

template<size_t N>
typename BitArray<N>::BitArrayProxy& BitArray<N>::BitArrayProxy::operator=(const BitArrayProxy& val)
{
	return *this = bool(val);
}

template<size_t N>
BitArray<N>::BitArrayProxy::operator bool() const
{
	return static_cast<const BitArray&>(m_bit_array)[m_index];
}

template<size_t N>
BitArray<N>& BitArray<N>::operator|=(const BitArray& other_)
{
    std::transform(m_array, m_array + ARRAY_SIZE, other_.m_array, m_array,
                                                     std::bit_or<size_t>());

    return *this;
}

template<size_t N>
BitArray<N>& BitArray<N>::operator&=(const BitArray& other_)
{
    std::transform(m_array, m_array + ARRAY_SIZE, other_.m_array, m_array,
                                                     std::bit_and<size_t>());

    return *this;
}

template<size_t N>
BitArray<N>& BitArray<N>::operator^=(const BitArray& other_)
{
    std::transform(m_array, m_array + ARRAY_SIZE, other_.m_array, m_array, std::bit_xor<size_t>());

    return *this;
}

template<size_t N>
bool BitArray<N>::Get(size_t index) const
{
    return (*this)[index];
}

template<size_t N>
BitArray<N>& BitArray<N>::Set(bool val, size_t index)
{
    (*this)[index] = val;

    return *this;
}

template<size_t N>
BitArray<N>& BitArray<N>::Set(bool val)
{
    size_t value = -val; // optimization (instead of if-else)

    std::fill(m_array, m_array + ARRAY_SIZE, value);
    CleanUpPadding(m_array[ARRAY_SIZE - 1]);

    return *this;
}

template<size_t N>
BitArray<N>& BitArray<N>::Flip(size_t index)
{
    (*this)[index] = !(*this)[index];

    return *this;
}

template<size_t N>
BitArray<N>& BitArray<N>::Flip()
{
    BitArray tmp;

    tmp.Set(true);
    (*this) ^= tmp;

    return *this;
}

template<size_t N>
bool BitArray<N>::operator==(const BitArray& other_) const
{
    return std::equal(m_array, m_array + ARRAY_SIZE, other_.m_array);
}

template<size_t N>
bool BitArray<N>::operator!=(const BitArray& other_) const
{
    return !(*this == other_);
}

template<size_t N>
size_t BitArray<N>::Count() const
{
    size_t count = 0;
    detail::FunctorCount myFunctor(count);
    const size_t stepSize = sizeof(size_t) / sizeof(unsigned char);

    std::for_each(reinterpret_cast<const unsigned char *>(m_array),
        reinterpret_cast<const unsigned char*>(m_array) + stepSize * ARRAY_SIZE, myFunctor);
    
    return count;
}

template<size_t N>
std::string BitArray<N>::ToString() const
{
    std::string str("");
    detail::FunctorString myFunctor(str);
    const size_t stepSize = sizeof(size_t) / sizeof(unsigned char);

    std::for_each(reinterpret_cast<const unsigned char *>(m_array),
        reinterpret_cast<const unsigned char*>(m_array) + stepSize * ARRAY_SIZE, myFunctor);

    str.resize(N);
    std::reverse(str.begin(), str.end());

    return str;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~ helper members methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<size_t N>
inline void BitArray<N>::CleanUpPadding(size_t &last_index)
{
    static const size_t s_mask = ~detail::zero >> (WORD_SIZE_BITS - (N -(ARRAY_SIZE - 1) * WORD_SIZE_BITS));

    last_index &= s_mask;
}
} //end namespace ilrd

#endif   /*ILRD_RD96_BITARRAY_HPP*/