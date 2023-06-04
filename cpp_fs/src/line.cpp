/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: square.cpp
*	author: Moshe Cohen
*	reviewer: Dor Glaubach

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include <cstring>   // strlen


#include "line.hpp"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
namespace ilrd
{

Line::Line()
{//empty
}

Line::~Line()
{//empty
}

void Line::Draw() const
{
	std::cout.width(GetOffset() + strlen("Line"));
    std::cout << "Line" << std::endl;
}

} //namespace ilrd

