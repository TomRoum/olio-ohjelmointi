#include "game.h"
#include <iostream>

Game::Game (int mn)
{
    maxNumber = mn;
    playerGuess = 0;
    //cout << "Game konstruktori" << endl;
    //cout << "maxNumber" << maxNumber << endl;
    //cout << "randomNumber" << randomNumber << endl;
}
Game::~Game()
{
    cout << "game desktruktori" << endl;
}

void Game::play()
{
    cout << "Game play" << endl;
    srand(time(0));
    randomNumber = (rand()%maxNumber)+1;  //otetaan jakojäännös, nyt pitäisi olla välillä 1-20

    bool stayInLoop = true;
    numOfGuesses = 0;
    maxNumber = 0;
    cout << "Give max value" << endl;
    cin >> maxNumber;
    while(stayInLoop)
    {
        cout << "Give your guess between 1-" << maxNumber << endl;
        cin >> playerGuess;
        if(playerGuess == randomNumber)
        {
            cout << "Arvasit oikein luku oli = " << playerGuess << endl;
            stayInLoop = false;
        }
        else if(playerGuess<randomNumber)
        {
            cout << "Lukusi on liian pieni" << endl;
        }
        else
        {
            cout << "Lukusi on liian suuri" << endl;
        }
        numOfGuesses++;
    }
    printGameResult();

}
void Game::printGameResult()
{
    cout << "Arvauksien määrä: " << numOfGuesses << endl;
}

