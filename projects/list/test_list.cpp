/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_list.cpp
*	author: Moshe Cohen
--------------------------------------------------------------------------------
*******************************************************************************/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iostream>  //atd::cout, std::endl
#include <cassert>   //assert
#include <queue>     //std::priority_queue
#include <time.h>    //time
#include <stdlib.h>  //srand, rand, abs
#include <chrono>    //std::chrono
#include <thread>    //std::thread
#include <vector>    //std::vector
#include <atomic>    //std::atomic   

#include "list.hpp"

// testing display tools
const char *RED_B = "\033[01;31m";
const char *GREEN_B = "\033[01;32m";
const char *YELLOW_B = "\033[01;33m";
const char *GREEN = "\033[0;32m";
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
const size_t BASIC_SIZE = 1000;
const size_t BIG_SIZE = 1000000;
const size_t MID_SIZE = 10000;
const size_t SLOW_BIG_SIZE = BIG_SIZE/10;
const size_t SLOW_BASIC_SIZE = BASIC_SIZE/10;
const size_t NUM_OF_THREADS = 15; //**Must be divisible by 3

using namespace ilrd;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~ Functions Declerations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool BasicTestPushList();
bool BasicTestPopList();

bool EfficiencyTestQuickPush();
bool EfficiencyTestQuickPop();
bool ThreadSafeTestQuickPushList();
bool ThreadSafeTestQuickPopList();

void DemonstrateSlowPop();
void DemonstrateSlowPush();

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Entry point ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{
    srand(time(NULL));

    RunTest(BasicTestPushList(),"BasicTestPushList");
    RunTest(BasicTestPopList(),"BasicTestPopList");

    RunTest(EfficiencyTestQuickPush(),"EfficiencyTestQuickPush");
    RunTest(EfficiencyTestQuickPop(),"EfficiencyTestQuickPop");

    RunTest(ThreadSafeTestQuickPushList(),"ThreadSafeTestQuickPushList");
    RunTest(ThreadSafeTestQuickPopList(),"ThreadSafeTestQuickPopList");

    // Not recommended to run with valgrind:
    DemonstrateSlowPop();     //caution: heavy test!
    // DemonstrateSlowPush(); //caution: a really (really) heavy test!!

    std::cout << GREEN << "The test has completed." << RESET << std::endl;

	return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~ Functions Definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
bool BasicTestPushList()
{
    std::priority_queue<int> controlGroup;
    ListQuickPop<int> list;

    for (size_t i = 0; i < BASIC_SIZE; ++i)
    {// fill std DS and ilrd list with the same data. 
        int data = rand();
        controlGroup.push(data);
        list.Push(data);
    }

    for (size_t i = 0; i < BASIC_SIZE; ++i)
    {// test basic functionality - return the right number
        int data = 0;
        int controlData = controlGroup.top();
        controlGroup.pop();
        list.Pop(&data);

        assert(data == controlData);
        (void)controlData;
    }

    return true;
}

bool BasicTestPopList()
{
    std::priority_queue<int> controlGroup;
    ListQuickPush<int> list;

    for (size_t i = 0; i < BASIC_SIZE; ++i)
    {
        int data = rand();
        controlGroup.push(data);
        list.Push(data);
    }

    for (size_t i = 0; i < BASIC_SIZE; ++i)
    {
        int data = 0;
        int controlData = controlGroup.top();
        controlGroup.pop();
        list.Pop(&data);

        assert(data == controlData);
        (void)controlData;
    }

    return true;
}

bool EfficiencyTestQuickPush()
{
    using namespace std::chrono;

    ListQuickPush<size_t> list;     
    static size_t arr[BIG_SIZE] = {0};

    for (size_t i = 0; i < BIG_SIZE; ++i)
    {// fill array with data to list.push
        arr[i] = rand();
    }

    // Measuring average time - Push to a small list
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < BASIC_SIZE; ++i)
    {
        list.Push(arr[i]);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    duration /= BASIC_SIZE;

    // Increase the size of the list
    for (size_t i = 0; i < BIG_SIZE; ++i)
    {
        list.Push(arr[i]);
    }
    
    // Measuring average time - Push to a big list
    auto start2 = high_resolution_clock::now();
    for (size_t i = 0; i < BASIC_SIZE; ++i)
    {
        size_t data =  arr[i];
        list.Push(data);
    }
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    duration2 /= BASIC_SIZE;

    std::cout << "Average time taken: Quick Push to a small list: " << YELLOW_B
              << duration.count() << RESET << " microseconds" << std::endl;
    std::cout << "Average time taken: Quick Push to a big list " << YELLOW_B
              << duration2.count() << RESET << " microseconds" << std::endl;
    
    // add a to both durations to avoid dividing by zero
    return ((duration2.count()+1) / (duration.count()+1) < 2); // big/small
}

bool EfficiencyTestQuickPop()
{
    using namespace std::chrono;

    ListQuickPop<size_t> list;      

    // Small list
    for (size_t i = 0; i < BASIC_SIZE; ++i)
    {// fill the list
        list.Push(rand());
    }

    // Measuring average time - Pop to a small list
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < BASIC_SIZE; ++i)
    {
        size_t data = 0;
        list.Pop(&data);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    duration /= BASIC_SIZE;


    // Big list
    for (size_t i = 0; i < MID_SIZE; ++i)
    {// fill the list
        list.Push(rand());
    }

    // Measuring average time - Pop to a big list
    auto start2 = high_resolution_clock::now();
    for (size_t i = 0; i < MID_SIZE; ++i)
    {
        size_t data = 0;
        list.Pop(&data);
    }
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    duration2 /= MID_SIZE;    


    std::cout << "Average time taken: Quick Pop to a small list " << YELLOW_B
              << duration.count() << RESET << " microseconds" << std::endl;
    std::cout << "Average time taken: Quick Pop to a big list " << YELLOW_B
              << duration2.count() << RESET << " microseconds" << std::endl;
    
    // add a to both durations to avoid dividing by zero
    return ((duration2.count()+1) / (duration.count()+1) < 2); // big/small
}

void DemonstrateSlowPop()
{
    using namespace std::chrono;
    ListQuickPush<size_t> list;      

    // Small list
    for (size_t i = 0; i < BASIC_SIZE; ++i)
    {// fill the list
        list.Push(rand());
    }

    // Measuring average time - Pop to a small list
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < BASIC_SIZE; ++i)
    {
        size_t data = 0;
        list.Pop(&data);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    duration /= BASIC_SIZE;


    // Big list
    for (size_t i = 0; i < MID_SIZE; ++i)
    {// fill the list
        list.Push(rand());
    }

    // Measuring average time - Pop to a big list
    auto start2 = high_resolution_clock::now();
    for (size_t i = 0; i < MID_SIZE; ++i)
    {
        size_t data = 0;
        list.Pop(&data);
    }
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    duration2 /= MID_SIZE;    


    std::cout << "Average time taken: Slow Pop to a small list " << RED_B
              << duration.count() << RESET << " microseconds" << std::endl;
    std::cout << "Average time taken: Slow Pop to a big list " << RED_B
              << duration2.count() << RESET << " microseconds" << std::endl;
}

void DemonstrateSlowPush()
{
    using namespace std::chrono;
    ListQuickPop<size_t> list;     
    static size_t arr[SLOW_BIG_SIZE] = {0};

    for (size_t i = 0; i < SLOW_BIG_SIZE; ++i)
    {// fill array with data to list.push
        arr[i] = rand();
    }

    // Measuring average time - Push to a small list
    auto start = high_resolution_clock::now();
    for (size_t i = 0; i < SLOW_BASIC_SIZE; ++i)
    {
        list.Push(arr[i]);
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    duration /= SLOW_BASIC_SIZE;

    // Increase the size of the list
    for (size_t i = 0; i < SLOW_BIG_SIZE; ++i)
    {
        list.Push(arr[i]);
    }
    
    // Measuring average time - Push to a big list
    auto start2 = high_resolution_clock::now();
    for (size_t i = 0; i < SLOW_BASIC_SIZE; ++i)
    {
        size_t data =  arr[i];
        list.Push(data);
    }
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);
    duration2 /= SLOW_BASIC_SIZE;

    std::cout << "**Smaller list: " << std::endl;
    std::cout << "Average time taken: Slow Push to a small list: " << RED_B
              << duration.count() << RESET << " microseconds" << std::endl;
    std::cout << "Average time taken: Slow Push to a big list " << RED_B
              << duration2.count() << RESET << " microseconds" << std::endl;   
}

// Thread safe tests:
std::atomic<size_t> g_count;

int PushWrap(ListQuickPush<size_t> *list)
{
    size_t data = rand() % 12;
    list->Push(data);

    return 0;
}

int PopWrap(ListQuickPush<size_t> *list)
{
    size_t data = 0;
    bool status = list->Pop(&data);

    atomic_fetch_add(&g_count, status);

    return 0;
}

bool ThreadSafeTestQuickPushList()
{
    using namespace std;
    vector<thread> threads;
    ListQuickPush<size_t> list;

    for (size_t i = 0; i < NUM_OF_THREADS/3; ++i)
    {//expected successfully Pop() = NUM_OF_THREADS/3
        threads.push_back(move(thread(PushWrap, &list)));
        threads.push_back(move(thread(PopWrap, &list)));
        threads.push_back(move(thread(PopWrap, &list)));
    }

    for (size_t i = 0; i < NUM_OF_THREADS; ++i)
    {
        threads[i].join();
    } 
    
    return  (NUM_OF_THREADS/3 - 3 <= g_count);
}


std::atomic<size_t> g_count2;

int PushWrap2(ListQuickPop<size_t> *list)
{
    size_t data = rand() % 12;
    list->Push(data);

    return 0;
}

int PopWrap2(ListQuickPop<size_t> *list)
{
    size_t data = 0;
    bool status = list->Pop(&data);

    atomic_fetch_add(&g_count2, status);

    return 0;
}

bool ThreadSafeTestQuickPopList()
{
    using namespace std;
    vector<thread> threads;
    ListQuickPop<size_t> list;

    for (size_t i = 0; i < NUM_OF_THREADS/3; ++i)
    {//expected successfully Pop() = NUM_OF_THREADS/3
        threads.push_back(move(thread(PushWrap2, &list)));
        threads.push_back(move(thread(PopWrap2, &list)));
        threads.push_back(move(thread(PopWrap2, &list)));
    }

    for (size_t i = 0; i < NUM_OF_THREADS; ++i)
    {
        threads[i].join();
    } 
    
    return  (NUM_OF_THREADS/3 - 3 <= g_count2);
}