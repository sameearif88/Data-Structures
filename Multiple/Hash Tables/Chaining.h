#include "Chaining.cpp"

#ifndef CHAINING__H
#define CHAINING__H

#include <string>
#include "LinkedList.cpp"
using namespace std;


class HashC
{
	private:
		//The size of the Hash Table
		long tableSize;

		shared_ptr<LinkedList<string>> hashTable;
		unsigned long hash(string input);
	public:
		HashC(int size); 
		~HashC();
		void insertWord(string word);
		void deleteWord(string word);
		shared_ptr<ListItem<string>> lookupWord(string word); 
};

#endif