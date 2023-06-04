#include <cstdlib>
#include <exception>
#include <stdexcept>   // for exception, runtime_error, out_of_range
#include <string>      // for string
#include <iostream>    // for cout, std::cerr


// class exception 
// {
// public:
//   exception() throw();
//   exception(const exception&) throw();
//   exception& operator=(const exception&) throw();
//   virtual ~exception() throw();
//   virtual const char* what() const throw(); // Get string identifying exception
// }

// class runtime_error : public exception 
// {
// public:
//   explicit runtime_error(const string& what_arg); // default Ctor
// };

using namespace std;

struct BadDog: public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog"): runtime_error(s_) {} // default Ctor
};

void Fifi()
{
    throw BadDog("bad pup");
    // throw runtime_error("bad boy");
    // throw 666;
    // int x = 2 / 0;
    cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    // X x1;
    Fifi();
    cerr << "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr << "Bar() after Foo()" << endl;
}

int main()
{
    try
    {
        Bar();
    }
    catch(bad_alloc&)
    {
        cerr << "Out of memory! exiting."; exit(2);
    }
    catch(BadDog& b)
    {
        cerr << "Bad dog exception: " << b.what(); //exit(3);
    }
    catch(exception& b)
    {
        cerr << "unknown exception: " << b.what();
        exit(4);
    }
    catch(int x)
    {
        cout << x << endl;
    }
    catch (...) 
    {
        std::cout << "Caught an unknown exception\n";
    }
    cout << endl << "LIDOR" << endl;
    return 0;
}
