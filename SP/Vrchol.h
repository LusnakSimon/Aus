#pragma once
#include <libds/heap_monitor.h>
#include <iostream>
#include <string>
#include "Zastavka.h"

using namespace std;

class Vrchol {
public:
    virtual ~Vrchol() = default;
    virtual string toString() const = 0;
    virtual bool hasZastavka() const { return false; }
};

class DopravcaVrchol : public Vrchol {
private:
    string nazovDopravcu;
public:
    DopravcaVrchol(const string& nazov);
    string toString() const override;
};

class ObecVrchol : public Vrchol {
private:
    string nazovObce;
public:
    ObecVrchol(const string& nazov);
    string toString() const override;
};

class ZastavkaVrchol : public Vrchol {
private:
    Zastavka& zastavka_;
public:
    ZastavkaVrchol(Zastavka& zastavka); 

    Zastavka& getZastavka();
    bool hasZastavka() const override;

    string toString() const override;
};

class KorenVrchol : public Vrchol {
public:
    KorenVrchol();
    string toString() const override;
};
