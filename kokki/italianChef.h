#ifndef ITALIANCHEF_H
#define ITALIANCHEF_H
#include "chef.h"
#include <iostream>

using namespace std;

// aliluokka
class ItalianChef  :public Chef
{
public:
    //yleiset funktiot
    ItalianChef(string name);
    ~ItalianChef();

    //yleiset muuttujat
    bool askSecret(string, int, int);

private:
    //yksityiset funktiot
    int makePizza();

    //yksityiset muuttujat
    string password = "pizza";
    int jauho;
    int vesi;
};

#endif // ITALIANCHEF_H
