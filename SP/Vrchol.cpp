#include "Vrchol.h"

DopravcaVrchol::DopravcaVrchol(const string& nazov) : nazovDopravcu(nazov) {}

string DopravcaVrchol::toString() const {
    return this->nazovDopravcu;
}

ObecVrchol::ObecVrchol(const string& nazov) : nazovObce(nazov) {}

string ObecVrchol::toString() const {
    return this->nazovObce;
}

ZastavkaVrchol::ZastavkaVrchol(Zastavka& zastavka) : zastavka_(zastavka) {
}

Zastavka& ZastavkaVrchol::getZastavka()
{
	return this->zastavka_;
}

bool ZastavkaVrchol::hasZastavka() const
{
    return true;
}

string ZastavkaVrchol::toString() const
{
    return this->zastavka_.getNazov();
}

KorenVrchol::KorenVrchol()
{
}

string KorenVrchol::toString() const
{
    return "koren";
}
