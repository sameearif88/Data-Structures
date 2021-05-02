#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

// Does some bitwise operations and generates a 64bit hash
unsigned long bitHash(string value)
{
	unsigned long bitwiseHash = 0;
    for(int i = 0; i < value.length(); ++i)
    {
        bitwiseHash ^= (bitwiseHash << 5) + (bitwiseHash >> 2) + value[i];
    }
    return bitwiseHash;
}

// tableSize is the size of array maintained by the hashtable
unsigned long divCompression(unsigned long hash, long tableSize)
{
	return hash%tableSize;
}

#endif