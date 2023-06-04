//*****************************************************************************
//*		Descriptions - singleton API functions	    				     							
//*     Date: 14.3.21  
//*		Group: RD96						      								   
//******************************************************************************

#ifndef ILRD_RD96_SINGLETON_HPP
#define ILRD_RD96_SINGLETON_HPP

#include <boost/utility.hpp>             // boost::noncopyable
#include <boost/thread/mutex.hpp>        // boost::mutex
#include <boost/thread/lock_guard.hpp>   // boost::lock_guard
#include <boost/atomic/fences.hpp>       // atomic_thread_fence()

namespace ilrd
{

//----------------------------- class Singleton --------------------------------
template <class T>
class Singleton : private boost::noncopyable
{
public:
    // throw std::bad_alloc, boost::lock_error
    // in the first call only - strong safety guarantee
    static T *GetInstance();    

private:
    Singleton();               
    static void DeleteInstance();

    static T *s_instance;
    static boost::mutex s_mutex;
    static bool s_isDeleted;
};

//--------------------- class Singleton - definitions --------------------------
template <class T>
T *Singleton<T>::s_instance = NULL;

template <class T>
boost::mutex Singleton<T>::s_mutex;

template <class T>
bool Singleton<T>::s_isDeleted = false;

//------------------------------------------------------------------------------
template <class T>
T *Singleton<T>::GetInstance()
{
    if(s_isDeleted)
    {
        abort();
    }

    if (NULL == s_instance)
    {// Double lock required - if 2 threads passed the first if,
     // only one of theme will create the instance (in the second if, after the lock).
        boost::lock_guard<boost::mutex> lock(s_mutex);
        if (NULL == s_instance)
        {   // seperate the assignment stage from the allocation and Ctor stages.hpp>       
            // prevent situation of Access uninitialized data from the next thread.
            // (in case "new" fails in Ctor stage after allocation)
            T *tmp = new T;
            boost::atomic_thread_fence(boost::memory_order_release);  // prevent optimization
            s_instance = tmp;
            std::atexit(Singleton<T>::DeleteInstance);
            std::set_terminate(Singleton<T>::DeleteInstance);
        }
    }

    return s_instance;
}

template <class T>
void Singleton<T>::DeleteInstance()
{
    s_isDeleted = true;
    delete s_instance;
    s_instance = NULL;
}



} //end namespace ilrd

#endif   /*ILRD_RD96_SINGLETON_HPP*/