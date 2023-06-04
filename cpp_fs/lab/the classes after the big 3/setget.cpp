#include <iostream>
//Set & Get member functions

enum status_t {SUCCESS, FAILURE};

class boy
{
public:
    std::string name;
    int age;
    void SetEyeC(std::string eye_c)
    {
        this->eye_c = eye_c;
    }
    std::string GetEyeC(void) const
    {
        return this->eye_c;
    }

private:
    std::string eye_c;
};

int main()
{
    boy yossi;
    yossi.name = "yossi";
    yossi.age = 28;

    std::cout << yossi.name << std::endl;

    yossi.SetEyeC("Blue");
    std::cout << "color is: " << yossi.GetEyeC() << std::endl;

    return SUCCESS;
}
