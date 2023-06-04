//*****************************************************************************
//*		Descriptions - Thread Pool header file	    				     	  
//*		Group:     RD96				
//*	    author:    Moshe Cohen
//*	    reviewer:  Yuliya Barabash		      								   
//******************************************************************************
#ifndef ILRD_RD96_THREAD_POOL_HPP
#define ILRD_RD96_THREAD_POOL_HPP

#include <utility>                       //std::pair
#include <boost/thread.hpp>              //boost::thread, hardware_concurrency	

#include "priority_queue_wrapper.hpp"   //ilrd::Priority_Queue
#include "waitable_queue.hpp"           //ilrd::WaitableQueue
#include "future.hpp"                   //ilrd::Future
#include "util.hpp"                     //ilrd::Uncopyable


namespace ilrd
{

class ThreadPool : private ilrd::Uncopyable
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ThreadPool ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Private ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
    //~~~~~~~~~~~~~~~~~~~~~~~~~~ Public enum, typedef ~~~~~~~~~~~~~~~~~~~~~~~~~~
    class Task;
    typedef boost::shared_ptr<Task>                                      task_t;
    enum Priority
    {
        LOW = 0,
        MED = 1,
        HIGH = 2
    };

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Public Methods ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // all of the ThreadPool public methods may         throw boost::lock_error
    ThreadPool(int niceness = 0, size_t num_threads =
               boost::thread::hardware_concurrency()); // throw: bad_alloc
    ~ThreadPool();

    void AddTask(task_t task, Priority priority);      // throw: bad_alloc
    void SetThreadNum(size_t size);                    // throw: bad_alloc

    void Pause();
    void Resume();
    void Shutdown();
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Task family ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // The ThreadPool receives Task *, priority and may also receives a Future
    // out parameter to return the return value from the Task function.
    // Futur<void> is suitable in case there is no return value, but the
    // time of the task done is required.

    //~~~~~~ interface Task ~~~~~~~~
    class Task
    {
    public:
        virtual void Run() = 0;
        virtual ~Task() = 0;
    };

    //~~~~~~~~ Regular Task ~~~~~~~~
    template<typename R, typename P>
    class TaskTemplate: public Task
    {
    public:
        typedef R(*task_ptr)(P);
        TaskTemplate(task_ptr task = NULL, P param = NULL);
        virtual void Run();

    private:
        task_ptr m_task;
        P m_param;
    };

    //~~~~~~~~ Fututre Task ~~~~~~~~
    template<typename R, typename P>
    class TaskWithFuture : public Task
    {
    public:
        typedef R(*task_ptr)(P);
        TaskWithFuture(boost::shared_ptr<Future<R> >future,
                       task_ptr task =NULL,
                       P param = NULL);
        void Run();
        Future<R> *GetFuture() {return m_future->get();}

    private:
        boost::shared_ptr<Future<R> > m_future; 
        task_ptr m_task;
        P m_param;
    };

    //~~~~~ Fututre<void> Task ~~~~~
    template<typename P>
    class TaskWithFuture<void, P> : public Task
    {
    public:
        typedef void(*task_ptr)(P);
        TaskWithFuture(boost::shared_ptr<Future<void> >future,
                       task_ptr task = NULL, 
                       P param = NULL);
        void Run();

    private:
        boost::shared_ptr<Future<void> > m_future; 
        task_ptr m_task;
        P m_param;
    };
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end of Tasks ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ThreadPool ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Private ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
    //~~~~~~~~~ enums, typedefs and functor for inretnal implementation ~~~~~~~~
    enum
    {
        EMPTY = -1,
        TOP_PRIORITY = HIGH + 1
    };

    class Compare;
    typedef std::pair<task_t, int>                             prioritized_task;
    typedef Priority_Queue< prioritized_task,
            std::vector<prioritized_task>, Compare >                     PQueue;
    typedef WaitableQueue<prioritized_task, PQueue>                      WQueue;
    typedef boost::thread                                                Thread;
    typedef boost::shared_ptr<Thread>                                 SharedPtr;
    typedef std::list<SharedPtr>                                   thread_group;
	typedef thread_group::iterator                                     iterator;

    class Compare
    {
    public:
        bool operator()(const prioritized_task& lhs,
                        const prioritized_task& rhs) const;
    };

    //~~~~~~~~~~~~~~~~~~~~~~~~ helping members variables ~~~~~~~~~~~~~~~~~~~~~~~
    int m_niceness;
    WQueue m_waitableQueue;
    thread_group m_threads;
    mutable boost::mutex m_threadLock;
    boost::mutex m_ShutdownLock;
    boost::condition_variable m_conditionVariable;

    bool m_paused;
    bool m_shutdown;
    size_t m_num_of_threads;                //number of total threads
    //a real time counter of active threads, used to check when the last thread ends.
    boost::atomic<size_t> m_active_threads; 
                                        
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~ helpers functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~
    void ManageThread();
    void ThreadsCreate(size_t num_of_threads);
    void ThreadsRemove(size_t num_of_threads);
    void ThreadCleanUp(prioritized_task &task);

}; //end class ThreadPool








//~~~~~~~~~~~~~~~~~~~~~~~ Template Implemententations ~~~~~~~~~~~~~~~~~~~~~~~~~~
//------------------------------- Task family ----------------------------------
//------------------------------- Interface Task -------------------------------
inline ThreadPool::Task::~Task()
{// empty
}

//------------------------------- Class TaskTemplate ---------------------------
template<typename R, typename P>
ThreadPool::TaskTemplate<R, P>::TaskTemplate(task_ptr task, P param):
m_task(task), m_param(param)
{// empty
}

template<typename R, typename P>
void ThreadPool::TaskTemplate<R, P>::Run()
{
	m_task(m_param);
}

//------------------------------- Class TaskWithFuture ------------------------
template<typename R, typename P>
ThreadPool::TaskWithFuture<R, P>::TaskWithFuture(
									boost::shared_ptr<Future<R> >future,
                       				task_ptr task, P param):
m_future(future), m_task(task), m_param(param)
{// empty
}

template<typename R, typename P>
void ThreadPool::TaskWithFuture<R, P>::Run()
{
	m_future->Set(m_task(m_param));
}

//-------------------------- Class TaskWithFuture<void, P> ---------------------
template<typename P>
ThreadPool::TaskWithFuture<void, P>::TaskWithFuture(
                                        boost::shared_ptr<Future<void> >future,
										task_ptr task, P param):
m_future(future), m_task(task), m_param(param)
{// empty
}

template<typename P>
void ThreadPool::TaskWithFuture<void, P>::Run()
{
	m_task(m_param);
    m_future->Set();
}

} //end namespace ilrd

#endif   /*ILRD_RD96_THREAD_POOL_HPP*/
