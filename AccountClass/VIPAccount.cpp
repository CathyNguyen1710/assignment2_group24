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
	this->setTotalBorrowItem(0);
	this->setTotalReturnItem(0);
	this->rewardPoint = 0;
}
VIPAccount::VIPAccount(Account* account) {
	//constructor used when promoting an account
	this->setId(account->getId());
	this->setName(account->getName());
	this->setAddress(account->getAddress());
	this->setPhone(account->getPhone());
	this->setNoOfRentals(account->getNoOfRentals());
	this->setTotalBorrowItem(account->getTotalBorrowItem());
	this->setTotalReturnItem(account->getTotalReturnItem());
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
void VIPAccount::addRentalList(string id) {
	this->listOfRentals.push_back(id);

	this->setTotalBorrowItem(this->getTotalBorrowItem() + 1);

	this->setRewardPoint(this->rewardPoint + 10);

	this->setNoOfRentals(this->listOfRentals.size());
}
bool VIPAccount::rentItem(string id, ItemManager* itemList) {
	for (string rentItem : this->getListOfRentals()) {
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

				bool free = false;

				if (this->getRewardPoint() >= 100) {
					string option;

					while (true) {
						printf("This current account has %d reward points. Do you want to use these reward points?\n1. Yes\n2. No\n", this->getRewardPoint());
						getline(cin, option);

						//trim string
						option.erase(option.find_last_not_of(" ") + 1);
						option.erase(0, option.find_first_not_of(" "));
						
						if (option == "1") {
							this->setRewardPoint(this->getRewardPoint() - 100);
							free = true;
							break;
						}
						else if (option == "2") {
							free = false;
							break;
						}
						else {
							cerr << "Invalid input, please try again" << endl;
						}
					}
				}

				if (free) {
					cout << "Fee: 0" << endl;
				}
				else {
					cout << "Fee: " << item->getFee() << endl;
				}

				return true;
			}
		}
	}

	cerr << "There is no item with matching id" << endl;
	return false;
}
bool VIPAccount::returnItem(string id, ItemManager* itemList) {
	return true;
}

//
void VIPAccount::print() {
	cout << "VIP print";
}
string VIPAccount::toString() {
	return "VIP to Database";
}