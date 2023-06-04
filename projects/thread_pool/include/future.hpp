/******************************************************************************
*		Descriptions - future		      				  
*		Date: Sun 04 Apr 2021 15:04:33 IDT					     				
*		Group: RD96		
*	    author:    Moshe Cohen
*	    reviewer:  Yuliya Barabash		      								   				      				*
*******************************************************************************/

#ifndef ILRD_RD96_FUTURE_HPP
#define ILRD_RD96_FUTURE_HPP

#include <boost/thread/mutex.hpp>       //boost::mutex
#include <boost/thread/lock_guard.hpp>  //boost::scope_lock
#include "util.hpp"                     //ilrd::Uncopyable

namespace ilrd
{

template<class T>
class Future: private ilrd::Uncopyable
{
public:
    Future();
    Future<T>& Set(const T& _result);
    ~Future();
    bool IsValid() const;
    T get();
    void wait() const;

private:
    T m_future;
    mutable boost::mutex m_mutex;
    bool m_isValid;
};

template <>
class Future<void>: private ilrd::Uncopyable
{
public:
    Future();
    ~Future();
    Future<void>& Set(); //active this function when you finish the task 
    bool IsValid() const;
    void get();    
    void wait() const;
    
private:
    mutable boost::mutex m_mutex; 
    bool m_isValid;
};

/*******************************************************************************
********************************** class Future *******************************/ 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<class T>
Future<T>::Future():
m_isValid(false)
{
    m_mutex.lock();
}

template<class T>
typename Future<T>::Future& Future<T>::Set(const T& _result)
{
    m_future = _result;

    if (!m_isValid)
    {
        m_isValid = true;
        m_mutex.unlock();
    }

    return *this;
}

template<class T>
Future<T>::~Future()
{
    if (!IsValid())
    {
        m_mutex.unlock();
    }
}

template<class T>
bool Future<T>::IsValid() const
{
    return m_isValid;
}

template<class T>
T Future<T>::get()
{
    wait();

    return m_future;
}

template<class T>
void Future<T>::wait() const
{
    boost::lock_guard<boost::mutex> lock(m_mutex);
}


} //end namespace ilrd
#endif   /*ILRD_RD96_FUTURE_HPP*/