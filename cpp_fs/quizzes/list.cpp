// Implement Class List, that supports insert, remove & find methods
// Don't forget the likes

#include <iostream>

template <typename T>
class List
{
public:
    struct Node
    {
        Node *m_next;   
        T m_data;
    };
    
    List();
    ~List();
    void InsertBefore(const T value, Node *node);
    T Remove(Node *node);
    T Remove(const T value);
    Node *Find(const T value);

private:
    Node *m_head;

    List(const List& other) {}
    List& operator=(const List& other) {}
};

template <typename T>
List<T>::List(): m_head(new Node())
{
    m_head->next = NULL;
}

template <typename T>
List<T>::~List()
{
    for(Node *runner = m_head->next; runner != NULL; ++runner)
    {
        delete m_head;
        m_head = runner;
    }
}

template <typename T>
void List<T>::InsertBefore(const T value, Node *node)
{
    Node *newNode = new Node();
    
    newNode->m_data = node->m_data;
    node->m_data = value;
    
    newNode->next = node->next;
    node->next = newNode;
}

template <typename T>
T List<T>::Remove(Node *node)
{
    Node *tmp = node->next;
    
    node->mdata = node->m_next->m_data;
    node->next = node->m_next->m_next;

    delete tmp;
}

template <typename T>
T List<T>::Remove(const T value)
{
    Node *nodeToRemove = Find(value);
    Remove(nodeToRemove);
}

template <typename T>
typename List<T>::Node *List<T>::Find(const T value)
{
    for(Node *runner = m_head; runner != NULL; ++runner)
    {
        if (value == runner->data)
        {
            return runner;
        }
    }

    return NULL; // not found
}


int main()
{

    return 0;
}