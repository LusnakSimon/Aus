#pragma once
#include <libds/heap_monitor.h>
#include <string>
#include <vector>
#include <functional>
#include "Zastavka.h"
#include "Vrchol.h"

class FilterZastavok {
public:
    FilterZastavok() {};

    template <typename Iterator, typename Predikat>
    void vyfiltruj(Iterator begin, Iterator end, Predikat predikat, ds::amt::ImplicitSequence<Zastavka*>& vyfiltrovane) {
        vyfiltrovane.clear();
        for (Iterator it = begin; it != end; ++it) {
            if constexpr (std::is_same_v<std::decay_t<decltype(*it)>, Zastavka>) {
                if (predikat(*it)) {
                    auto& lastBlock = vyfiltrovane.insertLast();
					Zastavka* z = &(*it);
                    lastBlock.data_ = z;
                }
            }
            else {
                Vrchol* vrchol = *it;
				if (vrchol == nullptr) {
					continue;
				}
                if (vrchol->hasZastavka()) {
                    ZastavkaVrchol* zastavkaVrchol = dynamic_cast<ZastavkaVrchol*>(vrchol);
                    if (zastavkaVrchol) {
                        Zastavka& z = zastavkaVrchol->getZastavka();
                        if (predikat(z)) {
                            auto& lastBlock = vyfiltrovane.insertLast();
                            lastBlock.data_ = &z;
                        }
                    }

                }
            }
        };
    }
    ~FilterZastavok() = default;
};