/******************************************************************************
*		Descriptions - scope_lock		      				  *
*		Date: Wed 03 Mar 2021 16:45:01 IST					     				*
*		Group: RD96						      				*
*******************************************************************************/

#ifndef __ILRD_RD96_SCOPE_LOCK_HPP__
#define __ILRD_RD96_SCOPE_LOCK_HPP__

#include <boost/utility.hpp>

namespace ilrd
{
    
template <class MutexTypes>
class ScopeLock : private boost::noncopyable
{
public: 
  explicit ScopeLock(MutexTypes& m);
  ~ScopeLock();

private:
  MutexTypes& m_mutex;
};


template<class MutexTypes>
ScopeLock<MutexTypes>::ScopeLock(MutexTypes& m): m_mutex(m)
{
  m_mutex.lock();
}
template<class MutexTypes>
ScopeLock<MutexTypes>::~ScopeLock()
{
  m_mutex.unlock();
}

}// end namespace ilrd


#endif //__ILRD_RD96_SCOPE_LOCK_HPP__

