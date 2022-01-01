#include "VIPAccount.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Constructor
VIPAccount::VIPAccount() :Account() {

}
VIPAccount::VIPAccount(string id, string name, string address, string phone, int noOfRentals, string type) :
	Account(id, name, address, phone, noOfRentals, type) {
	//this->setTotalBorrowItem(0);
	this->rewardPoint = 0;
}
VIPAccount::VIPAccount(Account* account) {
	//constructor used when promoting an account
	this->setId(account->getId());
	this->setName(account->getName());
	this->setAddress(account->getAddress());
	this->setPhone(account->getPhone());
	this->setNoOfRentals(account->getNoOfRentals());
	this->setType("VIP");
	//this->setTotalBorrowItem(account->getTotalBorrowItem());
	this->rewardPoint = 0;
}

//Getter
int VIPAccount::getRewardPoint() {
	return this->rewardPoint;
}

//Setter
void VIPAccount::setRewardPoint(int rewardPoint) {
	this->rewardPoint = rewardPoint;
}

//Other function
bool VIPAccount::promoteable() {
	cout << "You cannot promote your account any further" << endl;
	return false;
}
void VIPAccount::addRentalList(string id) {
	this->listOfRentals.push_back(id);

	this->setRewardPoint(this->rewardPoint + 10);

	this->setNoOfRentals(this->listOfRentals.size());
}
bool VIPAccount::rentItem(string id, ItemManager* itemList) {
	cerr << "There is no item with matching id" << endl;
	return false;
}
bool VIPAccount::returnItem(string id, ItemManager* itemList) {
	cerr << "The item specified was not rented" << endl;
	return false;
}

//
/*void VIPAccount::print() {
	cout << this->getId() << " " << this->getName() << " " << this->getAddress() << " " << this->getPhone() << " " << this->getNoOfRentals() << " " << this->getType() << endl;
*/
string VIPAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}