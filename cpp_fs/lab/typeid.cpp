// Ex.16

#include <iostream>
#include <typeinfo>

template <class T>

void foo(T t)
{
    std::cout << t << "Generic foo for " << typeid(t).name() << std::endl;
}

template <>
void foo(int t)
{
    std::cout << t << "Specialized foo (for int ) " << std::endl;
}

int main()
{
    foo(4.2);
    foo(5);
    foo<int>(5); //<int> is define the typename as int
    
    return 0;
}