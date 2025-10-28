#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "URLHashTable.h"

using namespace std;

int main(){
    int size = 0;
    int counter = 0;
    
    // Validate hash table size input
    while (true){
        cout << "Enter the hash table size: ";
        if(cin >> size){
            if(size > 0){
                cin.ignore(20, '\n');
                break;
            }
            else{
                cout << "Only Enter a positive integer for hash table size." << endl;
            }
        }
        else{
            cout << "Only enter the right hash table size." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    URLHashTable* hashTable = new URLHashTable(size);
    
    //Get hash function type and probing type
    int choice;
    while (true){
        cout << "\nSelect hash function:" << endl;
        cout << "1. Division Hashing" << endl;
        cout << "2. Universal Hashing" << endl;
        cout << "Enter choice (1 or 2): ";
        
        if(cin >> choice){
            if(choice==1 || choice==2){
                cin.ignore(20, '\n');
                break;
            } 
            else{
                cout << "Only enter 1 or 2." << endl;
            }
        } 
        else{
            cout << "Only enter 1 or 2." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    if(choice==1){
        hashTable->setHashFunction(DIVISION_HASH);
        cout << "Using Division Hashing" << endl;
    } 
    else{
        hashTable->setHashFunction(UNIVERSAL_HASH);
        cout << "Using Universal Hashing" << endl;
    }
    
    // Get probing method with validation
    int choice2;
    while (true){
        cout << "\nSelect probing method:" << endl;
        cout << "1. Linear Probing" << endl;
        cout << "2. Quadratic Probing" << endl;
        cout << "Enter choice (1 or 2): ";
        
        if(cin >> choice2){
            if(choice2==1 || choice2==2){
                cin.ignore(20, '\n');
                break;
            } 
            else{
                cout << "Only enter 1 or 2." << endl;
            }
        } 
        else{
            cout << "Only enter 1 or 2." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
    
    if(choice2==1){
        hashTable->setProbingMethod(LINEAR_PROBING);
        cout << "Using Linear Probing" << endl;
    } 
    else{
        hashTable->setProbingMethod(QUADRATIC_PROBING);
        cout << "Using Quadratic Probing" << endl;
    }
    
    cout << "\nEnter URLs (type 'InsertionEnd' to finish)" << endl;
    
    //Insert URLs
    do{
        string url;
        getline(cin, url);
        
        if(url == "InsertionEnd"){
            break;
        }
        
        if(!url.empty()){
            //Check ifit is a valid URL
            if(url.substr(0, 7)=="http://" || url.substr(0, 8)=="https://"){
                if(hashTable->insertURL(url)){
                    counter++;
                }
            } 
            else{
                cout << "Please enter a valid URL." << endl;
            }
        }
    } while (true);
    
    cout << "\nHash table size is: " << size << endl;
    cout << "Total URLs entered: " << counter << endl;
    
    do{
        cout << "\nAvailable Commands" << endl;
        cout << "hashSearch,<URL>" << endl;
        cout << "hashDelete,<URL>" << endl;
        cout << "hashDisplay" << endl;
        cout << "hashStats" << endl;
        cout << "hashReset" << endl;
        cout << "InsertionContinue" << endl;
        cout << "End" << endl;
        cout << "\nEnter commands:" << endl;
        string cLine;
        getline(cin, cLine);
        
        if(cLine == "End"){
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
            else if(cLine=="InsertionContinue"){
                cout << "\nContinue entering URLs (type 'InsertionEnd' to finish)" << endl;
                
                // Continue inserting URLs
                do{
                    string url;
                    getline(cin, url);
                    
                    if(url=="InsertionEnd"){
                        break;
                    }
                    
                    if(!url.empty()){
                        //Check ifits a valid URL
                        if(url.substr(0, 7)=="http://" || url.substr(0, 8)=="https://"){
                            if(hashTable->insertURL(url)){
                                counter++;
                            }
                        } 
                        else{
                            cout << "Enter a valid URL." << endl;
                        }
                    }
                } while (true);
                
                cout << "\nHash table size is: " << size << endl;
                cout << "Total URLs entered: " << counter << endl;
            }
            else{
                // Invalid command
                cout << "Enter a valid URL or command." << endl;
            }
        }
        else{
            // Command with parameter
            string command = cLine.substr(0, pos);
            string url = cLine.substr(pos + delimiter.length());
            
            if(command=="hashSearch"){
                if(!url.empty()){
                    hashTable->searchURL(url);
                }
                else{
                    cout << "Enter a valid URL or command." << endl;
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
                    cout << "Enter a valid URL or command." << endl;
                }
            }
            else{
                cout << "Enter a valid URL or command." << endl;
            }
        }
    } while (true);
    
    //Display final stats
    cout << "\nFinal Stats" << endl;
    hashTable->displayStats();
    
    delete hashTable;
    return 0;
}
