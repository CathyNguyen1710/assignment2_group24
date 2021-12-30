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

	//this->setTotalBorrowItem(this->getTotalBorrowItem() + 1);

	this->setNoOfRentals(this->listOfRentals.size());
}
bool GuestAccount::rentItem(string id, ItemManager* itemList) {
	if (this->getNoOfRentals() == 2) {
		cout << "This account reached the maximum number of rentals allow" << endl;
		return false;
	}

	for (string rentItem : this->listOfRentals) {
		if (rentItem == id) {
			cerr << "This account has already rented this item" << endl;
			return false;
		}
	}

	for (Item* item : itemList->getItemList()) {
		if (item->getId() == id) {
			if (item->getLoanType() == "2-day") {
				cout << "Guest account cannot borrow items with 2-day loan type" << endl;
				return false;
			}
			else if (item->getNoOfCopy() == 0) {
				cout << "Item is out of stock" << endl;
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
bool GuestAccount::returnItem(string id, ItemManager* itemList) {
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
/*void GuestAccount::print() {
	cout << this->getId() << " " << this->getName() << " " << this->getAddress() << " " << this->getPhone() << " " << this->getNoOfRentals() << " " << this->getType() << endl;
}*/
string GuestAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}