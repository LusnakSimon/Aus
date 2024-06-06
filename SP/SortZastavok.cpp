#include "SortZastavok.h"

SortZastavok::SortZastavok()
{
}

void SortZastavok::sort(ds::amt::ImplicitSequence<Zastavka*>& sequence, function<bool(const Zastavka*, const Zastavka*)> comparator)
{
    ds::adt::ShellSort<Zastavka*> shellSort;
    shellSort.sort(sequence, comparator);
}

