#ifndef PANKKITILI_H
#define PANKKITILI_H
#include <iostream>

using namespace std;

class Pankkitili {
public:
    // Constructor to initialize omistaja and saldo
    Pankkitili(string omistaja);

    // Public function to get the saldo
    double getsaldo() const;

    // Public function to withdraw an amount from the account
    virtual bool withdraw(double amount);

    // Public function to deposit an amount to the account
    virtual bool deposit(double amount);

protected:
    // Protected members to store saldo and omistaja
    double saldo = 0;
    string omistaja;
};

#endif // PANKKITILI_H
