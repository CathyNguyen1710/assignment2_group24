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

//Function to check if the account can be promote (qualified: return 3 or more item)
bool VIPAccount::promoteable() {
	return false;
}
//Function to add item to the account list of rental
void VIPAccount::addRentalList(string id) {
	int pos = 0; //value to find the position for insert
	for (string itemID : this->listOfRentals) {
		if (id > itemID) {
			pos++; //increase the position if id is larger
		}
	}

	this->listOfRentals.insert(this->listOfRentals.begin() + pos, id); //insert to the list with the position

	this->setRewardPoint(this->rewardPoint + 10); //Increase the reward point everytime the account rent an item by 10

	this->setNoOfRentals(this->listOfRentals.size()); //set the number of rental to be the size of the list
}
//Function for renting an item
bool VIPAccount::rentItem(string id, ItemManager* itemList) {
	//check if the account already borrow the item
	for (string rentItem : this->listOfRentals) {
		if (rentItem == id) {
			cerr << "\nThis account has already rented this item" << endl;
			return false; //if yes then the account cannot rent the item again
		}
	}

	bool itemFound = false; //boolean value to check if the account id exsit in the system

	//Check if the item is in the list of item
	for (Item* item : itemList->getItemList()) {
		string itemID = item->getId();
		if (itemID == id || itemID.substr(0, 4) == id || itemID.substr(0, 4) == id.substr(0, 4)) {
			//Check if item is out of stock
			if (item->getNoOfCopy() == 0) {
				cout << "\nItem is out of stock" << endl;
				return false; //if yes then the account cannot rent this item
			}

			item->setNoRented(item->getNoRented() + 1); //Increase the number of copy being rented
			item->setNoOfCopy(item->getNoOfCopy() - 1); //Decrease the number of copy available
			this->addRentalList(id); //add the item to the list of rental of the account

			bool free = false; //boolean value to check if the account can rent an item for free

			//Check if account have accumulate 100 or more reward points
			if (this->getRewardPoint() >= 100) {
				string option;

				//If yes, ask if the customer want to used the points for a free rentals
				while (true) {
					printf("This current account has %d reward points. Do you want to use these reward points?\n1. Yes\n2. No\n", this->getRewardPoint());
					getline(cin, option);

					//trim string
					option.erase(option.find_last_not_of(" ") + 1);
					option.erase(0, option.find_first_not_of(" "));

					if (option == "1" || option == "yes") { //if yes, then set the boolean value to true and deduce 100 reward point from the account
						this->setRewardPoint(this->getRewardPoint() - 100);
						free = true;
						break;
					}
					else if (option == "2" || option == "no") { //if no, break out of the loop
						free = false;
						break;
					}
					else {
						cerr << "\nInvalid input, please try again" << endl; //Print error message if input is in valid
					}
				}

				//Prinout the fee and a message inform the user that the item had been rent
				if (free) { //if free the prinout fee = 0
					cout << "\nThe rental Fee for the item " << id << " : 0" << endl;
				}
				else { //if not the prinout fee = the item cost of rental
					cout << "\nThe rental Fee for the item " << id << ": " << item->getFee() << endl;
				}
				cout << "The account " << this->getId() << " had succesfully rent the item " << id << " from the store\n";

				itemFound = true; //set the value to true if item is found
				return itemFound;
			}
		}
	}

	//If item not found then prinout warning message
	if (!itemFound) {
		cout << "\nThe item with the id " << id << " is not found, and therefore cannot be rent by the account " << this->getId() << endl;
	}

	return itemFound;
}
//Function for returning an item
bool VIPAccount::returnItem(string id, ItemManager* itemList) {
	int pos = 0; //int value for the position of the return item

	//Check if the item return is in the list of item rent by the account
	for (string itemID : this->listOfRentals) {
		if (itemID == id || itemID.substr(0, 4) == id || itemID.substr(0, 4) == id.substr(0, 4)) { //if found then check the item id with the items in the shop
			if (itemList->returnItem(itemID) == true) { //if found then return the item
				this->setNoOfRentals(this->getNoOfRentals() - 1); //decrease the number of item rent of the account
				this->listOfRentals.erase(this->listOfRentals.begin() + pos); //remove the item from the rental list
				cout << "\nThe account " << this->getId() << " had succesfully return the item " << id << " to the store\n";
				return true;
			}
		}
		else {
			pos++; //if the item id not matched with the input id, increase the position 
		}
	}

	//Printout error message if the item with id rented is not found
	cerr << "The item specified was not rented" << endl;
	return false;
}

//Function that printout the information of the account in format ID : name - address - phone - number of rental - account type
string VIPAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}