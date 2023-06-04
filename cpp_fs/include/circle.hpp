/*******************************************************************************
*	    Descriptions - Circle Class                                            *
*		Date: 4.2.2021                                                         *
*       Group: RD96                                                            *
*       name: Moshe Cohen                                                      *
*       reviewer: Dor Glaubach                                                 * 
*                                                                              *
*******************************************************************************/

#ifndef __ILRD_RD96_CIRCLE_HPP__
#define __ILRD_RD96_CIRCLE_HPP__

#include "shape.hpp"

namespace ilrd
{

class Circle: public Shape
{
public:
    Circle();       
    virtual ~Circle();                    

    virtual void Draw() const;
};


} // namespace ilrd

#endif   //__ILRD_RD96_CIECLE_HPP__
