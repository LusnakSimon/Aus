#pragma once
#include <libds/heap_monitor.h>
#include <string>
#include <vector>
#include <functional>
#include "Zastavka.h"
#include "Vrchol.h"
#include <libds/adt/sorts.h>

using namespace std;

class SortZastavok {
public:
    SortZastavok();
    ~SortZastavok() = default;
    void sort(ds::amt::ImplicitSequence<Zastavka*>& sequence, function<bool(const Zastavka*, const Zastavka*)> comparator);
};