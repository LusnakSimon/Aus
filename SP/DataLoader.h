#pragma once
#include <libds/heap_monitor.h>
#include <libds/amt/hierarchy.h>
#include <libds/amt/abstract_memory_type.h>
#include <libds/adt/tree.h>
#include <libds/adt/table.h>
#include <libds/adt/list.h>
#include<string>
#include <vector>
#include "Zastavka.h"
#include "Vrchol.h"

using namespace std;
using ZastavkaList = ds::adt::ImplicitList<Zastavka*>;

class DataLoader {
public:
	DataLoader();
	void nacitajData(ds::amt::MultiWayExplicitHierarchy<Vrchol*>& root, vector<Zastavka>& carrier, string nazovSuboru, string carrierName, ds::adt::HashTable<string, ZastavkaList*>& table);
	~DataLoader();
};