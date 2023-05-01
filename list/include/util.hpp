/*******************************************************************************
*		Descriptions - util		      				                           *
*		Date: Thu 18 Feb 2021 15:17:32 IST					     		       *
*		Author: Moshe Cohen 			      				                   *
*******************************************************************************/

#ifndef UTIL_HPP
#define UTIL_HPP

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
namespace ilrd
{

class Uncopyable
{
public:
    Uncopyable();

private:
    Uncopyable(const Uncopyable& _rhs);
    Uncopyable& operator=(const Uncopyable& _rhs);
};

Uncopyable::Uncopyable()
{//empty
}

}// namespace ilrd


#endif   /*UTIL_HPP*/
