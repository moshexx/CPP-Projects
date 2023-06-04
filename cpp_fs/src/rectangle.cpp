/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: rectangle.cpp
*	author: Moshe Cohen
*	reviewer: Dor Glaubach

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include <cstring>   // strlen

#include "rectangle.hpp"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

namespace ilrd
{

Rectangle::Rectangle()
{//empty
}

Rectangle::~Rectangle()
{//empty
}

void Rectangle::Draw() const
{
    std::cout.width(GetOffset() + strlen("Rectangle"));
    std::cout << "Rectangle" << std::endl;
}

} //namespace ilrd
