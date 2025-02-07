#include "Seuraaja.h"

Seuraaja::Seuraaja(string nimi) : nimi(nimi) {
    cout << "Seuraaja " << nimi << " luotu" << endl;
}

string Seuraaja::getNimi() {
    return nimi;
}

void Seuraaja::paivitys(string viesti) {
    cout << "Seuraaja " << getNimi() << " sai viestin: " << viesti << endl;
}
