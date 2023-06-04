/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_shared_pointer.cpp
*	author: Moshe Cohen
*	reviewer: Dor Glaubach

--------------------------------------------------------------------------------
*******************************************************************************/
#include <iostream>
#include <cstring>
#include <cassert>


const char *RED_B = "\033[01;31m";
const char *GREEN_B = "\033[01;32m";
const char *YELLOW_B = "\033[01;33m";
const char *BLUE_B = "\033[01;34m";
const char *BLACK_B = "\033[01;30m";
const char *WHITE_B = "\033[01;37m";
const char *RED = "\033[0;31m";
const char *GREEN = "\033[0;32m";
const char *YELLOW = "\033[0;33m";
const char *RESET = "\033[0m";
void RunTest(bool result, const char *name)
{
    std::cout << YELLOW_B << "Test "  << name << ": " << RESET;
    if (result)
    {
        std::cout << GREEN_B << "SUCCESS" << RESET << std::endl;
    }
    else
    {
        std::cout << RED_B << "FAILURE" << RESET << std::endl;
    }
}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~includes~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


#include "shared_pointer.hpp"

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~definitions~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~functions~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void TestCtor();
void TestCCtor();
void TestAssignmentOperator();
void TestDereferanceOperator();
void TestArrowOperator();
void TestCCtorD();
void TestNewOpratorDisallowed();
void TestBadCast();
void TestNir();

using namespace ilrd;        
int main()
{
    std::cout << std::endl << BLACK_B << "Shared Pointer tests:" << RESET << std::endl;

    TestCtor();
    TestCCtor();
    TestAssignmentOperator();
    TestDereferanceOperator();
    TestArrowOperator();
    TestCCtorD();
    TestNewOpratorDisallowed();
    TestBadCast();
    TestNir();

    std::cout << std::endl << GREEN_B << "SUCCESS" << RESET << std::endl;

	return 0;
}

void TestCtor()
{
    SharedPtr <int>sh_ptr(new int(2));
    SharedPtr <float>sh_ptr2(new float(2.5));
}

void TestCCtor()
{
    SharedPtr <int>sh_ptr(new int(2));
    SharedPtr <int> sh_ptr2(sh_ptr);

}

void TestAssignmentOperator()
{
    SharedPtr <int>sh_ptr(new int(2));
    SharedPtr <int>sh_ptr2;

    sh_ptr2 = sh_ptr;
}

void TestDereferanceOperator()
{
    SharedPtr <int>sh_ptr(new int(2));
    SharedPtr <int>sh_ptr2;

    sh_ptr2 = sh_ptr;

    assert(2 == *sh_ptr);
    assert(2 == *sh_ptr2);
}

struct MyStruct 
{
    int a;
    int b;
    int c;
};

void TestArrowOperator()
{
    MyStruct *var = new MyStruct;
    var->a = 1;
    var->b = 2;
    var->c = 3;

    SharedPtr <MyStruct> sh_ptr(var);
    
    assert(1 == sh_ptr->a);
    assert(2 == sh_ptr->b);
    assert(3 == sh_ptr->c);
}

class Base
{
public:
    Base(int num): m_base(new int(num)){}
    virtual ~Base(){delete m_base;}
    virtual int GetNum() { return *m_base; }
private:
    int *m_base;
};

class Derived : public Base
{
public:
    Derived(int num) : Base(num),m_derived(num){};
private:
    int m_derived;
};

void TestCCtorD()
{
    SharedPtr<Derived>ptr1(new Derived(1));
    SharedPtr<Base>ptr4(new Base(1));
    SharedPtr<Base>ptr5(ptr1);
    // SharedPtr<Derived>

    assert(ptr5->GetNum() == 1);
}

void TestNewOpratorDisallowed()
{
    // SharedPtr<int> *ptr_undefined = new SharedPtr<int>;
}

void TestBadCast()
{
    // SharedPtr<int> ptr_int(new int(1));
    // SharedPtr<float> ptr_float(ptr_int);
}


class BaseN
{
public:
    virtual ~BaseN() {}
    virtual void Foo(){std::cout << "Base Foo" << std::endl; }
private:
    int m_a;
};

class DeriveN : public BaseN
{
public:
    virtual ~DeriveN(){}
    virtual void Foo(){std::cout << "Derive Foo" << std::endl; }
    virtual void Doo(){std::cout << "Derive Doo" << std::endl; }

};

class Fake : public BaseN
{
public:
    virtual ~Fake(){}
    virtual void Foo(){std::cout << "Fake Foo" << std::endl; }
};

// detect bad cast in compile time (between 2 brothers classes)
void TestNir()
{
//in main:
/* SharedPtr<DeriveN> derived3(new DeriveN); 
SharedPtr<Fake> fake1(derived3);

SharedPtr<Fake> fake(new Fake); 
SharedPtr<DeriveN> derived2(fake);
derived2->Foo();
// derived2->Doo(); //Error in run-time*/
}  