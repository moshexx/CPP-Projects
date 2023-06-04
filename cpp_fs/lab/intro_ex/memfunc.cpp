//ex23. member functions in struct
#include <iostream>

struct X
{
    X(int a_, int b_);
    X &Inc();
    X &Dec();

    int m_a;
    int m_b;
};


X::X(int a_, int b_): m_a(a_), m_b(b_){std::cout << "X:: Ctor" << std::endl;}

X &X::Inc()
{
    ++m_a;
    ++m_b;
    std::cout << "X:: Inc" << std::endl;
    
    return *this;
}

X &X::Dec()
{
    --m_a;
    --m_b;
    std::cout << "X:: Dec" << std::endl;

    return *this;
}

void Inc(){std::cout << "General Inc" << std::endl;}

int main()
{
    X x1(7,-55);    // X:: Ctor
    X x2(x1); // default CCtor

    Inc();   //  general Inc
    x1.Inc();   // X:: Inc
    x1.Inc();   // X:: Inc
    x2.Dec();   // X:: Dec
    std::cout << "before Inc(): " << x1.m_a << std::endl;
    std::cout << "before Inc(): " << x1.m_b << std::endl;
    x1.Inc().Inc().Inc().Inc().Inc(); 
    std::cout << "before Inc(): " << x1.m_a << std::endl;
    std::cout << "before Inc(): " << x1.m_b << std::endl;
    
    std::cout << sizeof(X) << std::endl;

    
    return 0;
}