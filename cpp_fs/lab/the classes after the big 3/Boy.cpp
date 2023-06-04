#include "Boy.h"


Boy::Boy(std::string _name, std::string _ID, int _age, std::string d_name, std::string d_color)
{
    name = _name;
    ID = _ID;
    age = _age;
    my_dog = new Dog(d_name, d_color);
}

Boy::Boy(const Boy& other)
{
    name = other.name;
    ID = other.ID;
    age = other.age;
    my_dog = new Dog(other.getDog());	/// Full and smart cop
}

Boy& Boy::operator=(const Boy& other)
{
    if (this == &other) /// Testing that we do not copy the same variable
    {
        return *this;
    }
    delete my_dog; /// Memory Release
    name = other.name;
    ID = other.ID;
    age = other.age;
    my_dog = new Dog(other.getDog());   /// Full and smart copy
}

Boy::~Boy()
{
    delete my_dog;
}

Boy& Boy::setName(std::string _name)
{
    name = _name;
    return *this;
}

std::string Boy::getName() const
{
    return name;
}

Dog& Boy::getDog() const
{
    return *my_dog;
}

void Boy::releseDog(){
    delete my_dog;
}












