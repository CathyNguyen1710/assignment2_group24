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

//Function to check if the account can be promote (qualified: return 3 or more item)
bool GuestAccount::promoteable() {
	//Check if the account have already return 3 or more item
	if (this->getTotalReturnItem() >= 3) {
		return true;
	}
	
	return false;
}
//Function to add item to the account list of rental
void GuestAccount::addRentalList(string id) {
	int pos = 0; //value to find the position for insert
	for (string itemID : this->listOfRentals) {
		if (id > itemID) {
			pos++; //increase the position if id is larger
		}
	}

	this->listOfRentals.insert(this->listOfRentals.begin() + pos, id); //insert to the list with the position
	this->setNoOfRentals(this->listOfRentals.size()); //set the number of rental to be the size of the list
}
//Function for renting an item
bool GuestAccount::rentItem(string id, ItemManager* itemList) {
	
	//Check if account already rent 2 item
	if (this->getNoOfRentals() >= 2) {
		cout << "\nThis account reached the maximum number of rentals allow" << endl;
		return false; //if account are currently rent 2 item then account cannot rent anymore
	}

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
		if (item->getId() == id) {
			//Check if the item is of 2-day loan type
			if (item->getLoanType() == "2-day") {
				cout << "\nGuest account cannot borrow items of 2-day loan type" << endl;
				return false; //if yes then the account cannot rent this item
			}
			
			//Check if item is out of stock
			if (item->getNoOfCopy() == 0) {
				cout << "\nItem is out of stock" << endl;
				return false; //if yes then the account cannot rent this item
			}
			
			item->setNoRented(item->getNoRented() + 1); //Increase the number of copy being rented
			item->setNoOfCopy(item->getNoOfCopy() - 1); //Decrease the number of copy available
			this->addRentalList(id); //add the item to the list of rental of the account

			//Prinout the fee and a message inform the user that the item had been rent
			cout << "\nThe rental Fee for the item " << id << ": " << item->getFee() << endl;
			cout << "The account " << this->getId() << " had succesfully rent the item " << id << " from the store\n";
			itemFound = true; //set the value to true if item is found
			return itemFound;
		}
	}

	//If item not found then prinout warning message
	if (!itemFound) {
		cout << "\nThe item with the id " << id << " is not found, and therefore cannot be rent by the account "<< this->getId() << endl;
	}

	return itemFound;
}
//Function for returning an item
bool GuestAccount::returnItem(string id, ItemManager* itemList) {
	int pos = 0; //int value for the position of the return item

	//Check if the item return is in the list of item rent by the account
	for (string itemID : this->listOfRentals) {
		if (itemID == id || itemID.substr(0,4) == id || itemID.substr(0, 4) == id.substr(0, 4)) { //if found then check the item id with the items in the shop
			if (itemList->returnItem(itemID) == true) { //if found then return the item
				this->setNoOfRentals(this->getNoOfRentals() - 1); //decrease the number of item rent of the account
				this->setTotalReturnItem(this->getTotalReturnItem() + 1); //increase the number of item return
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
string GuestAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}