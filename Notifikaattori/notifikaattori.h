#ifndef NOTIFIKAATTORI_H
#define NOTIFIKAATTORI_H
#include "Seuraaja.h"
#include <iostream>
using namespace std;

class Notifikaattori {
public:
    Notifikaattori();
    void lisaa(Seuraaja* seur);
    void poista(Seuraaja* seur);
    void tulosta();
    void paivitys(string viesti);

private:
    Seuraaja* seuraajat = nullptr; // Head of the linked list
};

#endif // NOTIFIKAATTORI_H
