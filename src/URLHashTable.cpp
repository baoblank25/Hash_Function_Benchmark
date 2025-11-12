// ASU CSE310 Hash Table Assignment
// File: URLHashTable.cpp
// Description: Implementation using open addressing with linear/quadratic probing

#include "../include/URLHashTable.h"
#include <iostream>

URLHashTable::URLHashTable(int tableSize){
    size = tableSize;
    numElements = 0;
    table.resize(size);
    current_hType = BITWISE_HASH;
    current_pType = LINEAR_PROBING;
}

URLHashTable::~URLHashTable(){}

void URLHashTable::setHashFunction(HashType hashType){
    current_hType = hashType;
}

void URLHashTable::setProbingMethod(ProbingMethod probingType){
    current_pType = probingType;
}

int URLHashTable::probe(unsigned long hash, int i){
    if(current_pType==LINEAR_PROBING){
        return (hash+i)%size;
    }
    else{
        return (hash+i*i)%size;
    }
}

bool URLHashTable::searchURL(const string& url){
    clock_t start = clock();
    int comp = 0;
    bool found = false;
    
    unsigned long hash;
    if(current_hType==BITWISE_HASH){
        hash = hashFunc.bitwiseHash(url, size);
    }
    else if(current_hType==POLYNOMIAL_HASH){
        hash = hashFunc.polynomialHash(url, size);
    }
    else{
        hash = hashFunc.universalHash(url, size);
    }
    
    int idx = hash;
    int i = 0;
    
    while(i<size){
        if(table[idx].status==EMPTY){
            break;
        }
        
        if(table[idx].status==OCCUPIED){
            comp++;  // Count URL string comparison
            if(table[idx].url==url){
                found = true;
                break;
            }
        }
        
        i++;
        idx = probe(hash, i);
    }
    
    clock_t end = clock();
    stats.recordQuery(comp, end-start);
    
    if(found){
        cout << "\n\"" << url << "\" is a HIT - found in the hash table." << endl;
    }
    else{
        cout << "\n\"" << url << "\" is NOT found in the hash table." << endl;
    }
    
    return found;
}

bool URLHashTable::insertURL(const string& url){
    clock_t start = clock();
    int comp = 0;
    
    unsigned long hash;
    if(current_hType==BITWISE_HASH){
        hash = hashFunc.bitwiseHash(url, size);
    }
    else if(current_hType==POLYNOMIAL_HASH){
        hash = hashFunc.polynomialHash(url, size);
    }
    else{
        hash = hashFunc.universalHash(url, size);
    }
    
    int idx = hash;
    int i = 0;
    int firstAvailable = -1;
    
    // Search for URL and track first available slot
    while(i<size){
        if(table[idx].status==EMPTY){
            // Found empty slot - URL doesn't exist
            if(firstAvailable == -1){
                firstAvailable = idx;
            }
            break;
        }
        
        if(table[idx].status==DELETED && firstAvailable == -1){
            // Remember first deleted slot for insertion
            firstAvailable = idx;
        }
        
        if(table[idx].status==OCCUPIED){
            comp++;  // Count URL string comparison
            if(table[idx].url==url){
                clock_t end = clock();
                stats.recordQuery(comp, end-start);
                cout << "\n\"" << url << "\" is a HIT - already exists in the hash table." << endl;
                return false;
            }
        }
        
        i++;
        idx = probe(hash, i);
    }
    
    // Insert URL at first available slot
    if(firstAvailable != -1){
        table[firstAvailable].url = url;
        table[firstAvailable].status = OCCUPIED;
        numElements++;
        
        clock_t end = clock();
        stats.recordQuery(comp, end-start);
        return true;
    }
    
    cout << "Error: Hash table is full!" << endl;
    clock_t end = clock();
    stats.recordQuery(comp, end-start);
    return false;
}

bool URLHashTable::deleteURL(const string& url){
    clock_t start = clock();
    int comp = 0;
    bool deleted = false;
    
    unsigned long hash;
    if(current_hType==BITWISE_HASH){
        hash = hashFunc.bitwiseHash(url, size);
    }
    else if(current_hType==POLYNOMIAL_HASH){
        hash = hashFunc.polynomialHash(url, size);
    }
    else{
        hash = hashFunc.universalHash(url, size);
    }
    
    int idx = hash;
    int i = 0;
    
    while(i<size){
        if(table[idx].status==EMPTY){
            break;
        }
        
        if(table[idx].status==OCCUPIED){
            comp++;  // Count URL string comparison
            if(table[idx].url==url){
                table[idx].status = DELETED;
                table[idx].url = "";
                numElements--;
                deleted = true;
                break;
            }
        }
        
        i++;
        idx = probe(hash, i);
    }
    
    clock_t end = clock();
    stats.recordQuery(comp, end-start);
    
    if(deleted){
        cout << "\"" << url << "\" is deleted from hash table." << endl;
    }
    else{
        cout << "\"" << url << "\" is NOT deleted from hash table." << endl;
    }
    
    return deleted;
}

void URLHashTable::displayTable(){
    cout << "\nHash Table Contents" << endl;
    for(int i=0; i<size; i++){
        cout << "Slot[" << i << "]: ";
        if(table[i].status==OCCUPIED){
            cout << table[i].url;
        }
        else if(table[i].status==DELETED){
            cout << "[DELETED]";
        }
        else{
            cout << "[EMPTY]";
        }
        cout << endl;
    }
}

void URLHashTable::displayStats(){
    cout << "HASH STATS" << endl;
    
    cout << "\nConfiguration:" << endl;
    cout << "Hash Function: ";
    if(current_hType==BITWISE_HASH){
        cout << "Bitwise Mixing Hash (MurmurHash-style)" << endl;
    }
    else if(current_hType==POLYNOMIAL_HASH){
        cout << "Polynomial Rolling Hash (DJB2-style)" << endl;
    }
    else{
        cout << "Universal Hashing" << endl;
    }
    
    cout << "Probing Method: ";
    if(current_pType==LINEAR_PROBING){
        cout << "Linear Probing" << endl;
    }
    else{
        cout << "Quadratic Probing" << endl;
    }
    
    stats.display(size, numElements, getLoadFactor(), current_hType);

}

void URLHashTable::resetStats(){
    stats.reset();
}

double URLHashTable::getLoadFactor(){
    return (double)numElements/size;
}

int URLHashTable::getSize(){
    return size;
}

int URLHashTable::getNumElements(){
    return numElements;
}
