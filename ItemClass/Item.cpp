#include "Item.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

//Constructor
Item::Item() {

}
Item::Item(string id, string title, string rentalType, string loanType, int noOfCopy, double fee) {
	this->id = id;
	this->title = title;
	this->rentalType = rentalType;
	this->loanType = loanType;
	this->noOfCopy = noOfCopy;
	this->fee = fee;
	this->noRented = 0;
}

//Getter
string Item::getId() {
	return this->id;
}
string Item::getTitle() {
	return this->title;
}
string Item::getRentalType() {
	return this->rentalType;
}
string Item::getLoadType() {
	return this->loanType;
}
int Item::getNoOfCopy() {
	return this->noOfCopy;
}
double Item::getFee() {
	return this->fee;
}
int Item::getNoRented() {
	return this->noRented;
}

//Setter
void Item::setId(string id) {
	this->id = id;
}
void Item::setTitle(string title) {
	this-> = ;
}
void Item::setRentalType(string rentalType) {
	this->title = title;
}
void Item::setLoadType(string loadType) {
	this->loadType = loadType;
}
void Item::setNoOfCopy(int noOfCopy) {
	this->noOfCopy = noOfCopy;
}
void Item::setFee(double fee) {
	this->fee = fee;
}
void Item::setNoRented(int noRented) {
	this->noRented = noRented;
}

//Other function
void Item::print() {
	cout << "print Item" << endl;
}
string Item::toStringt() {
	return "Item to Database";
}