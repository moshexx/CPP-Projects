/* vertion 2 */

#include <stdio.h>  /*  printf() */
#include <stdlib.h> /*  malloc, free */

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~ Data Types Definitions ~~~~~~~~~~~~~~~~~~~~~~~~ */
typedef const struct v_table vt_t;

typedef struct PublicTransport
{
    vt_t *vt;

    int m_license_plate;
}pt_t;
 
typedef struct Minibus
{
    pt_t base;
    int m_numSeats;
    
}minibus_t;

typedef struct Taxi
{
    pt_t base;
}taxi_t;

typedef struct SpecialTaxi
{
    taxi_t taxi;
}staxi_t;

typedef struct PublicConvoy
{
    pt_t base;
    pt_t *m_pt1;
    pt_t *m_pt2;
    minibus_t m_m;
    taxi_t m_t;
}convoy_t;

struct v_table
{
    void (*dtor)(void *);
    void (*display)(const void *);
    void (*wash)(const minibus_t *this, int minutes);
};

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Declerations ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
/* Global Functions */
void print_info(void);
void print_info_minibus(minibus_t *m);
void print_info_pt(pt_t *a);
const pt_t print_info_int(int i);
void taxi_display(taxi_t s);
void *new_arr(size_t nmemb, size_t size, void (*ctor)());
void delete_arr(void *this, void (*dtor)());
void *new(size_t size, void (*ctor)());
void delete(void *object, void (*dtor)());
/* Public Transport */
void PTDtor(pt_t *this); 
void PTDisplay(const pt_t *this);
void PTCtor(pt_t *this);
void PTCCtor(pt_t *this, const pt_t *rhs);
int get_ID(const pt_t *this);
void print_count(void);
/* Minibus */
void MiniDtor(minibus_t *this);
void MiniDisplay(const minibus_t *this); 
void MiniCtor(minibus_t *this);
void MiniCCitor(minibus_t *this, const minibus_t *rhs);
void Wash(const minibus_t *this, int minutes);  
/* Taxi */
void TaxiDisplay(const taxi_t *this);
void TaxiDtor(taxi_t *this);
void TaxiCtor(taxi_t *this);
void TaxiCCtor(taxi_t *this, const taxi_t *rhs);
/* Special Taxi */
void STaxiDisplay(const staxi_t *this);
void STaxiDtor(staxi_t *this);         
void STaxiCCtor(staxi_t *this, const staxi_t *rhs);
void STaxiCtor(staxi_t *this);
/* PublicConvoy */
void ConvoyDisplay(const convoy_t *this);
void ConvoyDtor(convoy_t *this);
void ConvoyCCtor(convoy_t *this, const convoy_t *rhs);
void ConvoyCtor(convoy_t *this);


/* ~~~~~~~~~~~~~~~~~~~~~~ Global Variables Definitions ~~~~~~~~~~~~~~~~~~~~~~ */
int g_count = 0;

vt_t pt_vt = {(void *)PTDtor, (void *)PTDisplay, NULL};
vt_t mini_vt = {(void *)MiniDtor, (void *)MiniDisplay, Wash};
vt_t taxi_vt = {(void *)TaxiDtor, (void *)TaxiDisplay, NULL};
vt_t staxi_vt = {(void *)STaxiDtor, (void *)STaxiDisplay, NULL};
vt_t convoy_vt = {(void *)ConvoyDtor, (void *)ConvoyDisplay, NULL};


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
int main()
{
    minibus_t m;
    MiniCtor(&m);

    print_info_minibus(&m);

    pt_t tmp = print_info_int(3);
    PTDisplay(&tmp);
    PTDtor(&tmp);

    pt_t *array[3];
    array[0] = new(sizeof(minibus_t), MiniCtor);
    array[1] = new(sizeof(taxi_t), TaxiCtor);
    array[2] = new(sizeof(minibus_t), MiniCtor);
    
    int i;
    for (i = 0; i < 3; ++i) 
    {
        array[i]->vt->display(array[i]);
    }
    for (i = 0; i < 3; ++i) 
    {
        delete(array[i], array[i]->vt->dtor);
    }

    pt_t arr2[3];
    for (i = 0; i < 3; ++i) 
    {
        PTCtor(&arr2[i]); 
    }
    for (i = 0; i < 3; ++i) 
    {
        PTDisplay(&arr2[i]); 
    }

    print_info_pt(&arr2[0]);

    print_count();
    minibus_t m2;
    MiniCtor(&m2);
    print_count();

    minibus_t arr3[4];
    for (i = 0; i < 4; ++i) 
    {
        MiniCtor(&arr3[i]); 
    }

    taxi_t *arr4 = new_arr(4, sizeof(taxi_t), TaxiCtor);
    delete_arr(arr4, TaxiDtor);
    
    printf("%d\n", MAX(1, 2));
    printf("%0.f\n", MAX(1, 2.0f));

    staxi_t st;
    STaxiCtor(&st);
    taxi_t tmp2;
    TaxiCCtor(&tmp2, &st.taxi);
    taxi_display(tmp2);
    TaxiDtor(&tmp2);
    
    convoy_t *ts1 = new(sizeof(convoy_t), ConvoyCtor);
    convoy_t *ts2 = (convoy_t *)malloc(sizeof(convoy_t));
    ConvoyCCtor(ts2, ts1);
    
    ts1->base.vt->display(ts1);
    ts2->base.vt->display(ts2);
    delete(ts1, ts1->base.vt->dtor);
    ts2->base.vt->display(ts2);
    ts2->base.vt->dtor(ts2); 
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
/******************************************************************************/

/* ~~~~~~~~~~~~~~~~~~~~~~ Functions Definitions ~~~~~~~~~~~~~~~~~~~~~~ */
/* Global Functions Definitions */
void print_info(void)
{
    print_count();
}

void print_info_minibus(minibus_t *m)
{
    m->base.vt->wash(m, 3);
}

void print_info_pt(pt_t *a)
{
    a->vt->display(a);
}

const pt_t print_info_int(int i)  
{
    minibus_t ret;
    MiniCtor(&ret);

    printf("print_info(int i)\n");
    ret.base.vt->display((const pt_t *)&ret);
    
    pt_t pt_to_return;
    PTCCtor(&pt_to_return, &ret.base);
    MiniDtor(&ret);
    
    (void)i;
    return pt_to_return; 
}

void taxi_display(taxi_t s)
{
    s.base.vt->display(&s);
}

/* Public Transport - vitrual functions */
void PTDtor(pt_t *this)
{
    --g_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void PTDisplay(const pt_t *this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}
/* Public Transport - non vitrual functions */
void PTCtor(pt_t *this)
{
    this->vt = &pt_vt;
    this->m_license_plate = ++g_count;
    printf("PublicTransport::Ctor()%d\n", g_count);
}

void PTCCtor(pt_t *this, const pt_t *rhs)
{
    this->vt = rhs->vt;
    ++g_count;
    this->m_license_plate = g_count;

    printf("PublicTransport::CCtor() %d\n", g_count);
}

int get_ID(const pt_t *this)
{
        return this->m_license_plate;
}

void print_count(void)
{
    printf("s_count: %d\n", g_count);
}

/* Minibus - virtual functions */
void MiniDtor(minibus_t *this)
{
    printf("Minibus::Dtor()\n");
    this->base.vt = &pt_vt;
    PTDtor(&this->base);
}

void MiniDisplay(const minibus_t *this)
{
    printf("Minibus::display() ID:%d num seats:%d\n",
            this->base.m_license_plate, this->m_numSeats);
}

void Wash(const minibus_t *this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n",
            minutes, this->base.m_license_plate);
}
/* Minibus - non virtual functions */
void MiniCtor(minibus_t *this)
{
    PTCtor(&this->base);

    this->base.vt = &mini_vt;
    this->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void MiniCCitor(minibus_t *this, const minibus_t *rhs)
{
    PTCCtor(&this->base, &rhs->base);
    this->base.vt = &mini_vt;
    this->m_numSeats = rhs->m_numSeats;
    printf("Minibus::CCtor()\n");
}

/* Taxi - virtual functions */
void TaxiDisplay(const taxi_t *this)
{
    printf("Taxi::display() ID:%d\n",
            this->base.m_license_plate);
}

void TaxiDtor(taxi_t *this)
{
    printf("Taxi::Dtor()\n");
    this->base.vt = &pt_vt;
    PTDtor(&this->base);
}
/* Taxi - non virtual functions */
void TaxiCtor(taxi_t *this)
{
    PTCtor(&this->base);
    this->base.vt = &taxi_vt;
    printf("Taxi::Ctor()\n");
}

void TaxiCCtor(taxi_t *this, const taxi_t *rhs)
{
    PTCCtor(&this->base, &rhs->base);
    this->base.vt = &taxi_vt;
    printf("Taxi::CCtor()\n");
}

/* Special Taxi - virtual functions */
void STaxiDisplay(const staxi_t *this)
{
   printf("SpecialTaxi::Display ID: %d\n",
            this->taxi.base.m_license_plate); 
}

void STaxiDtor(staxi_t *this)
{
    printf("SpecialTaxi::Dtor()\n");
    this->taxi.base.vt = &taxi_vt;
    TaxiDtor(&this->taxi);
}
/* Special Taxi  - non virtual functions */
void STaxiCtor(staxi_t *this)
{
    TaxiCtor(&this->taxi);
    this->taxi.base.vt = &staxi_vt;
    printf("SpecialTaxi::Ctor()\n");
}

void STaxiCCtor(staxi_t *this, const staxi_t *rhs)
{
    TaxiCCtor(&this->taxi, &rhs->taxi);
    this->taxi.base.vt = &staxi_vt;
    printf("SpecialTaxi::CCtor()\n");
}

/* Public Convoy - virtual functions */
void ConvoyDisplay(const convoy_t *this)
{
    this->m_pt1->vt->display(this->m_pt1);
    this->m_pt2->vt->display(this->m_pt2);

    MiniDisplay(&this->m_m);  
    TaxiDisplay(&this->m_t);  
}

void ConvoyDtor(convoy_t *this)
{
    this->m_pt1->vt->dtor(this->m_pt1);
    free(this->m_pt1);
    this->m_pt2->vt->dtor(this->m_pt2);
    free(this->m_pt2);

    TaxiDtor(&this->m_t);
    MiniDtor(&this->m_m);

    this->base.vt = &pt_vt;
    PTDtor(&this->base);
}
/* Public Convoy - non virtual functions */
void ConvoyCtor(convoy_t *this)
{
    PTCtor(&this->base);
    this->base.vt = &convoy_vt;

    this->m_pt1 = (pt_t *)malloc(sizeof(minibus_t));
    MiniCtor((minibus_t *)this->m_pt1);

    MiniCtor(&this->m_m);
    TaxiCtor(&this->m_t);

    this->m_pt2 = (pt_t *)malloc(sizeof(taxi_t));
    TaxiCtor((taxi_t *)this->m_pt2);
}

void ConvoyCCtor(convoy_t *this, const convoy_t *rhs)
{
    PTCCtor(&this->base, &rhs->base);
    this->base.vt = &convoy_vt;

    this->m_pt1 = (pt_t *)malloc(sizeof(minibus_t));
    MiniCCitor((minibus_t *)this->m_pt1, (minibus_t *)rhs->m_pt1);

    MiniCCitor(&this->m_m, &rhs->m_m);
    TaxiCCtor(&this->m_t, &rhs->m_t);

    this->m_pt2 = (pt_t *)malloc(sizeof(taxi_t));
    TaxiCCtor((taxi_t *)this->m_pt2, (taxi_t *)rhs->m_pt2);
}

typedef struct metadata 
{
    size_t num_of_elem;
    size_t elem_size;
}metadata_t;

void *new_arr(size_t num_of_elem, size_t elem_size, void (*ctor)())
{
    char *runner = NULL;
    metadata_t *data = malloc(sizeof(metadata_t) + num_of_elem * elem_size);

    if(NULL == data)
    {
        return NULL;
    }
    data->num_of_elem = num_of_elem;
    data->elem_size = elem_size;
    data += 1;
    runner = (char *)data; /* first elem */

    while(runner < (char *)data + num_of_elem * elem_size)
    {
        ctor(runner);
        runner += elem_size;
    }
    return data;
}

void delete_arr(void *this, void (*dtor)() )
{
    metadata_t *metadata = (metadata_t *)this - 1;
    size_t num_of_elem = metadata->num_of_elem;
    size_t elem_size = metadata->elem_size;
    char *runner = (char *)this + (num_of_elem - 1) * elem_size; /* last elem */

    while((char *)this <= runner)
    {
        dtor(runner);
        runner -= elem_size;
    }
    free(metadata);
}

void *new(size_t size, void (*ctor)())
{
    void *new_object = malloc(size);
    ctor(new_object);

    return new_object;
}

void delete(void *object, void (*dtor)())
{
    dtor(object);
    free(object);
}