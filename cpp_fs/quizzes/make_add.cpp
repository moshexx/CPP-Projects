#include <iostream>

class Type
{
    public:
    Type(int add_): m_add(add_)
    { //empty
    }

    int operator()(int num)
    {
        return m_add + num;
    }

private:
    int m_add;
};

Type make_adder(int num)
{
    return Type(num);
}

int main()
{
    Type add_3 = make_adder(3);
    std::cout << add_3(5) << std::endl;
}