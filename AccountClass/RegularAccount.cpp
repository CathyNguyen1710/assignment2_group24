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

	this->setNoOfRentals(this->listOfRentals.size());
}
bool RegularAccount::rentItem(string id, ItemManager* itemList) {

	//check if the user is currently renting the item
	for (string rented : this->listOfRentals) {
		if (rented == id) {
			cerr << "Error: The item is already being rented by this account\n";
			return false;
		}
	}

	for (Item* item : itemList->getItemList()) {
		if (item->getId() == id) {
			if (item->getNoOfCopy() == 0) {									//check if item is still on stock
				cerr << "Error: the item is currently out of stock\n";
				return false;
			}
			else {															//add item to rental list then change item's properties accordingly
				this->addRentalList(id);
				item->setNoOfCopy(item->getNoOfCopy() - 1);
				item->setNoRented(item->getNoRented() + 1);
				return true;
			}
		}
	}

	//print out error if no item was found with the input id
	cerr << "Error: No item in the system matches the requested id\n";
	return false;
}
bool RegularAccount::returnItem(string id, ItemManager* itemList) {

	return false;
}

string RegularAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}