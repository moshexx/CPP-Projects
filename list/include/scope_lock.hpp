/******************************************************************************
*		Descriptions - scope_lock		      				  *
*		Date: Wed 03 Mar 2021 16:45:01 IST					     				*
*		Group: RD96						      				*
*******************************************************************************/

#ifndef __SCOPE_LOCK_HPP__
#define __SCOPE_LOCK_HPP__

#include <util.hpp>

namespace ilrd
{
    
template <class MutexTypes>
class ScopeLock : private ilrd::Uncopyable
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


#endif //__SCOPE_LOCK_HPP__

