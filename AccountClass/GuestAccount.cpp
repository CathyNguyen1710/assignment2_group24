#include "GuestAccount.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Constructor
GuestAccount::GuestAccount() :Account() {

}
GuestAccount::GuestAccount(string id, string name, string address, string phone, int noOfRentals) :
	Account(id, name, address, phone, noOfRentals) {
	this->setTotalBorrowItem(0);
	this->setTotalReturnItem(0);
	this->totalVideoReturn = 0;
}

//Getter
int GuestAccount::getTotalVideoReturn() {
	return this->totalVideoReturn;
}

//Setter
void GuestAccount::setTotalVideoReturn(int totalVideoReturn) {
	this->totalVideoReturn = totalVideoReturn;
}

//Other function
bool GuestAccount::promoteable() {
	if (this->getTotalVideoReturn() >= 3) {
		cout << "You have meet the requirement to promote into Regular Account" << endl;
		return true;
	}
	cout << "You have not meet the requirement to promote your account" << endl;
	return false;
}
void GuestAccount::addRentalList(string id, ItemManager* itemList) {
	this->listOfRentals.push_back(id);

	this->setTotalBorrowItem(this->getTotalBorrowItem() + 1);

	for (Item* item : itemList->getItemList()) {
		if (item->getId() == id && item->getLoanType() == "Video") {
			this->setTotalVideoReturn(this->totalVideoReturn + 1);
		}
	}

	this->setNoOfRentals(this->listOfRentals.size());
}
void GuestAccount::addRentalList(string id) {
	this->listOfRentals.push_back(id);

	this->setTotalBorrowItem(this->getTotalBorrowItem() + 1);

	this->setNoOfRentals(this->listOfRentals.size());
}
bool GuestAccount::rentItem(string id, ItemManager* itemList) {
	if (this->getNoOfRentals() == 2) {
		cout << "This account reached the maximum number of rentals allow" << endl;
		return false;
	}

	for (string rentItem: this->getListOfRentals()) {
		if (rentItem == id) {
			cerr << "This account has already rented this item" << endl;
			return false;
		}
	}

	for (Item* item : itemList->getItemList()) {
		if (item->getId() == id) {
			if (item->getLoanType() == "2-day") {
				cerr << "Guest account cannot borrow items with 2-day loan type" << endl;
				return false;
			}
			else if (item->getNoOfCopy() == 0) {
				cerr << "Item is out of stock" << endl;
				return false;
			}
			else {
				item->setNoRented(item->getNoRented() + 1);
				item->setNoOfCopy(item->getNoOfCopy() - 1);
				this->addRentalList(id, itemList);
				return true;
			}
		}
	}

	cerr << "There is no item with matching id" << endl;
	return false;
}
bool GuestAccount::returnItem(string id, ItemManager* itemList) {
	return true;
}

//
void GuestAccount::print() {
	cout << "Guest print" << endl;
}
string GuestAccount::toString() {
	return "Guest to Database";
}