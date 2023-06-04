// 9.2.2021
// Producer Consumer with FSA
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

typedef struct
{
    size_t size;
    size_t i_read;
    size_t i_write;
    int *buffer;
}buffer_t;

const size_t FSA_SIZE = 5;
sem_t g_full;
sem_t g_empty;
pthread_mutex_t g_mutex;
buffer_t *g_fsa;


static buffer_t *CreateBuffer(size_t size)
{
    buffer_t *buffer = (buffer_t*)operator new(sizeof(buffer_t) + size * sizeof(int));

    if(buffer == NULL)
    {
        return NULL;
    }
    buffer->i_write = 0;
    buffer->i_read = 0;
    buffer->size = size;
    buffer->buffer = (int *)(buffer + 1);

    return buffer;
}

class Producer 
{
public:
    Producer(int data_);
    ~Producer();
    static void Init();
private:
    pthread_t thread;
    int data;
};

//~~~~~~~ Producer ~~~~~~~~~~
void Producer::Init()
{
    g_fsa = CreateBuffer(FSA_SIZE);

    pthread_mutex_init(&g_mutex, NULL);
    sem_init(&g_full, 0, 0);
    sem_init(&g_empty, 0, g_fsa->size);
}

void *DoP(void *data)
{
    sem_wait(&g_empty);
    pthread_mutex_lock(&g_mutex);
    std::cout << "Produce: " << *(int *)data << std::endl;
    g_fsa->buffer[g_fsa->i_write] = *(int *)data;
    sem_post(&g_full);
    pthread_mutex_unlock(&g_mutex);

    ++g_fsa->i_write;
    if(g_fsa->i_write == g_fsa->size)
    {
        g_fsa->i_write = 0;  
    }

    return NULL;
}

Producer::Producer(int data_): data(data_) 
{
    pthread_create(&thread, NULL, DoP, &data);
}

Producer::~Producer()
{
    pthread_join(thread, NULL);
}

//~~~~~~~ Consumer ~~~~~~~~~~
class Consumer
{
public:
    Consumer();
    ~Consumer();
    int GetData();

private:
    pthread_t thread;
    int data;
};

void *DoC(void *data)
{
    sem_wait(&g_full);
    pthread_mutex_lock(&g_mutex);
    std::cout << "Consume: " << g_fsa->buffer[g_fsa->i_read] << std::endl;
    sem_post(&g_empty);
    pthread_mutex_unlock(&g_mutex);

    ++g_fsa->i_read;
    if(g_fsa->i_read == g_fsa->size)
    {
        g_fsa->i_read = 0;  
    }

    (void)data;
    return NULL;
}

Consumer::Consumer()
{
    pthread_create(&thread, NULL, DoC, NULL);
}

Consumer::~Consumer()
{
    pthread_join(thread, NULL);
}


int main()
{
    Producer::Init();
    Producer producer1(1);
    Producer producer2(2);
    Producer producer3(3);

    Consumer counsumer1;
    Consumer counsumer2;
    Consumer counsumer3;

    return 0;
}