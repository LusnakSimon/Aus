#include <chrono>
#include <fstream>
#include <iostream>
#include <libds/adt/table.h>

using namespace std;

template <typename K, typename T>
class HashTableAnalyzer {
public:
    HashTableAnalyzer(ds::adt::HashTable<K, T>& hashTable)
        : hashTable_(hashTable) {}

    void analyze(size_t numOperations, const string& outputFileName) {
        ofstream outFile(outputFileName);

        if (!outFile.is_open()) {
            cerr << "Subor sa nepodarilo otvorit: " << outputFileName << endl;
            return;
        }

        outFile << "Operacia ,Cas(ns)\n";

        // operacia insert
        for (size_t i = 0; i < numOperations; ++i) {
            auto key = generateKey(i);
            auto data = generateData(i);

            auto start = chrono::high_resolution_clock::now();
            hashTable_.insert(key, data);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            outFile << "insert," << duration << "\n";
        }

        // operacia tryFind ? alebo find ?
        for (size_t i = 0; i < numOperations; ++i) {
            auto key = generateKey(i);
            //T* data;

            auto start = chrono::high_resolution_clock::now();
            //hashTable_.tryFind(key, data);
			hashTable_.find(key);
            auto end = chrono::high_resolution_clock::now();
            auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

            outFile << "find," << duration << "\n";
        }

        outFile.close();
    }

private:
    ds::adt::HashTable<K, T>& hashTable_;

    K generateKey(size_t i) {
        return static_cast<K>(i); 
    }

    T generateData(size_t i) {
        return static_cast<T>(i); 
    }
};


