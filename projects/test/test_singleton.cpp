/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_singleton.cpp
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <boost/thread/thread.hpp>

#include "singleton.hpp"

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

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
using namespace ilrd;

boost::mutex g_mutex;

int TestSingleThread()
{   
    size_t res = 0;

    for(size_t i = 0; i < 10; ++i)
    {
        size_t *address = Singleton<size_t>::GetInstance();

        for(size_t j = 0; j < 10; ++j)
        {
            res += (Singleton<size_t>::GetInstance() == address);
        }
    }
    

    return res == 100;
}

void MultiThread(std::vector<int *> & vector)
{
    int *address = Singleton<int>::GetInstance();
    boost::lock_guard<boost::mutex> lock(g_mutex);
    vector.push_back(address);
}

void Printf(const int *elements)
{
    std::cout << elements << std::endl;
}

int TestMultiThread()
{
    boost::thread_group group;
    std::vector<int *> vector;
    size_t res = 0;
    for(size_t j = 0; j < 10; ++j)
    {
        for(size_t i = 0; i < 10;++i)
        {
            group.create_thread(boost::bind(MultiThread,boost::ref(vector)));
        }
        group.join_all();
        res += std::equal(vector.begin() + 1, vector.end(), vector.begin());
        vector.clear();
    }

    return res == 10;
}


int main()
{
    RunTest(TestSingleThread(),"Test single thread");
    RunTest(TestMultiThread(),"Test multi thread");
    // throw std::runtime_error("test_");

    return 0;
}