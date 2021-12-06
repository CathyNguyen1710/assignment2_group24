#include "VIPAccount.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//Constructor
VIPAccount::VIPAccount() {

}
VIPAccount::VIPAccount(string id, string name, string address, string phone, int noOfRentals) :
	Account(id, name, address, phone, noOfRentals) {
	this->rewardPoint = 0;
}
VIPAccount::VIPAccount(Account* account) {
	//constructor used when promoting an account
	this->setId(account->getId());
	this->setName(account->getName());
	this->setAddress(account->getAddress());
	this->setPhone(account->getPhone());
	this->setNoOfRentals(account->getNoOfRentals());
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
void VIPAccount::addRentalList(string item) {
	this->listOfRentals.push_back(item);

	this->setRewardPoint(this->rewardPoint + 10);

	this->setNoOfRentals(this->listOfRentals.size);
}

//
void VIPAccount::print() {
	cout << "VIP print";
}
string VIPAccount::toString() {
	return "VIP to Database";
}