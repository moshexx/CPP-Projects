/*******************************************************************************
*	    Descriptions - Shape.cpp                                    *
*		Date: 4.2.2021                                                         *
*       Group: RD96                                                            *
*       name: Moshe Cohen                                                      *
*       reviewer: Dor Glaubach                                                 * 
*                                                                              *
*******************************************************************************/


#include "shape.hpp"

namespace ilrd
{
void ListOfShapes(Shape **listOfShapes, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        listOfShapes[i]->Draw();
    }
}

} // namespace ilrd