/*******************************************************************************
--------------------------------------------------------------------------------
*	file name: test_factory.cpp
*	author: Moshe Cohen
*	reviewer:

--------------------------------------------------------------------------------
*******************************************************************************/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ includes ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#include <iostream>
#include <cstring>
#include <cassert>

#include "factory.hpp"

const char *RED_B = "\033[01;31m";
const char *GREEN_B = "\033[01;32m";
const char *YELLOW_B = "\033[01;33m";
const char *BLUE_B = "\033[01;34m";
const char *BLACK_B = "\033[01;30m";
const char *WHITE_B = "\033[01;37m";
const char *RED = "\033[0;31m";
const char *GREEN = "\033[0;32m";
const char *YELLOW = "\033[0;33m";
const char *RESET = "\033[0m";
void RunTest(bool result, const char *name)
{
    std::cout << YELLOW_B << "Test "  << name << ": " << RESET;
    if (result)
    {
        std::cout << GREEN_B << "SUCCESS" << RESET << std::endl;
    }
    else
    {
        std::cout << RED_B << "FAILURE" << RESET << std::endl;
    }
}

using namespace ilrd;


	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~ definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~ functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int BasicTest(void);

//******************************************************************************
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 
int main()
{
    BasicTest();

	return 0;
}


//******************************************************************************
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Classes ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
class Animal
{
public:
    Animal(std::string name = "animal"): m_name(name){ std::cout << "Animal" << std::endl; }
    virtual ~Animal() {}
    virtual std::string GetName(){return m_name;}
private:
    std::string m_name;
};

Animal *AnimalCreator(std::string name)
{
    return new Animal(name);
}

class Dog: public Animal
{
private:
    std::string m_name;
public:
    Dog(std::string name = "dog"): m_name(name){ std::cout << "Dog" << std::endl; }
    ~Dog() {}
    std::string GetName(){return m_name;}
};


Animal *DogCreator(std::string name)
{
    return new Dog(name);
}

class Cat: public Animal
{
private:
    std::string m_name;
public:
    Cat(std::string name = "Cat"): m_name(name){ std::cout << "Cat" << std::endl; }
    ~Cat() {}
    std::string GetName(){return m_name;}
};

Animal *CatCreator(std::string name)
{
    return new Cat(name);
}


//******************************************************************************
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Test Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int BasicTest(void)
{
    Factory<Animal *, int, std::string, Animal *(*)(std::string)> myFactory;

    myFactory.AddCreator(0, AnimalCreator);    
    myFactory.AddCreator(1, CatCreator);    
    // myFactory.AddCreator(2, CatCreator);    // bug
    myFactory.AddCreator(2, DogCreator);    

    Animal *myAnimal = myFactory.CreateObject(0, "Animal");
    Animal *myDog = myFactory.CreateObject(1, "Baby Dog");
    Animal *myCat = myFactory.CreateObject(2, "Katty");

    std::cout << "Animal:\t" << myAnimal->GetName() << std::endl;
    std::cout << "Dog:\t" << myDog->GetName() << std::endl;
    std::cout << "Cat:\t" << myCat->GetName() << std::endl;

    delete myAnimal;
    delete myDog;
    delete myCat;

    return true;
}
