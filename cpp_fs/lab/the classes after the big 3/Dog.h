#ifndef DOG_H
#define DOG_H

#include <iostream>
#include "Boy.h"

class Dog{

    public:

        Dog(std::string _name, std::string _color);
        Dog& setName(std::string _name);
        std::string getName() const;
        Dog& setColor(std::string _color);
        std::string getColor() const;

    private:

        std::string name, color;
};



#endif // DOG_H
