#ifndef CHAINING_CPP
#define CHAINING_CPP

#include "Chaining.h"
#include "HashFunction.cpp"


// Constructor
HashC::HashC(int size)
{
    tableSize = size;
    hashTable = shared_ptr<LinkedList<string>>(new LinkedList<string>[tableSize], default_delete<LinkedList<string>[]>());
}


// Destructor
HashC::~HashC()
{
    tableSize = 0;
    hashTable = NULL;
}


// Given a String, return its hash
unsigned long HashC::hash(string input)
{
	return divCompression(bitHash(input), tableSize);
}


// Takes a hash of 'word' and inserts it into hashTable accordingly
void HashC::insertWord(string word)
{
    //Insert
    unsigned long index = hash(word);
    LinkedList<string> list = hashTable.get()[index];
    if(list.getHead() == NULL)
    {
        list.insertAtHead(word);
    }
    else
    {
        list.insertAtTail(word);
    }
}


// Locates 'word' in the hash table and returns a pointer to it
shared_ptr<ListItem<string>> HashC::lookupWord(string word)
{
	unsigned long index = hash(word);
    LinkedList<string> list = hashTable.get()[index];
    shared_ptr<ListItem<string>> traverse = list.getHead();
    while(traverse != NULL)
    {
        if(traverse->value == word)
        {
            return traverse;
        }
        traverse = traverse->next;
    }
    return NULL;
}


// Deletes 'word' from the hash table
void HashC::deleteWord(string word)
{
	int index = hash(word);
    LinkedList<string> list = hashTable.get()[index];
    shared_ptr<ListItem<string>> traverse = list.getHead();
    while(traverse != NULL)
    {
        if(traverse->value == word)
        {
            if(traverse == list.getHead())
            {
                list.deleteHead();
                return;
            }
            else
            {
                traverse = traverse->prev;
                traverse = traverse->next->next;
                return;
            }
        }
        traverse = traverse->next;
    }
}


#endif