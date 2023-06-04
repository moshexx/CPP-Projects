
#include <iostream>        // std::cout, std::cerr
#include <typeinfo>       // std::bad_cast

using namespace std;

struct ipWrapper
{
	ipWrapper(int num)  { ip = new int(num); }
	~ipWrapper() { delete ip; }
	
	int *ip;
};

void Bar(ipWrapper &ipPtr){ cout << *ipPtr.ip << endl; }
void Fishi() {}
void Fifi() {}
void Dodo() {}

int main ()
{
	ipWrapper ipPtr(2);
	Bar(ipPtr);
	Fishi();
	Fifi();
	Dodo();
	
	return 0;
}