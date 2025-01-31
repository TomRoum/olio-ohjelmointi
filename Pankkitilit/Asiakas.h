#ifndef ASIAKAS_H
#define ASIAKAS_H
#include "luottotili.h"
#include <iostream>

using namespace std;

class Asiakas
{
public:
    // Constructor to initialize Asiakas with owner and creditLimit
    Asiakas(string owner, double creditLimit);

    // Public function to get the owner's name
    string getNimi();

    // Function to display the Pankkitili and credit account saldos
    void showSaldo();

    // Functions to deposit to Pankkitili and return true (success) or false (failure)
    bool talletus(double amount);

    // Functions to withdraw from Pankkitili and return true (success) or false (failure)
    bool Nosto(double amount);



    // Functions to withdraw from Luottotili and return true (success) or false (failure)
    bool luotonNosto(double amount);

    // Functions to deposit to Luottotili and return true (success) or false (failure)
    bool luotonMaksu(double amount);

    // Function to transfer money from one Asiakas to another
    bool tiliSiirto(double amount, Asiakas &recipient);

private:
    Pankkitili kayttotili;
    Luottotili luottotili;
    string nimi;
};
#endif // ASIAKAS_H
