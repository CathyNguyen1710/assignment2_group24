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

//Other function
bool GuestAccount::promoteable() {
	if (this->getTotalReturnItem() >= 3) {
		cout << "You have meet the requirement to promote into Regular Account" << endl;
		return true;
	}
	cout << "You have not meet the requirement to promote your account" << endl;
	return false;
}
void GuestAccount::addRentalList(string id) {
	this->listOfRentals.push_back(id);

	this->setNoOfRentals(this->listOfRentals.size());
}
bool GuestAccount::rentItem(string id, ItemManager* itemList) {
	
	//will figure out how to change from ItemManager to Item later


	/*if (this->listOfRentals.size() >= 2) {
		cout << "Your rent capacity limit is already reached, please return an item to rent more" << endl;
		return false;
	}
	else if (itemList->getLoanType() == "2-day") {
		cout << "Your rent capacity limit is already reached, please return an item to rent more" << endl;
		return false;
	}
	else if (itemList->getNoOfCopy() != 0) {
		cout << "Your rent capacity limit is already reached, please return an item to rent more" << endl;
		return false;
	} else {
		this->addRentalList(id);
		return true;
	}*/

	return false;
}


bool GuestAccount::returnItem(string id, ItemManager* itemList) 
{
	int pos = 0;
	bool Itemrented = false;
	if (this->listOfRentals.empty())
	{
		cout << " You have not rented any item(s) " << endl;
	}
	else{
		Itemrented = true;
		if (Itemrented)
		{
		for (string itemID : this->listOfRentals)
		{
				if (itemID == id) 
				{
					if (itemList->returnItem(itemID) == true) 
					{
						this->setNoOfRentals(this->getNoOfRentals() - 1);
						this->listOfRentals.erase(this->listOfRentals.begin() + pos);
						cout << " Item returned " << endl;
						return true;
					}
				}
				else {
					pos++;
				}
			}
		}
	}
	return false;
}

string GuestAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}
