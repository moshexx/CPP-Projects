
#include <iostream>        // std::cout, std::cerr

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
void BarB(int *ip) { cout << *ip << endl; }
void OptionB()
{
    int *ip = new int(2);

    try
    {
        BarB(ip);
        Fishi();
        Fifi();
        Dodo(); 
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    delete ip;
    
}


int main ()
{
	ipWrapper ipPtr(2);
	Bar(ipPtr);
	Fishi();
	Fifi();
	Dodo();

    OptionB();
	
	return 0;
}