#include "Record.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

Record::Record() {

}
Record::Record(string id, string title, string rentalType, string loanType, int noOfCopy, double fee, string genre) :
	Item(id, title, rentalType, loanType, noOfCopy, fee) {
	this->genre = genre;
}

//Getter
string Record::getGenre() {
	return this->genre;
}

//Setter
void Record::setGenres(string genre) {
	this->genre = genre;
}

//Other function
void Record::print() {
	cout << "print record" << endl;
}
string Record::toString() {
	return "Record to Database";
}