/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_rcstring.cpp
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
#include <iostream>
#include <cassert>
#include <cstring>

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


#include "rcstring.hpp"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
using namespace ilrd;

void Basic(void);
void Operators(void);
void Streaming();
void Advanced(void);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main()
{
    std::cout << std::endl << BLUE_B << "test rcstring:" << RESET << std::endl;

    

    Basic();
    Operators();
    Streaming();
    Advanced();

    std::cout << std::endl << GREEN_B <<
             "You have passed all the tests of rcstring" << RESET << std::endl;

	return 0;
}

void Basic(void)
{
    RCString str1;
    RCString str2("abc");
    RCString str3;
    str3 = str2;
    RCString *strp = new RCString("abcd");

    assert(!strcmp("abc", str2.GetStr()));  // GetStr(), ==
    assert(!strcmp("abc", str3.GetStr()));  // =, ==
    assert(strcmp(str1.GetStr(), str3.GetStr())); // !=
    assert(str2.Length() == 3) ;                 // Length()

    delete strp;
}

void Operators(void)
{
    RCString str1("abc");
    RCString str11("Bbb");
    RCString str2("defg");
    RCString str3;
    str1 += str2;
    assert(!strcmp("abcdefg", str1.GetStr()));  // +=
    assert(str1 == "abcdefg");

    assert(str1[1] == str11[1]);               // const []
    str11[0] = 'b';
    assert(str1[1] == str11[0]);               // []

    assert(str1 < str11);
    assert(str11 > str1);
    str1 = str1;
    assert(str1 == str1);
}

void Streaming()
 {
    RCString s0(GREEN);
    RCString s1("Test:");
    RCString s2(" ");
    RCString s3("print ");
    RCString s4("success");
    RCString s5(RESET);

    std::cout << s0 << s1 << s2 << s3 << s4 << s5 << std::endl;

    RCString str1;

    std::cout << "Cin test, Enter 'moshe':" << std::endl;
    std::cin >> str1;

    assert(str1 == "moshe");
    assert(!strcmp("moshe", str1.GetStr()));
 }

void Advanced(void)
{

}