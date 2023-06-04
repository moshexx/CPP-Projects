#include <iostream>

struct X
{
    explicit X(int);
    ~X();
    void Foo();
    void Bar() const;
    
    int m_a;
    int *m_p;
};

X::X(int a_): m_a(a_), m_p(new int(a_)) {}

X::~X() { delete m_p; m_p=0; }

void X::Foo() { ++m_a; --(*m_p); }

// argument: const X*const
void X::Bar() const //const func can't changed the field in the srtuct
{// Bar gets const this. Foo gets this.
    std::cout << "m_a:  " << m_a << std::endl;
    std::cout << "*m_p: " << *m_p << std::endl;
    std::cout << "m_p:  " << m_p << std::endl;
    // m_a = 0;  // ---1---
    // m_p = 0;  // ---2--- the ptr is const
    *m_p = 0;   // ---3---    the value which ptr point to is not const
    //Foo();    // ---5---
    // X x(5);
    //Bar();       //const member func is enable
}

void Fifi(const X&x_)
{
    //x_.Foo(); // ---4---  ==> const X&x_ mean no changes in x_
    x_.Bar();
}

int main()
{   
    X x1(10);

    x1.Bar(); 
    x1.Foo(); 
    std::cout << "after Foo" << std::endl;
    x1.Bar(); 
    Fifi(x1);
    
    return 0;
}