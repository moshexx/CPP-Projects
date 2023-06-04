#include <iostream>
#include <cmath>

int main()
{
    double x = 1.0 / 10.0;
    double y = x * 10.0;

    if (y != 1.0)
    {
        std::cout << "surprise: " << y << " != 1" << std::endl;
    }

    double delta = 0.001;
    if (y - 1.0 > delta)
    {
        std::cout << "surprise: " << y << " != 1" << std::endl;
    }

    return 0;
} 