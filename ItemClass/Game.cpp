#include "Game.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

Game::Game() {
    this->rentalType = "Game";
}

// Constructor
Game::Game(string id, string title, string rentalType, string loanType, int noOfCopy, double fee) :
    Item(id, title, rentalType, loanType, noOfCopy, fee) {
}

Game::~Game() {
    
}

// Other functions
void Game::print() {
    cout << this->getId() << " " << this->getTitle() << " " << this->getRentalType() << " " << this->getLoanType() << " " << this->getNoOfCopy() << " " << this->getFee() << endl;
}
string Game::toString() {
   string toDB = this->getId() + "," + this->getTitle() + "," + this->getRentalType() + "," + this->getLoanType() + "," + to_string(this->getNoOfCopy()) + "," + to_string(this->getFee()) + "," + this->getGenre();
   return toDB;
}