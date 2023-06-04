/*******************************************************************************
*	    Descriptions - Shapes API Functions                                    *
*		Date: 4.2.2021                                                         *
*       Group: RD96                                                            *
*       name: Moshe Cohen                                                      *
*       reviewer: Dor Glaubach                                                 * 
*                                                                              *
*******************************************************************************/

#ifndef __ILRD_RD96_SHAPES_HPP__
#define __ILRD_RD96_SHAPES_HPP__

#include <cstddef>  // size_t

namespace ilrd
{
class Shape
{
public:
    Shape();            
    virtual ~Shape();                 

    size_t GetOffset() const;
    Shape& Move(size_t shift_);
    virtual void Draw() const = 0;

private:
    size_t m_offset;
};

inline Shape::Shape(): m_offset(0) {}   

inline Shape::~Shape() {}   

inline size_t Shape::GetOffset() const
{
    return m_offset;
}

inline Shape& Shape::Move(size_t shift_)
{
    m_offset = shift_;

    return *this;
}

void ListOfShapes(Shape **listOfShapes, size_t size);

} // namespace ilrd

#endif   //__ILRD_RD96_SHAPES_HPP__