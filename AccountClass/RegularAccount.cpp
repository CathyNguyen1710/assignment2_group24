#include "RegularAccount.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Constructor
RegularAccount::RegularAccount() :Account() {

}
RegularAccount::RegularAccount(string id, string name, string address, string phone, int noOfRentals) :
	Account(id, name, address, phone, noOfRentals) {
	this->setTotalBorrowItem(0);
	this->setTotalReturnItem(0);
	this->totalVideoReturn = 0;
}
RegularAccount::RegularAccount(Account* account) {
	//constructor used when promoting an account
	this->setId(account->getId());
	this->setName(account->getName());
	this->setAddress(account->getAddress());
	this->setPhone(account->getPhone());
	this->setNoOfRentals(account->getNoOfRentals());
	this->setTotalBorrowItem(account->getTotalBorrowItem());
	this->setTotalReturnItem(account->getTotalReturnItem());
	this->totalVideoReturn = 0;
}

//Getter
int RegularAccount::getTotalVideoReturn() {
	return this->totalVideoReturn;
}

//Setter
void RegularAccount::setTotalVideoReturn(int totalVideoReturn) {
	this->totalVideoReturn = totalVideoReturn;
}

//Other function
bool RegularAccount::promoteable() {
	if (this->getTotalVideoReturn() >= 3) {
		cout << "You have meet the requirement to promote into VIP Account"<< endl;
		return true;
	}
	cout << "You have not meet the requirement to promote your account" << endl;
	return false;
}
void RegularAccount::addRentalList(string id, ItemManager* itemList) {
	this->listOfRentals.push_back(id);

	this->setTotalBorrowItem(this->getTotalBorrowItem() + 1);

	for (Item* item : itemList->getItemList()) {
		if (item->getLoanType() == "Video") {
			this->setTotalVideoReturn(this->totalVideoReturn + 1);
		}
	}

	this->setNoOfRentals(this->listOfRentals.size());
}
void RegularAccount::addRentalList(string id) {
	this->listOfRentals.push_back(id);

	this->setTotalBorrowItem(this->getTotalBorrowItem() + 1);

	this->setNoOfRentals(this->listOfRentals.size());
}
bool RegularAccount::rentItem(string id, ItemManager* itemList) {
	for (string rentItem : this->getListOfRentals()) {
		if (rentItem == id) {
			cerr << "This account has already rented this item" << endl;
			return false;
		}
	}
	
	for (Item* item : itemList->getItemList()) {
		if (item->getId() == id) {
			if (item->getNoOfCopy() == 0) {
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
bool RegularAccount::returnItem(string id, ItemManager* itemList) {
	return true;
}

//
void RegularAccount::print() {
	cout << "Regular print" << endl;
}
string RegularAccount::toString() {
	return "Regular to Database";
}