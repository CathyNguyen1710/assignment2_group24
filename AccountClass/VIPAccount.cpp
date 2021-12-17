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
	for (string rentItem : this->listOfRentals) {
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
				this->setNoOfRentals(this->getNoOfRentals() + 1);
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
	int pos = 0;
	for (string itemID : this->listOfRentals) {
		if (itemID == id) {
			if (itemList->returnItem(itemID) == true) {
				this->setNoOfRentals(this->getNoOfRentals() - 1);
				//this->setTotalBorrowItem(this->getTotalBorrowItem() + 1);
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
void VIPAccount::print() {
	cout << this->getId() << " " << this->getName() << " " << this->getAddress() << " " << this->getPhone() << " " << this->getNoOfRentals() << " " << this->getType() << endl;
}
string VIPAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}