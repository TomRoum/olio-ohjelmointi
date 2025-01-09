#include <iostream>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()
using namespace std;
int game();


int main(){
    int kerta;
        kerta = game();

    game();
    cout << "arvasit " << kerta << "kertaa" << endl;
    return 0;
    }


int game() {
        srand(time(0));
    int randomNum = rand() % 21;
    int arvaus = 0;
    int kerta = 0;
    cout << "arvaa mitä numeroa mietin välillä 0-20" << " [DEBUG]: " << randomNum << endl;
    while(randomNum != arvaus){
    cin >> arvaus;

    if (arvaus < randomNum) {
            cout << "väärä numero, mietin suurempaa numeroa " << endl;
            cout << "kokeile uudestaan" << endl;
        }
        if (arvaus > randomNum) {
            cout << "väärä numero, mietin pienempäää numeroa " << endl;
            cout << "kokeile uudestaan" << endl;

        }
    kerta ++;
    }
    cout << "oikein! mietin suurempaa numeroa " << endl;
    return kerta;
}
