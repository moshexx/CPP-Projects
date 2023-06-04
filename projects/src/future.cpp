/*******************************************************************************
*		Descriptions - future		      				  
*		Date: Sun 04 Apr 2021 15:04:33 IDT					     				
*		Group: RD96		
*	    author:    Moshe Cohen
*	    reviewer:  Yuliya Barabash		      								   				      				*
*******************************************************************************/

#include "future.hpp"

namespace ilrd
{

/*******************************************************************************
******************************* class Future<void> ****************************/ 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Future<void>::Future():
m_isValid(false)
{
    m_mutex.lock();
}

typename Future<void>::Future<void>& Future<void>::Set()
{
    m_isValid = true;

    m_mutex.unlock();

    return *this;
}

Future<void>::~Future()
{
    if (!IsValid())
    {
        m_mutex.unlock();
    }
}

bool Future<void>::IsValid() const
{
    return m_isValid;
}

void Future<void>::get()
{
    wait();
}

void Future<void>::wait() const
{
    boost::lock_guard<boost::mutex> lock(m_mutex);
}

} //end namespace ilrd