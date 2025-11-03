// ASU CSE310 Hash Table Assignment
// File: URLHashTable.h
// Description: Main hash table class with open addressing


#ifndef URLHASHTABLE_H
#define URLHASHTABLE_H


#include <vector>
#include <string>
#include "HashTypes.h"
#include "HashEntry.h"
#include "HashFunctions.h"
#include "Statistics.h"


using namespace std;


class URLHashTable{
private:
    vector<HashEntry> table;
    int size;
    int numElements;
    HashFunctions hashFunc;
    Statistics stats;
    HashType current_hType;
    ProbingMethod current_pType;
    int probe(unsigned long hash, int i);
    
public:
    URLHashTable(int tableSize);
    ~URLHashTable();
    void setHashFunction(HashType hashType);
    void setProbingMethod(ProbingMethod probingType);
    bool searchURL(const string& url);
    bool insertURL(const string& url);
    bool deleteURL(const string& url);
    void displayTable();
    void displayStats();
    void resetStats();
    double getLoadFactor();
    int getSize();
    int getNumElements();
};


#endif
