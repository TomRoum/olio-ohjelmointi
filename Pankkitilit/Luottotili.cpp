#include "luottotili.h"

Luottotili::Luottotili(string owner, double creditLimit) : Pankkitili(owner), creditLimit(creditLimit)
{
    cout << "Luottotili luotu " << owner << ":lle, luottoraja " << creditLimit << endl;
    cout << " " << endl; // blank row in terminal for readability
}

bool Luottotili::withdraw(double määrä)
{
    // Check if the withdrawal is within the allowed limit (saldo can go below 0 but no lower than the creditLimit)
    if (määrä >= 0 && (saldo - määrä) >= creditLimit)
    {
        saldo -= määrä;
        cout << omistaja << " nostaa " << määrä << "€ luotto tililtä." << endl;
        return true; // Withdrawal successful
    }
    else {
    cout << "Withdrawal failed due to invalid määrä or exceeding creditLimit" << endl;
    return false;
    }
}

bool Luottotili::deposit(double määrä)
{
    // is deposited amount positive?
    if (määrä > 0)
    {
        saldo += määrä; // Add credit to the Luottotili's saldo
        cout << omistaja << " tallettaa " << määrä << "€ luotto tilille." << endl;
        return true; // Deposit successful
    }
    else {
    cout << "Deposit failed due to invalid määrä" << endl;
    return false;
    }
}
