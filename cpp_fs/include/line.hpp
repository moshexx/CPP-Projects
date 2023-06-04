/*******************************************************************************
*		Descriptions - line		      				                           *
*		Date: Thu 04 Feb 2021 20:27:45 IST					     			   *
*		Group: RD96						      				                   *
*       name: Moshe Cohen                                                      *
*       reviewer: Dor Glaubach                                                 * 
*                                                                              *
*******************************************************************************/

#ifndef __ILRD_RD96_LINE_HPP__
#define __ILRD_RD96_LINE_HPP__

#include "shape.hpp"

namespace ilrd
{

class Line: public Shape
{
public:
    Line();                
    virtual ~Line();               

    virtual void Draw() const;
};

} // namespace ilrd

#endif   //__ILRD_RD96_LINE_HPP__
