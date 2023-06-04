/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_observer.cpp
*	author: Moshe Cohen
*	reviewer: TODO:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include <cstring>
#include <cassert>

#include "observer.hpp"

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

using namespace ilrd;


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
class Print : public Observer<int>
{
private:
    virtual void Callback(int param)
    {
        std::cout << param << std::endl;
    }

};

int main()
{
    Print o1;
    Print o2;
    Print o3;

    Subject<int> s1;

    o1.Subscribe(&s1);
    o2.Subscribe(&s1);
    o3.Subscribe(&s1);
    
    s1.Notify(5);
    return 0;
}
