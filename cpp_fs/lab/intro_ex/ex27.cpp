#include <iostream>

class X
{
public:
    explicit X();               // default Constructor
    explicit X(int a_);         // Constructor
    explicit X(int a_, int b_); // Constructor

    operator int() const;       // conversion operator
    void Print() const;

private:
    int m_a;
};


// Ctors:
X::X() : m_a(0) { }
X::X(int a_) : m_a(a_) { }
X::X(int a_, int b_) : m_a(a_ + b_) { }

X::operator int() const
{
    return m_a;
}

void X::Print() const
{
    std::cout << "X::Print() " << m_a << std::endl;
}


void Fifi(X& x_)
{
    std::cout << "Fifi() " << x_ << std::endl;
    x_.Print();
}

int main()
{
    X x1(7);

    Fifi(x1);    // (1)

    // build tmp object and send it to Fifi.
    Fifi(X(7)); // (2)  type: void.  value: none.   side_effect: none.

    // Fifi(9); // (3)  invalid argument. if we will remove the explicit from 
    // the second Ctor explicit X(int a_); it will work.

    //Fifi(3, 4); // (4) works in C11: Fifi({3,4});

    return x1 * 3; // (5) 7*3
}