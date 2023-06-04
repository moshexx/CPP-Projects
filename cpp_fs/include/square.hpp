/*******************************************************************************
*	    Descriptions - Square Class                                            *
*		Date: 4.2.2021                                                         *
*       Group: RD96                                                            * 
*       name: Moshe Cohen                                                      *
*       reviewer: Dor Glaubach                                                 * 
*                                                                              *
*******************************************************************************/

#ifndef __ILRD_RD96_SQUARE_HPP__
#define __ILRD_RD96_SQUARE_HPP__

#include "shape.hpp"

namespace ilrd
{

class Square: public Shape
{
public:
    Square();            
    virtual ~Square();                   

    virtual void Draw() const;
};

} // namespace ilrd

#endif   //__ILRD_RD96_SQUARE_HPP__