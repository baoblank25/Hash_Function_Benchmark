// ASU CSE310 Hash Table Assignment
// File: Statistics.cpp
// Description: Implementation of statistics tracking per assignment requirements

#include "../include/Statistics.h"

Statistics::Statistics(){
    numComp = 0;
    maxComp = 0;
    numQueries = 0;
    totalTime = 0;
}

void Statistics::recordQuery(int comp, clock_t time){
    numComp += comp;
    numQueries++;
    totalTime += time;
    
    if(comp>maxComp){
        maxComp = comp;
    }
}

void Statistics::reset(){
    numComp = 0;
    maxComp = 0;
    numQueries = 0;
    totalTime = 0;
}

void Statistics::display(int tableSize, int numElements, double loadFactor, HashType hashType){
    cout << "\nHash Table Statistics:" << endl;
    cout << fixed << setprecision(4);
    cout << "Table Size: " << tableSize << endl;
    cout << "Number of Elements: " << numElements << endl;
    cout << "Load Factor: " << loadFactor << endl;
    
    if(numQueries>0){
        double avgComp = (double)numComp/numQueries;
        double avgTime = ((double)totalTime/CLOCKS_PER_SEC)/numQueries;
        
        cout << "\nPerformance Metrics (as required by assignment):" << endl;
        cout << "Average number of comparisons per query: " << avgComp << endl;
        cout << "Maximum number of comparisons by a single query: " << maxComp << endl;
        cout << fixed << setprecision(8);
        cout << "Average running time per query: " << avgTime << " seconds" << endl;
        
        cout << fixed << setprecision(2);
        cout << "\nTotal queries processed: " << numQueries << endl;
    }
    else{
        cout << "\nNo queries have been processed yet." << endl;
    }
}

int Statistics::getTotalComp() const{
    return numComp;
}

int Statistics::getMaxComp() const{
    return maxComp;
}

int Statistics::getNumQueries() const{
    return numQueries;
}
