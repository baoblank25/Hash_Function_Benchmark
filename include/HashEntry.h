// ASU CSE310 Hash Table Assignment
// File: HashEntry.h
// Description: Hash table entry structure


#ifndef HASHENTRY_H
#define HASHENTRY_H


#include <string>
#include "HashTypes.h"


using namespace std;


struct HashEntry{
    string url;
    SlotStatus status;
    HashEntry();
};


#endif
