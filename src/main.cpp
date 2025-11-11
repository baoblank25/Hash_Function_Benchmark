// ASU CSE310 Hash Table Assignment
// File: main.cpp
// Description: Main program implementing open addressing hash table per assignment

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>
#include <vector>
#include "../include/URLHashTable.h"

using namespace std;

// Helper function to check if URL starts with valid HTTP prefix
bool isValidURL(const string& url) {
    if(url.length() < 6) return false;
    
    if(url.length() >= 7 && url.substr(0, 7) == "http://") return true;
    if(url.length() >= 6 && url.substr(0, 6) == "http//") return true;
    if(url.length() >= 8 && url.substr(0, 8) == "https://") return true;
    if(url.length() >= 7 && url.substr(0, 7) == "https//") return true;
    
    return false;
}

// Function to load URLs from CSV file
vector<string> loadURLsFromFile(const string& filename, int& tableSize) {
    vector<string> urls;
    ifstream inputFile(filename);
    
    if(!inputFile.is_open()){
        cout << "Error opening file: " << filename << endl;
        return urls;
    }
    
    // Read table size from first line
    string line;
    if(getline(inputFile, line)){
        stringstream ss(line);
        ss >> tableSize;
    }
    
    // Read all URLs
    while(getline(inputFile, line)){
        stringstream ss(line);
        string url;
        
        while(getline(ss, url, ',')){
            // Trim whitespace
            size_t start = url.find_first_not_of(" \t\r\n");
            size_t end = url.find_last_not_of(" \t\r\n");
            
            if(start != string::npos && end != string::npos){
                url = url.substr(start, end - start + 1);
            }
            
            if(!url.empty() && isValidURL(url)){
                urls.push_back(url);
            }
        }
    }
    
    inputFile.close();
    return urls;
}

// Function to run a single test with given configuration
void runTest(int size, const vector<string>& urls, HashType hashType, ProbingMethod probingType) {
    URLHashTable* hashTable = new URLHashTable(size);
    hashTable->setHashFunction(hashType);
    hashTable->setProbingMethod(probingType);
    
    int counter = 0;
    
    // Insert all URLs
    for(const string& url : urls){
        if(hashTable->insertURL(url)){
            counter++;
        }
    }
    cout << "Table Size: " << size << endl;
    cout << "URLs Inserted: " << counter << endl;
    
    hashTable->displayStats();
    
    delete hashTable;
}

int main(){
    string filename;
    int originalSize = 0;
    
    // Get CSV filename and load URLs
    cout << "Enter CSV filename: ";
    getline(cin, filename);
    
    vector<string> urls = loadURLsFromFile(filename, originalSize);
    
    if(urls.empty()){
        cout << "No valid URLs found in file. Exiting." << endl;
        return 1;
    }
    
    cout << "Loaded " << urls.size() << " URLs from file." << endl;
    cout << "Original table size from CSV: " << originalSize << endl;
    
    // Choose testing mode
    int mode;
    while(true){
        cout << "\nSelect mode:" << endl;
        cout << "1. Single table size test (interactive)" << endl;
        cout << "2. Multiple table size test (10 sizes)" << endl;
        cout << "Enter choice (1 or 2): ";
        
        if(cin >> mode){
            if(mode == 1 || mode == 2){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            else{
                cout << "Only enter 1 or 2." << endl;
            }
        }
        else{
            cout << "Only enter 1 or 2." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    // Get hash function type
    int hashChoice;
    while(true){
        cout << "\nSelect hash function:" << endl;
        cout << "1. Bitwise Mixing Hash" << endl;
        cout << "2. Polynomial Rolling Hash" << endl;
        cout << "3. Universal Hashing" << endl;
        cout << "Enter choice (1, 2, or 3): ";
        
        if(cin >> hashChoice){
            if(hashChoice >= 1 && hashChoice <= 3){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            else{
                cout << "Only enter 1, 2, or 3." << endl;
            }
        }
        else{
            cout << "Only enter 1, 2, or 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    HashType hashType;
    if(hashChoice == 1){
        hashType = BITWISE_HASH;
        cout << "Using Bitwise Mixing Hash" << endl;
    }
    else if(hashChoice == 2){
        hashType = POLYNOMIAL_HASH;
        cout << "Using Polynomial Rolling Hash" << endl;
    }
    else{
        hashType = UNIVERSAL_HASH;
        cout << "Using Universal Hashing" << endl;
    }
    
    // Get probing method
    int probingChoice;
    while(true){
        cout << "\nSelect probing method:" << endl;
        cout << "1. Linear Probing" << endl;
        cout << "2. Quadratic Probing" << endl;
        cout << "Enter choice (1 or 2): ";
        
        if(cin >> probingChoice){
            if(probingChoice == 1 || probingChoice == 2){
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            else{
                cout << "Only enter 1 or 2." << endl;
            }
        }
        else{
            cout << "Only enter 1 or 2." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    
    ProbingMethod probingType = (probingChoice == 1) ? LINEAR_PROBING : QUADRATIC_PROBING;
    cout << "Using " << (probingChoice == 1 ? "Linear" : "Quadratic") << " Probing" << endl;
    
    if(mode == 1){
        // SINGLE TABLE SIZE MODE (Interactive)
        int size;
        cout << "\nEnter hash table size: ";
        cin >> size;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        URLHashTable* hashTable = new URLHashTable(size);
        hashTable->setHashFunction(hashType);
        hashTable->setProbingMethod(probingType);
        
        int counter = 0;
        
        // Insert URLs
        cout << "\nInserting URLs into hash table..." << endl;
        for(const string& url : urls){
            if(hashTable->insertURL(url)){
                counter++;
            }
        }
        
        cout << "\nHash table size is: " << size << endl;
        cout << "Total URLs inserted: " << counter << endl;
        
        // Interactive command loop
        do{
            cout << "\nAvailable Commands" << endl;
            cout << "hashSearch,<URL>" << endl;
            cout << "hashDelete,<URL>" << endl;
            cout << "hashDisplay" << endl;
            cout << "hashStats" << endl;
            cout << "hashReset" << endl;
            cout << "End" << endl;
            cout << "\nEnter command:" << endl;
            string cLine;
            getline(cin, cLine);
            
            if(cLine=="End"){
                break;
            }
            
            string delimiter = ",";
            size_t pos = cLine.find(delimiter);
            
            if(pos==string::npos){
                if(cLine=="hashDisplay"){
                    hashTable->displayTable();
                }
                else if(cLine=="hashStats"){
                    hashTable->displayStats();
                }
                else if(cLine=="hashReset"){
                    hashTable->resetStats();
                    cout << "Stats have been reset." << endl;
                }
                else{
                    cout << "Enter a valid command." << endl;
                }
            }
            else{
                string command = cLine.substr(0, pos);
                string url = cLine.substr(pos+delimiter.length());
                
                if(command=="hashSearch"){
                    if(!url.empty()){
                        hashTable->searchURL(url);
                    }
                    else{
                        cout << "Enter a valid URL." << endl;
                    }
                }
                else if(command=="hashDelete"){
                    if(!url.empty()){
                        bool found = hashTable->searchURL(url);
                        if(found){
                            hashTable->deleteURL(url);
                            counter--;
                        }
                    }
                    else{
                        cout << "Enter a valid URL." << endl;
                    }
                }
                else{
                    cout << "Enter a valid command." << endl;
                }
            }
        }while(true);
        
        cout << "\nFinal Stats" << endl;
        hashTable->displayStats();
        
        delete hashTable;
    }
    else{
        // BATCH MODE - Test multiple table sizes
        cout << "Testing same " << urls.size() << " URLs with different table sizes" << endl;
        
        // Generate at least 10 different table sizes
        // Using different load factors: from sparse (α≈0.3) to very full (α≈0.95)
        vector<int> tableSizes;
        int numURLs = urls.size();
        
        // Calculate sizes for different load factors
        tableSizes.push_back(numURLs * 3);      // α ≈ 0.33
        tableSizes.push_back(numURLs * 2);      // α ≈ 0.50
        tableSizes.push_back((numURLs * 3) / 2); // α ≈ 0.67
        tableSizes.push_back((numURLs * 4) / 3); // α ≈ 0.75
        tableSizes.push_back((numURLs * 5) / 4); // α ≈ 0.80
        tableSizes.push_back((numURLs * 10) / 9); // α ≈ 0.90
        tableSizes.push_back((numURLs * 20) / 19); // α ≈ 0.95
        tableSizes.push_back(numURLs + 100);    // α varies
        tableSizes.push_back(numURLs + 50);     // α varies
        tableSizes.push_back(numURLs + 10);     // α varies
        
        // Run tests for each table size
        for(int i = 0; i < tableSizes.size(); i++){
            int size = tableSizes[i];
            double expectedLoadFactor = (double)numURLs / size;
            
            cout << "TEST #" << (i+1) << " - Table Size: " << size << endl;
            cout << "Expected Load Factor: " << fixed << setprecision(4) << expectedLoadFactor << endl;
            
            runTest(size, urls, hashType, probingType);
            
            // Pause between tests
            if(i < tableSizes.size() - 1){
                cout << "\nPress Enter to continue to next test...";
                cin.get();
            }
        }
        
    }
    
    return 0;
}
