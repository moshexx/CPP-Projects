/* vertion 1 */

#include <stdio.h>  /*  printf() */
#include <stdlib.h> /*  malloc, free, sizeof, size_t */

#define MAX(type, x, y) (((type)(x) > (type)(y)) ? (type)(x) : (type)(y))

/* ~~~~~~~~~~~~~~~~~~~~~~ Data Types Definitions ~~~~~~~~~~~~~~~~~~~~ */
typedef struct PublicTransport PT_t;
typedef struct Minibus Minibus_t;
typedef struct Taxi Taxi_t;
typedef struct SpecialTaxi SpecialTaxi_t;
typedef struct PublicConvoy PublicConvoy_t;

enum virtual_functions { dtor, display, wash };
struct PublicTransport
{
    void (**vt)();

    int m_license_plate;
};

struct Minibus
{
    PT_t base;
    int m_numSeats;
    
};

struct Taxi
{
    PT_t base;
};

struct SpecialTaxi
{
    Taxi_t taxi;
};

struct PublicConvoy
{
    PT_t base;
    PT_t *m_pt1;
    PT_t *m_pt2;
    Minibus_t m_m;
    Taxi_t m_t;
};

/* ~~~~~~~~~~~~~~~~~~~~~~ Declerations ~~~~~~~~~~~~~~~~~~~~~~ */
/* Classic Global Functions (in the c++ file) */
void print_info(void);
void Minibusprint_info(Minibus_t minibus);
void PublicTransportprint_info(PT_t *publicTransport);
void taxi_display(Taxi_t taxi);
/* PublicTransport */
void PTDtor(PT_t *this);                   /* virtual */
void PTDisplay(const PT_t *this);            /* virtual */
int get_ID(const PT_t *this);
void PrintCount(void);
void PTCCtor(PT_t *this, const PT_t *rhs);
void PTCtor(PT_t *this);
/* Minibus */
void MiniDtor(Minibus_t *this);                         /* virtual */
void MiniDisplay(const Minibus_t *this);                /* virtual */
void Wash(const Minibus_t *this, int minutes);          /* virtual */
void MiniCCitor(Minibus_t *this, const Minibus_t *rhs);
void MiniCtor(Minibus_t *this);
/* Taxi */
void TaxiDisplay(const Taxi_t *this);                   /* virtual */
void TaxiDtor(Taxi_t *this);                            /* virtual */
void TaxiCCtor(Taxi_t *this, const Taxi_t *rhs);
void TaxiCtor(Taxi_t *this);
/* SpecialTaxi_t */
void STaxiDisplay(const SpecialTaxi_t *this);           /* virtual */
void STaxiDtor(SpecialTaxi_t *this);                    /* virtual */
void STaxiCCtor(SpecialTaxi_t *this, const SpecialTaxi_t *rhs);
void STaxiCtor(SpecialTaxi_t *this);
/* PublicConvoy_t */
void ConvoyDisplay(const PublicConvoy_t *this);         /* virtual */
void ConvoyDtor(PublicConvoy_t *this);                  /* virtual */
void ConvoyCCtor(PublicConvoy_t *this, const PublicConvoy_t *rhs);
void ConvoyCtor(PublicConvoy_t *this);

/* ~~~~~~~~~~~~~~~~~~~~~~ global definitions ~~~~~~~~~~~~~~~~~~~~~~ */
int g_count = 0;

void (*vt[])() = { PTDtor, PTDisplay };
void (*mini_vt[])() =  {MiniDtor, MiniDisplay, Wash };
void (*taxi_vt[])() = { TaxiDtor, TaxiDisplay };
void (*staxi_vt[])() = { STaxiDtor, STaxiDisplay };
void (*convoy_vt[])() = { ConvoyDtor, ConvoyDisplay };

/* ~~~~~~~~~~~~~~~~~~~~~~ global functions definitions ~~~~~~~~~~~~~~~~~~~~~~ */
void print_info(void)
{
    PrintCount();
}

void Minibusprint_info(Minibus_t minibus)
{
    Wash(&minibus, 3);
}

void PublicTransportprint_info(PT_t *publicTransport)
{
    publicTransport->vt[display](publicTransport);
}

const PT_t print_info_int(int i)  
{
    Minibus_t ret;
    MiniCtor(&ret);

    printf("print_info(int i)\n");
    ret.base.vt[display]((const PT_t *)&ret);
    
    PT_t publicTransportToReturn;
    PTCCtor(&publicTransportToReturn, &ret.base);
    MiniDtor(&ret);
    
    (void)i;
    return publicTransportToReturn; 
}

void taxi_display(Taxi_t taxi)
{
    TaxiDisplay(&taxi);
}

/* ~~~~~~~~~~~~~~~~~~~~~~ PublicTransport ~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~ virtual functions ~~~~~~~~~~~ */
void PTDtor(PT_t *this)
{
    --g_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void PTDisplay(const PT_t *this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

/* ~~~~~~~~~~~ global functions ~~~~~~~~~~~ */
int get_ID(const PT_t *this)
{
    return this->m_license_plate;
}

void PrintCount(void)
{
    printf("s_count: %d\n", g_count);
}

void PTCCtor(PT_t *this, const PT_t *rhs)
{
    ++g_count;
    printf("PublicTransport::CCtor() %d\n", g_count);

    this->m_license_plate = g_count;
    this->vt = vt;
}

void PTCtor(PT_t *this)
{
    PT_t publicTransport;

    ++g_count;
    printf("PublicTransport::Ctor()%d\n", g_count);

    this->m_license_plate = g_count;
    this->vt = vt;
}

/* ~~~~~~~~~~~~~~~~~~~~~~ Minibus ~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~ virtual functions ~~~~~~~~~~~ */
void MiniDtor(Minibus_t *this)
{
    printf("Minibus::Dtor()\n");
    this->base.vt = vt;
    this->base.vt[dtor](&this->base);
}

void MiniDisplay(const Minibus_t *this)
{
    printf("Minibus::display() ID:%d num seats:%d\n",
            this->base.m_license_plate, this->m_numSeats);
}

void Wash(const Minibus_t *this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n",
            minutes, this->base.m_license_plate);
}

/* ~~~~~~~~~~~ global functions ~~~~~~~~~~~ */

void MiniCCitor(Minibus_t *this, const Minibus_t *rhs)
{
    PTCCtor(&this->base, &rhs->base);
    this->m_numSeats = rhs->m_numSeats;
    this->base.vt = mini_vt;
    printf("Minibus::CCtor()\n");
}

void MiniCtor(Minibus_t *this)
{
    PTCtor(&(this->base));

    this->m_numSeats = 20;
    this->base.vt = mini_vt;

    printf("Minibus::Ctor()\n");
}

/* ~~~~~~~~~~~~~~~~~~~~~~ Taxi ~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~ virtual functions ~~~~~~~~~~~ */
void TaxiDisplay(const Taxi_t *this)
{
    printf("Taxi::display() ID:%d\n",
            this->base.m_license_plate);
}

void TaxiDtor(Taxi_t *this)
{
    printf("Taxi::Dtor()\n");
    this->base.vt = vt;
    this->base.vt[dtor](&this->base);
}

/* ~~~~~~~~~~~ global functions ~~~~~~~~~~~ */

void TaxiCCtor(Taxi_t *this, const Taxi_t *rhs)
{
    PTCCtor(&this->base, &rhs->base);
    this->base.vt = taxi_vt;

    printf("Taxi::CCtor()\n");
}

void TaxiCtor(Taxi_t *this)
{
    PTCtor(&this->base);
    this->base.vt = taxi_vt;
    printf("Taxi::Ctor()\n");
}

/* ~~~~~~~~~~~~~~~~~~~~~~ STaxi ~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~ virtual functions ~~~~~~~~~~~ */
void STaxiDisplay(const SpecialTaxi_t *this)
{
    printf("SpecialTaxi::Display ID: %d\n",
            this->taxi.base.m_license_plate);
} 

void STaxiDtor(SpecialTaxi_t *this) 
{
    printf("SpecialTaxi::Dtor()\n");
    this->taxi.base.vt = taxi_vt;
    this->taxi.base.vt[dtor](&this->taxi);
}

/* ~~~~~~~~~~~ global functions ~~~~~~~~~~~ */
void STaxiCCtor(SpecialTaxi_t *this, const SpecialTaxi_t *rhs)
{
    TaxiCCtor(&this->taxi, &rhs->taxi);

    this->taxi.base.vt = staxi_vt;
    printf("SpecialTaxi::CCtor()\n");
}

void STaxiCtor(SpecialTaxi_t *this)
{
    TaxiCtor(&this->taxi);
    this->taxi.base.vt = staxi_vt;
    printf("SpecialTaxi::Ctor()\n");
}

/* ~~~~~~~~~~~~~~~~~~~~~~ PublicConvoy ~~~~~~~~~~~~~~~~~~~~~~ */
/* ~~~~~~~~~~~ virtual functions ~~~~~~~~~~~ */
void ConvoyDisplay(const PublicConvoy_t *this)
{
    this->m_pt1->vt[display](this->m_pt1);
    this->m_pt2->vt[display](this->m_pt2);

    MiniDisplay(&this->m_m);  
    TaxiDisplay(&this->m_t);  
}

void ConvoyDtor(PublicConvoy_t *this)
{
    /* printf("PublicConvoy::Dtor()\n"); */

    this->m_pt1->vt[dtor](this->m_pt1);
    free(this->m_pt1); this->m_pt1 = NULL;
    this->m_pt2->vt[dtor](this->m_pt2);
    free(this->m_pt2); this->m_pt2 = NULL;
    TaxiDtor(&this->m_t);
    MiniDtor(&this->m_m);
    this->base.vt = vt;
    this->base.vt[dtor](&this->base);
}

/* ~~~~~~~~~~~ global functions ~~~~~~~~~~~ */
void ConvoyCCtor(PublicConvoy_t *this, const PublicConvoy_t *rhs)
{
    PTCCtor(&this->base, &rhs->base);
    this->base.vt = convoy_vt;
 
    /* printf("PublicConvoy::CCtor()\n"); */

    this->m_pt1 = (PT_t *)malloc(sizeof(Minibus_t));
    if (NULL == this->m_pt1)
    {
        return; /* BAD_CONVOY */
    }  
    MiniCCitor((Minibus_t *)this->m_pt1, (Minibus_t *)rhs->m_pt1);

    MiniCCitor(&this->m_m, &rhs->m_m);
    TaxiCCtor(&this->m_t, &rhs->m_t);

    this->m_pt2 = (PT_t *)malloc(sizeof(Taxi_t));
    if (NULL == this->m_pt2)
    {
        free (this->m_pt1) ; this->m_pt1 = NULL;
        return; /* BAD_CONVOY */
    }
    (TaxiCCtor((Taxi_t *)this->m_pt2, (Taxi_t *)rhs->m_pt2));
}

void ConvoyCtor(PublicConvoy_t *this)
{
    PTCtor(&this->base);
    this->base.vt = convoy_vt;
    /* printf("PublicConvoy::Ctor()\n"); */

    this->m_pt1 = (PT_t *)malloc(sizeof(Minibus_t));
    if (NULL == this->m_pt1)
    {
         return; /* BAD_CONVOY */
    }  
    MiniCtor((Minibus_t *)this->m_pt1);
    
    MiniCtor(&this->m_m);
    TaxiCtor(&this->m_t);

    this->m_pt2 = (PT_t *)malloc(sizeof(Taxi_t));
    if (NULL == this->m_pt2)
    {
        free (this->m_pt1) ; this->m_pt1 = NULL;
        return;  /* BAD_CONVOY */
    }
    TaxiCtor((Taxi_t *)this->m_pt2);
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
int main()
{
    Minibus_t m;
    MiniCtor(&m);

    Minibusprint_info(m);

    PT_t tmp = print_info_int(3);
    PTDisplay(&tmp);
    PTDtor(&tmp);

    PT_t *array[3];
    array[0] = (PT_t *)malloc(sizeof(Minibus_t));
    MiniCtor((Minibus_t *)array[0]);
    array[1] = (PT_t *)malloc(sizeof(Taxi_t));
    TaxiCtor((Taxi_t *)array[1]);
    array[2] = (PT_t *)malloc(sizeof(Minibus_t));
    MiniCtor((Minibus_t *)array[2]);

    /* first loop */
    int i;
    for (i = 0; i < 3; ++i) 
    {
        array[i]->vt[display](array[i]);
    }
    for (i = 0; i < 3; ++i) 
    {
        array[i]->vt[dtor](array[i]);
        free(array[i]); array[i] = NULL;
    }

    /* second loop */
    PT_t arr2[3];
    for (i = 0; i < 3; ++i) 
    {
        PTCtor(&arr2[i]); 
    }
    for (i = 0; i < 3; ++i) 
    {
        PTDisplay(&arr2[i]); 
    }

    PublicTransportprint_info(&arr2[0]);

    PrintCount();
    Minibus_t m2;
    MiniCtor(&m2);
    PrintCount();

    Minibus_t arr3[4];
    for (i = 0; i < 4; ++i) 
    {
        MiniCtor(&arr3[i]); 
    }

    Taxi_t *arr4 = (Taxi_t *)malloc(sizeof(Taxi_t) * 4);
    for (i = 0; i < 4; ++i) 
    {
        TaxiCtor(&arr4[i]);
    }
    for (i = 3; 0 <= i; --i) 
    {
        arr4[i].base.vt[dtor](&arr4[i]);
    }    
    free(arr4);
    
    printf("%d\n", MAX(int, 1, 2));
    printf("%d\n", MAX(int, 1, 2.0f));

    SpecialTaxi_t st;
    STaxiCtor(&st);
    Taxi_t tmp2;
    TaxiCCtor(&tmp2, &st.taxi);
    taxi_display(tmp2);
    TaxiDtor(&tmp2);

    PublicConvoy_t *ts1 = (PublicConvoy_t *)malloc(sizeof(PublicConvoy_t));
    ConvoyCtor(ts1);
    PublicConvoy_t *ts2 = (PublicConvoy_t *)malloc(sizeof(PublicConvoy_t));
    ConvoyCCtor(ts2, ts1);
    
    ts1->base.vt[display](ts1);
    ts2->base.vt[display](ts2);
    ts1->base.vt[dtor](ts1); 
    free(ts1); ts1 = NULL;
    ts2->base.vt[display](ts2);
    ts2->base.vt[dtor](ts2); 
    free(ts2); ts2 = NULL;

    STaxiDtor(&st);
    for (i = 3; 0 <= i; --i) 
    {
        MiniDtor(&arr3[i]); 
    }
    MiniDtor(&m2);
    for (i = 2; 0 <= i; --i) 
    {
        PTDtor(&arr2[i]); 
    }
    MiniDtor(&m);
    
    return 0;
}