#include <libds/heap_monitor.h>
#include "ZastavkaManager.h"
#include "HashTableAnalyzer.h"

using namespace std;

int main() {
    
    initHeapMonitor();


	ZastavkaManager zastavkaManager;
	zastavkaManager.start();

    /*
	cout << "Spustit analyzu casovej zlozitosti HashTable ?\n1. ANO\n2. NIE" << endl;
    int volba;
	cin >> volba;
    if (volba == 1) {
        ds::adt::HashTable<int, int> hashTable;
        HashTableAnalyzer<int, int> analyzer(hashTable);

        size_t numOperations = 1000;
        std::string outputFileName = "analyza_casovej_zlozitosti_HashTable.csv";

        analyzer.analyze(numOperations, outputFileName);
    }
    */

	return 0;
}