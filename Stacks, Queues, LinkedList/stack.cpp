#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{}
    
template <class T>
Stack<T>::Stack(Stack<T>& otherStack)
{
    LinkedList<T> tempList(otherStack.list);
    list = tempList;
}

template <class T>
Stack<T>::~Stack()
{}

template <class T>
void Stack<T>::push(T item)
{
    list.insertAtHead(item);
}

template <class T>
T Stack<T>::top()
{
    shared_ptr<ListItem<T>> tempHead = list.getHead();
    return tempHead->value;
}

template <class T>
T Stack<T>::pop()
{
    shared_ptr<ListItem<T>> returnHead = list.getHead();
    list.deleteHead();
    return returnHead->value;
}

template <class T>
int Stack<T>::length()
{
    return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
    if(list.getHead() == NULL)
    {
        return true;
    }
    return false;
}

#endif
