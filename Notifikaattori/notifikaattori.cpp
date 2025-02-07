#include "Notifikaattori.h"

Notifikaattori::Notifikaattori() {
    cout << "Luodaan Notifikaattori" << endl;
}

void Notifikaattori::lisaa(Seuraaja* seur) {
    seur->next = seuraajat; // Insert at the head
    seuraajat = seur;
    cout << "Notifikaattori lisää seuraajan " << seur->getNimi() << endl;
}

void Notifikaattori::poista(Seuraaja* seur) {
    Seuraaja* current = seuraajat;
    Seuraaja* previous = nullptr;

    while (current != nullptr) {
        if (current == seur) {
            if (previous == nullptr) {
                seuraajat = current->next; // Removing head
            } else {
                previous->next = current->next;
            }
            cout << "Notifikaattori poistaa seuraajan " << seur->getNimi() << endl;
            return;
        }
        previous = current;
        current = current->next;
    }
}

void Notifikaattori::tulosta() {
    cout << "Notifikaattorin seuraajat:" << endl;
    Seuraaja* current = seuraajat;
    while (current != nullptr) {
        cout << "Seuraaja " << current->getNimi() << endl;
        current = current->next;
    }
}

void Notifikaattori::paivitys(string viesti) {
    cout << "Notifikaattori päivitti viestin: '" << viesti << "'" << endl;
    Seuraaja* current = seuraajat;
    while (current != nullptr) {
        current->paivitys(viesti);
        current = current->next;
    }
}
