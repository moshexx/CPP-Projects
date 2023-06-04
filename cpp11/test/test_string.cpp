/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_string.cpp
*	author: Moshe Cohen
*	reviewer: 

--------------------------------------------------------------------------------
*******************************************************************************/
#include <iostream>
#include <cstring>
#include <cassert>

#include "string.hpp"

const char* RED = "\x1B[31m" ;
const char* GREEN = "\x1B[32m" ;
const char* YELLOW = "\x1B[33m" ;
const char* BLUE = "\x1B[34m" ;
const char* PURPLE = "\x1B[35m" ;
const char* LIGHT_BLUE = "\x1B[36m";
const char* RESET = "\033[0m";

void RunTest(bool result, const char* name)
{
    if(true == result)
    {
        std::cout << name << ": " << GREEN << "Success" << RESET << std::endl;
    }
    else
    {
        std::cout << name << ": " << RED <<"Failed" << RESET << std::endl;
    }
}


using namespace ilrd;

bool MoveCtorTest();
bool MoveAssignmentOpTest();

int main()
{
   String s1;
   String s2("My new Class");
   String s3(s2);
   String s4("aba");
   String s5("baba");
   String s6;

   //print tets
   std::cout << s1 << std::endl;
   std::cout << s2 << std::endl;
   std::cout << s3 << std::endl;
   s1 = s2;
   std::cout << s1 << std::endl;
   std::cout << s2 << std::endl;
   

   RunTest(strlen("My new Class") == s2.Length(), "Length()");
   RunTest(strlen("") == s6.Length(), "Length()");
   RunTest(strlen("baba") == s5.Length(), "Length()");

   RunTest(s1 == s2, "==, =, Citor");
   RunTest(s4 < s5, "<, Citor");
   RunTest(s5 > s4, ">, Citor");

   RunTest("baba" == s5, "baba == s5");
   RunTest(0 == ("baba" == s2), "baba == s2");

    MoveCtorTest();
   RunTest(MoveCtorTest(), "MoveCtorTest");
   RunTest(MoveAssignmentOpTest(), "Move Assigntment Operator Test");

   
   return 0;
}

bool MoveCtorTest()
{
   String s1("My new Class");
   String s_copy(s1);

   String s2(std::move(s1));
   
   assert(s1.CStr() == nullptr);

   return s2 == s_copy;
}

bool MoveAssignmentOpTest()
{
    String s1("My new Class");
    String s_copy(s1);
    String s2;

    s2 = std::move(s1);
 
    assert(s1.CStr() == nullptr);

    return s2 == s_copy;
}
