#include <iostream>
//ptr to class & "this" ptr

//every class have ptr named "this" which point to this class.
enum status_t {SUCCESS, FAILURE};

class Boy
{
    public:
    int age;
    // return reference to this class whith "this"
    Boy& SetEyeC(std::string eye_c)
    {
        this->eye_c = eye_c;
        //same as eye_c = eye_c;
        return *this;
    }
    std::string GetEyeC(void) const
    {
        return this->eye_c;
    }

    Boy& SetName(std::string name)
    {
        this->name = name;
        
        return *this;
    }
    std::string GetName(void) const
    {
        return this->name;
    }
    
    private:
    std::string name;
    std::string eye_c;
};

int main()
{
    Boy *yossi = new Boy();
 
    yossi->age = 28;

    yossi->SetEyeC("Blue");
    yossi->SetName("Yossi");
    std::cout << "color is: " << yossi->GetEyeC() << std::endl;
    std::cout << yossi->GetName() << std::endl;

    delete yossi;yossi = NULL;
    return SUCCESS;
}