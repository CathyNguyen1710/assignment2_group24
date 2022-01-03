#include "GuestAccount.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Constructor
GuestAccount::GuestAccount() :Account() {

}
GuestAccount::GuestAccount(string id, string name, string address, string phone, int noOfRentals, string type) :
	Account(id, name, address, phone, noOfRentals, type) {
	//this->setTotalBorrowItem(0);
	this->totalReturnItem = 0;
}

//Getter
int GuestAccount::getTotalReturnItem() {
	return this->totalReturnItem;
}

//Setter
void GuestAccount::setTotalReturnItem(int totalReturnItem) {
	this->totalReturnItem = totalReturnItem;
}

//Other function
bool GuestAccount::promoteable() {
	if (this->getTotalReturnItem() >= 3) {
		cout << "You have meet the requirement to promote into Regular Account" << endl;
		return true;
	}
	cout << "You have not meet the requirement to promote your account" << endl;
	return false;
}
void GuestAccount::addRentalList(string id) {
	this->listOfRentals.push_back(id);

	this->setNoOfRentals(this->listOfRentals.size());
}
bool GuestAccount::rentItem(string id, ItemManager* itemList) {
	return false;
}
bool GuestAccount::returnItem(string id, ItemManager* itemList) {
	return false;
}

string GuestAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}