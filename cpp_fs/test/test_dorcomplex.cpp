#include "complex.hpp"

using ilrd::Complex;

const char* RED = "\x1B[31m" ;
const char* GREEN = "\x1B[32m" ;
const char* YELLOW = "\x1B[33m" ;
const char* BLUE = "\x1B[34m" ;
const char* PURPLE = "\x1B[35m" ;
const char* LIGHT_BLUE = "\x1B[36m";
const char* RESET = "\033[0m";

void RunTest(bool result, const char* name)
{
    if(true == result)
    {
        std::cout << name << ": " << GREEN << "Success" << RESET << std::endl;
    }
    else
    {
        std::cout << name << ": " << RED <<"Failed" << RESET << std::endl;
    }
}


int TestOpPlus()
{
    size_t res = 0;

    Complex x(6,6);
    Complex x1(x);

    Complex y(4,4);
    Complex y1(8,8);

    res += x + x1 == y + y1;
 
    x += x1;
    y += Complex(1,5) + y;
    res += (x == Complex(12,12));
    res += (y == Complex(9,13));

    return res == 3;
}

int TestOpMinus()
{
    size_t res = 0;
    Complex x(10,10);
    Complex x1(5,0);

    Complex y(15,22);
    Complex y1(10,12);

    res += x - x1 == y- y1;;
    y -= y;
    res += y == Complex(0,0);

    return res == 2; 
}

int TestOpMultip()
{
    size_t res = 0;
    Complex x(2,2);
    Complex x1(x);
    Complex x2(0,8);

    Complex y(81,16);
    Complex y1(10,9);
    Complex y2(2,4);

    Complex y3(-2224,4442);

    res += x * x1 == x2;
    res += (y * y1 * y2)  == y3;
    y *= 0;
    res += y == 0;
    y1 *= y2;
    res += y1 == Complex(-16,58);

    return res == 4;
}

int TestOpDivision()
{
    size_t res = 0;
    Complex x(2,2);
    Complex x1(4,4);
    Complex x2(0.5,0);

    Complex y(2,6);
    Complex y1(4,4);
    Complex y2(8,4);

    Complex y3(2.125,2);

    res += x / x1 == x2;
    res  += y / y1 / y2 + x == y3;

    res += (y2 /= y1).GetReal() == 1.5;

    res += y2 == Complex(1.5,-0.5);


    return res == 4;
}



int TestGetAndSet()
{
    int res = 0;
    Complex r1i0;
    Complex r5i6(5.0,6.0);

        
    res += r1i0.GetImag() == 0 && r1i0.GetReal() == 1;
    res += r5i6.GetImag() == 6 && r5i6.GetReal() == 5;

    r1i0.SetImag(10);
    r5i6.SetImag(100);
    r5i6.SetReal(5.5);

    res += r1i0.GetImag() == 10 && r1i0.GetReal() == 1;
    res += r5i6.GetImag() == 100 && r5i6.GetReal() == 5.5;


    return res == 4;
}


int TestOpCompar()
{
    int res = 0;
    Complex x;
    Complex x1(1,0);
    Complex y(5,5);
    Complex y1(100,100);

    res += x == x1;
    res += y != y1;

    return res == 2;
}

int TestLast()
{



    
}



int main()
{

    RunTest(TestGetAndSet(),"TestGetAndSet");
    RunTest(TestOpCompar(),"TestOpCompar");
    RunTest(TestOpPlus(),"TestOpPlus");
    RunTest(TestOpMinus(),"TestOpMinus");
    RunTest(TestOpMultip(),"TestOpMultip");
    RunTest(TestOpDivision(),"TestOpDivision()");
    RunTest(TestLast(),"TestLast()");

}