/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: thread_pool.cpp
*	author:    Moshe Cohen
*	reviewer:  Yuliya Barabash
--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <sys/resource.h> //setpriority

#include "thread_pool.hpp"

namespace ilrd
{

//------------------------------- ThreadPool -----------------------------------
//------------------------------- Public ---------------------------------------
ThreadPool::ThreadPool(int niceness, size_t num_threads):
m_niceness(niceness), m_waitableQueue(), m_threads(), m_threadLock(),
m_paused(false), m_shutdown(false), 
m_num_of_threads(num_threads), m_active_threads(num_threads)
{
	ThreadsCreate(num_threads);
	m_ShutdownLock.lock();
}

ThreadPool::~ThreadPool()
{
	Shutdown();
	boost::lock_guard<boost::mutex> lock(m_ShutdownLock);
}

void ThreadPool::AddTask(task_t task, Priority priority)
{
	prioritized_task newTask(task, priority);
	m_waitableQueue.Enqueue(newTask);
}

void ThreadPool::SetThreadNum(size_t size)
{
	boost::lock_guard<boost::mutex> lock(m_threadLock);

	if (size < m_num_of_threads)
	{
		ThreadsRemove(m_num_of_threads - size);
	}
	else if (m_num_of_threads < size)
	{
		ThreadsCreate(size - m_num_of_threads);
		m_active_threads.add(size - m_num_of_threads);
	}
	m_num_of_threads = size;
}

void ThreadPool::Pause()
{
	if (!m_paused)
	{
		boost::lock_guard<boost::mutex> lock(m_threadLock);
		m_paused = true;
	}
}

void ThreadPool::Resume()
{
	if (m_paused)
	{
		boost::lock_guard<boost::mutex> lock(m_threadLock);
		m_paused = false;
		m_conditionVariable.notify_all();
	}
}

void ThreadPool::Shutdown()
{
	boost::lock_guard<boost::mutex> lock(m_threadLock);

	m_shutdown = true;
	
    for (iterator it = m_threads.begin(); it != m_threads.end(); ++it)
	{
		(*it)->interrupt();
	}
	m_threads.clear();
}
//------------------------------- ThreadPool -----------------------------------
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ end of public ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//------------------------------- ThreadPool -----------------------------------
//------------------------------- private --------------------------------------
// throw boost::lock_error
void ThreadPool::ManageThread()
{
	setpriority(PRIO_PROCESS, gettid(), m_niceness); //same niceness for each thread
	prioritized_task newTask(task_t(), EMPTY);

	try
	{
		while (!m_shutdown)
		{
			newTask.second = EMPTY;
			m_waitableQueue.Dequeue(&newTask);

			if (m_paused)
			{
				boost::mutex::scoped_lock lock(m_threadLock);
				if (m_paused)
				{
					m_conditionVariable.wait(lock);
				}
			}
			boost::this_thread::interruption_point();
			boost::this_thread::disable_interruption disable;
			newTask.first->Run();
		}
	}
	catch(const boost::thread_interrupted& e) // case of Shutdown / Remove Thread
	{}

	ThreadCleanUp(newTask);
}

// throw bad_alloc
void ThreadPool::ThreadsCreate(size_t num_of_threads)
{
	for (size_t i = 0; i < num_of_threads; ++i)
	{
		m_threads.push_back(SharedPtr(new Thread(
									&ThreadPool::ManageThread, this)));
	}
}

void ThreadPool::ThreadsRemove(size_t num_of_threads)
{
	for (; 0 < num_of_threads; --num_of_threads)
	{
        m_threads.front()->interrupt();
        m_threads.pop_front();
	}
}

// throw bad_alloc, boost::lock_error
void ThreadPool::ThreadCleanUp(prioritized_task &task)
{
	if (task.second != EMPTY && !m_shutdown)
	{
		m_waitableQueue.Enqueue(task);
	}
	
	if (!m_active_threads.sub_and_test(1))
	{
		m_ShutdownLock.unlock();
	}
}

//------------------------------- Class Compare --------------------------------
//------------------------------- Public ---------------------------------------
bool ThreadPool::Compare::operator()(const prioritized_task& lhs,
                        			 const prioritized_task& rhs) const
{
	return lhs.second < rhs.second;
}

}//end namespace ilrd

