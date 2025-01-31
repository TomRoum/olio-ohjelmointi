#ifndef LUOTTOTILI_H
#define LUOTTOTILI_H
#include "pankkitili.h"

using namespace std;

class Luottotili : public Pankkitili
{
public:
    // Constructor to initialize omistaja and creditLimit for Luottotili
    Luottotili(string owner, double creditLimit);

    // Modified withdraw function for Luottotili
    virtual bool withdraw(double amount) override;

    // Modified withdraw function for Luottotili
    virtual bool deposit(double amount) override;

protected:
    // Protected member to store creditLimit for the Luottotili
    double creditLimit;
};
#endif // LUOTTOTILI_H
