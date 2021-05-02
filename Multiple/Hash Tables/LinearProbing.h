#include "LinearProbing.cpp"
#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class tableItem
{
    public:
        unsigned long key;
        string value;

        tableItem(unsigned long newKey, string newValue)
        {
            this->key = newKey;
            this->value = newValue;
        }
};


class HashL
{
    private:
        // The Hash Table
        vector<shared_ptr<tableItem>> hashTable; 
        
        // Current size of the hash table
        long tableSize; 

        // Keeps a count of the number of entries in the table.
        long count;

        unsigned long hash(string value);
        void resizeTable();
    public:
        HashL(int size);
        ~HashL();
        void insertWord(string value);
        void deleteWord(string value); 
        shared_ptr<tableItem> lookupWord(string value);
};

#endif