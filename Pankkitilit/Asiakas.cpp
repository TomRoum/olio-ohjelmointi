#include "asiakas.h"

Asiakas::Asiakas(string owner, double creditLimit)
    : kayttotili(owner), luottotili(owner, creditLimit)
{
    nimi = owner;
    cout << "Asiakkuus luotu " << owner << ":lle" << endl;
    cout << " " << endl; // blank row in terminal for readability
}

string Asiakas::getNimi()
{
    return nimi;
}

void Asiakas::showSaldo()
{

    cout << getNimi() << ":n Pankkitili Account saldo: " << kayttotili.getsaldo() << "€" << endl;
    cout << getNimi() << ":n Credit Account saldo: " << luottotili.getsaldo() << "€" << endl;
    cout << " " << endl; // blank row in terminal for readability
}

bool Asiakas::Nosto(double määrä)
{
    return kayttotili.withdraw(määrä) ? true : false;  // Return true if deposit successful, otherwise false

}

bool Asiakas::talletus(double määrä)
{
    return kayttotili.deposit(määrä) ? true : false; // Return true if deposit successful, otherwise false

}

bool Asiakas::luotonNosto(double määrä)
{
    return luottotili.withdraw(määrä) ? true : false; // Return true if deposit successful, otherwise false
}

bool Asiakas::luotonMaksu(double määrä)
{
    return luottotili.withdraw(määrä) ? true : false ; // Return true if deposit successful, otherwise false
}

bool Asiakas::tiliSiirto(double määrä, Asiakas &recipient)
{
    if (kayttotili.getsaldo() >= määrä)
    {
        if (kayttotili.withdraw(määrä))
        {       // Deposit the määrä into the recipient's Pankkitili
            if (recipient.talletus(määrä))
            {
                cout << getNimi() <<" siirtää rahaa " << määrä << "€ to " << recipient.getNimi() << endl;
                cout << " " << endl; // blank row in terminal for readability
                return true; // Transfer successful
            }
            else
            {   // If recipient deposit fails, revert the withdrawal
                kayttotili.deposit(määrä); // Revert the withdrawal
            }
        }
    }
    return false; // Transfer failed (insufficient funds or deposit failed)
}
