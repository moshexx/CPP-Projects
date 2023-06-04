#include <iostream>
#include <string>
// constructors
// the default constructor is Boy(){};
// when we define constructor the default constructor is gone


class Boy
{
    public:
    //constructor:                              //define const member
    Boy(int age = 4, std::string _name = "moshe"):name(_name)
    {
        this->age = age;
    }
    const std::string name;

    Boy& SetAge(int age)
    {
        this->age = age;
        
        return *this;
    }
    int GetAge(void) const
    {
        return this->age;
    }
     Boy& SetEyeC(std::string eyes)
    {
        this->eyes = eyes;
        //same as eye_c = eye_c;
        return *this;
    }
    std::string GetEyeC(void) const
    {
        return this->eyes;
    }
    
    private:
    int age;
    std::string eyes;
    
};
int main()
{
    Boy ben(5, "Ben");
    Boy defaultBoy;

    std::cout << ben.GetAge() << std::endl;
    std::cout << defaultBoy.GetAge() << std::endl;

    defaultBoy.SetAge(12).SetEyeC("pink");
    std::cout << defaultBoy.GetAge() << std::endl;
    std::cout << defaultBoy.GetEyeC() << std::endl;

    return 0;
}