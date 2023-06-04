#include <iostream>

struct X
{
    explicit X();                   //default constructor
    explicit X(int a_, int b_= 0);  //constructor case the user send at least 1 argument
    ~X();                           //distructor
    X(const X& other_);             //copy constructor
    X& operator=(const X& other_); //assignment operator
    X& operator+(const X& other_); //+ operator

    int m_a;
    const int m_b;
};

/* struct Y
{
    explicit Y();
    Y& operator=(const Y& other_);
    X m_x; 
    int m_i;
};

Y::Y():m_x(3), m_i(4) // implemetation of default Y Ctor
{
    std::cout<<"this:" << this <<" Y default Ctor" << std::endl;
}

Y& Y::operator=(const Y& other_)
{
    m_x.m_a = other_.m_x.m_a;
    m_i = other_.m_i;
    std::cout<<"this:" << this <<" Y assignment operator. m_a:"<<m_x.m_a
                                                    <<" m_b:"<<m_x.m_b<<std::endl;

    return *this;
} */

X::X():m_a(3), m_b(4) // implemetation of default Ctor
{
    std::cout<<"this:" << this <<" X default Ctor. m_a:"<<m_a
                                                    <<" m_b:"<<m_b<<std::endl;
}

X::X(int a_, int b_):m_a(a_), m_b(b_) // implemetation of second Ctor
{
    std::cout<<"this:" << this <<" X int int  Ctor. m_a:"<<m_a
                                                    <<" m_b:"<<m_b<<std::endl;

}

X::X(const X& other_):m_a(other_.m_a), m_b(other_.m_b) // implemetation of copy Ctor
{
    std::cout<<"this:" << this <<" X copy Ctor. m_a:"<<m_a
                                                    <<" m_b:"<<m_b<<std::endl;
}

// X& X::operator=(const X& other_)
// {
//     m_a = other_.m_a;
//     //m_b = other_.m_b;
//     std::cout<<"this:" << this <<" X assignment operator. m_a:"<<m_a
//                                                     <<" m_b:"<<m_b<<std::endl;

//     return *this;
// }

X& X::operator+(const X& other_)
{
    m_a += other_.m_a;
    //m_b += other_.m_b;

    return *this;
}

X::~X()
{
    std::cout<<"this:" << this <<" X Dtor. m_a:"<<m_a
                                                    <<" m_b:"<<m_b<<std::endl;
}

int main()
{
    X x1;     //    implemetation of default Ctor m_a(3), m_b(4)
    X x2(7); //     implemetation of second Ctor m_a(7), m_b(0)
    X *px = new X(x2); // use in copy constructor
    X x3(9,10); //     implemetation of second Ctor m_a(9), m_b(10)
    X x4(x1);  //      use in copy constructor x4.m_a = x1.m_a == 9

    x4 = x1 + x3;
    std::cout << "add:   " << x4.m_a << std::endl;

    delete px; px = 0;
    std::cout << sizeof(x2) << std::endl;

    // ex. 21:
    X *xp = new X[10];
    delete[] xp;

    // ex.22:
    // Y y1;
    // y1.m_x.m_a = 250;
    // // y1.m_x.m_b = 750;
    // Y y2(y1);
    // Y y3;
    
    // y3 = y1;

    return 0;
}