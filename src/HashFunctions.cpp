// ASU CSE310 Hash Table Assignment
// File: HashFunctions.cpp
// Description: Implementation of hash functions

#include "../include/HashFunctions.h"

HashFunctions::HashFunctions(){
    k = 1000003;  // Large odd prime
    a = 31415;    // Random value
    b = 27183;    // Random value
}

// Bitwise Hash using folding and mixing (similar to MurmurHash style)
// Uses bit-level operations for speed and good distribution
unsigned long HashFunctions::bitwiseHash(const string& url, int size){
    unsigned long hash = 0;
    
    // First pass: accumulate characters
    for(size_t i = 0; i < url.length(); i++){
        hash = hash * 31 + (unsigned char)url[i];
    }
    
    // Bitwise mixing for better distribution
    hash ^= hash >> 16;
    hash *= 0x7feb352d;
    hash ^= hash >> 15;
    hash *= 0x846ca68b;
    hash ^= hash >> 16;
    
    return hash % size;
}

// Polynomial Rolling Hash
// Formula: h(s) = (s[0]*a^(n-1) + s[1]*a^(n-2) + ... + s[n-1]) mod m
// Using a=31 (small prime) with Horner's rule for efficiency
unsigned long HashFunctions::polynomialHash(const string& url, int size){
    unsigned long hash = 0;
    const unsigned long prime = 31;  // Small prime base
    
    // Use Horner's rule: h = (h * a + c) mod m
    for(size_t i = 0; i < url.length(); i++){
        hash = (hash * prime + (unsigned char)url[i]) % size;
    }
    
    return hash;  // Already < size from loop
}

// Universal hash function as specified in assignment
// Formula: ha,b(x) = ((a * #(x) + b) mod k*Hsize) / k
unsigned long HashFunctions::universalHash(const string& url, int size){
    unsigned long kHsize = k*size;
    unsigned long hashValue = 0;
    
    // Compute #(x) using Horner's rule with base 256
    for(size_t i=0; i<url.length(); i++){
        hashValue = (hashValue*256+(unsigned char)url[i])%kHsize;
    }
    
    // Apply universal hash formula - result is already in [0, size-1]
    hashValue = ((a*hashValue+b)%kHsize)/k;
    return hashValue;
}
