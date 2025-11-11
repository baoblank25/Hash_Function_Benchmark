// ASU CSE310 Hash Table Assignment
// File: HashFunctions.h

#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H

#include <string>
using namespace std;

class HashFunctions {
private:
    unsigned long k;  // Large odd number
    unsigned long a;  // Random value for universal hashing
    unsigned long b;  // Random value for universal hashing
    
public:
    HashFunctions();
    unsigned long bitwiseHash(const string& url, int size);
    unsigned long polynomialHash(const string& url, int size);
    unsigned long universalHash(const string& url, int size);
};

#endif
