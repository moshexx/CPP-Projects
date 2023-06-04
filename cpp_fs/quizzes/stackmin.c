#include <stddef.h>
#include <stdio.h>

typedef enum 
{
    SUCCESS = 0,
    FULL = 1,
    EMPTY = 2,
    ALLOCATION_FAILURE = 3
}status_t;

#define STACK_IS_EMPTY 777 /* for StackPeek */
#define SIZE 10            /* sizeof arr */

typedef struct
{
    size_t index;
    size_t total_elements;
    int arr[SIZE];
}stack_t;

/* ~~~~~~~~~~~~~~~~~~~~~~~~ Declerations ~~~~~~~~~~~~~~~~~~~~~~~~ */ 
status_t StackPush(stack_t *stack, int data);
status_t StackPop(stack_t *stack);
int StackPeek(stack_t *stack);
int StackGetMin(stack_t *stack);
static int GetMin(int *arr, size_t size);

/* ~~~~~~~~~~~~~~~~~~~~~~~~ main ~~~~~~~~~~~~~~~~~~~~~~~~ */ 
int main()
{
    stack_t stack;

    /* stack create */
    stack.index = 0;
    stack.total_elements = 10;    

    StackPush(&stack, 5);
    printf("Push 5: %d\n", StackPeek(&stack));
    StackPush(&stack, 2);
    printf("Push 2: %d\n", StackPeek(&stack));
    StackPush(&stack, 4);
    printf("Push 4: %d\n", StackPeek(&stack));
    printf("StackGetMin 2: %d\n",StackGetMin(&stack)); 

    printf("Pop\n");
    StackPop(&stack);

    StackPush(&stack, 1);
    printf("Push 1: %d\n", StackPeek(&stack));

    printf("StackGetMin 1: %d\n",StackGetMin(&stack)); 

    return 0;
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~ API functions ~~~~~~~~~~~~~~~~~~~~~~~~ */ 
status_t StackPush(stack_t *stack, int data)
{
    if (stack->index == stack->total_elements)
    {
        return FULL;
    }

    stack->arr[stack->index++] = data;

    return SUCCESS;
}

status_t StackPop(stack_t *stack)
{
    if (stack->index == 0)
    {
        return EMPTY;
    }

    --stack->index;
}

int StackPeek(stack_t *stack)
{
    if (stack->index == 0)
    {
        return STACK_IS_EMPTY; /* 777 */
    }

    return stack->arr[stack->index-1];
}

int StackGetMin(stack_t *stack)
{
    return GetMin(stack->arr, stack->index);
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~ Static functions ~~~~~~~~~~~~~~~~~~~~~~~~ */ 
static int GetMin(int *arr, size_t size)
{
    size_t i = 1;    
    int min = arr[0];

    /* O(n) */
    for (i = 1; i < size; ++i)
    {
        if (arr[i] < min)
        {
            min = arr[i];
        }
    }

    return min;
}