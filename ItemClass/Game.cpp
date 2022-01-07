#include "Game.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

Game::Game() {

}
Game::Game(string id, string title, string rentalType, string loanType, int noOfCopy, double fee) :
	Item(id, title, rentalType, loanType, noOfCopy, fee) {
}

//Other function
void Game::print() {
	cout << this->getId() << " " << this->getTitle() << " " << this->getRentalType() << " " << this->getLoanType() << " " << this->getNoOfCopy() << " " << this->getFee() << endl;
}
string Game::toString() {
	string toDB = this->getId() + "," + this->getTitle() + "," + this->getRentalType() + "," + this->getLoanType() + "," + to_string(this->getNoOfCopy()) + "," + to_string(this->getFee());
	return toDB;
}