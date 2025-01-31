#include "pankkitili.h"

Pankkitili::Pankkitili(string omistaja) : omistaja(omistaja)
{
    cout << "Pankkitili luotu " << omistaja << ":lle" << endl;
    cout << " " << endl; // blank row in terminal for readability
}

double Pankkitili::getsaldo() const
{
    return saldo;
}

bool Pankkitili::withdraw(double määrä)
{
    if (määrä >= 0 && määrä <= saldo)
    {
        Pankkitili::saldo -= määrä;
        cout << omistaja << " nostaa " << määrä << "€ pankki tililtä." << endl;
        return true; // Withdrawal successful
    }
    else {
        cout << "Withdrawal failed due to invalid määrä" << endl;
        return false;
    }
}

bool Pankkitili::deposit(double määrä)
{
    if (määrä > 0)
    {
        saldo += määrä;
        cout << omistaja << " tallettaa " << määrä << "€ pankki tilille." << endl;
        return true; // Deposit successful
    }
    else {
        cout << "Deposit failed due to invalid määrä" << endl;
        return false;
    }
}

