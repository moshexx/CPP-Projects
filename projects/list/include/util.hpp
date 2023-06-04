/*******************************************************************************
*		Descriptions - util		      				                           *
*		Date: Thu 18 Feb 2021 15:17:32 IST					     		       *
*		Group: RD96						      			                       *
*******************************************************************************/

#ifndef ILRD_RD96_UTIL_HPP
#define ILRD_RD96_UTIL_HPP

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


#endif   /*ILRD_RD96_UTIL_HPP*/
