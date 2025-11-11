// ASU CSE310 Hash Table Assignment
// File: HashEntry.h

#ifndef HASHENTRY_H
#define HASHENTRY_H

#include <string>
#include "HashTypes.h"
using namespace std;

class HashEntry {
public:
    string url;
    SlotStatus status;
    
    HashEntry();
};

#endif
