#include "Seuraaja.h"
#include "Notifikaattori.h"
using namespace std;

int main() {
    Seuraaja A("Aapeli");
    Seuraaja B("Beethoven");
    Seuraaja C("Chopin");

    Notifikaattori N;
    N.lisaa(&A);
    N.lisaa(&B);
    N.lisaa(&C);

    N.tulosta();
    N.paivitys("Kiitos kahvista!");

    N.poista(&B);
    N.tulosta();
    N.paivitys("Heippa");

    return 0;
}
