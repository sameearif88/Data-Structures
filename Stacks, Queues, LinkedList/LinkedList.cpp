#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include <memory>
#include "LinkedList.h"
using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    tail = NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
    shared_ptr<ListItem<T>> traverse = otherLinkedList.head;
    head = make_shared<ListItem<T>>(traverse->value);
    tail = head;
    traverse = traverse->next;
    while(traverse != NULL)
    {
        tail->next = make_shared<ListItem<T>>(traverse->value);
        tail->next->prev = tail;
        tail = tail->next;
        traverse = traverse->next;
    }
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{
    if(head == NULL)
    {
        head = make_shared<ListItem<T>>(item);
        tail = head;
    }
    else
    {
        shared_ptr<ListItem<T>> tempHead = make_shared<ListItem<T>>(item);
        tempHead->next = head;
        head->prev = tempHead;
        head = tempHead;
    }
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
    if(tail == NULL)
    {
        head = make_shared<ListItem<T>>(item);
        tail = head;
    }
    else
    {
        shared_ptr<ListItem<T>> tempTail = make_shared<ListItem<T>>(item);
        tempTail->prev = tail;
        tail->next = tempTail;
        tail = tempTail;
    }
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
    shared_ptr<ListItem<T>> traverse = head;
    while(traverse != NULL)
    {
        if(traverse->value == afterWhat)
        {
            shared_ptr<ListItem<T>> temp = make_shared<ListItem<T>>(toInsert);
            temp->next = traverse->next;
            temp->prev = traverse;
            traverse->next = temp;
            if(traverse == tail)
            {
                tail = temp;
            }
            break;
        }
        traverse = traverse->next;
    }
}


template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getHead()
{
    return head;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::getTail()
{
    return tail;
}

template <class T>
shared_ptr<ListItem<T>> LinkedList<T>::searchFor(T item)
{
    shared_ptr<ListItem<T>> traverse = head;
    while(traverse != NULL)
    {
        if(traverse->value == item)
        {
            return traverse;
        }
        traverse = traverse->next;
    }
    return NULL;
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    shared_ptr<ListItem<T>> traverse = head;
    while(traverse != NULL)
    {
        if(traverse->value == item)
        {
            if(traverse == head)
            {
                deleteHead();
            }
            else if(traverse == tail)
            {
                deleteTail();
            }
            else
            {
                traverse->prev->next = traverse->next;
                traverse->next->prev = traverse->prev;
            }
            break;
        }
        traverse = traverse->next;
    }
}

template <class T>
void LinkedList<T>::deleteHead()
{
    if(head != NULL)
    {
        if(head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            shared_ptr<ListItem<T>> tempHead = head->next;
            head = tempHead;
            head->prev = NULL;
        }
    }
}

template <class T>
void LinkedList<T>::deleteTail()
{
    if(tail != NULL)
    {
        if(tail == head)
        {
            tail = NULL;
            head = NULL;
        }
        else
        {
            shared_ptr<ListItem<T>> tempTail = tail->prev;
            tail = tempTail;
            tail->next = NULL;
        }
    }
}

template <class T>
int LinkedList<T>::length()
{
    int length = 0;
    shared_ptr<ListItem<T>> traverse = head;
    while(traverse != NULL)
    {
        length++;
        traverse = traverse->next;
    }
    return length;
}

#endif
