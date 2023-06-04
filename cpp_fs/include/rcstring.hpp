/*******************************************************************************
*	    Descriptions - Reference Counting String API Functions                 *
*		Date: 31.01.2021                                                       *
*       Group: RD96                                                            * 
*                                                                              *
*******************************************************************************/

#ifndef __ILRD_RD96_RCSTRING_HPP__
#define __ILRD_RD96_RCSTRING_HPP__ 

#include <iostream> // std::istream, std::ostream
#include <cstddef> // size_t

namespace ilrd
{

class RCString
{
public:
    // strong exception safety guarantee: throw std::bad_alloc
    RCString(const char *str = "");  // non-explicit on purpose. 
    RCString(const RCString& str);    
    ~RCString();           

    RCString& operator=(const RCString& rhs_);
    
    // strong safety guarantee: throw std::bad_alloc
    RCString& operator+=(const RCString& rhs_); 
    
    // strong safety guarantee: throw std::bad_alloc
    char& operator[](size_t index);             
    const char& operator[](size_t index) const;

    size_t Length() const;
    const char *GetStr() const; 
    
private:
    struct string_data
    {
        size_t counter;
        char flex_str[1];
    };
    string_data *m_data;
    static const int NULL_TERMINATOR;
    string_data *Init(const char *str);
    void RemoveInstance();
};

std::ostream& operator<<(std::ostream& os_, const RCString& s_);
std::istream& operator>>(std::istream& is_, RCString& s_);

bool operator==(const RCString& lhs_, const RCString& rhs_);
bool operator!=(const RCString& lhs_, const RCString& rhs_);
bool operator>(const RCString& lhs_,const RCString& rhs_); 
bool operator<(const RCString& lhs_,const RCString& rhs_); 

} // namespace ilrd

 #endif   /*__ILRD_RD96_RCSTRING_HPP__ */
