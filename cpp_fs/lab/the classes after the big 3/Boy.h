#ifndef BOY_H
#define BOY_H

#include <iostream>
#include "Dog.h"

class Boy{

    public:

        Boy(std::string _name, std::string _ID, int _age, std::string d_name, std::string d_color);
        Boy(const Boy& other);
        Boy& operator=(const Boy& other);
        ~Boy();
        Boy& setName(std::string _name);
        std::string getName() const;
        Dog& getDog() const;
        void releseDog();

    private:
        std::string name, ID;
        int age;
        Dog* my_dog;
};

#endif // BOY_H
