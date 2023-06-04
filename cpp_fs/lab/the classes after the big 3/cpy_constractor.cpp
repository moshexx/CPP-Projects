#include <iostream>
// copy constructor:
// the default copy constructor, Boy ben(dudu), is ben = dudu (in all fields)
// when we define new one the default is gone
// when we have a memory alocation field - the default cpyconstructor is'nt good


// distructor function
// whem we delete the class the distractor function called.
// the default distructor is: ~Boy(){};


class Boy
{
    public:
    //constructor:                              //define const member
    Boy(int age = 4, std::string _name = "moshe"):name(_name)
    {
        this->age = age;
    }
    const std::string name;
    
    // default distructor ~Boy(){};

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
    Boy ben2(ben);
    Boy *boy_ptr = new Boy(22, "nir");

    std::cout << ben.GetAge() << std::endl;
    std::cout << ben2.GetAge() << std::endl;

    ben2.SetAge(12).SetEyeC("pink");
    std::cout << ben2.GetAge() << std::endl;
    std::cout << ben2.GetEyeC() << std::endl;

    delete boy_ptr; boy_ptr = NULL;
    return 0;
}