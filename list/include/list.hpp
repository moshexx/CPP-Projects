/*******************************************************************************
*		Descriptions - list		      				                           *
*		Date: Thu 25 Mar 2021 16:36:03 IST					     			   *
*		Author: Moshe Cohen 			      				                   *
*******************************************************************************/

#ifndef ILRD_RD96_LIST_HPP
#define ILRD_RD96_LIST_HPP

#include <mutex>                                 // std::mutex

#include "scope_lock.hpp"                       // class ScopeLock
#include "util.hpp"                             // Uncopyable

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
namespace ilrd
{

template <class T>
class CmpFunctor;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class List ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename COMPARE = CmpFunctor<T> >
class List: private ilrd::Uncopyable
{
public:
    List();                         // throw bad_alloc
    virtual void Push(T data) = 0;      
    virtual bool Pop(T *_outparam) = 0; 
    virtual ~List();

protected:
    class Node 
    {
    public:
        Node():        m_next(NULL){}
        Node(T data_): m_data(data_), m_next(NULL){}

        T m_data; 
        Node *m_next;
    };

    std::mutex m_mtx;
    Node *m_head;

    //helpers functions
    bool IsEmpty() const; 
    Node *FindNode(T data) const;
    void InsertBeforeNode(Node *new_node, Node *node);
    void RemoveNode(Node *node);
};//end class List

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class ListQuickPop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename COMPARE = CmpFunctor<T> >
class ListQuickPop: public List<T, COMPARE>
{
public:
    // default constructor
    // default destructor
    virtual void Push(T data);      // throw std::bad_alloc, std::lock_error
    virtual bool Pop(T *_outparam); // throw std::lock_error

private:
    typedef typename List<T, COMPARE>::Node Node;
};//end class ListQuickPop

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class ListQuickPush ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename COMPARE = CmpFunctor<T> >
class ListQuickPush: public List<T, COMPARE>
{
public:
    // default constructor
    // default destructor
    virtual void Push(T data);      // throw std::bad_alloc, std::lock_error
    virtual bool Pop(T *_outparam); // throw std::lock_error

private:
    typedef typename List<T, COMPARE>::Node Node;
    Node *FindMax() const;
};//end class ListQuickPush


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ implementations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// default COMPARE functor
template <class T>
class CmpFunctor
{
public:
    CmpFunctor(T one, T other): m_one(one), m_other(other){}

    bool operator()() const
    {
        return m_one < m_other;
    }

private:
    const T m_one;
    const T m_other;
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class List ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename COMPARE>
List<T, COMPARE>::List():
m_mtx(), m_head(new Node)
{    //empty
}

template<typename T, typename COMPARE>
List<T, COMPARE>::~List()
{
    ScopeLock<std::mutex>lock(m_mtx);

    while (NULL != m_head)
    {
        Node *tmp = m_head;

        m_head = m_head->m_next;
        delete tmp;
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~ class List - helpers functions ~~~~~~~~~~~~~~~~~~~~
template<typename T, typename COMPARE>
inline bool List<T, COMPARE>::IsEmpty() const
{
    return NULL == m_head->m_next;
}

template<typename T, typename COMPARE>
typename List<T, COMPARE>::Node *List<T, COMPARE>::FindNode(T data) const
{
    Node *current = List<T, COMPARE>::m_head;

    for (;NULL != current->m_next; current = current->m_next)
    {
        if (0 < COMPARE(current->m_data, data)()) //Ctor + operator()                             
        {
            break;
        }
    }

    return current;
}

template<typename T, typename COMPARE>
inline void List<T, COMPARE>::InsertBeforeNode(Node *new_node, Node *node)
{
    T newData = new_node->m_data;

    new_node->m_next = node->m_next;
    node->m_next = new_node;

    // swap data (an optimization technique)
    new_node->m_data = node->m_data;
    node->m_data = newData;
}   

template<typename T, typename COMPARE>
inline void List<T, COMPARE>::RemoveNode(Node *node)
{
    node->m_data = node->m_next->m_data;
    Node *tmp = node->m_next;
    node->m_next = node->m_next->m_next;
    delete tmp;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class ListQuickPop ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename COMPARE>
void ListQuickPop<T, COMPARE>::Push(T data)
{
    ScopeLock<std::mutex>lock(List<T, COMPARE>::m_mtx);
    Node *newNode = new Node(data);
    Node *current = List<T, COMPARE>::FindNode(data);

    List<T, COMPARE>::InsertBeforeNode(newNode, current);
}

template<typename T, typename COMPARE>
bool ListQuickPop<T, COMPARE>::Pop(T *_outparam)
{
    Node *head = List<T, COMPARE>::m_head;
    ScopeLock<std::mutex>lock(List<T, COMPARE>::m_mtx);

    if (List<T, COMPARE>::IsEmpty())
    {
        return false;
    }
    *_outparam = head->m_data;

    List<T, COMPARE>::RemoveNode(head);

    return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ class ListQuickPush ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<typename T, typename COMPARE>
void ListQuickPush<T, COMPARE>::Push(T data)
{
    Node *head = List<T, COMPARE>::m_head;
    ScopeLock<std::mutex>lock(List<T, COMPARE>::m_mtx);
    Node *newNode = new Node(data);

    List<T, COMPARE>::InsertBeforeNode(newNode, head);
}

template<typename T, typename COMPARE>
bool ListQuickPush<T, COMPARE>::Pop(T *_outparam)
{
    ScopeLock<std::mutex>lock(List<T, COMPARE>::m_mtx);
    
    if (List<T, COMPARE>::IsEmpty())
    {
        return false;
    }

    Node *found = FindMax();
    *_outparam = found->m_data;

    List<T, COMPARE>::RemoveNode(found);

    return true;
}

template<typename T, typename COMPARE>
typename List<T, COMPARE>::Node *ListQuickPush<T, COMPARE>::FindMax() const
{
    Node *maxNode = List<T, COMPARE>::m_head;

    for (Node *runner = List<T, COMPARE>::m_head;
         NULL != runner->m_next; runner = runner->m_next)
    {
        if (0 < COMPARE(maxNode->m_data, runner->m_data)())                 
        {
            maxNode = runner;
        }
    }

    return maxNode;
}

}//end namespace ilrd


#endif   //ILRD_RD96_LIST_HPP
