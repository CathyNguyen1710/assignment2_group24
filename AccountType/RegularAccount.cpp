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