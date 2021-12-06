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
	this->totalBorrowItem = 0;
	this->totalReturnItem = 0;
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
	if (this->getTotalReturnItem() >= 3) {
		cout << "You have meet the requirement to promote into VIP Account"<< endl;
		return true;
	}
	cout << "You have not meet the requirement to promote your account" << endl;
	return false;
}

//
void RegularAccount::print() {
	cout << "Regular print" << endl;
}
string RegularAccount::toString() {
	return "Regular to Database";
}