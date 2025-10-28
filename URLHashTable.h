
#ifndef URLHASHTABLE_H
#define URLHASHTABLE_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

// Status of each hash table slot
enum SlotStatus{
    EMPTY,
    OCCUPIED,
    DELETED
};

// Hash table entry
struct HashEntry{
    string url;
    SlotStatus status;
    HashEntry() : url(""), status(EMPTY){}
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

class URLHashTable{
private:
    vector<HashEntry> table;
    int size;
    int numElements;
    int numComp;      
    int maxComp;     
    int numQueries;         
    clock_t totalTime;    
    
    //Universal hashing variables
    unsigned long a;
    unsigned long b;
    unsigned long k;
    
    // Current hash function and probing method
    HashType current_hType;
    ProbingMethod current_pType;
    
    //Code for hashDivision
    unsigned long hashDivision(const string& url){
        unsigned long hash = 0;
        
        for (size_t i=0; i<url.length(); i++){
            hash = (hash*31+(unsigned char)url[i])%size;
        }
        
        return hash%size;
    }
    
    unsigned long hashUniversal(const string& url){
        unsigned long kHsize = k*size;
        
        //using Horner's rule with base 256
        unsigned long hashValue = 0;
        
        for (size_t i = 0; i < url.length(); i++){
            hashValue = (hashValue*256 +(unsigned char)url[i])%kHsize;
        }
        
        // Apply universal hash formula
        hashValue = ((a*hashValue+b)%kHsize)/k;
        
        return hashValue%size;
    }
    
public:
    // Constructor
    URLHashTable(int tableSize){
        size = tableSize;
        numElements = 0;
        numComp = 0;
        maxComp = 0;
        numQueries = 0;
        totalTime = 0;
        
        table.resize(size);
        
        //Universal hashing parameters
        k = 1000003;  // Large odd prime
        a = 31415;    // Random value < k*size
        b = 27183;    // Random value < k*size
        
        // Default to division hash with linear probing
        current_hType = DIVISION_HASH;
        current_pType = LINEAR_PROBING;
    }
    
    //Destructor
    ~URLHashTable(){
    }
    
    // Set hash function type
    void setHashFunction(HashType hashType){
        current_hType = hashType;
    }
    
    // Set probing method
    void setProbingMethod(ProbingMethod probingType){
        current_pType = probingType;
    }
    
    // Search for URL in hash table
    bool searchURL(const string& url){
        clock_t start = clock();
        int comp = 0;
        bool found = false;
        
        // Compute initial hash
        unsigned long hash;
        if (current_hType==DIVISION_HASH){
            hash = hashDivision(url);
        } 
        else{
            hash = hashUniversal(url);
        }
        
        int idx = hash;
        int i = 0;
        
        //Probe until we find the URL, find an empty slot, or check entire table
        while (i<size){
            comp++;
            
            if (table[idx].status==EMPTY){
                break;
            }
            
            if (table[idx].status==OCCUPIED){
                if (table[idx].url==url){
                    found = true;
                    break;
                }
            }
            
            //Compute next probe position
            i++;
            if (current_pType==LINEAR_PROBING){
                idx = (hash + i) % size;
            } 
            else{
                idx = (hash + i * i) % size;
            }
        }
        
        clock_t end = clock();
        totalTime += (end-start);
        numComp += comp;
        numQueries++;
        
        if (comp>maxComp){
            maxComp = comp;
        }
        
        //Display result
        if (found){
            cout << "\n\"" << url << "\" is found in the hash table." << endl;
        } 
        else{
            cout << "\n\"" << url << "\" is NOT found in the hash table." << endl;
        }
        
        return found;
    }
    
    //Insert URLs
    bool insertURL(const string& url){
        clock_t start = clock();
        int comp = 0;
        
        unsigned long hash;
        if (current_hType==DIVISION_HASH){
            hash = hashDivision(url);
        } 
        else{
            hash = hashUniversal(url);
        }
        
        int idx = hash;
        int i = 0;
        
        //URL check if exists
        while (i < size){
            comp++;
            
            if (table[idx].status==EMPTY){
                break;
            }
            
            if (table[idx].status==OCCUPIED && table[idx].url==url){
                // URL already exists - this is a "hit"
                clock_t end = clock();
                totalTime += (end-start);
                numComp += comp;
                numQueries++;
                
                if (comp>maxComp){
                    maxComp = comp;
                }
                
                cout << "\n\"" << url << "\" is a HIT - already exists in the hash table." << endl;
                return false;
            }
            
            i++;
            if (current_pType==LINEAR_PROBING){
                idx = (hash+i)%size;
            } 
            else{
                idx = (hash+i*i)%size;
            }
        }
        
        //If it doesnt exist, insert
        idx = hash;
        i = 0;
        
        //Find avaiable spot
        while (i<size){
            if (table[idx].status==EMPTY || table[idx].status==DELETED){
                table[idx].url = url;
                table[idx].status = OCCUPIED;
                numElements++;
                
                clock_t end = clock();
                totalTime += (end-start);
                numComp += comp;
                numQueries++;
                
                if (comp>maxComp){
                    maxComp = comp;
                }
                
                return true;
            }
            
            i++;
            if (current_pType==LINEAR_PROBING){
                idx = (hash+i)%size;
            } 
            else{
                idx = (hash+i*i)%size;
            }
        }
        
        cout << "Error: Hash table is full!" << endl;
        return false;
    }
    
    //Delete URLs
    bool deleteURL(const string& url){
        clock_t start = clock();
        int comp = 0;
        bool deleted = false;
        
        unsigned long hash;
        if (current_hType==DIVISION_HASH){
            hash = hashDivision(url);
        } 
        else{
            hash = hashUniversal(url);
        }
        
        int idx = hash;
        int i = 0;
        
        while (i<size){
            comp++;
            
            if (table[idx].status==EMPTY){
                break;
            }
            
            if (table[idx].status==OCCUPIED && table[idx].url==url){
                table[idx].status = DELETED;
                table[idx].url = "";
                numElements--;
                deleted = true;
                break;
            }
            
            i++;
            if (current_pType==LINEAR_PROBING){
                idx = (hash+i)%size;
            } 
            else{
                idx = (hash+i*i)%size;
            }
        }
        
        clock_t end = clock();
        totalTime += (end-start);
        numComp += comp;
        numQueries++;
        
        if (comp>maxComp){
            maxComp = comp;
        }
        
        if (deleted){
            cout << "\"" << url << "\" is deleted from hash table." << endl;
        } 
        else{
            cout << "\"" << url << "\" is NOT deleted from hash table." << endl;
        }
        
        return deleted;
    }
    
    // Display entire hash table
    void displayTable(){
        cout << "\nHash Table Contents" << endl;
        for (int i=0; i<size; i++){
            cout << "Slot[" << i << "]: ";
            if (table[i].status==OCCUPIED){
                cout << table[i].url;
            } 
            else if (table[i].status==DELETED){
                cout << "[DELETED]";
            } 
            else{
                cout << "[EMPTY]";
            }
            cout << endl;
        }
    }
    
    // Display stats
    void displayStats(){
        cout << "\nHash Table Stats" << endl;
        cout << "Hash Function: ";
        if (current_hType == DIVISION_HASH){
            cout << "Division Hashing" << endl;
        } 
        else{
            cout << "Universal Hashing" << endl;
        }
        
        cout << "Probing Method: ";
        if (current_pType==LINEAR_PROBING){
            cout << "Linear Probing" << endl;
        } 
        else{
            cout << "Quadratic Probing" << endl;
        }
        
        cout << fixed << setprecision(4);
        cout << "Table Size: " << size << endl;
        cout << "Number of Elements: " << numElements << endl;
        cout << "Load Factor: " << getLoadFactor() << endl;
        cout << "Total Queries: " << numQueries << endl;
        
        if (numQueries > 0){
            double avgComp = (double)numComp/numQueries;
            double avgTime = ((double)totalTime/CLOCKS_PER_SEC)/numQueries;
            double idealLoad = getLoadFactor();
            double performanceRatio = avgComp/(1+idealLoad);
            
            cout << "Average Comparisons per Query: " << avgComp << endl;
            cout << "Maximum Comparisons: " << maxComp << endl;
            cout << fixed << setprecision(8);
            cout << "Average Time: " << avgTime << " seconds" << endl;
            cout << fixed << setprecision(2);
            cout << "Performance Ratio: " << performanceRatio << endl;
        }
    }
    
    // Reset Stats
    void resetStats(){
        numComp = 0;
        maxComp = 0;
        numQueries = 0;
        totalTime = 0;
    }
    
    double getLoadFactor(){
        return (double)numElements/size;
    }
    
    int getSize(){ return size; }
    int getNumElements(){ return numElements; }
};

#endif
