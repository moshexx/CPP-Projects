#include <iostream>

class X
{
public:
    X() {std::cout << "X  " << this << std::endl;}
    virtual ~X() {std::cout << "~X  " << this << std::endl;}

private:
    double m_a;
};

class Y: public X
{
public:
    Y() {std::cout << "Y  " << this << std::endl;}
    ~Y() {std::cout << "~Y  " << this << std::endl;}
private:
    int m_b;
};

void Foo(X x)
{
    std::cout << "Foo  " << &x << std::endl;
}

int main()
{
    // X *xp = new Y[5];

    // delete[] xp;

    Y y1;
    Foo(y1);

    return 0;
}