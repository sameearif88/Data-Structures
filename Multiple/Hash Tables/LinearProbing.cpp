#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "LinearProbing.h"
#include "HashFunction.cpp"
#include <memory>

// Constructor
HashL::HashL(int size)
{
    count = 0;
    tableSize = size;
    hashTable.resize(tableSize, NULL);
}

// Destructor
HashL::~HashL()
{
    count = 0;
    tableSize = 0;
    hashTable.clear();
}

// Computes the key corresponding to the value.
unsigned long HashL::hash(string value)
{
	unsigned long index = divCompression(bitHash(value), tableSize);
    while(hashTable[index] != NULL)
    {
        index = (index + 1)%tableSize;
    }
    return index;
}

// Function to resize the hash table
void HashL::resizeTable()
{
    double loadFactor = double(count)/double(tableSize);
	if(loadFactor > 0.5)
    {
        tableSize *= 13;
        vector<shared_ptr<tableItem>> tempHashTable = hashTable;
        hashTable.clear();
        hashTable.resize(tableSize, NULL);
        for(unsigned long i = 0; i < tableSize/13; ++i)
        {
            if(tempHashTable[i] != NULL)
            {
                string indexValue = tempHashTable[i]->value;
                unsigned long index = hash(indexValue);
                hashTable[index] = tempHashTable[i];
                hashTable[index]->key = index;
            }
        }
    }
}

// Takes the hash of 'value' and insert it into the hash table
void HashL::insertWord(string value)
{
    resizeTable();
    unsigned long index = hash(value);
    hashTable[index] = make_shared<tableItem>(index, value);
    count++;
}

// Deletes 'value' from the hash table.
void HashL::deleteWord(string value)
{
	unsigned long index = divCompression(bitHash(value), tableSize);
    if(hashTable[index] && hashTable[index]->value == value)
    {
        hashTable[index]->key = hashTable[index]->key + 1;
    }
    else
    {
        unsigned long tempIndex = index;
        index++;
        while(tempIndex != index)
        {
            if(hashTable[index] && hashTable[index]->value == value)
            {
                hashTable[index]->key = hashTable[index]->key + 1;
                return;
            }
            index = (index + 1)%tableSize;
        }
    }
}

// Locates value in the hash table and returns a pointer to it
shared_ptr<tableItem> HashL::lookupWord(string value)
{
	unsigned long index = divCompression(bitHash(value), tableSize);
    if(hashTable[index] && hashTable[index]->value == value)
    {
        if(hashTable[index]->key != index)
        {
            return NULL;
        }
        return hashTable[index];
    }
    else
    {
        unsigned long tempIndex = index;
        index = (index + 1)%tableSize;
        while(tempIndex != index)
        {
            if(hashTable[index] && hashTable[index]->value == value)
            {
                if(hashTable[index]->key != index)
                {
                    return NULL;
                }
                return hashTable[index];
            }
            index = (index + 1)%tableSize;
        }
        return NULL;
    }
}

#endif
