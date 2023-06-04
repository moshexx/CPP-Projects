//*****************************************************************************
//*		Descriptions - Thread Safe Priority Queue API functions	    				     	  
//*		Group: RD96						      								   
//******************************************************************************

#ifndef ILRD_RD96_WAITABLE_QUEUE_HPP
#define ILRD_RD96_WAITABLE_QUEUE_HPP

#include <boost/utility.hpp>                    // boost::noncopyable
#include <boost/thread/mutex.hpp>               // boost::mutex
#include <boost/thread/condition_variable.hpp>  // boost::condition_variable
#include <boost/chrono.hpp>                     // boost::chrono
#include <boost/thread/locks.hpp>               // boost::scope_lock

#include "priority_queue_wrapper.hpp"           // remove in case we wan't use 
                                                // our Priority_Queue.
namespace ilrd
{

template <class TYPE, class QUEUE = Priority_Queue<TYPE> > 
class WaitableQueue : private boost::noncopyable
{
public:

    void Enqueue(TYPE element);
    void Dequeue(TYPE *outparam);

    template <class REP, class PERIOD>
    bool Dequeue(TYPE *outparam, boost::chrono::duration<REP, PERIOD> duration);

    bool IsEmpty() const;
    
private:
    QUEUE m_queue;
    mutable boost::mutex m_func_lock;
    boost::condition_variable m_accessCond;
};// end of class WaitableQueue

/*******************************************************************************
*******************************************************************************/ 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class TYPE, class QUEUE> 
void WaitableQueue<TYPE, QUEUE>::Enqueue(TYPE element)
{
    boost::mutex::scoped_lock lock(m_func_lock);

    m_queue.push(element);

    m_accessCond.notify_one();
}

template <class TYPE, class QUEUE> 
void WaitableQueue<TYPE, QUEUE>::Dequeue(TYPE *outparam)
{
    boost::mutex::scoped_lock lock(m_func_lock);
    
    while(m_queue.empty())
    {
        m_accessCond.wait(lock);
    }
    *outparam = m_queue.front();
    m_queue.pop();
}

template <class TYPE, class QUEUE>
template <class REP, class PERIOD>
bool WaitableQueue<TYPE, QUEUE>::
Dequeue(TYPE *outparam, boost::chrono::duration<REP, PERIOD> duration)
{
    boost::mutex::scoped_lock lock(m_func_lock);

    while(m_queue.empty())
    {
        if (boost::cv_status::timeout == m_accessCond.wait_for(lock, duration))
        {
            return false;
        }
    }
    *outparam = m_queue.front(); 
    m_queue.pop();

    return true;
}

template <class TYPE, class QUEUE> 
bool WaitableQueue<TYPE, QUEUE>::IsEmpty() const
{
    boost::mutex::scoped_lock lock(m_func_lock);

    return m_queue.empty();
}

} //end namespace ilrd

#endif   /*ILRD_RD96_WAITABLE_QUEUE_HPP*/