/*******************************************************************************
*	    Descriptions - String API Functions                                    *
*		Date: 19.01.2021                                                       *
*       Group: RD96                                                            * 
*                                                                              *
*******************************************************************************/
#ifndef __ILRD_RD96_STRING_HPP__
#define __ILRD_RD96_STRING_HPP__

#include <cstddef>
#include <iostream>

namespace ilrd
{

class String
{
public:
    String(const char *str = "");  // non-explicit on purpose
    String(const String& str);    
    ~String();                    

    String& operator=(const String& rhs_);

    bool operator>(const String& rhs_) const; 
    bool operator<(const String& rhs_) const; 
    
    size_t Length() const;
    const char *CStr() const; 

private:
    friend std::ostream& operator<<(std::ostream& os_, const String& s_);
    char *m_cstr;
};

bool operator==(const String& lhs_, const String& rhs_);
//bool operator==(const char *str, const String& rhs_);

} // namespace ilrd

#endif   //__ILRD_RD96_STRING_HPP__
