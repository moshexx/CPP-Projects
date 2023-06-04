#include <iostream>
#include <fstream>

#include "complex.hpp"

using namespace ilrd;

void Benchmark()
{
    Complex num1(0, 0), num2(1, 1);
    size_t num_of_actions = 10000000;

    for (size_t i = 0; i < num_of_actions; ++i)
    {
        num1 + num2;
    }
    // Complex x(1);
    // Complex y(5);
    // Complex z(3);
    // x + y = z;
    // (x + y).GetReal();

    // for (size_t i = 0; i < num_of_actions; ++i)
    // {
    //     num1 += num2;
    // } 
}


int main()
{
	Benchmark();
	return 0;
}
