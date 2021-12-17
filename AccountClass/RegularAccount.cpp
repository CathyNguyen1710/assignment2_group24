#include "RegularAccount.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Constructor
RegularAccount::RegularAccount() :Account() {

}
RegularAccount::RegularAccount(string id, string name, string address, string phone, int noOfRentals, string type) :
	Account(id, name, address, phone, noOfRentals, type) {
	//this->setTotalBorrowItem(0);
	this->totalReturnItem = 0;
}
RegularAccount::RegularAccount(Account* account) {
	//constructor used when promoting an account
	this->setId(account->getId());
	this->setName(account->getName());
	this->setAddress(account->getAddress());
	this->setPhone(account->getPhone());
	this->setNoOfRentals(account->getNoOfRentals());
	this->setType("Regular");
	//this->setTotalBorrowItem(account->getTotalBorrowItem());
	this->totalReturnItem = 0;
}

//Getter
int RegularAccount::getTotalReturnItem() {
	return this->totalReturnItem;
}

//Setter
void RegularAccount::setTotalReturnItem(int totalReturnItem) {
	this->totalReturnItem = totalReturnItem;
}

//Other function
bool RegularAccount::promoteable() {
	if (this->getTotalReturnItem() >= 3) {
		cout << "You have meet the requirement to promote into VIP Account"<< endl;
		return true;
	}
	cout << "You have not meet the requirement to promote your account" << endl;
	return false;
}
void RegularAccount::addRentalList(string id) {
	this->listOfRentals.push_back(id);

	//this->setTotalBorrowItem(this->getTotalBorrowItem() + 1);

	this->setNoOfRentals(this->listOfRentals.size());
}
bool RegularAccount::rentItem(string id, ItemManager* itemList) {
	for (string rentItem : this->listOfRentals) {
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
				this->addRentalList(id);
				return true;
			}
		}
	}

	cerr << "There is no item with matching id" << endl;
	return false;
}
bool RegularAccount::returnItem(string id, ItemManager* itemList) {
	int pos = 0;
	for (string itemID : this->listOfRentals) {
		if (itemID == id) {
			if (itemList->returnItem(itemID) == true) {
				this->setNoOfRentals(this->getNoOfRentals() - 1);
				//this->setTotalBorrowItem(this->getTotalBorrowItem() + 1);
				this->setTotalReturnItem(this->getTotalReturnItem() + 1);
				this->listOfRentals.erase(this->listOfRentals.begin() + pos);
				return true;
			}
		}
		else {
			pos++;
		}
	}

	cerr << "The item specified was not rented" << endl;
	return false;
}

//
void RegularAccount::print() {
	cout << this->getId() << " " << this->getName() << " " << this->getAddress() << " " << this->getPhone() << " " << this->getNoOfRentals() << " " << this->getType() << endl;
}
string RegularAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}