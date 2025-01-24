#include "chef.h"

Chef::Chef()
{
    cout << "Chef default construktori" << endl;
}

Chef::Chef(string name)
{
    chefName = name;
    cout << "Chef " << chefName << " construktori" << endl;
}

string Chef::getChefName()
{
    return chefName;
}

Chef::~Chef()
{
    cout << "Chef " << chefName << " destruktori" << endl;
}

int Chef::makeSalad(int eines)
{
    int annoksia = eines / 5;
    cout << "Chef "  << chefName << ":n varastossa on " << eines
         << " kpl kaalta, josta voi tehdä " << annoksia << " annosta salaattia" << endl;
    return 0;
}

int Chef::makeSoup(int eines)
{
    int annoksia = eines / 3;
    cout << "Chef " << chefName << ":n varastossa on " << eines
         << " kiloa keittopohjaa, josta voi tehdä " << annoksia << " annosta keittoa" << endl;
    return 0;
}
