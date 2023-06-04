//*****************************************************************************
//*		Descriptions - Observer API functions	    				     	  
//*		Group: RD96
//*     Date: 11/4/2021
//*     author: Moshe Cohen
//*     reviewer: 				TODO:		      								   
//******************************************************************************


#ifndef ILRD_RD96_OBSERVER_HPP
#define ILRD_RD96_OBSERVER_HPP

#include <boost/unordered_set.hpp>  // boost::unordered_set
#include <boost/shared_ptr.hpp>

namespace ilrd
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Forward Declerations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class PARAM>
class Subject;

template <class PARAM>
class Observer;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Declerations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class Observer ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class PARAM>
class Observer
{
public:
    // default constructor
    // default assignment operator
    virtual ~Observer();
    void Subscribe(Subject<PARAM> *subject);
    void Unsubscribe(Subject<PARAM> *subject);  // may throw exception if
                                                // observer does not exist in 
                                                // subscription list
private:
    typedef boost::unordered_set<Subject<PARAM> *>                    Container;
    typedef typename Container::iterator                               Iterator;
    Container m_subjects;
    virtual void Callback(PARAM param) = 0;
    friend void Subject<PARAM>::Notify(PARAM param) const;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class Subject ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class PARAM>
class Subject
{
public:
    // default constructor
    // default assignment operator
    void Notify(PARAM param) const;
    virtual ~Subject();

private:
    typedef boost::unordered_set<Observer<PARAM> *>                   Container;
    typedef typename Container::iterator                               Iterator;
    typedef typename Container::const_iterator                    ConstIterator;
    Container m_observers;
    void AddObserver(Observer<PARAM> * observer);
    void RemoveObserver(Observer<PARAM> * observer);

    
    //Avoid C/C++ IntelliSense extension memory leak:
    #ifndef __INTELLISENSE__ 
    template <class P>
    friend void Observer<P>::Subscribe(Subject<P> *subject);
    template <class P>
    friend void Observer<P>::Unsubscribe(Subject<P> *subject);
    #endif
    
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class Observer ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class PARAM>
Observer<PARAM>::~Observer()
{
    for (Iterator it = m_subjects.begin(); it != m_subjects.end(); ++it)
    {
        Unsubscribe(*it);
    }
}

template <class PARAM>
void Observer<PARAM>::Subscribe(Subject<PARAM> *subject)
{
    subject->AddObserver(this);
    m_subjects.insert(subject);
}

template <class PARAM>
void Observer<PARAM>::Unsubscribe(Subject<PARAM> *subject)
{
    subject->RemoveObserver(this);
    m_subjects.erase(subject);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class Subject ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template <class PARAM>
Subject<PARAM>::~Subject()
{
    Iterator it = m_observers.begin();
    
    while (!m_observers.empty())
    {
        Iterator tmp = it;
        ++it;
        (*tmp)->Unsubscribe(this);
    }
}

template <class PARAM>
void Subject<PARAM>::Notify(PARAM param) const
{
    for (ConstIterator it = m_observers.begin() ,end = m_observers.end();
                                                         it != end; ++it)
    {
        (*it)->Callback(param);
    }
}

template <class PARAM>
void Subject<PARAM>::AddObserver(Observer<PARAM> * observer)
{
    m_observers.insert(observer);
}

template <class PARAM>
void Subject<PARAM>::RemoveObserver(Observer<PARAM> * observer)
{
    m_observers.erase(observer);
}

} //end namespace ilrd

#endif   /*ILRD_RD96_OBSERVER_HPP*/
