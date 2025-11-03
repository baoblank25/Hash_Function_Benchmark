// ASU CSE310 Hash Table Assignment
// File: HashTypes.h
// Description: Type definitions and enumerations


#ifndef HASHTYPES_H
#define HASHTYPES_H


// Status of each hash table slot
enum SlotStatus{
    EMPTY,
    OCCUPIED,
    DELETED
};


// Probing methods
enum ProbingMethod{
    LINEAR_PROBING,
    QUADRATIC_PROBING
};


// Hash function types
enum HashType{
    DIVISION_HASH,
    UNIVERSAL_HASH
};


#endif
