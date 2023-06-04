#include <cstdio>

class X
{
    public:
        explicit X(int a_);
        void Foo();
        friend void Foo(const X &x_);

        const int &GetMA(void) const
        {
            return this->m_a;
        }
        int &SetMA(void) 
        {
            return this->m_a;
        }

    private:
        int m_a;
};

X::X(int a_):m_a(a_){}

void X::Foo()
{
    printf("%d \n", m_a);
}

void Foo(const X &x_)
{
    printf("%d \n", x_.m_a);
}

int main()
{
    X x1(1);

    x1.Foo();
    x1.SetMA() = 22;
   printf("%d \n", x1.GetMA());

    Foo(x1);
    return 0;

}