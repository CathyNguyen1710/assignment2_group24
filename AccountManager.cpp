#include "AccountManager.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;
//Constructor
AccountManager::AccountManager() {
	this->customerFile = "customers.txt";
	this->noOfAccount = 0;

	ifstream inStream(customerFile);

	if (!inStream) {
		cerr << "Error" << endl;
	}

	string line;
	vector<string> customerListData;

	while (getline(inStream, line)) {
		istringstream stream(line);
		string fields;
		while (getline(stream, fields, ',')) {
			customerListData.push_back(fields);
		}

		if (customerListData.size() == 6) {
			this->noOfAccount++;

			if (customerListData[5] == "Guest") {
				Account* newAccount = new GuestAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], stoi(customerListData[4]), customerListData[5]);
				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "Regular") {
				Account* newAccount = new RegularAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], stoi(customerListData[4]), customerListData[5]);
				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "VIP") {
				Account* newAccount = new VIPAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], stoi(customerListData[4]), customerListData[5]);
				this->accountList.push_back(newAccount);
			}
			else {
				cout << "error" << endl;
			}
		}
		else if (customerListData.size() == 1) {
			this->accountList.back()->addRentalList(customerListData[0]);
			//cout << customerListData[0] << endl;
		}
		else {
			cout << "error" << endl;
		}
		
		customerListData.clear();
	}

	inStream.close();
}
AccountManager::AccountManager(string customerFile) {
	this->customerFile = customerFile;
	this->noOfAccount = 0;

	ifstream inStream(customerFile);

	if (!inStream) {
		cerr << "Error" << endl;
	}

	string line;
	vector<string> customerListData;

	while (getline(inStream, line)) {
		istringstream stream(line);
		string fields;
		while (getline(stream, fields, ',')) {
			customerListData.push_back(fields);
		}

		if (customerListData.size() == 6) {
			this->noOfAccount++;

			if (customerListData[5] == "Guest") {
				Account* newAccount = new GuestAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], stoi(customerListData[4]), customerListData[5]);
				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "Regular") {
				Account* newAccount = new RegularAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], stoi(customerListData[4]), customerListData[5]);
				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "VIP") {
				Account* newAccount = new VIPAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], stoi(customerListData[4]), customerListData[5]);
				this->accountList.push_back(newAccount);
			}
		}
		else if (customerListData.size() == 1) {
			this->accountList.back()->addRentalList(customerListData[0]);
			//cout << customerListData[0] << endl;
		}
		else {
			cout << "error" << endl;
		}

		customerListData.clear();
	}

	inStream.close();
}

//Destructor
AccountManager::~AccountManager() {
	for (Account* account : this->accountList) {
		delete account;
	}
}

//Getter
vector<Account*> AccountManager::getAccountList() {
	return this->accountList;
}
int AccountManager::getNoOfAccount() {
	return this->noOfAccount;
}
string AccountManager::getCustomerFile() {
	return this->customerFile;
}

//Setter
void AccountManager::setAccountList(vector<Account*> accountList) {
	this->accountList = accountList;
}
void AccountManager::setNoOfAccount(int noOfAccount) {
	this->noOfAccount = noOfAccount;
}
void AccountManager::setCustomerFile(string customerFile) {
	this->customerFile = customerFile;
}

//Other Function
bool AccountManager::promoteAccount(string id) {
	int pos = 0;
	bool matched = false;
	for (Account* account : this->accountList) {
		if (account->getId() == id) {
			bool promotable = account->promoteable();
			if (promotable == true && account->getType() == "Guest") {
				RegularAccount* promoteAcc = new RegularAccount(account);

				this->accountList.erase(this->accountList.begin() + pos);

				this->accountList.insert(this->accountList.begin() + pos, promoteAcc);

				cout << "Account with id " << id << " is successfully promoted to Regular Account" << endl;

				matched = true;
				return matched;

				break;
			}
			else if (promotable == true && account->getType() == "Regular") {
				VIPAccount* promoteAcc = new VIPAccount(account);

				this->accountList.erase(this->accountList.begin() + pos);

				this->accountList.insert(this->accountList.begin() + pos, promoteAcc);

				cout << "Account with id " << id << " is successfully promoted to VIP Account" << endl;

				matched = true;
				return matched;

				break;
			}
		}
		else {
			pos++;
		}
	}

	if (matched == false) {
		cerr << "There is no account with matching id" << endl;
	}
	return matched;
}

bool AccountManager::addAccount() {
	return true;
}
bool AccountManager::updateAccount(string id) {
	return true;
}
void AccountManager::displaySortedAccountName()
{
	
	for (Account *accounts : accountList)
	{
		sort(accounts->getName().begin(), accounts->getName().end());
	}
	for (Account *ac : accountList)
	{
		cout << ac->toString();
	}
}

void AccountManager::displaySortedAccountID()
{
	
	for (Account *accounts : accountList)
	{
		sort(accounts->getId().begin(), accounts->getId().end());
	}
	for (Account *ac : accountList)
	{
		cout << ac->toString();
	}
}
void AccountManager::getAccountByLevel(string level)
{

	cout << "find by level" << endl;
}
void AccountManager::searchAccount(string name)
{

	for (Account *account : this->accountList)
	{
		if (account->getName() == name)
		{
			cout << account->toString();
			break;
		}
	}
	cout << "search by name" << name << endl;
}
void AccountManager::searchAccount(char *id)
{

	for (Account *account : this->accountList)
	{
		if (account->getId() == id)
		{
			cout << account->toString();
			break;
		}
	}
}


bool AccountManager::saveToFile() {
	ofstream outStream(this->customerFile);

	for (Account* account : this->accountList) {
		outStream << account->toString() << endl;
	}
	return true;
}

void AccountManager::displayAll() {
	for (Account* account : this->getAccountList()) {
		account->print();
	}
}
void AccountManager::displayAllRental(string accountID, ItemManager* itemList) {
	for (Account* account : this->accountList) {
		if (account->getId() == accountID) {
			for (string itemID : account->getListOfRentals()) {
				itemList->getItemFromRental(itemID);
			}
		}
	}
}
void AccountManager::displayAllAvailable(string accountID, ItemManager* itemList) {
	vector<Item*> availableItem = itemList->getItemList();

	for (Account* account : this->accountList) {
		if (account->getId() == accountID) {
			int pos = 0;
			for (string itemID : account->getListOfRentals()) {
				for (Item* item : availableItem) {
					if (item->getId() == itemID) {
						remove(availableItem.begin(), availableItem.end(), item);
						availableItem.resize(availableItem.size() - 1);
					}
				}
			}
			break;
		}
	}

	for (Item* item : availableItem) {
		item->print();
	}
}

void AccountManager::print() {
	cout << "print acc manager" << endl;
}