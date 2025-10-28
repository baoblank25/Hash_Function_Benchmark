// ASU CSE310 Hash Table Assignment
// File: HashFunctions.h
// Description: Hash function declarations


#ifndef HASHFUNCTIONS_H
#define HASHFUNCTIONS_H


#include <string>


using namespace std;


class HashFunctions{
private:
    unsigned long a;
    unsigned long b;
    unsigned long k;
    
public:
    HashFunctions();
    unsigned long divisionHash(const string& url, int size);
    unsigned long universalHash(const string& url, int size);
};


#endif
