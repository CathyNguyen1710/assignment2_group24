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

	//check if the user is currently renting the item
	for (string rented : this->listOfRentals) {
		if (rented == id) {
			cerr << "Error: The item is already being rented by this account\n";
			return false;
		}
	}

	bool usedRewardPoint = false;


	for (Item* item : itemList->getItemList()) {
		if (item->getId() == id) {
			if (item->getNoOfCopy() == 0) {									//check if item is still on stock
				cerr << "Error: the item is currently out of stock\n";
				return false;
			}
			else {															////add item to rental list then change item's properties accordingly	
				this->addRentalList(id);
				this->setNoOfRentals(this->getNoOfRentals() + 1);
				item->setNoOfCopy(item->getNoOfCopy() - 1);
				item->setNoRented(item->getNoRented() + 1);

				if (this->getRewardPoint() >= 100) {				//check if user has enough reward points to begind the process
					string option;
					for (;;) {		//set up infinite loop
						// Guide user to use the reward point system
						cout << "Your account currently has "<<this->getRewardPoint()<<" reward points. Do you want to use these reward points?\n1.Yes\n2.No\n";
						cout << "Please select an option by typing in 1 or 2: ";
						getline(cin, option);
						cout << endl;

						if (option == "1") {		//if user chosed Yes
							this->setRewardPoint(this->getRewardPoint() - 100);
							usedRewardPoint = true;
							break;
						}
						else if (option == "2") {	//if user chosed No
							usedRewardPoint = false;
							break;
						}
						else {						//print out error and let customer retry when they typed in Invalid input
							cerr << "Error: Invalid input, please choose again by typing ONLY 1 or 2 accordingly to your option" << endl;
						}
					}
				}

				//check if User used reward point
				if (usedRewardPoint) {							
					cout << "Your fee is: 0" << endl;
				}
				else {
					cout << "Your Fee is: " << item->getFee() << endl;
				}

				return true;
			}
		}
	}

	//print out error if no item was found with the input id
	cerr << "Error: No item in the system matches the requested id\n";
	return false;
}


bool VIPAccount::returnItem(string id, ItemManager* itemList) 
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

string VIPAccount::toString() {
	string toDB = this->getId() + "," + this->getName() + "," + this->getAddress() + "," + this->getPhone() + "," + to_string(this->getNoOfRentals()) + "," + this->getType();
	return toDB;
}