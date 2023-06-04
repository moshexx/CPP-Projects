/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_priority_queue.cpp
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include <cstring>
#include <cassert>
#include <functional>
#include <vector>

#include "priority_queue_wrapper.hpp"

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
int BasicTest();
int AssignTest();
void PrintMyQueue(Priority_Queue<int> q);
template<typename T>
void printQueue(T q);

int main()
{
    BasicTest();
    AssignTest();

    std::cout << GREEN_B << "SUCCESS" << RESET << std::endl;
    
	return 0;
}

int BasicTest()
{
    std::priority_queue<int> queue;
    Priority_Queue<int> myQueue;
    const int data[] = {1,8,5,6,3,4,0,9,7,2};
    size_t i = 0;

    for(i = 0; i < sizeof(data)/sizeof(data[0]); ++i)
    {
        queue.push(data[i]);
        myQueue.push(data[i]);
        assert(myQueue.front() == queue.top());
    }

    printQueue(queue);
    PrintMyQueue(myQueue);
    
    assert(myQueue.size() == i);
    assert(queue.size() == i);
    assert(!queue.empty());
    assert(!myQueue.empty());
    
    return true;
}   

int AssignTest()
{
    Priority_Queue<char> myQueue;
    Priority_Queue<char> cpyQueue;
    const char data[] = { 'a', 'b', 'c', 'd', 'e', 'f'};
    size_t i = 0;
    
    for(i = 0; i < sizeof(data)/sizeof(data[0]); ++i)
    {
        myQueue.push(data[i]);
    }
    cpyQueue = myQueue;

    while(!myQueue.empty()) 
    {
        assert(myQueue.front() == cpyQueue.front());
        myQueue.pop();
        cpyQueue.pop();
    }

    return true;
}

template<typename T>
void printQueue(T q) 
{ // NB: pass by value so the print uses a copy
    while(!q.empty()) 
    {
        std::cout << q.top() << ' ';
        q.pop();
    }
    std::cout << '\n';
}

void PrintMyQueue(Priority_Queue<int> q) 
{
    while(!q.empty()) 
    {
        std::cout << q.front() << ' ';
        q.pop();
    }
    std::cout << '\n';
    assert(q.empty());
}