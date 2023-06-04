/******************************************************************************
*		Descriptions - priority_queue		      				  *
*		Date: Thu 18 Mar 2021 17:51:52 IST					     				*
*		Group: RD96						      				*
*******************************************************************************/

#ifndef ILRD_RD96_PRIORITY_QUEUE_HPP
#define ILRD_RD96_PRIORITY_QUEUE_HPP

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <queue>    // std::priority_queue<T, Container, Compare>
#include <cstddef>  // size_t

namespace ilrd
{
template< class T,
          class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type> > 
class Priority_Queue: private std::priority_queue<T, Container, Compare>
{
public:
    explicit Priority_Queue(const Compare& compare = Compare(),
                           const Container& container = Container());
    const T& front() const; // top()
    bool empty() const;
    size_t size() const;
    void push(const T& value);
    void pop();
}; // end of class Priority_Queue

/*******************************************************************************
*******************************************************************************/ 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
template<class T, class Container, class Compare> 
Priority_Queue<T, Container, Compare>::
Priority_Queue(const Compare& compare, const Container& container)
:std::priority_queue<T, Container, Compare>::priority_queue(compare, container)
{ //empty
}

template<class T, class Container, class Compare> 
const T& Priority_Queue<T, Container, Compare>::front() const
{
    return std::priority_queue<T, Container, Compare>::top();
}

template<class T, class Container, class Compare> 
bool Priority_Queue<T, Container, Compare>::empty() const
{
    return std::priority_queue<T, Container, Compare>::empty();
}

template<class T, class Container, class Compare> 
size_t Priority_Queue<T, Container, Compare>::size() const
{
    return std::priority_queue<T, Container, Compare>::size();
}

template<class T, class Container, class Compare> 
void Priority_Queue<T, Container, Compare>::push(const T& value)
{
    std::priority_queue<T, Container, Compare>::push(value);
}

template<class T, class Container, class Compare> 
void Priority_Queue<T, Container, Compare>::pop() 
{
    return std::priority_queue<T, Container, Compare>::pop();
}

} //end namespace ilrd

#endif   //ILRD_RD96_PRIORITY_QUEUE_HPP

