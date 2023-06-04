//specific func:
// using std::count;
//
//all the namespace
//using namespace std;
#include <iostream>

namespace useless
{
    unsigned int g_wasteful[400];
    extern int g_notthere;
    void Foo() { std::cout << "useless Foo\n";}

    namespace wasteoftyme
    {
        void Foo() { std::cout << "useless::wasteoftyme:: Foo\n";}
    } //namespace wasteoftyme
} //namespace useless

// to use Foo ==>   using namespace useless::wasteoftyme;

namespace stupid
{
    void Foo() { std::cout << "stupid Foo\n";}
    void Bar() { std::cout << "stupid Bar\n";}
    void DoNothing(unsigned int) {}
}//namespace stupid

namespace useless
{
    void DoNothing(int) {}
} //namespace useless


using namespace useless;
void DoStuff()
{
    std::cout << "in DoStuff\n";
    Foo();      //useless::Foo();
    using stupid::Foo;
    stupid::Bar();
    Foo();      //stupid::Foo();
    DoNothing(g_wasteful[3] + 1);
}

void Foo() { std::cout << "Main Foo\n";}

using namespace stupid;

namespace comeon = useless::wasteoftyme;    //comeon = wasteoftyme

void DoMoreStuff()
{
    comeon::Foo();
    useless::wasteoftyme::Foo();
    Bar();
    DoNothing(g_wasteful[3] + 1);
}

namespace uselessage
{
    void DoUselessStuff()
    {
        DoNothing(g_wasteful[3] + 1);
    }
}
//TODO

//FIXME:
/* TODO: */


using namespace stupid;
int main()
{
    unsigned int dor = 9;
    int roy = 7;
    float moshe = 5;

    Bar();
    stupid::Foo();
    ::Foo();
    DoStuff();
    DoNothing(dor);
    stupid::DoNothing(roy);
    // DoNothing(moshe);
    DoMoreStuff();
    
}