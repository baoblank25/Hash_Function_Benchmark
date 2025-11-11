// ASU CSE310 Hash Table Assignment
// File: Statistics.h

#ifndef STATISTICS_H
#define STATISTICS_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include "HashTypes.h"

using namespace std;

class Statistics {
private:
    int numComp;
    int maxComp;
    int numQueries;
    clock_t totalTime;
    
public:
    Statistics();
    void recordQuery(int comp, clock_t time);
    void reset();
    void display(int tableSize, int numElements, double loadFactor, HashType hashType);
    
    int getTotalComp() const;
    int getMaxComp() const;
    int getNumQueries() const;
};

#endif
