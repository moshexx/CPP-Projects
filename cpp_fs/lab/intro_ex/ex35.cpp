// Exception safety - Ctors

#include <iostream>        // std::cout, std::cerr
#include <typeinfo>       // std::bad_cast

using namespace std;

struct X 
{   // If a constructor throws an exception, the object’s destructor is not run. 
    X() { cerr << "X Ctor" << endl; throw bad_cast(); } // throw in Ctor 
    X(int) { cerr << "X Ctor int" << endl; }
    ~X() { cerr << "X Dtor" << endl; }
};

struct Y
{
    Y() { cerr << "Y Ctor" << endl; }
    ~Y() { cerr << "Y Dtor" << endl; }
};

class Ywrappers
{
public:
    Ywrappers()  { m_y = new Y; }
    ~Ywrappers() {delete m_y;}
    Y *m_y;
};

class L
{
public:
    L(): m_x(2) { cerr << "L Ctor" << endl; }
    ~L() { cerr << "L Dtor" << endl; }
private:
    Y m_y;
    X m_x;
};

class M // M cause exception trow (bad cast)
{
public:
    M() { cerr << "M Ctor" << endl; }
    ~M() { cerr << "M Dtor" << endl; }
private:
    X m_x;
    Y m_y;
};

class N // N cause exception trow (bad cast)
{
public:
    N() { cerr << "N Ctor" << endl; }
    ~N() { cerr << "N Dtor" << endl; }
private:
    Y m_y;
    X m_x;
};

class J // J allocate memory in initilization list and 
        // cause exception trow (bad cast) !!!!!
{
public:
    J(): m_y(), // allocate memory without delete.
         m_x(new X) 
     { cerr << "J Ctor" << endl; }
    Ywrappers GetY() { return m_y; }
    ~J() { cerr << "J Dtor" << endl; delete m_x;}
private:
    Ywrappers m_y;
    X *m_x;
};

class K // M cause exception trow (bad cast) after allocating memory in body Ctor
{
public:
    K() 
    { 
        cerr << "K Ctor" << endl;
        // m_y;
        m_x = new X; 
    }
    ~K() { cerr << "K Dtor" << endl; delete m_x; }
private:
    Ywrappers m_y;
    X *m_x;
};

int main()
{
    try
    {
        K var1;
    }
    catch(exception& e)
    {
        cerr << "Exception cout. what: " << e.what() << endl;
    }
    
    return 0;
}
