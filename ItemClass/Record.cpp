#include "Record.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

Record::Record() {
    this->rentalType = "Record";
    this->genre = "";
}
// Constructor
Record::Record(string id, string title, string rentalType, string loanType, int noOfCopy, double fee, string genre):
Item(id, title, rentalType, loanType, noOfCopy, fee) {
    this->rentalType = rentalType;
    this->genre = genre;
}

Record::~Record() {
    
}

// Getter
string Record::getGenre() {
    return this->genre;
}

// Setter
void Record::setGenre(string genre) {
    this->genre = genre;
}

// Other functions
void Record::print() {
    cout << this->getId() << " : " << this->getTitle() << " - " << this->getRentalType() << " - " << this->getLoanType() << " - " << this->getNoOfCopy() << " - " << this->getFee() << " - " << this->getGenre() << endl;
}
string Record::toString() {
    string toDB = this->getId() + "," + this->getTitle() + "," + this->getRentalType() + "," + this->getLoanType() + "," + to_string(this->getNoOfCopy()) + "," + to_string(this->getFee()) + "," + this->getGenre();
    return toDB;
}