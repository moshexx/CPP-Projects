/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_waitable_queue.cpp
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include <cstring>
#include <cassert>

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "waitable_queue.hpp"
#include "priority_queue_wrapper.hpp"

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

using namespace ilrd;

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~ definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~*/
const size_t NUM_OF_THREADS = 20;
const size_t TIME_TO_WAIT = 10;
boost::mutex g_enq_lock;
boost::mutex g_deq_lock;
size_t g_enq_count = 0;
size_t g_deq_count = 0;
static size_t outparam[NUM_OF_THREADS];
WaitableQueue<size_t> g_pqueue;


class Test
{
public:
    Test(size_t size):m_array(new size_t[size]){memset(m_array, 0, size);}
    ~Test(){ delete[] m_array;}

    WaitableQueue<size_t> m_queue;
    size_t *m_array;
};

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
// Test functions
int BasicTest();
int AnotherBasicTest();
int ThreadsTest();
bool TimeWaitTest();
bool TimeWaitTest2();

// helper functions
int EnqueueWrap(Test &queue, size_t data);
int DequeueWrap(Test &queue);
int DequeueWrap(Test &queue, size_t i); //TimeOutDequeue
int MyEnqueue(void); // for TimeWaitTest2
int MyDequeue(void); //TimeOutDequeue for TimeWaitTest2

template<typename T>
void printQueue(T q);
void PrintMyQueue(WaitableQueue<int, Priority_Queue<int> >& q);

/*******************************************************************************
*******************************************************************************/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main()
{

    RunTest(AnotherBasicTest(),"AnotherBasicTest");
    RunTest(BasicTest(),"BasicTest");
    RunTest(ThreadsTest(),"ThreadsTest");
    RunTest(TimeWaitTest(),"TimeWaitTest");
    RunTest(TimeWaitTest2(),"TimeWaitTest2");

    std::cout << GREEN << "Test SUCCEEDED" << RESET << std::endl;

	return 0;
}

/*******************************************************************************
*******************************************************************************/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Tests ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int BasicTest()
{
    WaitableQueue<int> myQueue;
    std::priority_queue<int> queue;

    const int data[] = {1,8,5,6,3,4,0,9,7,2};
    size_t i = 0;
    
    for(i = 0; i < sizeof(data)/sizeof(data[0]); ++i)
    {
        queue.push(data[i]);
        myQueue.Enqueue(data[i]);

        int outparam;
        myQueue.Dequeue(&outparam);
        myQueue.Enqueue(outparam);

        assert(outparam == queue.top());
    }

    printQueue(queue);
    PrintMyQueue(myQueue); // by references (noncopyable)

    return true;
}

bool TestPush(Priority_Queue<size_t> &my_pq, std::priority_queue<size_t>& pq)
{
    size_t res = 0;

    for(size_t i = 0; i < 50; ++i)
    {
        my_pq.push(i);
        pq.push(i);
        res += my_pq.size() == pq.size();
        res += my_pq.front() == pq.top();
    }   
    assert(res == 100);

    return res == 100;
}

bool TestPop(Priority_Queue<size_t> &my_pq, std::priority_queue<size_t>& pq)
{
    size_t res = 0;
    Priority_Queue<size_t> new_pq = my_pq;

    for(size_t i = 0; i < 50; ++i)
    {
        new_pq.pop();
        pq.pop();
        res += new_pq.size() == pq.size();
    } 
    res += my_pq.empty() == false;
    res += pq.empty() == true;

    res += my_pq.empty() == false;

    assert(res == 53);

    return res == 53;
}

int AnotherBasicTest()
{
    size_t res = 0;
    Priority_Queue<size_t> my_pq;
    std::priority_queue<size_t> pq;

    res += TestPush(my_pq, pq);
    res += TestPop(my_pq, pq);

    return res == 2;
}

int ThreadsTest()
{    
    Test testClass(NUM_OF_THREADS);
    size_t i = 0;
    size_t res = 0;
    boost::thread_group group;

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        group.create_thread(boost::bind(DequeueWrap, boost::ref(testClass)));
        group.create_thread(boost::bind(EnqueueWrap, boost::ref(testClass), i));
    }
    group.join_all();

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
         res +=  testClass.m_array[i] == i;
    }

    return res == NUM_OF_THREADS;
}

bool TimeWaitTest2()
{
    size_t i = 0;
    boost::thread_group group;

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        group.create_thread(MyDequeue); // first deq
        group.create_thread(MyDequeue); // second deq
        group.create_thread(MyEnqueue); // first and only enq
    }
    group.join_all();

    std::cout << "total Dequeue succeeded: " << g_deq_count <<
                    "\nfrom total expected " << g_enq_count << std::endl;

    // for (size_t j = 0; j < NUM_OF_THREADS; ++j)
    // {
    //     std::cout << "outparam: " << outparam[j] << std::endl;
    // }
    return g_deq_count <= g_enq_count; //expected to succeeded 1/2 deq for every enq.
}

bool TimeWaitTest()
{
    Test testClass(NUM_OF_THREADS);
    size_t i = 0;
    size_t res = 0;
    boost::thread_group group;

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {

        group.create_thread(boost::bind(DequeueWrap, boost::ref(testClass), i));
        group.create_thread(boost::bind(DequeueWrap, boost::ref(testClass), i));
        group.create_thread(boost::bind(EnqueueWrap, boost::ref(testClass), i));
    }
    group.join_all();

    for(size_t i = 0; i < NUM_OF_THREADS; ++i)
    {// relative of: 2:1  Dequeue:Enqueue -> half of Dequeue always return false
         res += testClass.m_array[i] == true; // Dequeue succeeded
    }
    // std::cout << "total Dequeue succeeded: " << res << "\nfrom total " << 2*(NUM_OF_THREADS/3) << std::endl;

    return res <= NUM_OF_THREADS / 2;
}
/*******************************************************************************
*******************************************************************************/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ helper functions ~~~~~~~~~~~~~~~~~~~~~~~~~~
// wrappers
int EnqueueWrap(Test &myClass, size_t data)
{
    myClass.m_queue.Enqueue(data);

    return 0;
}

int DequeueWrap(Test &myClass)
{
    size_t data = 0;
    myClass.m_queue.Dequeue(&data);
    myClass.m_array[data] = data;

    return 0;
}

int DequeueWrap(Test &myClass, size_t i)
{
    size_t data = 0;

    myClass.m_array[i] = 
           myClass.m_queue.Dequeue(&data, boost::chrono::seconds(TIME_TO_WAIT));

    return 0;
}

int MyEnqueue(void)
{
    // boost::mutex::scoped_lock lock(g_enq_lock);
    ++g_enq_count;
    g_pqueue.Enqueue(g_enq_count);

    return 0;
}

int MyDequeue(void)
{
    static size_t i;
    size_t local_count;
    // lock the mutex here to prevent race condition on outparam[i]. (slower test)
    
    local_count = g_pqueue.Dequeue(&outparam[i], boost::chrono::seconds(2));
    boost::mutex::scoped_lock lock(g_deq_lock);
    g_deq_count += local_count;

    return 0;
}

// print functions
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

void PrintMyQueue(WaitableQueue<int, Priority_Queue<int> >& q) 
{
    while(!q.IsEmpty()) 
    {
        int outparam;
        q.Dequeue(&outparam);
        std::cout << outparam << ' ';
    }
    std::cout << '\n';
    assert(q.IsEmpty());
}