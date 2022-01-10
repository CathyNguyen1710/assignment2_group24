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

	//check the user's rent capacity
	if (this->getNoOfRentals() == 2) {
		cerr << "Error: Your rent capacity is reached." << endl;
		return false;
	}

	//check if the user is currently renting the item
	for (string rented : this->listOfRentals) {
		if (rented == id) {
			cerr << "Error: The item is already being rented by this account\n";
			return false;
		}
	}

	
	for (Item* item : itemList->getItemList()) {
		if (item->getId() == id) {
			if (item->getNoOfCopy() == 0) {							//check if item is still on stock
				cerr << "Error: the item is currently out of stock\n";
				return false; 
			}
			else if (item->getLoanType() == "2-day") {				//check loan type to see if the user can rent it with current Account type
				cerr << "Error: Guest account cannot borrow items with 2-day loan type\n";
				return false;
			}
			else {													//add item to rental list then change item's properties accordingly
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
bool GuestAccount::returnItem(string id, ItemManager* itemList) {
	return false;
}

string GuestAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}