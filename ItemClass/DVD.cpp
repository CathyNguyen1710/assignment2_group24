#include "DVD.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

DVD::DVD() {

}
DVD::DVD(string id, string title, string rentalType, string loanType, int noOfCopy, double fee, string genre):
	Item(id, title, rentalType, loanType, noOfCopy, fee) {
	this->genre = genre;
}

//Getter
string DVD::getGenre() {
	return this->genre;
}

//Setter
void DVD::setGenre(string genre) {
	this->genre = genre;
}

//Other function
void DVD::print() {
	cout << this->getId() << " : " << this->getTitle() << " - " << this->getRentalType() << " - " << this->getLoanType() << " - " << this->getNoOfCopy() << " - " << this->getFee() << " - " << this->getGenre() << endl;
}
string DVD::toString() {
	string toDB = this->getId() + "," + this->getTitle() + "," + this->getRentalType() + "," + this->getLoanType() + "," + to_string(this->getNoOfCopy()) + "," + to_string(this->getFee()) + "," + this->getGenre();
	return toDB;
}