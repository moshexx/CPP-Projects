#include <iostream>
using namespace std;

struct E 
{
  const char* message;
  E(const char* arg) : message(arg) { }
};

void my_unexpected() 
{
  cout << "Call to my_unexpected" << endl;
  throw E("Exception thrown from my_unexpected");
}

void f() throw(E) 
{
  cout << "In function f(), throw const char * object" << endl;
  throw("Exception, type const char*, thrown from f()"); // throw char * instead of E
														//  not in the throw list
}

int main()
{
//   set_unexpected(my_unexpected); // throw something whcich not alowed 
  try 
  {
    f();
  }
  catch (E& e) 
  {
    cout << "Exception in main(): " << e.message << endl;
  }
}