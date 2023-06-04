/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_lock.cpp
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
  /*
  mutexes types:
  boost::mutex;
  boost::recursive_mutex;
  boost::timed_mutex;
  boost::recursive_timed_mutex; */

#include <iostream>
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
#include <boost/thread.hpp>

#include "scope_lock.hpp"

using namespace ilrd;
boost::mutex g_mutex;
static int g_num;
boost::mutex m;
static size_t count = 0;
static size_t s_thread_num = 0;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void Bar(int a)
{
    if (true)
    {
        std::cout << GREEN << "Bar" << a << RESET << std::endl;
    }
}

void Foo()
{
    {
    ScopeLock <boost::mutex> mtx(m); // try to comment this line
    ++s_thread_num;
    std::cout << "thread num:" <<s_thread_num << std::endl;
    for( size_t i = 0; i < 10; ++i )
    {
        count += 10;
        std::cout << BLACK_B << i << ":\t" << count << RESET << std::endl;
    }
    }
    for (size_t i = 0; i < 11101; ++i )
    {

    }
    std::cout << "Async segment" << std::endl;
}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


void Foof(void)
{
    for (int i = 0; i < 1000; ++i)
    {
        ScopeLock <boost::mutex> mtx(g_mutex);
        ++g_num;
    }
}

void Test1(void)
{
    boost::thread_group threads;
    int num_of_threads = 5;

    for (int i = 0; i < num_of_threads; ++i)
    {
        threads.create_thread(Foof);
    }
    threads.join_all();
    assert(g_num == (num_of_threads * 1000));
}

int main()
{
    boost::thread some_thread(Foo);
    boost::thread some_thread1(Foo);
    boost::thread some_thread2(Foo);
    boost::thread some_thread3(Foo);
    boost::thread some_thread4(Bar, 2);
    
    some_thread.join();
    some_thread1.join();
    some_thread2.join();
    some_thread3.join();
    Test1();
    std::cout << "end of main" << std::endl;

	return 0;
}