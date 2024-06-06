#include "ZastavkaManager.h"
#include "SortZastavok.h"


ZastavkaManager::ZastavkaManager() {
    
    cow.reserve(600);
    kam.reserve(700);
    nan.reserve(900);
    vic.reserve(2400);
    vly.reserve(1000);
    whi.reserve(200);
    wil.reserve(100);
    wkt.reserve(700);

    root.emplaceRoot();
    auto rootBlock = root.accessRoot();
    rootBlock->data_ = new KorenVrchol();

    loader.nacitajData(root, cow, "data\\cow_busstops.csv", "Cowichan Valley Regional", cowTable);
    loader.nacitajData(root, kam, "data\\kam_busstops.csv", "Kamloops Transit System", kamTable);
    loader.nacitajData(root, nan, "data\\nan_busstops.csv", "Regional District of Nanaimo Transit System", nanTable);
    loader.nacitajData(root, vic, "data\\vic_busstops.csv", "Victoria Regional Transit System", vicTable);
    loader.nacitajData(root, vly, "data\\vly_busstops.csv", "Fraser Valley Region", vlyTable);
    loader.nacitajData(root, whi, "data\\whi_busstops.csv", "Whistler Transit System", whiTable);
    loader.nacitajData(root, wil, "data\\wil_busstops.csv", "Williams Lake Transit System", wilTable);
    loader.nacitajData(root, wkt, "data\\wkt_busstops.csv", "West Kootenay Transit System", wktTable);

}

void ZastavkaManager::prvaUroven() {
    int dopravca = -1;

    FilterZastavok filter;

    while (dopravca != 0) {

        cout << "1.Cowichan Valley Regional\n2.Kamloops Transit System" <<
            "\n3.Regional District of Nanaimo Transit System\n4.Victoria Regional Transit System" <<
            "\n5.Fraser Valley Region\n6.Whistler Transit System\n7.Williams Lake Transit System" <<
            "\n8.West Kootenay Transit System\n\nVyber dopravcu (1-8) alebo ('0' - EXIT): ";

        cin >> dopravca;

        if (dopravca == 0) {
            return;
        }

        cout << endl;

        int metoda;

        cout << "1. startsWithStr\n2. containsStr\n\nVyber metodu:";
        cin >> metoda;
        cout << endl;
        string kluc;
        cout << "Zadaj kluc pre filtrovanie:";
        cin >> kluc;

        std::function<bool(const Zastavka&)> predikat;
        if (metoda == 1) {
            predikat = [&kluc](const Zastavka& z) { return z.getNazov().substr(0, kluc.size()) == kluc; };
        }
        else if (metoda == 2) {
            predikat = [&kluc](const Zastavka& z) { return z.getNazov().find(kluc) != string::npos; };
        }
        else {
            system("cls");
            cout << " Nespravna metoda. Zadaj 1 pre startsWithStr alebo 2 pre containsStr.\n\n";
            continue;
        }

        switch (dopravca) {
        case 1:

            filter.vyfiltruj(cow.begin(), cow.end(), predikat, vyfiltrovane);
            break;
        case 2:
            filter.vyfiltruj(kam.begin(), kam.end(), predikat, vyfiltrovane);
            break;
        case 3:
            filter.vyfiltruj(nan.begin(), nan.end(), predikat, vyfiltrovane);
            break;
        case 4:
            filter.vyfiltruj(vic.begin(), vic.end(), predikat, vyfiltrovane);
            break;
        case 5:
            filter.vyfiltruj(vly.begin(), vly.end(), predikat, vyfiltrovane);
            break;
        case 6:
            filter.vyfiltruj(whi.begin(), whi.end(), predikat, vyfiltrovane);
            break;
        case 7:
            filter.vyfiltruj(wil.begin(), wil.end(), predikat, vyfiltrovane);
            break;
        case 8:
            filter.vyfiltruj(wkt.begin(), wkt.end(), predikat, vyfiltrovane);
            break;
		default:
            system("cls");
			cout << "Nespravny vyber dopravcu. Skus to znova.\n\n";
			continue;
        }
	    
	

        cout << endl << "Vysledok filtrovania:\n\n";
        for (auto it = vyfiltrovane.begin(); it != vyfiltrovane.end(); ++it) {
            if (*it != nullptr) {
                std::cout << (*it)->getNazov() << std::endl;
            }
        }
        cout << "\n\n";
		cout << "Chcete pokracovat? (1 - ANO, 0 - NIE): ";
		int pokracovat;
		cin >> pokracovat;
        if (pokracovat == 0) {
            return;
		}
		else {
			system("cls");
		}
    }
}

void ZastavkaManager::druhaUroven() {
    auto currentBlock = root.accessRoot();
    FilterZastavok filter;
    while (true) {
        system("cls");
		if (currentBlock != root.accessRoot()) {
            cout << "Aktualna uroven: " << currentBlock->data_->toString() << "\n\n";
		}
        ds::amt::MultiWayExplicitHierarchy<Vrchol*>::PreOrderHierarchyIterator it(&root, currentBlock);
        size_t degree = root.degree(*currentBlock);

        for (size_t i = 0; i < degree; ++i) {
            if (root.accessSon(*currentBlock, i) == nullptr) {
                std::cerr << "Error: Null son block." << endl;
                continue;
            }
            cout << i + 1 << ". " << root.accessSon(*currentBlock, i)->data_->toString() << endl;
        }

        string selection;
        cout << "\nVyber jednu z moznosti (1-n) alebo ('0' uroven vyssie, 'f' -filtrovanie, 'e' - exit) : ";
        cin >> selection;

        if (selection == "e") {
            return;
        }

        cout << endl;

        if (selection == "0") {
            auto parentBlock = root.accessParent(*currentBlock);
            if (parentBlock == nullptr) {
                std::cout << "Uz si na najvyssej urovni.\n\n";
                continue;
            }
            currentBlock = parentBlock;
            continue;
        }

        if (selection == "f") {
            cout << "\nVyber moznost: (1 - startsWithStr , 2 - containsStr) : ";
            int metoda;
            cin >> metoda;
            cout << endl;
            cout << "Zadaj kluc pre filtrovanie:";
            string filterString;
            cin >> filterString;
            std::function<bool(const Zastavka&)> predikat;
            if (metoda == 1) {
                predikat = [&filterString](const Zastavka& z) { return z.getNazov().substr(0, filterString.size()) == filterString; };
            }
            else if (metoda == 2) {
                predikat = [&filterString](const Zastavka& z) { return z.getNazov().find(filterString) != std::string::npos; };
            }
            else {
                cout << "Nespravna metoda. Zadaj 1 pre startsWithStr alebo 2 pre containsStr.\n";
                continue;
            }
            filter.vyfiltruj(it, root.end(), predikat, vyfiltrovane);
            cout << "Vysledok filtrovania:\n\n";
            for (auto it = vyfiltrovane.begin(); it != vyfiltrovane.end(); ++it) {
                if (*it != nullptr) {
                    std::cout << (*it)->getNazov() << std::endl;
                }
            }
            cout << endl;
			cout << "chcete vysledky zoradit? ( 1 - ANO, 0 - NIE): ";
			int zoradit;
			cin >> zoradit;
            if (zoradit == 1) {
                stvrtaUroven();
			}
            continue;
        }

        int sonIndex = stoi(selection) - 1;

        if (sonIndex < 0 || sonIndex >= static_cast<int>(degree)) {
            cerr << "Nespravny vyber. Skus to znova." << endl;
            continue;
        }

        currentBlock = root.accessSon(*currentBlock, static_cast<size_t>(sonIndex));
    }
}

void ZastavkaManager::tretiaUroven() {
    while (true) {
        cout << "1.Cowichan Valley Regional\n2.Kamloops Transit System" <<
            "\n3.Regional District of Nanaimo Transit System\n4.Victoria Regional Transit System" <<
            "\n5.Fraser Valley Region\n6.Whistler Transit System\n7.Williams Lake Transit System" <<
            "\n8.West Kootenay Transit System\n\nVyber dopravcu (1-8) alebo ('0' - exit): ";
        int dopravca;
        cin >> dopravca;

        if (dopravca == 0) {
            return;
        }

        cout << endl;
        //vyhladavanie podla nazvu
        string key;
        cout << "Vyhladaj podla nazvu: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, key);
        if (key == "0") {
            return;
        }
        if (dopravca == 1) {
            if (cowTable.contains(key) == false) {
                system("cls");
                cout << "***Zastavka nebola najdena.***\n" << endl;
                continue;
            }
            ds::adt::ImplicitList<Zastavka*>* zastavka = cowTable.find(key);
            vypisZastavku(zastavka);
        }
        else if (dopravca == 2) {
            if (kamTable.contains(key) == false) {
                system("cls");
                cout << "***Zastavka nebola najdena.***\n" << endl;
                continue;
            }
            ds::adt::ImplicitList<Zastavka*>* zastavka = kamTable.find(key);
            vypisZastavku(zastavka);
        }
        else if (dopravca == 3) {
            if (nanTable.contains(key) == false) {
                system("cls");
                cout << "***Zastavka nebola najdena.***\n" << endl;
                continue;
            }
            ds::adt::ImplicitList<Zastavka*>* zastavka = nanTable.find(key);
            vypisZastavku(zastavka);
        }
        else if (dopravca == 4) {
            if (vicTable.contains(key) == false) {
                system("cls");
                cout << "***Zastavka nebola najdena.***\n" << endl;
                continue;
            }
            ds::adt::ImplicitList<Zastavka*>* zastavka = vicTable.find(key);
            vypisZastavku(zastavka);
        }
        else if (dopravca == 5) {
            if (vlyTable.contains(key) == false) {
                system("cls");
                cout << "***Zastavka nebola najdena.***\n" << endl;
                continue;
            }
            ds::adt::ImplicitList<Zastavka*>* zastavka = vlyTable.find(key);
            vypisZastavku(zastavka);
        }
        else if (dopravca == 6) {
            if (whiTable.contains(key) == false) {
                system("cls");
                cout << "***Zastavka nebola najdena.***\n" << endl;
                continue;
            }
            ds::adt::ImplicitList<Zastavka*>* zastavka = whiTable.find(key);
            vypisZastavku(zastavka);
        }
        else if (dopravca == 7) {
            if (wilTable.contains(key) == false) {
                system("cls");
                cout << "***Zastavka nebola najdena.***\n" << endl;
                continue;
            }
            ds::adt::ImplicitList<Zastavka*>* zastavka = wilTable.find(key);
            vypisZastavku(zastavka);
        }
        else if (dopravca == 8) {
            if (wktTable.contains(key) == false) {
                system("cls");
                cout << "***Zastavka nebola najdena.***\n" << endl;
                continue;
            }
            ds::adt::ImplicitList<Zastavka*>* zastavka = wktTable.find(key);
            vypisZastavku(zastavka);
        }
        else {
            system("cls");
            cout << "***Nespravny vyber. Skus to znova.***\n" << endl;
            continue;
        }
        cout << "chces pokracovat? (1 - ANO, 0 - NIE): ";
        int pokracovat;
        cin >> pokracovat;
        if (pokracovat == 0) {
            return;
        }
        else {
            system("cls");
            continue;
        }
    }
}

void ZastavkaManager::stvrtaUroven() {
    SortZastavok sortZastavok;
    while (true) {
		if (vyfiltrovane.size() == 0) {
			cout << "Najprv v prvej alebo druhej urovni vyfiltruj zastavky.  ( 0 - EXIT )\n";
            int empty;
            cin >> empty;
			break;
		}
        std::function<bool(const Zastavka* a, const Zastavka* b)> komparator;
		cout << "1. Zorad abecedne\n2. Zorad podla poctu spoluhlasok\n\nVyber moznost: ";
		int moznost;
		cin >> moznost;
		cout << endl;
		if (moznost == 1) {
			komparator = [](const Zastavka* a, const Zastavka* b) { return a->porovnajPodlaAbecedy(b);};
		}
		else if (moznost == 2) {
			komparator  = [](const Zastavka* a, const Zastavka* b) { return a->porovnajPocetSpoluhlasok(b);};
		}
		else {
			cout << "Nespravna moznost. Skus to znova.\n";
			continue;
		}   
        
        sortZastavok.sort(vyfiltrovane, komparator);

		string zoradenie = moznost == 1 ? " abecedy:" : " poctu spoluhlasok:";
		int counter = 0;
        cout << endl;
        cout << "Zoradenie podla" + zoradenie +"\n\n";
        for (auto it = vyfiltrovane.begin(); it != vyfiltrovane.end(); ++it) {
            if (*it != nullptr) {
                counter++;
				auto hodnota = moznost == 1 ? counter : (*it)->getPocetSpoluhlasok();
                std::cout << (*it)->getNazov() << " ["  << hodnota  << "]" << std::endl;
            }
        }
        cout << endl;

        
        cout << "spat na vyber zoradenia ( 1 - ANO, 0 - NIE ): ";
		int exit;
		cin >> exit;
        if (exit == 0) {
			break;

		}
        system("cls");

    }
    
}

void ZastavkaManager::start() {
    while (true) {
        system("cls");
        cout << "**************\n1. Prva uroven\n2. Druha uroven\n3. Tretia uroven\n4. Stvrta uroven\n0. Exit\n\nVyber moznost: ";
        int moznost;
        cin >> moznost;
        system("cls");
        if (moznost == 1) {
            prvaUroven();
        }
        else if (moznost == 2) {
            druhaUroven();
        }
        else if (moznost == 3) {
            tretiaUroven();
        }
        else if (moznost == 4) {
            stvrtaUroven();
        }
        else if (moznost == 0) {
            break;
        }
        else {
            cout << "Nespravna moznost. Skus to znova.\n";
        }
    }
	vymazTabulkyAHierarchiu();
}

void ZastavkaManager::vymazTabulkyAHierarchiu() {

    for (auto it = cowTable.begin(); it != cowTable.end(); ++it) {
        delete (*it).data_;
    }
    for (auto it = kamTable.begin(); it != kamTable.end(); ++it) {
        delete (*it).data_;
    }
    for (auto it = nanTable.begin(); it != nanTable.end(); ++it) {
        delete (*it).data_;
    }
    for (auto it = vicTable.begin(); it != vicTable.end(); ++it) {
        delete (*it).data_;
    }
    for (auto it = vlyTable.begin(); it != vlyTable.end(); ++it) {
        delete (*it).data_;
    }
    for (auto it = whiTable.begin(); it != whiTable.end(); ++it) {
        delete (*it).data_;
    }
    for (auto it = wilTable.begin(); it != wilTable.end(); ++it) {
        delete (*it).data_;
    }
    for (auto it = wktTable.begin(); it != wktTable.end(); ++it) {
        delete (*it).data_;
    }

    auto rootBlock = root.accessRoot();
    ds::amt::MultiWayExplicitHierarchy<Vrchol*>::PostOrderHierarchyIterator it(&root, rootBlock);

    while (it != root.end()) {
        delete (*it);
        ++it;
    }
    root.clear();

    vyfiltrovane.clear();

}

void ZastavkaManager::vypisZastavku(ds::adt::ImplicitList<Zastavka*>*& zastavka) {
    cout << endl;
    for (auto it = zastavka->begin(); it != zastavka->end(); ++it) {
        cout << "Nazov: " << (*it)->getNazov() << endl;
        cout << "Zemepisna sirka: " << (*it)->getZemSirka() << endl;
        cout << "Zemepisna dlzka: " << (*it)->getZemDlzka() << endl;
        cout << "Dopravca: " << (*it)->getDopravca() << endl;
        cout << "Kod dopravcu: " << (*it)->getKodDopravcu() << endl;
        cout << "Obec: " << (*it)->getObec() << endl;
        cout << endl;
    }
}
