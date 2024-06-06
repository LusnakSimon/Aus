#include<string>
#include "Zastavka.h"
#include <iostream>
#include <algorithm>
using namespace std;

int Zastavka::computeConsonantCount(const string& str)
{
    static const string consonants = "dtnlhgkcjbmprsvzf";
    int count = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        char c = tolower(str[i]);
        if (c == 'c' && i + 1 < str.size() && tolower(str[i + 1]) == 'h') {
            continue; 
        }
        else if (c == 'd' && i + 1 < str.size() && tolower(str[i + 1]) == 'z') {
            continue; 
        }
        else if (consonants.find(c) != string::npos) {
            count++;
        }
    }
    return count;
}

Zastavka::Zastavka(string nazovZastavky, string zemSirka, string zemDlzka, string dopravca, string kodDopravcu, string obec) {
    this->nazovZastavky = nazovZastavky;
    this->zemSirka = zemSirka;
    this->zemDlzka = zemDlzka;
    this->dopravca = dopravca;
    this->kodDopravcu = kodDopravcu;
    this->obec = obec;
	this->pocetSpoluhlasok = computeConsonantCount(nazovZastavky);
}



string Zastavka::getNazov() const{
    return this->nazovZastavky;
}

string Zastavka::getZemSirka() const {
    return this->zemSirka;
}

string Zastavka::getZemDlzka() const {
    return this->zemDlzka;
}

string Zastavka::getDopravca() const {
    return this->dopravca;
}

string Zastavka::getKodDopravcu() const {
    return this->kodDopravcu;
}

string Zastavka::getObec() const {
    return this->obec;
}

int Zastavka::getPocetSpoluhlasok() const
{
    return this->pocetSpoluhlasok;
}

bool Zastavka::porovnajPodlaAbecedy(const Zastavka* zastavka) const
{
    string thisLower = this->nazovZastavky;
    string otherLower = zastavka->getNazov();

    transform(thisLower.begin(), thisLower.end(), thisLower.begin(), ::tolower);
    transform(otherLower.begin(), otherLower.end(), otherLower.begin(), ::tolower);

    return thisLower < otherLower;

}


bool Zastavka::porovnajPocetSpoluhlasok(const Zastavka* zastavka) const
{
    return this->pocetSpoluhlasok < zastavka->getPocetSpoluhlasok();
}

Zastavka::~Zastavka() = default;
