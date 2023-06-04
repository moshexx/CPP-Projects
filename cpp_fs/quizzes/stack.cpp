// 28.1.2021
/* 
1. What does this class represent?
2. Rewrite this class:
   * Fix the bug
   *  Improve the code style
   * Improve the safety of using this class */

#include <iostream>     // std::cout

const int SIZE = 100;

class Stack
{
public:
    Stack(): top_index(0) {}
    int Push(int data);
    int Pop(int &_data);
    int Peak() { return elements[top_index - 1]; }
    int IsEmpty() { return (0 == top_index); }
    int Size() { return top_index; }
    int IsFull() { return ((SIZE - 1) == top_index); }
private:
    int elements[SIZE];
    int top_index;
};

inline int Stack::Push(int data)
{
    if (1 == IsFull())
    {
        return 1;
    }
    elements[top_index++] = data; 

    return 0;
}

inline int Stack::Pop(int &_data)
{
    if (1 == IsEmpty())
    {
        return 1;
    }
    _data = elements[--top_index];

    return 0;
}

int main() 
{
    Stack stack;

    stack.Push(1);
    stack.Push(2);
    stack.Push(3);
    stack.Push(4);
    int tmp;

    std::cout << "size(4)" << stack.Size() << std::endl;
    std::cout << "peak(4)" << stack.Peak() << std::endl;
    stack.Pop(tmp);
    std::cout << "pop(4)" << tmp << std::endl;
    stack.Pop(tmp);
    std::cout << "pop(3)" << tmp << std::endl;
    stack.Pop(tmp);
    std::cout << "pop(2)" << tmp << std::endl;
    std::cout << "IsEmpty(false)" << stack.IsEmpty() << std::endl;
    std::cout << "IsFull(false)" << stack.IsFull() << std::endl;
    stack.Pop(tmp);
    std::cout << "pop(1)" << tmp << std::endl;
    std::cout <<  "IsEmpty(true)" << stack.IsEmpty() << std::endl;
    
    return 0;
}
