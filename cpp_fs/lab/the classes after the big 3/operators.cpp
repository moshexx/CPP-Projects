#include <iostream>
// set operators functions


class Complex
{
    public:
    Complex(int num1, int num2)
    {
        real = num1;
        imag = num2;
    }
    Complex& operator=(const Complex& other)
    {
        real = other.real;
        imag = other.imag;
        return *this;
    }
    Complex& operator+(const Complex& other)
    {
        real += other.real;
        imag += other.imag;
        return *this;
    }
    void Print()const
    {
        std::cout << "The Complex number is: " << real << " + " << imag << "i" << std::endl; 
    }

    private:
    int real, imag;
};


int main()
{
    Complex num1(5, 12);
    Complex num2(3,7);
    Complex num3(13,17);
    num2.Print();
    num2 = num1; //assignment operator
    num2.Print();
    num2 + num3;
    num2.Print();
}