#include "DataLoader.h"
#include <fstream>
#include <iostream>
using namespace std;
DataLoader::DataLoader() {}
void DataLoader::nacitajData(ds::amt::MultiWayExplicitHierarchy<Vrchol*>& root, vector<Zastavka>& carrier, string nazovSuboru, string carrierName, ds::adt::HashTable<string, ZastavkaList*>& table) {
    ifstream subor = ifstream(nazovSuboru);
    if (!subor.is_open()) {
        cerr << "subor " + nazovSuboru + " sa nepodarilo nacitat.";
        return;
    }

    string prvyRiadok;
    getline(subor, prvyRiadok);

    string riadok;
    ds::amt::MultiWayExplicitHierarchyBlock<Vrchol*>* rootBlock = root.accessRoot();

    if (rootBlock == nullptr) {
        cerr << "Root block is null.";
        return;
    }

    DopravcaVrchol* carrierNode = new DopravcaVrchol(carrierName);
    ds::amt::MultiWayExplicitHierarchyBlock<Vrchol*>* carrierBlock = &root.emplaceSon(*rootBlock, root.degree(*rootBlock));

    if (carrierBlock == nullptr) {
        cerr << "Carrier block is null.";
        return;
    }

    carrierBlock->data_ = carrierNode;

    ds::amt::MultiWayExplicitHierarchyBlock<Vrchol*>* townNode = nullptr;
    string lastTown;

    while (getline(subor, riadok)) {
        string idZastavky;
        string nazovZastavky;
        string stopsite;
        string zemSirka;
        string zemDlzka;
        string dopravca;
        string kodDopravcu;
        string obec;
        stringstream inputString(riadok);

        getline(inputString, idZastavky, ';');
        getline(inputString, nazovZastavky, ';');
        getline(inputString, stopsite, ';');
        getline(inputString, zemSirka, ';');
        getline(inputString, zemDlzka, ';');
        getline(inputString, kodDopravcu, ';');
        getline(inputString, dopravca, ';');
        getline(inputString, obec, ';');

        carrier.emplace_back(nazovZastavky, zemSirka, zemDlzka, dopravca, kodDopravcu, obec);
        // vkladanie do tabuliek
        if (table.contains(nazovZastavky)) {
			ds::adt::ImplicitList<Zastavka*>** list = nullptr;
			table.tryFind(nazovZastavky, list);
			(*list)->insertLast(&carrier.back());
        }
        else {
            ds::adt::ImplicitList<Zastavka*>* list = new ds::adt::ImplicitList<Zastavka*>;
            list->insertLast(&carrier.back());
            table.insert(nazovZastavky, list);
        }
		

        if (obec != lastTown) {
            ObecVrchol* townData = new ObecVrchol(obec);
            townNode = &root.emplaceSon(*carrierBlock, root.degree(*carrierBlock));

            if (townNode == nullptr) {
                cerr << "Town node is null.";
                continue;
            }

            townNode->data_ = townData;
            lastTown = obec;
        }
        if (townNode != nullptr) {
            ZastavkaVrchol* stopData = new ZastavkaVrchol(carrier.back());
            ds::amt::MultiWayExplicitHierarchyBlock<Vrchol*>* stopBlock = &root.emplaceSon(*townNode, root.degree(*townNode));
            if (stopBlock == nullptr) {
                cerr << "Stop block is null.";
                continue;
            }
            stopBlock->data_ = stopData;
        }  
    }
    subor.close();
}
DataLoader::~DataLoader() = default;




