#include <iostream>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()
using namespace std;

int game(int kerta) {
    srand(time(0));
    int randomNum = rand() % 21;
    int arvaus = 0;
    kerta = 0;
    cout << "arvaa mitä numeroa mietin välillä 0-20" << endl; //<< " [DEBUG:" << randomNum << "]" << endl;
    while(randomNum != arvaus){ //toistaa, kunnes arvaat oikein
        cin >> arvaus;
        if (cin.fail()) { //basic input sanitation
            cout<<"anna numero!"<<endl;
            cin.clear();
            cin.ignore();
            cin >> arvaus;
        }
        if (arvaus < 0 || arvaus > 20) {
            cout << "anna numero joka on välillä 0-20!" << endl;
            cin.clear();
            cin.ignore();
            cin >> arvaus; //don't try that again
        }
        if (arvaus < randomNum) {   //onko pienempi
            cout << "väärä numero, mietin SUUREMPAA numeroa. ";
            cout << "kokeile uudestaan!" << endl;
        }
        if (arvaus > randomNum) {   //onko suurempi
            cout << "väärä numero, mietin PIENEMPÄÄ numeroa! ";
            cout << "kokeile uudestaan!" << endl;
        }

        kerta ++; //keeping count
    }
    cout << "Oikein! ";
    return kerta; //palauttaa "main()" funktiolle luvun montako kertaa on arvattu
}
int main(){
    int kerta = 0;
    kerta = game(kerta); //ottaa "kerta" muuttujan "game()" funtiolta ja asettaa sen "kerta" muuttujan arvoksi
    cout << "Arvasit " << kerta << " kertaa";
    return 0;
    //terve
}
