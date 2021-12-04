#include "RegularAccount.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Constructor
RegularAccount::RegularAccount() {

}
RegularAccount::RegularAccount(string id, string name, string address, string phone, int noOfRentals) :
	Account(id, name, address, phone, noOfRentals) {
	this->totalBorrowItem = 0;
	this->totalReturnItem = 0;
}
RegularAccount::RegularAccount(Account* account) {
	//constructor used when promoting an account
	this->setId(account->getId());
	this->setName(account->getName());
	this->setAddress(account->getAddress());
	this->setPhone(account->getPhone());
	this->setNoOfRentals(account->getNoOfRentals());
	this->totalBorrowed = 0;
	this->totalReturned = 0;
}

//Getter
int RegularAccount::getTotalBorrowItem() {
	return this->totalBorrowItem;
}
int RegularAccount::getTotalReturnItem() {
	return this->totalReturnItem;
}

//Setter
void RegularAccount::setTotalBorrowItem(int totalBorrowItem) {
	this->totalBorrowItem = totalBorrowItem;
}
void RegularAccount::setTotalReturnItem(int totalReturnItem) {
	this->totalReturnItem = totalReturnItem;
}

//Other function
bool RegularAccount::promoteable() {
	return true;
}

//
void RegularAccount::print() {
	cout << "Regular print" << endl;
}
string RegularAccount::toString() {
	return "Regular to Database";
}