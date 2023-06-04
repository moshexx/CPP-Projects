/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: circle.cpp
*	author: Moshe Cohen
*	reviewer: Dor Glaubach

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include <cstring>   // strlen


#include "circle.hpp"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
namespace ilrd
{

Circle::Circle()
{//empty
}

Circle::~Circle()
{//empty
}

void Circle::Draw() const
{
	// cout.width make sure the length of
	// the print line will be in the follow length
	std::cout.width(GetOffset() + strlen("Circle"));
    std::cout << "Circle" << std::endl;
}

} //namespace ilrd