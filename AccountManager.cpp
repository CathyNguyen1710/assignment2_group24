#include "AccountManager.h"
#include "AccountClass/Account.h"
#include "AccountClass/GuestAccount.h"
#include "AccountClass/RegularAccount.h"
#include "AccountClass/VIPAccount.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

//Constructor
AccountManager::AccountManager() {
	this->customerFile = "customers.txt";
	this->noOfAccount = 0;

	ifstream inStream(customerFile);

	if (!inStream()) {
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

		if (customerListData.size == 6) {
			this->noOfAccount++;

			if (customerListData[5] == "Guest") {
				Account* newAccount = new GuestAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], customerListData[4]);

				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "Regular") {
				Account* newAccount = new RegularAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], customerListData[4]);

				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "VIP") {
				Account* newAccount = new VIPAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], customerListData[4]);

				this->accountList.push_back(newAccount);
			}
			else {
				cout << "error" << endl;
			}
		}
		else if (customerListData.size == 1) {
			this->accountList.back()->addRentalList(customerListData[0]);
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

	if (!inStream()) {
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

		if (customerListData.size == 6) {
			this->noOfAccount++;

			if (customerListData[5] == "Guest") {
				Account* newAccount = new GuestAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], customerListData[4]);

				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "Regular") {
				Account* newAccount = new RegularAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], customerListData[4]);

				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "VIP") {
				Account* newAccount = new VIPAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], customerListData[4]);

				this->accountList.push_back(newAccount);
			}
		}
		else if (customerListData.size == 1) {
			this->accountList.back()->addRentalList(customerListData[0]);
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

//Other function
bool AccountManager::addAccount() {
	return true;
}
bool AccountManager::updateAccount(string id) {
	return true;
}
bool AccountManager::saveToFile() {
	return true;
}
void AccountManager::displaySortedAccountName() {
	cout << "sort by name" << endl;
}
void AccountManager::displaySortedAccountID() {
	cout << "sort by id" << endl;
}
void AccountManager::getAccountByLevel(string level) {
	cout << "find by level" << endl;
}
void AccountManager::searchAccount(string name) {
	cout << "search by name" << endl;
}
void AccountManager::searchAccount(char* id) {
	cout << "search by id" << endl;
}

//
void AccountManager::print() {
	cout << "print acc manager" << endl;
}