#include <stdio.h> /*  printf() */
#include <stdlib.h> /*  malloc, free */

/* ~~~~~~~~~~~~~~~~~~~~~~ Declerations ~~~~~~~~~~~~~~~~~~~~~~ */
typedef struct PublicTransport PublicTransport;
typedef struct Minibus Minibus;
typedef struct Taxi Taxi;
typedef struct SpecialTaxi SpecialTaxi;
typedef struct PublicConvoy PublicConvoy;

void PrintCount(void);
void Display(const PublicTransport *publicTransport);
PublicTransport PublicTransportCCtor(const PublicTransport rhs);
PublicTransport PublicTransportCreate();
void PublicTransportDestroy(PublicTransport publicTransport);
void Wash(const Minibus minibus, int minutes);
void MinibusDisplay(const Minibus *minibus);
void MinibusDestroy(Minibus minibus);
int get_ID(const PublicTransport publicTransport);
void TaxiDisplay(const Taxi *taxi);
Taxi TaxiCreate(void);
void TaxiDestroy(Taxi taxi);
void SpecialTaxiDisplay(const SpecialTaxi *specialTaxi);
SpecialTaxi SpecialTaxiCreate(void);
void SpecialTaxiDestroy(SpecialTaxi specialTaxi);
void PublicConvoyDisplay(const PublicConvoy *publicConvoy);
PublicConvoy PublicConvoyCreate(void);
void PublicConvoyDestroy(PublicConvoy publicConvoy);
int MinibusGetID(const Minibus minibus);
int TaxiGetID(const Taxi taxi);
int SpecialTaxiGetID(const SpecialTaxi specialTaxi);
/* int PublicConvoyGetID(const PublicConvoy publicConvoy); has 4 cars */
Minibus MinibusCopy(Minibus minibus);
Taxi TaxiCopy(Taxi taxi);
SpecialTaxi SpecialTaxiCopy(SpecialTaxi specialTaxi);
PublicConvoy PublicConvoyCopy(PublicConvoy publicConvoy);


int g_count = 0;

struct PublicTransport
{
    int m_license_plate;

    void (*PrintCount)(void);
    void (*display)(const PublicTransport *publicTransport);
    int (*get_ID)(const PublicTransport publicTransport);
    PublicTransport (*CCtor)(const PublicTransport rhs);
};

struct Minibus
{
    PublicTransport publicTransport;
    int m_numSeats;
    
    Minibus (*CCtor)(Minibus minibus);
    int (*get_ID)(const Minibus minibus);
    void (*display)(const Minibus *minibus);
    void (*wash)(const Minibus minibus, int minutes);
};

struct Taxi
{
    PublicTransport publicTransport;

    Taxi (*CCtor)(Taxi taxi);
    int (*get_ID)(const Taxi taxi);
    void (*display)(const Taxi *taxi);
};

struct SpecialTaxi
{
    Taxi taxi;

    SpecialTaxi (*CCtor)(SpecialTaxi specialTaxi);
    int (*get_ID)(const SpecialTaxi specialTaxi);
    void (*display)(const SpecialTaxi *specialTaxi);
};

struct PublicConvoy
{
    Minibus *m_pt1;
    Taxi *m_pt2;
    Minibus m_m;
    Taxi m_t;

    PublicConvoy (*CCtor)(PublicConvoy publicConvoy);
    void (*display)(const PublicConvoy *publicConvoy);
};

/* ~~~~~~~~~~~~~~~~~~~~~~ PublicTransport ~~~~~~~~~~~~~~~~~~~~~~ */
void PrintCount(void)
{
    printf("g_count is |%d|\n", g_count);
}

void Display(const PublicTransport *publicTransport)
{
    printf("PublicTransport::display(): %d\n", publicTransport->m_license_plate);
}

int get_ID(const PublicTransport publicTransport)
{
    return publicTransport.m_license_plate;
}

PublicTransport PublicTransportCCtor(const PublicTransport rhs)
{
    PublicTransport publicTransport;

    ++g_count;
    printf("PublicTransport::CCtor() %d\n", g_count);

    publicTransport.m_license_plate = g_count;
    publicTransport.PrintCount = PrintCount;
    publicTransport.display = Display;
    publicTransport.CCtor = PublicTransportCCtor;

    return publicTransport;
}

PublicTransport PublicTransportCreate()
{
    PublicTransport publicTransport;

    ++g_count;
    printf("PublicTransport::Ctor()%d\n", g_count);

    publicTransport.m_license_plate = g_count;
    publicTransport.PrintCount = PrintCount;
    publicTransport.display = Display;
    publicTransport.CCtor = PublicTransportCCtor;

    return publicTransport;
}

void PublicTransportDestroy(PublicTransport publicTransport)
{
    --g_count;
    printf("PublicTransport::Dtor()%d\n", publicTransport.m_license_plate);

}

/* ~~~~~~~~~~~~~~~~~~~~~~ Minibus ~~~~~~~~~~~~~~~~~~~~~~ */
void Wash(const Minibus minibus, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n",
            minutes, minibus.publicTransport.m_license_plate);
}

void MinibusDisplay(const Minibus *minibus)
{
    printf("Minibus::display() ID:%d num seats:%d\n",
            minibus->publicTransport.m_license_plate, minibus->m_numSeats);
}

int MinibusGetID(const Minibus minibus)
{
    return minibus.publicTransport.m_license_plate;
}

Minibus MinibusCopy(Minibus minibus)
{
    Minibus new_mb;

    new_mb.wash = Wash;
    new_mb.display = MinibusDisplay;
    new_mb.m_numSeats = 20;
    new_mb.publicTransport = PublicTransportCCtor(new_mb.publicTransport);
    printf("Minibus::CCtor()\n");

    (void)minibus;
    return new_mb;
}

Minibus MinibusCreate()
{
    Minibus minibus;

    minibus.publicTransport = PublicTransportCreate();
    printf("Minibus::Ctor()\n");

    minibus.m_numSeats = 20;
    minibus.wash = Wash;
    minibus.display = MinibusDisplay;

    return minibus;
}

void MinibusDestroy(Minibus minibus)
{
    printf("Minibus::Dtor()\n");
    PublicTransportDestroy(minibus.publicTransport);
}

/* ~~~~~~~~~~~~~~~~~~~~~~ Taxi ~~~~~~~~~~~~~~~~~~~~~~ */
void TaxiDisplay(const Taxi *taxi)
{
    printf("Taxi::Display ID: %d\n",
            taxi->publicTransport.m_license_plate);
}

int TaxiGetID(const Taxi taxi)
{
    return (taxi.publicTransport.m_license_plate);
}

Taxi TaxiCopy(Taxi taxi)
{
    Taxi new_taxi;

    new_taxi.display = TaxiDisplay;
    new_taxi.publicTransport = PublicTransportCCtor(new_taxi.publicTransport);
    printf("Taxi::CCtor()\n");

    (void)taxi;
    return new_taxi;
}

Taxi TaxiCreate(void)
{
    Taxi taxi;


    taxi.publicTransport = PublicTransportCreate();
    taxi.display = TaxiDisplay;
    printf("Taxi::Ctor()\n");

    return taxi;
}

void TaxiDestroy(Taxi taxi)
{
    printf("Taxi::Dtor()\n");

    PublicTransportDestroy(taxi.publicTransport);
}

/* ~~~~~~~~~~~~~~~~~~~~~~ SpecialTaxi ~~~~~~~~~~~~~~~~~~~~~~ */
void SpecialTaxiDisplay(const SpecialTaxi *specialTaxi)
{
    printf("SpecialTaxi::Display ID: %d\n",
            specialTaxi->taxi.publicTransport.m_license_plate);
}

int SpecialTaxiGetID(const SpecialTaxi specialTaxi)
{
    return (specialTaxi.taxi.publicTransport.m_license_plate);
}

SpecialTaxi SpecialTaxiCopy(SpecialTaxi specialTaxi)
{
    SpecialTaxi new_specialTaxi;

    new_specialTaxi.display = SpecialTaxiDisplay;
    new_specialTaxi.taxi = TaxiCopy(new_specialTaxi.taxi);
    printf("SpecialTaxi::CCtor()\n");

    (void)specialTaxi;
    return new_specialTaxi;
}



SpecialTaxi SpecialTaxiCreate(void)
{
    SpecialTaxi specialTaxi;

    printf("SpecialTaxi::Ctor()\n");

    specialTaxi.taxi = TaxiCreate();

    specialTaxi.display = SpecialTaxiDisplay;

    return specialTaxi;
}

void SpecialTaxiDestroy(SpecialTaxi specialTaxi)
{
    printf("SpecialTaxi::Dtor()\n");

    TaxiDestroy(specialTaxi.taxi);
}

/* ~~~~~~~~~~~~~~~~~~~~~~ PublicConvoy ~~~~~~~~~~~~~~~~~~~~~~ */
void PublicConvoyDisplay(const PublicConvoy *publicConvoy)
{
    publicConvoy->m_pt1->display(publicConvoy->m_pt1);
    publicConvoy->m_pt2->display(publicConvoy->m_pt2);

    publicConvoy->m_m.display(&publicConvoy->m_m);
    publicConvoy->m_t.display(&publicConvoy->m_t);
}

PublicConvoy PublicConvoyCopy(PublicConvoy publicConvoy)
{
    PublicConvoy new_Convoy;

    new_Convoy.display = PublicConvoyDisplay;
 
    printf("PublicConvoy::CCtor()\n");

    new_Convoy.m_pt1 = (Minibus *)malloc(sizeof(Minibus));
    if (NULL == new_Convoy.m_pt1)
    { return publicConvoy; } // TODO: BAD_CONVOY
    *new_Convoy.m_pt1 = MinibusCopy(new_Convoy.m_m);

    new_Convoy.m_pt2 = (Taxi *)malloc(sizeof(Taxi));
    if (NULL == new_Convoy.m_pt2)
    {
        free (new_Convoy.m_pt1) ; new_Convoy.m_pt1 = NULL;
        return publicConvoy; // TODO: BAD_CONVOY
    }
    *new_Convoy.m_pt2 = TaxiCopy(new_Convoy.m_t);

    new_Convoy.m_m = MinibusCopy(new_Convoy.m_m);
    new_Convoy.m_t = TaxiCopy(new_Convoy.m_t);

    (void)publicConvoy;
    return new_Convoy;
}


PublicConvoy PublicConvoyCreate(void)
{
    PublicConvoy publicConvoy;

    printf("PublicConvoy::Ctor()\n");

    publicConvoy.m_pt1 = (Minibus *)malloc(sizeof(Minibus));
    if (NULL == publicConvoy.m_pt1)
    { return publicConvoy; } // TODO: BAD_CONVOY
    *publicConvoy.m_pt1 = MinibusCreate();

    publicConvoy.m_pt2 = (Taxi *)malloc(sizeof(Taxi));
    if (NULL == publicConvoy.m_pt2)
    {
        free (publicConvoy.m_pt1) ; publicConvoy.m_pt1 = NULL;
        return publicConvoy; // TODO: BAD_CONVOY
    }
    *publicConvoy.m_pt2 = TaxiCreate();

    publicConvoy.m_m = MinibusCreate();
    publicConvoy.m_t = TaxiCreate();

    return publicConvoy;
}

void PublicConvoyDestroy(PublicConvoy publicConvoy)
{
    printf("PublicConvoy::Dtor()\n");

    free(publicConvoy.m_pt1); publicConvoy.m_pt1 = NULL;
    free(publicConvoy.m_pt2); publicConvoy.m_pt2 = NULL;
    MinibusDestroy(publicConvoy.m_m);
    TaxiDestroy(publicConvoy.m_t);
}

void PublicTransportprint_info(PublicTransport publicTransport)
{
    publicTransport.display(&publicTransport);
}

void Minibusprint_info(Minibus minibus)
{
    minibus.wash(minibus, 3);
    // minibus.publicTransport.Display(minibus.publicTransport);
}

void Taxiprint_info(Taxi taxi)
{
    taxi.publicTransport.display(&taxi.publicTransport);
}

void SpecialTaxiprint_info(SpecialTaxi specialTaxi)
{
    specialTaxi.taxi.publicTransport.display(&specialTaxi.taxi.publicTransport);
}

void PublicConvoyprint_info(PublicConvoy publicConvoy)
{
    publicConvoy.display(&publicConvoy);
}

void print_info()
{
    PrintCount();
}

const PublicTransport print_info_int(int i)  
{
    Minibus ret = MinibusCreate();

    printf("print_info(int i)\n");
    ret.display(&ret);
    
    PublicTransport publicTransportToReturn =
                                 PublicTransportCCtor(ret.publicTransport);
    MinibusDestroy(ret);
    
    (void)i;
    return publicTransportToReturn; 
}

void taxi_display(Taxi taxi)
{
    taxi.display(&taxi);
}

/* ~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~ */
int main ()
{
    Minibus minibus = MinibusCreate();

    Minibusprint_info(minibus);

    PublicTransport tmp = print_info_int(3);
    tmp.display(&tmp);
    PublicTransportDestroy(tmp);

    PublicTransport *array[3];
    array[0] = (PublicTransport *)(Minibus *)malloc(sizeof(Minibus));
    array[1] = (PublicTransport *)(Taxi *)malloc(sizeof(Taxi));
    array[2] = (PublicTransport *)(Minibus *)malloc(sizeof(Minibus));
    *(Minibus *)array[0] = MinibusCreate();
    *(Taxi *)array[1] = TaxiCreate();
    *(Minibus *)array[2] = MinibusCreate();

    /* first loop */
    ((Minibus *)array[0])->display((Minibus *)array[0]);
    ((Taxi *)array[1])->display((Taxi *)array[1]);
    ((Minibus *)array[2])->display((Minibus *)array[2]);

    MinibusDestroy(*(Minibus *)array[0]); free(array[0]);
    TaxiDestroy(*(Taxi *)array[1]);       free(array[1]);
    MinibusDestroy(*(Minibus *)array[2]); free(array[2]);
    
    PublicTransport arr2[3];
    int i;
    for (i = 0; i < 3; ++i) 
    {
        arr2[i] = PublicTransportCreate(); 
    }
    
    for (i = 0; i < 3; ++i) 
    {
        arr2[i].display; 
    }
    
    MinibusDestroy(minibus);

    return 0;
}
