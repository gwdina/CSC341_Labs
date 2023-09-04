#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <bitset>
#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>



using namespace std;

// configurable data
int cachSize = 64 * 1000; // 16, 32, 64, 128, and 256, in KB so *1000
int blockSize = pow(1,2); // 1(1), 2(4), 3(9), 4(16), 5(25), 6(36), 7(49), 8(64) 
int associativity = 2;

// calcuated inital
int totalSets = 0;
int totalBlocks = 0;

// get from LRU
int accesses = 0;
int hitCount = 0;
int missCount = 0;

// calculated last
double hitRate = 0.0;
double missRate = 0.0;

// LRU indedx
int LRUIndex[150000][10];

// LRU Replacement Policy
void LRUREPLACEMENT(int setValue, int associativityValue, int indextloc) {
    
    int currentloc = 0;

    for(int j = 0; j < associativityValue; j++) {
        if(LRUIndex[setValue][j] == indextloc) { currentloc = j;}
    }

    // move the index up
    for(int l = currentloc; l < associativityValue - 1 ; l++) {
        LRUIndex[setValue][l] = LRUIndex[setValue][l + 1];
    }

    LRUIndex[setValue][associativityValue - 1] = indextloc;
}

//reads the trace file
void readTraceFile(string file_name) {
    // cache index
    int cacheindex[totalSets][associativity];

    long long int address; // adress from value
    
    int addressloc = 0; 
    int setValue = 0;
    int cacheLocation = 0;

    int i = 0;
    int j = 0;

    bool addressFound = false; // if a hit was found from the address

    string fileLine = "";

    ifstream file(file_name);

    // failure test
    if (!file) {
        cout << "File was not found";
        exit(0);
    }

    for (i = 0; i < totalSets; i++) {
        for (j = 0; j < associativity; j++) {
            cacheindex[i][j] = 0;
            LRUIndex[i][j] = j;
        }
    }

    //get addresses from the trace file
    while(!file.eof( )) {
        file >> fileLine;
        address = stoi(fileLine);

        accesses++;  

        // hit reset
        addressFound = false; 

        addressloc = address / (blockSize * totalSets); 

        setValue = (address / blockSize) % totalSets;
    

        for(i = 0; i < associativity; i++) {
            if(cacheindex[setValue][i] == addressloc) {
                cacheLocation = i;
                addressFound = true;
            }
        }

        // hit found
        if(addressFound) {
            LRUREPLACEMENT(setValue, associativity, cacheLocation);
            hitCount++;
        }

        // hit not found
        else {
            i = LRUIndex[setValue][0];  
            LRUREPLACEMENT(setValue, associativity, i); 
            cacheindex[setValue][i] = addressloc;
            missCount++;
        }
    }
    // close file
    file.close(); 
} 


int main(){
    //calculate  data for LRU
    totalSets = cachSize / (blockSize * associativity);
    totalBlocks = totalSets * associativity;

    

    readTraceFile("tracefile.txt");

    //inital data
    cout << "\nCache Size: " << cachSize/1000 << " KBytes" << endl;
    cout << "Block Size: " << sqrt(blockSize) << " words" << endl;
    cout << "Associativity: " << associativity << " way" << endl;
    cout << "Replacement Policy: LRU"  << endl;

    accesses = accesses - 1;
    hitCount = hitCount - 1;
    //data found by LRU
    cout << "Total Number of Accesses: " << accesses << endl;
    cout << "Cache Hits: " << hitCount << endl;
    cout << "Cache Misses: " << missCount << endl;
    
    hitRate = (double(hitCount) / double(accesses));
    cout << "Hit rate: " << hitRate * 100 << " %" << endl;

    missRate = (1 - hitRate) * 100;
    cout << "Miss rate: " << missRate << " %" << endl;
    

    return 0;
}