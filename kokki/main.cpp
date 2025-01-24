#include "chef.h"
#include "italianchef.h"
#include <iostream>

using namespace std;

int main()
{
    //antaa c_oliolle nimen Matti, joka on oikeasti muuttuja: string name
    Chef c_olio("Matti");
    //antaa c_olio :n funktiolle makeSalad arvon
    c_olio.makeSalad(15);
    //antaa c_olio :n funktiolle makeSoup arvon
    c_olio.makeSoup(30);

    //antaa i_oliolle nimen Luigi, joka on oikeasti muuttuja: string name
    ItalianChef i_olio("Luigi");
    //antaa i_olio :n funktiolle makeSalad arvon
    i_olio.makeSalad(18);
    //tässä voisi taas se soupfuntio
    //kysyy salasanaa askSecret funtiota varten
    cout << "Anna salasana: ";
    string pw;
    cin >>pw;
    i_olio.askSecret(pw,20,48);

    return 0;
}
