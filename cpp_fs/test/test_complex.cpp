/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_complex.cpp
*	author: Moshe Cohen
*	reviewer: Dor Glaubach

--------------------------------------------------------------------------------
*******************************************************************************/
#include <ostream>
#include <iostream>
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
#include <iostream>


#include "complex.hpp"

using ilrd::Complex;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int BasicOperators(void);
int Basic(void);
int Streaming(void);
int AdvancedOperators(void);

// try new convention of tests: @Yinon
void AssertBasicOperators(void);
void AssertBasic(void);
void AssertStreaming(void);
void AssertAdvancedOperators(void);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main()
{
    std::cout << std::endl << BLUE_B << "test Complex:" << RESET << std::endl;

    RunTest(Basic() == 0, "Basic");
    RunTest(BasicOperators() == 0, "Basic Operators");
    RunTest(AdvancedOperators() == 0, "Advanced Operators");
    // RunTest(Streaming() == 0, "Streaming");

    AssertBasicOperators();
    AssertBasic();
    AssertStreaming();
    AssertAdvancedOperators();

    std::cout << std::endl << GREEN_B <<
     "You have passed all the tests of Complex tests:" << RESET << std::endl;

	return 0;
}

int Basic(void)
{
    int count = 6;

    Complex comp;
    Complex comp2;
    Complex comp3(12, 22);

    comp2.SetReal(12);
    comp2.SetImag(22);

    comp.GetReal() == 1 ? --count : count;
    comp.GetImag() == 0 ? --count : count;

    comp2.GetReal() == 12 ? --count : count;
    comp2.GetImag() == 22 ? --count : count;

    comp3.GetReal() == 12 ? --count : count;
    comp3.GetImag() == 22 ? --count : count;

    return count;
}

// ==, !=, +, -, *, /
int BasicOperators(void)
{
    int count = 5;

    Complex comp(10, 20);
    Complex comp2(12, 22);
    Complex tmp(22, 42);

    Complex one(10, 10);
    Complex other(10, 10);

    Complex tmp2(0, 200);   // one * other
    Complex tmp3(1, 0);    // one / other

    tmp == comp + comp2 ?   --count : count;
    comp2 == tmp - comp ?   --count : count;
    tmp2 == one * other ?   --count : count;
    tmp3 == one / other ?   --count : count;

    tmp2 != tmp3 ?          --count : count;

    return count;
}

int Streaming(void)
{
    int count = 2;

    Complex comp(10, 20);
    Complex comp2(11, 11);

    std::cout << comp == std::cout << "10 + 20i" ? --count : count;

    std::cout << std::endl << "Please Enter => 11, 11" << std::endl;
    std::cin >> comp;

    comp == comp2 ? --count : count;

    return count;

}

int AdvancedOperators(void)
{
    int count = 4;

    Complex one(10, 10);
    Complex other(20, 20);
    Complex inc(30, 30);   // one + other
    one += other;
    inc == one ?   --count : count;

    Complex one2(10, 10);
    Complex other2(10, 10);
    Complex multi(0, 200);    // one2 * other2
    one2 *= other2;
    multi == one2 ? --count : count;

    Complex one3(10, 10);
    Complex other3(10, 10);
    Complex dec(0, 0);    // one3 - other3
    one3 -= other3;
    dec == one3 ? --count : count;

    Complex one4(10, 10);
    Complex other4(10, 10);
    Complex dev(1, 0);    // one4 - other4
    one4 /= other4;
    dev == one4 ? --count : count;

    return count;
}


void AssertBasic(void)
{
    Complex comp;
    Complex comp2;
    Complex comp3(12, 22);

    comp2.SetReal(12);
    comp2.SetImag(22);

    assert(comp.GetReal() == 1);
    assert(comp.GetImag() == 0);

    assert(comp2.GetReal() == 12);
    assert(comp2.GetImag() == 22);

    assert(comp3.GetReal() == 12);
    assert(comp3.GetImag() == 22);
}

// ==, !=, +, -, *, /
void AssertBasicOperators(void)
{
    Complex comp(10, 20);
    Complex comp2(12, 22);
    Complex tmp(22, 42);

    Complex one(10, 10);
    Complex other(10, 10);

    Complex tmp2(0, 200);   // one * other
    Complex tmp3(1, 0);    // one / other

    assert(tmp == comp + comp2); 
    assert(comp2 == tmp - comp);
    assert(tmp2 == one * other);
    assert(tmp3 == one / other);

    assert(tmp2 != tmp3);       

}

void AssertStreaming(void)
{
    Complex comp(10, 20);
    Complex comp2(11, 11);

    assert(std::cout << comp == std::cout << "10 + 20i");

    std::cout << std::endl << "Please Enter => 11, 11" << std::endl;
    std::cin >> comp;

    assert(comp == comp2);
}

void AssertAdvancedOperators(void)
{
    Complex one(10, 10);
    Complex other(20, 20);
    Complex inc(30, 30);   // one + other
    one += other;
    assert(inc == one);

    Complex one2(10, 10);
    Complex other2(10, 10);
    Complex multi(0, 200);    // one2 * other2
    one2 *= other2;
    assert(multi == one2);

    Complex one3(10, 10);
    Complex other3(10, 10);
    Complex dec(0, 0);    // one3 - other3
    one3 -= other3;
    assert(dec == one3);

    Complex one4(10, 10);
    Complex other4(10, 10);
    Complex dev(1, 0);    // one4 - other4
    one4 /= other4;
    assert(dev == one4);
}

// a   lhs_.GetReal()
// b   lhs_.GetImag()
// c   rhs_.GetReal()
// d   rhs_.GetImag()