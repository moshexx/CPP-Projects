/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: string.cpp
*	author: Moshe Cohen
*	reviewer: Nir 

--------------------------------------------------------------------------------
*******************************************************************************/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <cstring> // strlen, strcmp, memcpy

#include "string.hpp" 

namespace ilrd
{
static char *StrDup(const char *str);
const int NULL_TERMINATOR = 1;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ API functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

String::String(const char *str): m_cstr(StrDup(str))
{// Empty CStr()
}

String::String(const String& other)
{
    m_cstr = new char[other.Length() + NULL_TERMINATOR];
    memcpy(m_cstr, other.CStr(), other.Length() + NULL_TERMINATOR);
}

// move constructor
String::String(String&& other) noexcept: m_cstr(other.m_cstr)
{
    other.m_cstr = nullptr;
}

// move assignment operator
String& String::operator=(String&& rhs_) noexcept
{
    if (this != &rhs_)
    {
        delete[] m_cstr;
        m_cstr = rhs_.m_cstr;
        rhs_.m_cstr = nullptr;
    }

    return *this;
}

String::~String()
{
    delete[] m_cstr;
}

// Operators functions
String& String::operator=(const String& rhs_)
{// Assignment operator
    if (this == &rhs_)
    {
        return *this;
    }

    delete[] m_cstr;
    m_cstr = new char[rhs_.Length() + NULL_TERMINATOR];
    memcpy(m_cstr, rhs_.CStr(), rhs_.Length() + NULL_TERMINATOR);

    return *this;
}

bool String::operator>(const String& rhs_) const
{
    return strcmp(CStr(), rhs_.CStr()) > 0;
}

bool String::operator<(const String& rhs_) const
{
    return strcmp(m_cstr, rhs_.CStr()) < 0;
}

// Member Functions
size_t String:: Length() const
{
    return strlen(CStr());
}

const char *String::CStr() const
{
    return m_cstr;
}


std::ostream& operator<<(std::ostream& os_, const String& s_)
{
    return os_ << s_.CStr();
}

bool operator==(const String& lhs_, const String& rhs_)
{
    return 0 == strcmp(lhs_.CStr(), rhs_.CStr());
}


static char *StrDup(const char *str)
{
    size_t len = strlen(str) + NULL_TERMINATOR;

    char *char_p = new char[len];
    memcpy(char_p, str, len);

    return char_p;
}

}//namespace ilrd