/*******************************************************************************
*                     File name: shared_pointer.hpp                            *
*               Descriptions - Shared_pointer API Functions                    *
*	                          Date: 4.3.21                                       *
*                           Group: RD96                                        *
*                                                                              *
*             author: Moshe Cohen                                              *
*	            reviewer: Dor Glaubach                                           *
*                                                                              *
*******************************************************************************/
#ifndef __ILRD_RD96_SHARED_POINTER_HPP__
#define __ILRD_RD96_SHARED_POINTER_HPP__

#include <cstddef> // size_t
#include <typeinfo> // std::bad_cast

namespace ilrd
{

//~~~~~~~~~~~~~~~~~~~~~~~~~~~ Class UniquePtr Definition ~~~~~~~~~~~~~~~~~~~~~~~
template <class T>
class UniquePtr
{
public:
  explicit UniquePtr(T* ptr = NULL) noexcept;
  ~UniquePtr() noexcept;

  UniquePtr(UniquePtr<T>&& other_) noexcept;
  UniquePtr<T>& operator=(UniquePtr<T>&& other_) noexcept;

  UniquePtr(const UniquePtr<T>& other_)=delete;
  UniquePtr<T>& operator=(const UniquePtr<T>& other_)=delete;
  void *operator new(size_t)=delete; 
  //reset() 

  T& operator*() const noexcept;
  T *operator->() const noexcept;

  
private:
  T *m_ptr;

  // Helper Functions Declerations:
  void RemoveInstance() noexcept;
};// end Class UniquePtr

//~~~~~~~~~~~~~~~~~~~~~~~~~~~ Methods Definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class             T>
UniquePtr<T>::UniquePtr(T* ptr) noexcept: 
m_ptr(ptr)
{//empty budy
}

template <class T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other_) noexcept: 
m_ptr(other_.m_ptr)
{
  other_.m_ptr = nullptr;
}

template <class T>
UniquePtr<T>::~UniquePtr() noexcept
{
  RemoveInstance();
}

template <class T>
inline T& UniquePtr<T>::operator*() const noexcept
{
  return *m_ptr;
}

template <class T>
inline T* UniquePtr<T>::operator->() const noexcept
{
  return m_ptr;
}

template <class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other_) noexcept
{
  if (this != &other_) //Avoid self assignment
  {
    RemoveInstance();
    m_ptr = other_.m_ptr;
    other_.m_ptr = nullptr;
  }

  return *this;    
}

//~~~~~~~~~~~~~~~~~~~~~~~ Helper Functions Definitions ~~~~~~~~~~~~~~~~~~~~~~~~~
template <class T>
inline void UniquePtr<T>::RemoveInstance() noexcept
{
  delete m_ptr;
}


}// end namespace ilrd

#endif   //__ILRD_RD96_SHARED_POINTER_HPP__
