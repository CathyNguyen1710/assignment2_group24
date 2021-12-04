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
void DVD::setGenres(string genre) {
	this->genre = genre;
}

//Other function
void DVD::print() {
	cout << "print dvd" << endl;
}
string DVD::toString() {
	return "DVD to Database";
}