#include "asiakas.h"
using namespace std;

int main() {
    // Creating two Asiakass with a credit limit of -500
    Asiakas asiakas1("Tiina", -500);
    Asiakas asiakas2("Matti", -500);

    // Initial saldos
    asiakas1.showSaldo();
    asiakas2.showSaldo();

    // Depositing money into Tiina:n Pankkitili account
    asiakas1.talletus(1000);
    asiakas1.showSaldo();
    asiakas2.showSaldo();

    // Withdrawing money from Tiina:n Pankkitili account
    asiakas1.Nosto(200);
    asiakas1.showSaldo();

    // Transferring money from Tiina to Matti
    asiakas1.tiliSiirto(300, asiakas2);
    asiakas1.showSaldo();
    asiakas2.showSaldo();

    // Withdrawing from Matti:n credit account. Matti has no saldo on pankki tili
    asiakas2.luotonNosto(400);
    asiakas2.showSaldo();

    // Attempting to overdraw beyond credit limit by withdrawing from credit account ()
    asiakas2.luotonNosto(1000);
    asiakas2.showSaldo();

    return 0;
}
