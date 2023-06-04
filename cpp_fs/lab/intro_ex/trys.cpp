String foo (String s_)
{
    String s2(s_);
    
    return s2;
}

// int main()
// {
//     String str1 = "123 "; // Ctor: heap: string + counter
//     String str2 = ""; 
//     str2 = foo(str1);
    
    

//     return 0;
// }

int main()
{
    RCString str1 = "hello";
    RCString str2 = str1;
    RCString str3 = "bye";
    str1 = str3;
        String::~String()  ;
        char *tmp = str1.m_str;
        str1.m_str = str3.m_str
        str1.m_count = ++str3.m_count

    return 0;
}
    