#include <iostream>


float Power(long int power)
{   

}

int main()
{
    std::cout << "Power:" << std::endl;
    std::cout << "1: " << Power(0) << std::endl;
    
    std::cout << "3: " << Power(1) << std::endl;
    std::cout << "9: " << Power(2) << std::endl;
    std::cout << "27: " << Power(3) << std::endl;

    std::cout << "0.33: " << Power(-1) << std::endl;
    std::cout << "0.11: " << Power(-2) << std::endl;
    std::cout << "0.03: " << Power(-3) << std::endl;

    return 0;
}