// 31.1.2021
// class String that can perform the following tasks:
// String s1("aaa");
// String s2="bbb";
// String s3(s2);
// String s4;
// s4 = s2;
// s3[2]='k';

#include <cstring>
#include <iostream>

const int NULL_TERMINATOR = 1;

static char *StrDup(const char *str_)
{
    size_t len = strlen(str_ ) + NULL_TERMINATOR;

    char *str = new char[len];
    memcpy(str, str_, len);

    return str;
}
class String 
{
public:
    String(const char *str_ = "default"): str(StrDup(str_)) {} // no explicit on purpose
    String(const String& other);
    String& operator=(const String& other);
    const char& operator[](int num) const;
    ~String() { delete[] str; }

private:
    char *str;
};

String::String(const String& other)
{
    str = StrDup(other.str); 
}

String& String::operator=(const String& other)
{
    if (this == &other)
    {
        return *this;
    }

    delete[] str;
    str = StrDup(other.str);

    return *this;
}

const char& String::operator[](int num) const
{
    return this->str[num];
}
int main()
{
    
    return 0;
}

