
//******************************************************************************
//------------------------------------------------------------------------------
//*    file name: string.cpp
//*    author: Yarden Natovich Miller
//*    reviewer: Moshe Cohen
//
//------------------------------------------------------------------------------
//******************************************************************************
#include <cstring>

#include "string.hpp"

using namespace ilrd;

String::String(const char *str)
{
    m_cstr= new (std::nothrow) char[strlen(str)+1];
    if(!m_cstr)
    {
        std::cout<<"allocation fail"<< std::endl;
    }
    else
    {
        strcpy(m_cstr, str); 
    }
}

String::String(const String& str)
{
    m_cstr = new (std::nothrow) char[strlen(str.m_cstr)+1];
    if(!m_cstr)
    {
        std::cout<<"allocation fail"<< std::endl;
    }
    else
    {
        strcpy(m_cstr, str.CStr()); 
    
    }
}   

String::~String()
{
    delete [] m_cstr;
}

String& String::operator=(const String& rhs_)
{
    delete [] m_cstr;
    m_cstr = new (std::nothrow) char[strlen(rhs_.CStr()) + 1];
    if(!m_cstr)
    {
        std::cout<<"allocation fail"<< std::endl;
    }
    else
    {
        strcpy(m_cstr,rhs_.CStr());
    }
    
    return *this;
}

bool String :: operator>(const String& rhs_) const
{
    return (strcmp(this->m_cstr, rhs_.CStr()) > 0);
}

bool String :: operator<(const String& rhs_) const
{
    return (strcmp(this->m_cstr, rhs_.CStr()) < 0);
}

size_t String :: Length() const
{
    return (strlen(m_cstr));
}

const char* String::CStr()const
{
    return m_cstr;
}

namespace ilrd
{
    std::ostream& operator<<(std::ostream& os_, const String& s_)
    {
        return os_<< s_.m_cstr;
    }

    bool operator==(const String& lhs_, const String& rhs_)
    {
        return(0 == strcmp(lhs_.CStr(), rhs_.CStr()));
    }

}
