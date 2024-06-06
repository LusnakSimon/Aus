#pragma once
#include <libds/heap_monitor.h>
#include <iostream>
#include <libds/adt/tree.h>
#include <libds/adt/table.h>
#include <libds/adt/list.h>
#include <libds/amt/hierarchy.h>
#include <libds/amt/abstract_memory_type.h>
#include <vector>
#include <string>
#include <fstream>
#include "Zastavka.h"
#include "FilterZastavok.h"
#include "Vrchol.h"
#include "DataLoader.h"

class ZastavkaManager {
public:

	ZastavkaManager();
	void start();
	~ZastavkaManager() = default;
private:

	std::vector<Zastavka> cow, kam, nan, vic, vly, whi, wil, wkt;

	ds::amt::MultiWayExplicitHierarchy<Vrchol*> root;
	ds::amt::ImplicitSequence<Zastavka*> vyfiltrovane;
	using ZastavkaList = ds::adt::ImplicitList<Zastavka*>;

	ds::adt::HashTable<string, ZastavkaList*> cowTable;
	ds::adt::HashTable<string, ZastavkaList*> kamTable;
	ds::adt::HashTable<string, ZastavkaList*> nanTable;
	ds::adt::HashTable<string, ZastavkaList*> vicTable;
	ds::adt::HashTable<string, ZastavkaList*> vlyTable;
	ds::adt::HashTable<string, ZastavkaList*> whiTable;
	ds::adt::HashTable<string, ZastavkaList*> wilTable;
	ds::adt::HashTable<string, ZastavkaList*> wktTable;

	DataLoader loader;

	void vymazTabulkyAHierarchiu();

	void vypisZastavku(ds::adt::ImplicitList<Zastavka*>*& zastavka);
	void prvaUroven();
	void druhaUroven();
	void tretiaUroven();
	void stvrtaUroven();
};