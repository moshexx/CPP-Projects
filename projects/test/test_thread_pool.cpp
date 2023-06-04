/*******************************************************************************
--------------------------------------------------------------------------------
*	file name:  test_thread_pool.cpp
*	author:     Moshe Cohen
*	reviewer:   Yulia Barbash

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>                 // std::cout, std::endl
#include <cassert>                  // assert
#include <boost/chrono.hpp>         //boost::chrono
#include <boost/thread/mutex.hpp>   // boost::mutex

#include "thread_pool.hpp"

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
typedef ThreadPool::task_t task_t;
typedef ThreadPool::Task Task;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~globals~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
static boost::mutex g_buffer_lock;

const size_t NUM_OF_THREAD = 10;
const size_t NUM_OF_RUNS = 1;

const size_t BUFFER_SIZE = 100;
static size_t g_buffer[BUFFER_SIZE];


static const size_t size  = 10;
boost::mutex m1;
boost::atomic<int> counter(size);
int arr[size] = {1,2,3,4,5,6,7,8,9,10};
std::vector<size_t> vector;

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~declerations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void AntiPatternTest(void);
void PatternTest(void);

void FastExecuteTasks(void);
void PauseTest(size_t num_of_runs);

void AddThreads(void);
void DecThreads(void);

void TrickyOperations(void);
void SetThreadNumDecAdvanced(void);

void CleanBuffer(void);
void *Write(void *params);
void *Read(void *params);


void CleanBuffer(void);
void *Write(void *params);
void *Read(void *params);
void *SimpleTask(void *data);
void *HighPriorityTask(void *data);
void *MidPriorityTask(void *data);
void *LowPriorityTask(void *data);
void* Task1(void *data);
void* Sleep(void *data);
bool SimpleTest();
bool PauseTest();
bool PriorityTest();
void *AnotherTask(void* data);
void* AnotherTask(void* data);
bool AnotherTest();
bool AdvancedTest();
void* FooVoidPtr(int *num);
void FooVoidFuture(int *num);
void FooVoid(int *num);
bool TestBasic();

int main()
{
    for(size_t i = 0; i < 1; ++i)
    {
        for(size_t i = 0; i < 2; ++i)
        {
            RunTest(SimpleTest(),"Simple Test");
            RunTest(PauseTest(),"Pause Test");
            RunTest(PriorityTest(),"PriorityTest Test");
            RunTest(AnotherTest(),"AnotherTest");
            RunTest(TestBasic(),"TestBasic");
        }
        AdvancedTest();
    }

    AntiPatternTest();
    // FastExecuteTasks(); //bug
    PatternTest();
    PauseTest(5);
    AddThreads();
    DecThreads();
    SetThreadNumDecAdvanced();

    std::cout << GREEN << "The test has completed." << RESET << std::endl;
    
	return 0;
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~test functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void CleanBuffer(void)
{
    boost::mutex::scoped_lock lock(g_buffer_lock);

    for (size_t i = 0; i < BUFFER_SIZE; ++i)
    {
        g_buffer[i] = 0;
    }
}

void *Write(void *params)
{
    boost::mutex::scoped_lock lock(g_buffer_lock);
    usleep(100000);
    g_buffer[(size_t)params] = (size_t)params;
    // std::cout << "write: " << (size_t)params << std::endl;
    return NULL;
}

void *Read(void *params)
{
    boost::mutex::scoped_lock lock(g_buffer_lock);
    usleep(100000);
    // std::cout << "read: " << (size_t)params << std::endl;

    return (void *)g_buffer[(size_t)params];
}

void AntiPatternTest()
{
    std::cout << "\t\tAntiPatternTest" << std::endl;
    time_t start_test = time(NULL);
    boost::thread thread_grp[NUM_OF_THREAD];
    
    for (size_t num_of_runs = NUM_OF_RUNS; num_of_runs > 0; --num_of_runs)
    {
        CleanBuffer();

        for (size_t i = 0; i < NUM_OF_THREAD / 2; ++i)
        {
            thread_grp[i] = boost::thread(Write, (void *)i);
            thread_grp[i + 1] = boost::thread(Read, (void *)i);
        }
        for (size_t i = 0; i < NUM_OF_THREAD; ++i)
        {
            thread_grp[i].join();
        }
    }

    time_t end_test = time(NULL);
    std::cout << "AntiPatternTest took: ";
    std::cout << difftime(end_test, start_test) << " seconds" << std::endl;
}

void PatternTest()
{
    std::cout << "\t\tPatternTest" << std::endl;
    time_t start_test = time(NULL);
    ThreadPool thread_pool(0, NUM_OF_THREAD);
    
    for (size_t num_of_runs = NUM_OF_RUNS; num_of_runs > 0; --num_of_runs)
    {
        CleanBuffer();

        for (size_t i = 0; i < NUM_OF_THREAD / 2; ++i)
        {
            ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
                <void *, void *>(Write, (void *)i));
            thread_pool.AddTask(write_task, ThreadPool::HIGH);

            ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
                <void *, void *>(Read, (void *)i));
            thread_pool.AddTask(read_task, ThreadPool::HIGH);
        }
    }

    time_t end_test = time(NULL);
    std::cout << "PatternTest took: ";
    std::cout << difftime(end_test, start_test) << " seconds" << std::endl;
}

void PauseTest(size_t num_of_runs)
{
    CleanBuffer();

    std::cout << "\t\tPauseTest" << std::endl;
    
    size_t i_upper_limit;

    {
        ThreadPool thread_pool(0, NUM_OF_THREAD);

        size_t i = 0;
        

        for (; num_of_runs > 0; --num_of_runs)
        {
            i_upper_limit = i + 10;
            thread_pool.Resume();
            sleep(2);
            for (; i < i_upper_limit; ++i)
            {
                ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
                    <void *, void *>(Write, (void *)i));
                thread_pool.AddTask(write_task, ThreadPool::HIGH);

                ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
                    <void *, void *>(Read, (void *)i));
                thread_pool.AddTask(read_task, ThreadPool::HIGH);
            }
            thread_pool.Pause();
            sleep(3);
        }

        thread_pool.Resume();
        sleep(6);
    }
    std::cout << "Check buffer:" << std::endl;
    for (size_t i = 0; i < i_upper_limit; ++i)
    {
        std::cout << i << " " << g_buffer[i] << std::endl;
        assert(i == g_buffer[i]);
    }

    std::cout << "Success" << std::endl;
}

void FastExecuteTasks()
{
    std::cout << "\t\tFastExecute2Tasks" << std::endl;
    
    std::cout << "should finish 2 tasks before done (W & R)" << std::endl;

    {
        CleanBuffer();

        ThreadPool thread_pool(0, 2);
    
        for (size_t i = 0; i < BUFFER_SIZE; ++i)
        {
            ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
                <void *, void *>(Write, (void *)i));
            thread_pool.AddTask(write_task, ThreadPool::HIGH);

            ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
                <void *, void *>(Read, (void *)i));
            thread_pool.AddTask(read_task, ThreadPool::HIGH);
        }
        sleep(12);
    }
    
    std::cout << "Check buffer:" << std::endl;
    for (size_t i = 0; i < BUFFER_SIZE; ++i)
    {
        std::cout << i << " " << g_buffer[i] << std::endl;
        assert(i == g_buffer[i]);
    }

    std::cout << "Success" << std::endl;
}

void AddThreads()
{
    {
        std::cout << "\t\tAddThreads" << std::endl;
        ThreadPool thread_pool(0, 2);
        CleanBuffer();
        size_t start = 0;
        size_t end = start + 8;

        for (; start < end; ++start)
        {
            ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
                <void *, void *>(Write, (void *)start));
            thread_pool.AddTask(write_task, ThreadPool::HIGH);

            ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
                <void *, void *>(Read, (void *)start));
            thread_pool.AddTask(read_task, ThreadPool::HIGH);
        }
        thread_pool.SetThreadNum(4);

        end += 8;
        for (; start < end; ++start)
        {
            ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
                <void *, void *>(Write, (void *)start));
            thread_pool.AddTask(write_task, ThreadPool::HIGH);

            ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
                <void *, void *>(Read, (void *)start));
            thread_pool.AddTask(read_task, ThreadPool::HIGH);
        }
        thread_pool.SetThreadNum(8);
        end += 8;
        for (; start < end; ++start)
        {
            ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
                <void *, void *>(Write, (void *)start));
            thread_pool.AddTask(write_task, ThreadPool::HIGH);

            ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
                <void *, void *>(Read, (void *)start));
            thread_pool.AddTask(read_task, ThreadPool::HIGH);
        }
        sleep(5);
    }

    std::cout << "Check buffer:" << std::endl;
    for (size_t i = 0; i < 8 * 3; ++i)
    {
        std::cout << i << " " << g_buffer[i] << std::endl;
        assert(i == g_buffer[i]);
    }

    std::cout << "Success" << std::endl;
    
}

void DecThreads()
{
    {
        std::cout << "\t\tDecThreads" << std::endl;
        ThreadPool thread_pool(0, 8);
        CleanBuffer();
        size_t start = 0;
        size_t end = start + 8;

        for (; start < end; ++start)
        {
            ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
                <void *, void *>(Write, (void *)start));
            thread_pool.AddTask(write_task, ThreadPool::HIGH);

            ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
                <void *, void *>(Read, (void *)start));
            thread_pool.AddTask(read_task, ThreadPool::HIGH);
        }
        thread_pool.SetThreadNum(4);

        end += 8;
        for (; start < end; ++start)
        {
            ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
                <void *, void *>(Write, (void *)start));
            thread_pool.AddTask(write_task, ThreadPool::HIGH);

            ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
                <void *, void *>(Read, (void *)start));
            thread_pool.AddTask(read_task, ThreadPool::HIGH);
        }
        thread_pool.SetThreadNum(2);
        end += 8;
        for (; start < end; ++start)
        {
            ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
                <void *, void *>(Write, (void *)start));
            thread_pool.AddTask(write_task, ThreadPool::HIGH);

            ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
                <void *, void *>(Read, (void *)start));
            thread_pool.AddTask(read_task, ThreadPool::HIGH);
        }

        sleep(5);
    }

    std::cout << "Check buffer:" << std::endl;
    for (size_t i = 0; i < 8 * 3; ++i)
    {
        std::cout << i << " " << g_buffer[i] << std::endl;
        assert(i == g_buffer[i]);
    }

    std::cout << "Success" << std::endl;
}

void TrickyOperations()
{
    {
        ThreadPool thread_pool1(0, 100);
        std::cout << "\t\tTrickyOperations" << std::endl;

        {
            ThreadPool thread_pool(0, 8);

            thread_pool.Resume();
            thread_pool.Resume();
            thread_pool.Pause();
            thread_pool.Pause();
            thread_pool.Pause();
            thread_pool.Resume();

            thread_pool.SetThreadNum(0);
        }
        
        {
            ThreadPool thread_pool(0, 8);

            thread_pool.Pause();
            thread_pool.SetThreadNum(0);
            thread_pool.Resume();
        }

        {
            ThreadPool thread_pool(0, 1);

            thread_pool.Pause();
            thread_pool.SetThreadNum(0);
            thread_pool.SetThreadNum(1);
            thread_pool.SetThreadNum(2);
            thread_pool.SetThreadNum(3);
            thread_pool.SetThreadNum(100);
            thread_pool.Resume();
            thread_pool.SetThreadNum(8);
            thread_pool.Pause();
        }

        {
            ThreadPool thread_pool(0, 1);

            size_t start = 0;
            size_t end = start + 30;

            for (; start < end; ++start)
            {
                ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
                    <void *, void *>(Write, (void *)start));
                thread_pool.AddTask(write_task, ThreadPool::HIGH);

                ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
                    <void *, void *>(Read, (void *)start));
                thread_pool.AddTask(read_task, ThreadPool::HIGH);
            }

            thread_pool.Pause();
            thread_pool.SetThreadNum(0);
            thread_pool.SetThreadNum(1);
            thread_pool.SetThreadNum(2);
            thread_pool.SetThreadNum(3);
            thread_pool.SetThreadNum(100);
            thread_pool.Resume();
            thread_pool.SetThreadNum(8);
            thread_pool.Pause();
        }
        ThreadPool thread_pool2(0, 100);
    }
    ThreadPool thread_pool(0, 100);
    sleep(5);
}

void SetThreadNumDecAdvanced()
{
    ThreadPool thread_pool(0, 100);
    std::cout << "\t\tSetThreadNumDecAdvanced" << std::endl;

    size_t start = 0;
    size_t end = start + 1000;

    for (; start < end; ++start)
    {
        ThreadPool::task_t write_task (new ThreadPool::TaskTemplate
            <void *, void *>(Write, (void *)start));
        thread_pool.AddTask(write_task, ThreadPool::HIGH);

        ThreadPool::task_t read_task (new ThreadPool::TaskTemplate
            <void *, void *>(Read, (void *)start));
        thread_pool.AddTask(read_task, ThreadPool::HIGH);
    }

    thread_pool.Pause();
    thread_pool.SetThreadNum(1);
    thread_pool.Resume();
}






void *SimpleTask(void *data)
{
    --counter;
    *(int *)data = 0;
    return NULL;
}

void *HighPriorityTask(void *data)
{
    counter.add(10);
    vector.push_back(counter.load());
    (void)data;
    return NULL;
}

void *MidPriorityTask(void *data)
{
    counter.sub(4);
    vector.push_back(counter.load());

    (void)data;
    return NULL;
}

void *LowPriorityTask(void *data)
{
    counter.sub(6);
    vector.push_back(counter.load());

    (void)data;
    return NULL;
}

void* Task1(void *data)
{
    int *arr = new int[10];
    (void)data;
    delete[] arr;

    return NULL;
}

void* Sleep(void *data)
{
    boost::chrono::duration<int, boost::milli> d(100);
    boost::this_thread::sleep_for(d);

    (void)data;
    return NULL;
}

bool SimpleTest()
{
    counter.store(size);
    size_t res = 0;
    ThreadPool pool;
    for(size_t i = 0; i < size; ++i)
    {
        ThreadPool::task_t task1(new ThreadPool::TaskTemplate<void *,void *>(SimpleTask,&arr[i]));
        pool.AddTask(task1,ThreadPool::HIGH);
    }
    while(counter.load());
    for(size_t i = 0 ; i < size; ++i)
    {
        res += arr[i];
    }

    pool.Shutdown();
    return res == 0;
}

bool PauseTest()
{

    ThreadPool pool(1,3);
    counter.store(10);
    pool.Pause();
    for(size_t i = 0; i < size; ++i)
    {
        ThreadPool::task_t task(new ThreadPool::TaskTemplate<void *,void *>(SimpleTask,&arr[i]));
        pool.AddTask(task,ThreadPool::HIGH);
    }
    usleep(50);
    
    pool.Shutdown();

    return counter.load() ==  10;
}

bool PriorityTest()
{
    vector.clear();
    size_t res = 0; 
    size_t i = 8;
    ThreadPool pool(30, 1);
    size_t arr[size] = {10,20,30,26,22,18,12,6,0};
    counter.store(0);

    pool.Pause();
    pool.SetThreadNum(1);
    for(size_t i = 0; i < 3; ++i)
    {
        ThreadPool::task_t task1(new ThreadPool::TaskTemplate<void *,void *>(HighPriorityTask,&vector));
        ThreadPool::task_t task2(new ThreadPool::TaskTemplate<void *,void *>(MidPriorityTask,&vector));
        ThreadPool::task_t task3(new ThreadPool::TaskTemplate<void *,void *>(LowPriorityTask,&vector));
        pool.AddTask(task1,ThreadPool::HIGH);
        pool.AddTask(task2,ThreadPool::MED);
        pool.AddTask(task3,ThreadPool::LOW);
    }
    pool.Resume();
    sleep(1);
    while(counter.load() > 0);
    while(!vector.empty())
    {
        res += vector.back() == arr[i];
        vector.pop_back();
        --i;
    }
    pool.Shutdown();

    return res == 9;
}


void *AnotherTask(void* data)
{
    boost::mutex::scoped_lock lock(m1);
    try
    {
       vector.push_back((size_t)data);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    counter.add(1);
    return NULL;
}

bool AnotherTest()
{
    vector.clear();
    const size_t size1 = 50;
    counter.store(0);
    ThreadPool pool1(10,30);
    ThreadPool pool2(20,30);
    size_t res = 0;
    for(size_t i = 0; i < size1; ++i)
    {
        if(i % 10 == 0)// checks speed resizes of the pool
        {
            pool2.Pause();
            pool2.SetThreadNum(i % 10 + 1);
            pool1.SetThreadNum(i % 10 + 1);
            pool2.Resume();
        }
        ThreadPool::task_t task1(new ThreadPool::TaskTemplate<void *,void *>(AnotherTask,(void *)i));
        ThreadPool::task_t task2(new ThreadPool::TaskTemplate<void *,void *>(AnotherTask,(void *)i));
        pool1.AddTask(task1, ThreadPool::HIGH);
        pool2.AddTask(task2, ThreadPool::HIGH); 
    }
    
    pool1.SetThreadNum(15);
    pool2.SetThreadNum(15);
    pool2.Resume();
    while(counter.load() != 100)
    {
    }
    for(int i = 0; i < counter.load() ;++i)
    {
        res += vector[i];
    }
    pool1.Resume();
    pool1.SetThreadNum(5);
    
    pool2.Shutdown();
    

    pool1.Pause();
    pool1.Shutdown();
    return res ==  2450;
}


bool AdvancedTest()
{
    ThreadPool pool(10,10);

    char str1[] = "111";
    char str2[] = "222";
    char str3[] = "333";
    char str4[] = "444";

    
    size_t res = 0;
    ThreadPool::task_t task1(new ThreadPool::TaskTemplate<void *,void *>(Sleep,&str1));
    ThreadPool::task_t task2(new ThreadPool::TaskTemplate<void *,void *>(Task1,&str2));
    ThreadPool::task_t task3(new ThreadPool::TaskTemplate<void *,void *>(Task1,&str3));
    ThreadPool::task_t task4(new ThreadPool::TaskTemplate<void *,void *>(Task1,&str4));

    pool.AddTask(task1,ThreadPool::HIGH);
    while(res < 10)
    {
        pool.SetThreadNum(8);
        pool.AddTask(task2,ThreadPool::MED);
        pool.Pause();
        pool.SetThreadNum(3);
        pool.AddTask(task3,ThreadPool::LOW);
        pool.AddTask(task4,ThreadPool::HIGH);
        pool.Resume();
        ++res;
    }

    return NULL;
}

void* FooVoidPtr(int *num)
{
    *num += 10;
    return num;
}

void FooVoidFuture(int *num)
{
    *num += 15;
}

void FooVoid(int *num)
{
    *num += 20;
}

bool TestBasic()
{
    ThreadPool pool1(20,20);
    boost::shared_ptr<Future<void* > > ret_FooVoidPtr(new Future<void* >);
    boost::shared_ptr<Future<void> >ret_FooVoidFuture(new Future<void >);
    int sum = 0;

    int x = 5;
    pool1.AddTask(boost::shared_ptr<Task>
                (new ThreadPool::TaskTemplate<void,int*>(FooVoid, &x)), ThreadPool::LOW);
    pool1.AddTask(boost::shared_ptr<Task>(new ThreadPool::TaskWithFuture<void*,int*>(ret_FooVoidPtr,FooVoidPtr, &x)), ThreadPool::LOW);
    pool1.AddTask(boost::shared_ptr<Task>(new ThreadPool::TaskWithFuture<void,int*>(ret_FooVoidFuture,FooVoidFuture, &x)), ThreadPool::LOW);

    sum += (&x == ret_FooVoidPtr->get());
    ret_FooVoidFuture->get();
    sum += (x == 50);

    return (2 == sum);

}