#include "italianChef.h"

ItalianChef::ItalianChef(string name)
{
    chefName = name;
    cout << "italianChef " << chefName << " construktori" << endl;
}

ItalianChef::~ItalianChef()
{
    cout << "italianChef " << chefName << " destruktori" << endl;
}

bool ItalianChef::askSecret(string pw, int f, int w)
{
    //compare vertaa onko pw ja muuttuja password identtisiä
    if ((password.compare(pw)) == 0  ) {
        cout << "salasana ok" <<endl;
        jauho = f;
        vesi = w;
        makePizza();
        //siirtyy makePizza funktioon, jauho ja vesi muuttujat mujanaan
    }
    else {
        cout << "salasana väärin" <<endl;
    }
    return 0;
}

int ItalianChef::makePizza()
{
    //vertaa kumpaa on vähemmä jauho vai vettä, sitten tekee laskut
    int annoksia = min(jauho / 5, vesi / 5);

    cout << "ItalianChef " << chefName
         << ":n varastossa on " << jauho
         << " kpl jauhoa ja " << vesi
         << " litraa vettä, josta voidaan tehdä "
         << annoksia << " annosta pizzaa" << endl;
    return 0;
}
