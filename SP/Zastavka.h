#pragma once
#include <libds/heap_monitor.h>
#include<string>
using namespace std;
class Zastavka {
private:
    string nazovZastavky;
    string zastavka;
    string zemSirka;
    string zemDlzka;
    string dopravca;
    string kodDopravcu;
    string obec;
    int pocetSpoluhlasok;
    static int computeConsonantCount(const string& str);
public:
    Zastavka(string nazovZastavky, string zemSirka, string zemDlzka, string dopravca, string kodDopravcu, string obec);
    string getNazov() const;
    string getZemSirka() const;
    string getZemDlzka() const;
    string getDopravca() const;
    string getKodDopravcu() const;
    string getObec() const;
    int getPocetSpoluhlasok() const;
	bool porovnajPodlaAbecedy(const Zastavka* zastavka) const;
	bool porovnajPocetSpoluhlasok(const Zastavka* zastavka) const;
    ~Zastavka();
};
