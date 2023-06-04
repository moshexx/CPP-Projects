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


#include "square.hpp"
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
namespace ilrd
{

Square::Square()
{//empty
}

Square::~Square()
{//empty
}

void Square::Draw() const
{
	std::cout.width(GetOffset() + strlen("Square"));
    std::cout << "Square" << std::endl;
}

} //namespace ilrd

