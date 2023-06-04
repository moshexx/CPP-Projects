#include "Dog.h"

Dog::Dog(std::string _name, std::string _color)
{
    name = _name;
    color = _color;
}

Dog& Dog::setName(std::string _name)
{
    name = _name;
    return * this;
}

std::string Dog::getName() const
{
    return name;
}

Dog& Dog::setColor(std::string _color)
{
    color = _color;
    return *this;
}

std::string Dog::getColor() const
{
    return color;
}



















