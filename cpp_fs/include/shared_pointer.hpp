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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~ Class SharedPtr Definition ~~~~~~~~~~~~~~~~~~~~~~~
template <class T>
class SharedPtr
{
public:
  explicit SharedPtr(T* ptr = NULL); // May throw exception on allocation
  ~SharedPtr();

  SharedPtr(const SharedPtr<T>& other_);
  SharedPtr<T>& operator=(const SharedPtr<T>& other_);

  T& operator*() const;
  T* operator->() const;

  template <class D>
  SharedPtr(const SharedPtr<D>& other_);

  
private:
  T *m_ptr;
  size_t *m_rc;

  // Helper Functions Declerations:
  void RemoveInstance();

  void *operator new(size_t); // disable operator new

  template<class U, class D>
  friend U* JoinTwo(SharedPtr<U>& one, const SharedPtr<D>& other);
};// end Class SharedPtr

//~~~~~~~~~~~~~~~~~~~~~~~~~~~ Methods Definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class T>
SharedPtr<T>::SharedPtr(T* ptr): 
m_ptr(ptr),
m_rc(new size_t(1))
{  //empty budy
}

template <class T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other_): 
m_ptr(other_.m_ptr), m_rc(other_.m_rc) 
{ 
  ++*m_rc;
}

template <class T>
SharedPtr<T>::~SharedPtr() 
{
  RemoveInstance();
}

template <class T>
inline T& SharedPtr<T>::operator*() const
{
  return *m_ptr;
}

template <class T>
inline T* SharedPtr<T>::operator->() const
{
  return m_ptr;
}

template <class T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other_)
{
  if (this != &other_) //Avoid self assignment
  {
    RemoveInstance();
    m_ptr = other_.m_ptr;
    m_rc = other_.m_rc;
    ++*m_rc;
  }

  return *this;    
}

template <class T>
template <class D>
SharedPtr<T>::SharedPtr(const SharedPtr<D>& other_):
m_ptr(JoinTwo(*this, other_))
{   //empty budy
}

//~~~~~~~~~~~~~~~~~~~~~~~ Helper Functions Definitions ~~~~~~~~~~~~~~~~~~~~~~~~~
template <class T>
inline void SharedPtr<T>::RemoveInstance()
{
  delete m_ptr;
}

template<class U, class D>
U* JoinTwo(SharedPtr<U>& one, const SharedPtr<D>& other)
{
    U* temp_ptr = NULL;
    (void)static_cast<U*>(other.m_ptr); // detect bad cast in compile time (between 2 brothers classes)
    if(NULL == (temp_ptr = dynamic_cast<U*>(other.m_ptr))) 
    {
        throw std::bad_cast();
    }
    one.m_ptr = temp_ptr;
    one.m_rc = other.m_rc;

    ++*one.m_rc;

    return one.m_ptr;
}

}// end namespace ilrd

#endif   //__ILRD_RD96_SHARED_POINTER_HPP__
