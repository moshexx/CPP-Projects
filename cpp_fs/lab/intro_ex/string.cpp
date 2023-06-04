#include <iostream>
using namespace std;

class X; //decleration of X because the functions operator+, operator<<, use in
        // X (before the defenition of X).

int operator+(const X& x1_, const X& x2_)
{
    return 7;
}

// ostream& operator<<(ostream& os_, const X& x_);

class X
{
public:
    bool operator==(const X& o_) const { return this->m_a == o_.m_a; }
private:
// the operator '<<' return referance to ostream.
    friend ostream& operator<<(ostream& os_, const X& x_);
    int m_a;
};

int main ()
{
    X x1; // not an expression (defenition)
    X x2; // not an expression
    int num = 2;
    int num2 = 1;
    cout << "+:  " << num + num2 << endl;

    std::cout << " x1+x2: " << (x1 + x2) << "  x1==x2: " <<
     (x1 == x2) << "  x1: " << (x1) << "  x2: " << (x2) << std::endl;

    // x1.operator==(x2);
    // x1 + x2  type: int
    //          value: 7
    //          side effect: none

    // x1 == x2 type: bool
    //          value: 0 or 1
    //          side effect: none

    // exampel of expression with << operator
    // "x1:" << x1  type: ostream&
    //              value: os_ after the change
    //              side effect: shirshur x1 to ostream& "x1: " 



    return 0;
}

ostream& operator<<(ostream& os_, const X& x_)
{
    return os_ << x_.m_a;
}