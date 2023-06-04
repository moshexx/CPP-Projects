#include <iostream> // std::cout
using namespace std;

class PublicTransport 
{
public:
    PublicTransport() : m_license_plate(++s_count)
    {
        cout << "PublicTransport::Ctor()" << m_license_plate << "\n";
    }

    virtual ~PublicTransport()
    {
        --s_count;
        cout << "PublicTransport::Dtor()" << m_license_plate << "\n";
    }

    PublicTransport(const PublicTransport &other) : m_license_plate(++s_count) // regular Ctor
    {
        cout << "PublicTransport::CCtor() " << m_license_plate << "\n";
    }

    virtual void display()
    {
        cout << "PublicTransport::display(): " << m_license_plate << "\n";
    }

    static void print_count()
    {
        cout << "s_count: " << s_count << "\n";
    }
protected:
    int get_ID()
    {
        return m_license_plate;
    }

private:
    static int s_count;
    int m_license_plate;
    PublicTransport &operator=(const PublicTransport &); // disabled
};

int PublicTransport::s_count = 0;

class Minibus: public PublicTransport 
{
public:
    Minibus() : m_numSeats(20)
    {
        cout << "Minibus::Ctor()\n";
    }

    Minibus(const Minibus &other) : PublicTransport(other),
                                    m_numSeats(other.m_numSeats)
    {
        cout << "Minibus::CCtor()\n";
    }

    ~Minibus()
    {
        cout << "Minibus::Dtor()\n";
    }

    void display()
    {
        cout << "Minibus::display() ID:" << get_ID();
        cout << " num seats:" << m_numSeats << "\n";
    }

    virtual void wash(int minutes)
    {
        cout << "Minibus::wash(" << minutes << ") ID:" << get_ID() << "\n";
    }

private:
    int m_numSeats;
};

class Taxi: public PublicTransport 
{
public:
    Taxi()
    {
        cout << "Taxi::Ctor()\n";
    }

    Taxi(const Taxi &other) : PublicTransport(other)
    {
        cout << "Taxi::Ctor()\n";
    }

    ~Taxi()
    {
        cout << "Taxi::Dtor()\n";
    }

    void display()
    {
        cout << "Taxi::display() ID:" << get_ID() << "\n";
    }

private:
};

template<class T>
inline T max_func(const T &t1, const T &t2)
{
    return ((t1 > t2) ? t1 : t2);
}

class SpecialTaxi: public Taxi 
{
public:
    SpecialTaxi()
    {
        cout << "SpecialTaxi::Ctor()\n";
    }

    SpecialTaxi(const SpecialTaxi& other) : Taxi(other)
    {
        cout << "SpecialTaxi::CCtor()\n";
    }

    ~SpecialTaxi()
    {
        cout << "SpecialTaxi::Dtor()\n";
    }

    void display()
    {
        cout << "SpecialTaxi::display() ID:" << get_ID() << "\n";
    }
};

class PublicConvoy: public PublicTransport 
{
public:
    PublicConvoy() : m_pt1(new Minibus()) 
    {
        try
        {
            m_pt2 = new Taxi();
        }
        catch(const std::bad_alloc& e)
        {
            delete m_pt1;
            std::cerr << e.what() << '\n';
        }
    }

    PublicConvoy(const PublicConvoy& other): PublicTransport(other),
                                             m_m(other.m_m), m_t(other.m_t),
                    m_pt1(new Minibus(*(dynamic_cast<Minibus*>(other.m_pt1))))
    {
        try
        {
            m_pt2 = new Taxi(*(dynamic_cast<Taxi*>(other.m_pt2)));
        }
        catch(const std::bad_alloc& e)
        {
            delete m_pt1;
            std::cerr << e.what() << '\n';
        }
          
    }

    ~PublicConvoy()
    {
        delete m_pt1;
        delete m_pt2;
    }

    void display()
    {
        m_pt1->display();
        m_pt2->display();
        m_m.display();
        m_t.display();
    }

private:
    PublicTransport *m_pt1;
    PublicTransport *m_pt2;
    Minibus m_m; // default Ctor()
    Taxi m_t;
};

void print_info(PublicTransport &a)
{
    a.display();
}

void print_info()
{
    PublicTransport::print_count();
}

void print_info(Minibus &m)
{
    m.wash(3);
}

/*const*/PublicTransport print_info(int i)  // unused int
{
    Minibus ret;
    cout << "print_info(int i)\n";
    ret.display();
    return ret; // CCtor
}

void taxi_display(Taxi s)
{
    s.display();
}

int main(int argc, char **argv, char **envp)
{
    Minibus m;

    print_info(m); // print wash with 3 and ID
    print_info(3).display(); // print ID + seats -> CCtor (return by value)-> ++ID: and send to display()

    /* PublicTransport *array[] = { new Minibus, new Taxi, new Minibus };
    for (int i = 0; i < 3; ++i) 
    {
        array[i]->display(); //Minibus.display(), Taxi.display();..
    }
    
    for (int i = 0; i < 3; ++i) 
    {
        delete array[i];
    }

    PublicTransport arr2[3]; // = { Minibus(), Taxi(), PublicTransport() }; // every element will be only the base class

    for (int i = 0; i < 3; ++i) 
    {
        arr2[i].display(); // each iteration will be PublicTransport.displey()
    }
    print_info(arr2[0]); // global PrintInfo

    PublicTransport::print_count(); // static class function
    Minibus m2;
    m2.print_count(); // more logic to write: PublicTransport::print_count();

    Minibus arr3[4];
    Taxi *arr4 = new Taxi[4]; // array in the heap
    delete[] arr4;

    std::cout << max_func(1, 2) << "\n";
    std::cout << max_func<int>(1, 2.0f)<< "\n";
    SpecialTaxi st;
    taxi_display(st); // global taxi_display expect to get Taxi and get SpecialTaxi

    std::cout << __LINE__ << endl;
    PublicConvoy *ts1 = new PublicConvoy();
    PublicConvoy *ts2 = new PublicConvoy(*ts1);
    ts1->display();
    ts2->display();
    delete ts1;
    ts2->display(); // this crashes. fix the bug!
    delete ts2;
 */
    return 0;
}

