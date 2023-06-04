/*******************************************************************************
*	    Descriptions - Rectangle Class                                         *
*		Date: 4.2.2021                                                         *
*       Group: RD96                                                            * 
*       name: Moshe Cohen                                                      *
*       reviewer: Dor Glaubach                                                 * 
*                                                                              *
*******************************************************************************/

#ifndef __ILRD_RD96_RECTANGLE_HPP__
#define __ILRD_RD96_RECTANGLE_HPP__

#include "shape.hpp"

namespace ilrd
{

class Rectangle: public Shape
{
public:
    Rectangle();          
    virtual ~Rectangle();                   

    virtual void Draw() const;
};

} // namespace ilrd

#endif   //__ILRD_RD96_RECTANGLE_HPP__