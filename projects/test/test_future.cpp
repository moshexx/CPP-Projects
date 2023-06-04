/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_future.cpp
*	author: Moshe Cohen
*	reviewer:   Yulia Barbash

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#include <iostream>                 // std::cout
#include <boost/thread/thread.hpp>

#include "future.hpp"


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

int result = -1;

// a non-optimized way of checking for prime numbers:
bool is_prime (int x)
{
  for (int i=2; i<x; ++i)
  {
      if (x%i==0)
      {
          return false;
      }
  }
  return true;
}

void Getter(Future<bool> *fut)
{
    result = fut->get();
}

void Setter(Future<bool> *fut)
{
    fut->Set(is_prime(444444443));
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Main~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int main()
{
    Future<bool> fut;
    boost::thread thread_grp[2];
    thread_grp[0] = boost::thread(boost::bind(Getter, &fut));
    sleep(3);
    thread_grp[1] = boost::thread(boost::bind(Setter, &fut));
    
    thread_grp[0].join();
    thread_grp[1].join();

    if (1 == result)
    {
        std::cout << GREEN_B << "Success" << std::endl;
    }
    else
    {
        std::cout << RED_B << "Failure.." << std::endl;
    }


    return 0;
}
