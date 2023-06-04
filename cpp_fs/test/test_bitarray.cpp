/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_bitarray.cpp
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
#include <iostream>
#include <cstring>
#include <cassert>

const char *RED_B = "\033[01;31m";
const char *GREEN_B = "\033[01;32m";
const char *YELLOW_B = "\033[01;33m";
const char *BLUE_B = "\033[01;34m";
const char *BLACK_B = "\033[01;30m";
const char *WHITE_B = "\033[01;37m";
const char *RED = "\033[0;31m";
const char *GREEN = "\033[0;32m";
const char *YELLOW = "\033[0;33m";
const char *RESET = "\033[0m";
void RunTest(bool result, const char *name)
{
    std::cout << YELLOW_B << "Test "  << name << ": " << RESET;
    if (result)
    {
        std::cout << GREEN_B << "SUCCESS" << RESET << std::endl;
    }
    else
    {
        std::cout << RED_B << "FAILURE" << RESET << std::endl;
    }
}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#include "bitarray.hpp"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static const size_t BITS_PER_WORD = sizeof(size_t) * CHAR_BIT;
static const size_t LESS = 13;
static const size_t MORE = 200;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
using namespace ilrd;

int TestPhaseOne();
void TestNewCosntObj(void);
void TestAssignmentBool(void);
void TestAssignmentProxy(void);
int TestMultiElement(void);
int TestOrOperator(void);
int TestAndOperator(void);
int TestXorOperator(void);
int TestSetAll(void);
int TestSetIndex(void);
int TestFlip(void);
int TestFlipAll(void);
int TestIsequal(void);
int TestSpareBits(void);
int TestCount(void);
void TestToString(void);

int main()
{
    RunTest(TestPhaseOne(),"TestPhaseOne");
    TestNewCosntObj();
    TestAssignmentBool();
    TestAssignmentProxy();
    RunTest(TestMultiElement(), "Multiple elements");
    RunTest(TestOrOperator(), "Or operator");
    RunTest(TestAndOperator(), "And operator");
    RunTest(TestXorOperator(), "Xor operator");
    RunTest(TestSetAll(), "SetAll");
    RunTest(TestSetIndex(), "SetIndex");
    RunTest(TestFlip(), "TestFlip");
    RunTest(TestFlipAll(), "TestFlipAll");
    RunTest(TestIsequal(), "TestIsequal");
    RunTest(TestSpareBits(), "SpareBits");
    RunTest(TestCount(), "TestCount");
    TestToString();

    return 0;
}

int TestPhaseOne()
{
    size_t res = 0;

    BitArray<64> b1;
    BitArray<64> b2;

    assert(b1[0] == false); // Ctor test
    assert(b1[15] == false); // Ctor test
    assert(b1[22] == false); // Ctor test

    b1[0] = true;
    b2[0] = true;
    res += b1[0] && b2[0];

    b1[2] = b1[1] = b1[0];

    if(b1[2] && b1[1])
    {
        ++res;
        b1[0] = false;
    }

    if(!b1[0])
    {
        ++res;
    }

    b1[63] = b2[0];

    res += b1[63] && b2[0];

    res += b2[61] == false;

    BitArray<70> b3;
    BitArray<70> b4;
    b3 == b4;
    
    return res == 5;
}


int TestSetIndex(void)
{
    BitArray<BITS_PER_WORD> b1;

    b1.Set(true);
    
    for (size_t i = 0; i < BITS_PER_WORD; ++i)
    {
        if (0 != i%2)
        {
            b1.Set(true, i);
            assert(b1[i] == true);
        }
    }

    return true;
}

int TestSetAll(void)
{
    int res = 0;
    BitArray<BITS_PER_WORD> word;
    word.Set(true);
    
    for (size_t i = 0; i <BITS_PER_WORD; ++i)
    {
        res += (word[i] == true);
    }
    word.Set(false);
    for (size_t i = 0; i <BITS_PER_WORD; ++i)
    {
        res += (word[i] == false);
    }

    BitArray<LESS> less;
    less.Set(true);
    
    for (size_t i = 0; i <LESS; ++i)
    {
        res += (less[i] == true);
    }
    less.Set(false);
    for (size_t i = 0; i <LESS; ++i)
    {
        res += (less[i] == false);
    }

    BitArray<MORE> more;
    more.Set(true);
    
    for (size_t i = 0; i <MORE; ++i)
    {
        res += (more[i] == true);
    }
    more.Set(false);
    for (size_t i = 0; i <MORE; ++i)
    {
        res += (more[i] == false);
    }

    return (BITS_PER_WORD + LESS + MORE) * 2 == res;
}

int TestXorOperator(void)
{
    int res = 0;
    BitArray<BITS_PER_WORD> leftWord;
    BitArray<BITS_PER_WORD> rightWord;

    for (size_t i = 0; i < BITS_PER_WORD; ++i)
    {
        if (0 == i % 2)
        {
            rightWord[i] = true;
        }
    }

    leftWord ^= rightWord;

    for (size_t i = 0; i < BITS_PER_WORD; ++i)
    {
        if (0 == i % 2)
        {
            res += (leftWord[i] == true);
        }
        else
        {
            res += (leftWord[i] == false);
        }
    }

    BitArray<LESS> leftLess;
    BitArray<LESS> rightLess;

    for (size_t i = 0; i < LESS; ++i)
    {
        if (0 == i % 2)
        {
            rightLess[i] = true;
        }
    }

    leftLess ^= rightLess;

    for (size_t i = 0; i < LESS; ++i)
    {
        if (0 == i % 2)
        {
            res += (leftLess[i] == true);
        }
        else
        {
            res += (leftLess[i] == false);
        }
    }

    BitArray<MORE> leftMore;
    BitArray<MORE> rightMore;

    for (size_t i = 0; i < MORE; ++i)
    {
        if (0 == i % 2)
        {
            rightMore[i] = true;
            
        }
    }

    leftMore ^= rightMore;

    for (size_t i = 0; i < MORE; ++i)
    {
        if (0 == i % 2)
        {
            res += (leftMore[i] == true);
        }
        else
        {
            res += (leftMore[i] == false);
        }
    }

    return BITS_PER_WORD + LESS + MORE == res;
}

int TestAndOperator(void)
{
    int res = 0;
    BitArray<BITS_PER_WORD> leftWord;
    BitArray<BITS_PER_WORD> rightWord;

    for (size_t i = 0; i < BITS_PER_WORD; ++i)
    {
        if (0 == i % 2)
        {
            rightWord[i] = true;
            leftWord[i] = true;
        }
    }

    leftWord &= rightWord;

    for (size_t i = 0; i < BITS_PER_WORD; ++i)
    {
        if (0 == i % 2)
        {
            res += (leftWord[i] == true);
        }
        else
        {
            res += (leftWord[i] == false);
        }
    }

    BitArray<LESS> leftLess;
    BitArray<LESS> rightLess;

    for (size_t i = 0; i < LESS; ++i)
    {
        if (0 == i % 2)
        {
            rightLess[i] = true;
            leftLess[i] = true;
        }
    }

    leftLess &= rightLess;

    for (size_t i = 0; i < LESS; ++i)
    {
        if (0 == i % 2)
        {
            res += (leftLess[i] == true);
        }
        else
        {
            res += (leftLess[i] == false);
        }
    }

    BitArray<MORE> leftMore;
    BitArray<MORE> rightMore;

    for (size_t i = 0; i < MORE; ++i)
    {
        if (0 == i % 2)
        {
            rightMore[i] = true;
            leftMore[i] = true;
        }
    }

    leftMore &= rightMore;

    for (size_t i = 0; i < MORE; ++i)
    {
        if (0 == i % 2)
        {
            res += (leftMore[i] == true);
        }
        else
        {
            res += (leftMore[i] == false);
        }
    }

    return BITS_PER_WORD + LESS + MORE == res;
}

int TestOrOperator(void)
{
    int res = 0;
    BitArray<BITS_PER_WORD> leftWord;
    BitArray<BITS_PER_WORD> rightWord;

    for (size_t i = 0; i < BITS_PER_WORD; ++i)
    {
        if (0 == i % 2)
        {
            rightWord[i] = true;
        }
    }

    leftWord |= rightWord;

    for (size_t i = 0; i < BITS_PER_WORD; ++i)
    {
        if (0 == i % 2)
        {
            res += (leftWord[i] == true);
        }
        else
        {
            res += (leftWord[i] == false);
        }
    }

    BitArray<LESS> leftLess;
    BitArray<LESS> rightLess;

    for (size_t i = 0; i < LESS; ++i)
    {
        if (0 == i % 2)
        {
            rightLess[i] = true;
        }
    }

    leftLess |= rightLess;

    for (size_t i = 0; i < LESS; ++i)
    {
        if (0 == i % 2)
        {
            res += (leftLess[i] == true);
        }
        else
        {
            res += (leftLess[i] == false);
        }
    }

    BitArray<MORE> leftMore;
    BitArray<MORE> rightMore;

    for (size_t i = 0; i < MORE; ++i)
    {
        if (0 == i % 2)
        {
            rightMore[i] = true;
        }
    }

    leftMore |= rightMore;

    for (size_t i = 0; i < MORE; ++i)
    {
        if (0 == i % 2)
        {
            res += (leftMore[i] == true);
        }
        else
        {
            res += (leftMore[i] == false);
        }
    }

    return BITS_PER_WORD + LESS + MORE == res;
}

int TestMultiElement(void)
{
    int res = 0;
    
    const BitArray<66> a1;
      
    for (size_t i = 0; i < 66; ++i)
    {
        res += (false == a1[i]);
    }

    const BitArray<13> a2;
    
    for (size_t i = 0; i < 13; ++i)
    {
        res += (false == a2[i]);
    }

    const BitArray<65 * 2> a3;
    
    for (size_t i = 0; i < 65 * 2; ++i)
    {
        res += (false == a3[i]);
    }

    BitArray<65> b1;

    
    b1[64] = true;
    b1[0] = true;
    res += (b1[64] == true);
    res += (b1[0] == true);

    
    return 66 + 13 + 65 * 2 + 2 == res;
}



void TestAssignmentBool()
{
    BitArray<BITS_PER_WORD> b1;

    if (b1[4])
    {
        assert(1 == 2);
    }
    b1[4] = true;

    for (size_t i = 0; i < sizeof(size_t); ++i)
    {
        if (4 == i)
        {
            assert(true == b1[4]);
            continue;
        }
        assert(false == b1[i]);
    }

    b1[4] = false;

    for (size_t i = 0; i < sizeof(size_t); ++i)
    {
        assert(false == b1[i]);
    }

    for (size_t i = 0; i < sizeof(size_t); ++i)
    {
        b1[i] = true;
        assert(true == b1[i]);
    }
}

int PhaseOne()
{
    int res = 0;

    BitArray<BITS_PER_WORD> const arr1;

    res += (false == arr1[0]);
    res += (false == arr1[63]);
    
    return 2 == res;
}
void TestNewCosntObj()
{
    const BitArray<BITS_PER_WORD> a1;
    
    for (size_t i = 0; i < sizeof(size_t); ++i)
    {
        assert(false == a1[i]);
    }

    
}

void TestAssignmentProxy()
{
    BitArray<BITS_PER_WORD> b1;
    BitArray<BITS_PER_WORD> b2;

    assert(b1[0] == b2[63]);
    assert(b1[0] == b1[63]);

    for (size_t i = 0; i < sizeof(size_t); ++i)
    {
        b1[i] = true;
        assert(b1[0] != b2[63]);
    }
}

int TestFlip(void)
{
    BitArray<BITS_PER_WORD> b1;

    b1.Set(true);
    
    for (size_t i = 0; i < BITS_PER_WORD; ++i)
    {
        if (0 != i%2)
        {
            b1.Flip(i);
            assert(b1[i] == false);
        }
    }

    b1.Set(false);
    
    for (size_t i = 0; i < BITS_PER_WORD; ++i)
    {
        if (0 != i%2)
        {
            b1.Flip(i);
            assert(b1[i] == true);
        }
    }

    return true;
}

int TestFlipAll(void)
{
    BitArray<102> b1; //0000000000000000
    
    b1.Flip();                  // 111111111111111
    for (size_t i = 0; i < 102; ++i)
    {
        assert(b1[i] == true);       
    }

    b1.Flip();                  //0000000000000000
    for (size_t i = 0; i < 102; ++i)
    {
        assert(b1[i] == false);       
    }

    return true;
}

int TestIsequal(void)
{
    BitArray<165> b3;
    const BitArray<165> b4;
    
    assert(b3 == b4);

    b3.Flip(0);
    assert(b3 != b4);
    assert(0 == (b3 == b4));
    
    b3.Flip(0);
    assert(0 == (b3 != b4));
    assert((b3 == b4));
    
    return true;
}

int TestSpareBits()
{
    BitArray<BITS_PER_WORD> b1;
    BitArray<BITS_PER_WORD> b2;

    b1.Set(true);
    
    for (size_t i = 0; i < BITS_PER_WORD; ++i)
    {
        if (0 != i%2)
        {
            b2.Set(true, i);
            assert(b1[i] == b2[i]);
        }
        else
        {
            assert(b1[i] != b2[i]);
        }
    }

    return true;
}

int TestCount(void)
{
    BitArray<BITS_PER_WORD> b1;

    assert(0 == b1.Count());

    b1.Set(true);
    assert(BITS_PER_WORD == b1.Count());

    b1.Set(false);
    assert(0 == b1.Count());

    b1.Set(true, 5);
    assert(1 == b1.Count());

    b1.Set(true, 12);
    assert(2 == b1.Count());

    b1.Set(true, 27);
    assert(3 == b1.Count());

    b1.Set(false, 27);
    assert(2 == b1.Count());

    BitArray<100> b2;
    b2.Set(true, 80);
    assert(1 == b2.Count());

    return true;
}

void TestToString(void)
{
    BitArray<84> b1;
    BitArray<102> b2;
    b2.Set(false);
    BitArray<72> b3;
    b3.Set(true, 5);
    b3.Set(true, 6);
    b3.Set(true, 32);
    b3.Set(true, 12);
    b3.Set(true, 57);

    std::string str1 = b1.ToString();
    std::string str2 = b2.ToString();
    std::string str3 = b3.ToString();

    std::cout << str1 << std::endl;
    std::cout << str2 << std::endl;
    std::cout << str3 << std::endl;
}
