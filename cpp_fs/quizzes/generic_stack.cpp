#include <vector>                               //std::vector

template<typename T>
class Stack
{
public:
    Stack();
    Stack(const Stack&other);
    Stack& operator=(const Stack& other);
    //default ~Stack();

    void Push(const T data);
    bool Pop(T &_outparam);
    size_t Size() const;
    bool IsEmpty() const;
    
private:
    std::vector<T> m_stack;
    int m_top;
};

template<typename T>
Stack<T>::Stack():
m_stack(), m_top(-1)
{//empty
}

template<typename T>
Stack<T>::Stack(const Stack& other):
m_stack(other.m_stack), m_top(m_stack.m_top)
{//empty
}

template<typename T>
typename Stack<T>::Stack& Stack<T>::operator=(const Stack& other)
{
    m_stack = other.m_stack;
    m_top = other.m_top;

    return *this;
}

template<typename T>
void Stack<T>::Push(const T data)
{
    m_stack.push_back(data);
    ++m_top;
}

template<typename T>
bool Stack<T>::Pop(T &_outparam)
{
    if (IsEmpty())
    {
        return false;
    }
    
    _outparam = m_stack[m_top];
    --m_top;
    m_stack.pop_back();

    return true;
}

template<typename T>
size_t Stack<T>::Size() const
{
    return m_stack.size();
}

template<typename T>
bool Stack<T>::IsEmpty() const
{
    return m_stack.empty();
}

#include <iostream>
int main()
{
    Stack<int> myStack;

    if (true != myStack.IsEmpty())
    {
        std::cout << "IsEmpty() Fail" << std::endl;
    }

    if (0 != myStack.Size())
    {
        std::cout << "IsEmpty() Fail" << std::endl;
    }

    int data = 55;
    myStack.Push(data);
    data = 22;
    myStack.Push(data);
    data = 44;
    myStack.Push(data);
    data = 99;
    myStack.Push(data);
    data = 77;
    myStack.Push(data);

    myStack.Pop(data);
    if (77 != data)
    {
        std::cout << "Pop() Fail" << data << std::endl;
    }

    myStack.Pop(data);
    if (99 != data)
    {
        std::cout << "Pop() Fail" << data << std::endl;
    }

    if (false != myStack.IsEmpty())
    {
        std::cout << "IsEmpty() Fail" << std::endl;
    }

    if (3 != myStack.Size())
    {
        std::cout << "IsEmpty() Fail" << std::endl;
    }

    myStack.Pop(data);
    myStack.Pop(data);
    myStack.Pop(data);

    if (false != myStack.Pop(data))
    {
        std::cout << "Pop() while list is empty : Fail" << std::endl;

    }

    return 0;
}