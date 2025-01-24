#ifndef CHEF_H
#define CHEF_H
#include <iostream>

using namespace std;

// yliluokka
class Chef
{
public:
    //yleiset funktiot
    Chef();
    Chef(string name);
    ~Chef();
    string getChefName();
    int makeSalad(int);
    int makeSoup(int);

protected:
    //suojatut muuttujat
    string chefName;
};

#endif // CHEF_H
