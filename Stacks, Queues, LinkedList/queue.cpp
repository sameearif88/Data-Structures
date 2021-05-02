#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{}
    
template <class T>
Queue<T>::Queue(Queue<T>& otherQueue)
{
    LinkedList<T> tempList(otherQueue.list);
    list = tempList;
}

template <class T>
Queue<T>::~Queue()
{}

template <class T>
void Queue<T>::enqueue(T item)
{
    list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
    shared_ptr<ListItem<T>> tempHead = list.getHead();
    return tempHead->value;
}

template <class T>
T Queue<T>::dequeue()
{
    shared_ptr<ListItem<T>> tempHead = list.getHead();
    list.deleteHead();
    return tempHead->value;
}

template <class T>
int Queue<T>::length()
{
    return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
    if(list.getHead() == NULL)
    {
        return true;
    }
    return false;
}


#endif
