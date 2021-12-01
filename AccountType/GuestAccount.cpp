#include "GuestAccount.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Constructor
GuestAccount::GuestAccount() {

}
GuestAccount::GuestAccount(string id, string name, string address, string phone, int noOfRentals) :
	Account(id, name, address, phone, noOfRentals) {
	this->totalBorrowItem = 0;
	this->totalReturnItem = 0;
}

//Getter
int GuestAccount::getTotalBorrowItem() {
	return this->totalBorrowItem;
}
int GuestAccount::getTotalReturnItem() {
	return this->totalReturnItem;
}

//Setter
void GuestAccount::setTotalBorrowItem(int totalBorrowItem) {
	this->totalBorrowItem = totalBorrowItem;
}
void GuestAccount::setTotalReturnItem(int totalReturnItem) {
	this->totalReturnItem = totalReturnItem;
}