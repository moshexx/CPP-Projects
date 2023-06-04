// string with tricky requierments (BF)

#include <iostream> // std::
#include <cstring> // std::

class String
{
public:
    String(const char *str_ = ""); // explicit conversion may apear
    // String(const char ch);
    String(const String& other);
    ~String();

    String& operator=(const String& other); // return by value on purpose
    String& operator=(const char other); 
    char& operator[](size_t index);
    const char operator[](size_t index) const;

    char *GetStr() const { return m_str; }
    static size_t GetCount() { return m_count; }

private:
    char *m_str;
    static size_t m_count;
};

size_t String::m_count = 0;

char *StrDup(const char *str_)
{
    char *char_p = new char[strlen(str_) + 1];
    memcpy(char_p, str_, strlen(str_) + 1);

    return char_p;
}

String::String(const char *str_): m_str(StrDup(str_))
{
    ++m_count;
}

// String::String(const char ch)
// {
//     m_str = new char[ch];
    
//     ++m_count;
// }

String::String(const String& other): m_str(other.GetStr())
{
    ++m_count; 
}

String::~String()
{
    --m_count;

    delete[] m_str;
}

String& String::operator=(const char other)
{
    memset(m_str, other, strlen(m_str));

    return *this;
}

String& String::operator=(const String& other)
{
    if (this != &other)
    {
        size_t other_len = strlen(other.GetStr());
        size_t this_len = strlen(GetStr());

        --m_count;
        if (m_count == 0)
        {
            delete[] m_str;
        }

        m_str = other.m_str;
        m_count = other.m_count;        
    }

    return *this;
}

char& String::operator[](size_t index)
{
    if (1 < m_count) 
	{
		*this = String(GetStr());
	}

    return GetStr()[index];
}

const char String::operator[](size_t index) const
{
    return GetStr()[index];
}

int main()
{
    String s1("1234");
    std::cout << s1.GetStr() << std::endl;
    s1 = '@';
    std::cout << s1.GetStr() << std::endl;
    String *s2 = new String;
    std::cout << s2->GetCount() << std::endl;
    std::cout << s2->GetStr() << std::endl;
    delete s2;
    std::cout << String::GetCount() << std::endl;

    return 0;
}