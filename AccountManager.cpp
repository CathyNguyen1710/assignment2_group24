#include "AccountManager.h"

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
	string input;
	string name, address, phone, type;

	this->noOfAccount++;

	ostringstream streamID;
	streamID << "C" << setw(3) << setfill('0') << this->noOfAccount;
	string id = streamID.str();

	while (true) {
		cout << "Please enter your name: ";
		getline(cin, input);

		//trim string
		input.erase(input.find_last_not_of(" ") + 1);
		input.erase(0, input.find_first_not_of(" "));

		if (!input.empty()) {
			name = input;
			break;
		}
	}

	while (true) {
		cout << "Please enter your address: ";
		getline(cin, input);

		//trim string
		input.erase(input.find_last_not_of(" ") + 1);
		input.erase(0, input.find_first_not_of(" "));

		if (!input.empty()) {
			address = input;
			break;
		}
	}

	while (true) {
		cout << "Please enter your phone number: ";
		getline(cin, input);

		//trim string
		input.erase(input.find_last_not_of(" ") + 1);
		input.erase(0, input.find_first_not_of(" "));

		bool matched = true;

		if (!input.empty()) {
			for (int i = 0; i < input.length(); i++) {
				if (input[i] < 32 || input[i] > 57) {
					matched = false;
					break;
				}
			}

			if (matched == true) {
				phone = input;
				break;
			}
		}
	}

	Account* newAccount = new GuestAccount(id, name, address, phone, 0, "Guest");
	this->accountList.push_back(newAccount);
	newAccount->print();

	return true;
}
bool AccountManager::updateAccount(string id) {

	Account* updateAcc = nullptr;
	string input, field;

	for (Account* acc : this->accountList) {
		if (acc->getId() == id) {
			updateAcc = acc;
			break;
		}
		else {
			cout << "The account does not exsist or have been deleted" << endl;
			return false;
		}
	}

	string requestField = "Which field you want to update on the Account " + updateAcc->getId()
		+ "\n1. Name"
		+ "\n2. Address"
		+ "\n3. Phone"
		+ "\n4. Exit";

	while (true) {
		cout << requestField << endl;

		getline(cin, input);

		//trim string
		input.erase(input.find_last_not_of(" ") + 1);
		input.erase(0, input.find_first_not_of(" "));

		if (input == "1") {
			while (true) {
				cout << "Please enter the name you want to change to: ";
				getline(cin, field);

				//trim string
				field.erase(field.find_last_not_of(" ") + 1);
				field.erase(0, field.find_first_not_of(" "));

				if (!field.empty()) {
					updateAcc->setName(field);
					break;
				}
			}
		}
		else if (input == "2") {
			while (true) {
				cout << "Please enter the address you want to change to: ";
				getline(cin, field);

				//trim string
				field.erase(field.find_last_not_of(" ") + 1);
				field.erase(0, field.find_first_not_of(" "));

				if (!field.empty()) {
					updateAcc->setAddress(field);
					break;
				}
			}
		}
		else if (input == "3") {
			while (true) {
				cout << "Please enter the phone number you want to change to: ";
				getline(cin, field);

				//trim string
				field.erase(field.find_last_not_of(" ") + 1);
				field.erase(0, field.find_first_not_of(" "));

				bool matched = true;

				if (!field.empty()) {
					for (int i = 0; i < field.length(); i++) {
						if (field[i] < 32 || field[i] > 57) {
							matched = false;
							break;
						}
					}

					if (matched == true) {
						updateAcc->setPhone(field);
						break;
					}
				}
			}
		}
		else if (input == "4") {
			cout << "break" << endl;
			break;
		}
		else {
			cerr << "Error message" << endl;
		}
	}

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

bool AccountManager::saveToFile() {
	ofstream outStream(this->customerFile);

	for (Account* account : this->accountList) {
		outStream << account->toString() << endl;
		for (string itemID: account->getListOfRentals()) {
			outStream << itemID << endl;
		}
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
					if (item->getId() == itemID || item->getNoOfCopy() == 0) {
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