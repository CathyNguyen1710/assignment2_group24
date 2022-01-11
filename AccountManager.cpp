#include "AccountManager.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;

//Constructors (Read file)
AccountManager::AccountManager() {
	this->customerFile = "customers.txt"; //Default constructor will read the file customers.txt
	this->noOfAccount = 0; //set the number of account to 0

	ifstream inStream(customerFile); //open file

	//Check if the file exist
	if (!inStream) {
		cerr << "File not found" << endl;
	}

	string line;
	vector<string> customerListData; //vector list to store data fields

	//While loop to read each line of data
	while (getline(inStream, line)) {
		istringstream stream(line);
		string fields;

		//While loop that get data fields seperate by ',' from the line and but it in the vector
		while (getline(stream, fields, ',')) {
			customerListData.push_back(fields);
		}

		//Check for the number of data fields get in the file
		if (customerListData.size() == 6) { //If there are 6 data fields
			this->noOfAccount++; //increase the size of array

			//Check for the data Type to create the appropiate account and then push it inside the list of account
			if (customerListData[5] == "Guest") {
				Account* newAccount = new GuestAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], 0, customerListData[5]);
				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "Regular") {
				Account* newAccount = new RegularAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], 0, customerListData[5]);
				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "VIP") {
				Account* newAccount = new VIPAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], 0, customerListData[5]);
				this->accountList.push_back(newAccount);
			}
		}
		else if (customerListData.size() == 1) { //If there only one data field --> id of the item in rental by the account
			this->accountList.back()->addRentalList(customerListData[0]); //add the item id to the rental list of each account
		}

		customerListData.clear(); //clear the data in the vector to reused for the next line
	}

	inStream.close(); //close file after read
}
AccountManager::AccountManager(string customerFile) {
	this->customerFile = customerFile; //Read file base on the file name in param
	this->noOfAccount = 0; //set the number of account to 0

	ifstream inStream(customerFile); //open file

	//Check if the file exist
	if (!inStream) {
		cerr << "File not found" << endl;
	}

	string line;
	vector<string> customerListData; //vector list to store data fields

	//While loop to read each line of data
	while (getline(inStream, line)) {
		istringstream stream(line);
		string fields;

		//While loop that get data fields seperate by ',' from the line and but it in the vector
		while (getline(stream, fields, ',')) {
			customerListData.push_back(fields);
		}

		//Check for the number of data fields get in the file
		if (customerListData.size() == 6) { //If there are 6 data fields
			this->noOfAccount++; //increase the size

			//Check for the data Type to create the appropiate account and then push it inside the list of account
			if (customerListData[5] == "Guest") {
				Account* newAccount = new GuestAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], 0, customerListData[5]);
				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "Regular") {
				Account* newAccount = new RegularAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], 0, customerListData[5]);
				this->accountList.push_back(newAccount);
			}
			else if (customerListData[5] == "VIP") {
				Account* newAccount = new VIPAccount(customerListData[0], customerListData[1], customerListData[2], customerListData[3], 0, customerListData[5]);
				this->accountList.push_back(newAccount);
			}
		}
		else if (customerListData.size() == 1) { //If there only one data field --> id of the item in rental by the account
			this->accountList.back()->addRentalList(customerListData[0]); //add the item id to the rental list of each account
		}

		customerListData.clear(); //clear the data in the vector to reused for the next line
	}

	inStream.close(); //close file after read
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

//Function used to promote an account when meet the requirement
bool AccountManager::promoteAccount(string id) {
	int pos = 0; //int to find the position of an item in the array
	bool matched = false; //boolean to check if the vector have the account with the id input 

	//Loop through the vector of accout to check for the account that match the id input
	for (Account* account : this->accountList) {
		if (account->getId() == id) { //if found a match
			bool promotable = account->promoteable(); //chech if the account is promotable
			if (promotable == true) {
				//If promotable, check if the account if of type Guest or type Regular
				if (account->getType() == "Guest") { //if the current account is type Guest -> promote to Regular
					RegularAccount* promoteAcc = new RegularAccount(account); //Create a new Regular account based on the info

					this->accountList.erase(this->accountList.begin() + pos); //Remove the old account type from the vector

					this->accountList.insert(this->accountList.begin() + pos, promoteAcc); //Add the promote account

					cout << "\nAccount with id " << id << " is successfully promoted to Regular Account\n" << endl;

					matched = true; //set match value to true

					break;
				}
				else if (account->getType() == "Regular") { //if the current account is type Regular -> promote to VIP
					VIPAccount* promoteAcc = new VIPAccount(account); //Create a new Regular account based on the info

					this->accountList.erase(this->accountList.begin() + pos); //Remove the old account type from the vector

					this->accountList.insert(this->accountList.begin() + pos, promoteAcc); //Add the promote account

					cout << "\nAccount with id " << id << " is successfully promoted to VIP Account\n" << endl;

					matched = true; //set match value to true

					break;
				}
			}
		}
		else { //if the id is not matched
			pos++; //increase the position
		}
	}

	return matched;
}

//Function to add a new account of type Guest
bool AccountManager::addAccount() {
	string input; //string for geting the input
	string name, address, phone, type; //string data fields to create a new account

	this->noOfAccount++; //get the size of the vector (number of account) and increase by 1 to create a new id

	//Set the id in the format Cxxx (where x is number from 0 to 9)
	ostringstream streamID;
	streamID << "C" << setw(3) << setfill('0') << this->noOfAccount;
	string id = streamID.str();

	//While true loop that ask for the name input
	while (true) {
		cout << "\nPlease enter your name: ";
		getline(cin, input);

		//trim string
		input.erase(input.find_last_not_of(" ") + 1);
		input.erase(0, input.find_first_not_of(" "));

		if (!input.empty()) { //Check if the input is empty or not
			name = input; //if not empty then set name to be input
			break;
		}
		else {
			cerr << "The field cannot be empty." << endl; //printout error message if field empty
		}
	}

	//While true loop that ask for the address input
	while (true) {
		cout << "\nPlease enter your address: ";
		getline(cin, input);

		//trim string
		input.erase(input.find_last_not_of(" ") + 1);
		input.erase(0, input.find_first_not_of(" "));

		if (!input.empty()) { //Check if the input is empty or not
			address = input;//if not empty then set address to be input
			break;
		}
		else {
			cerr << "The field cannot be empty." << endl; //printout error message if field empty
		}
	}

	//While true loop that ask for the phone number input
	while (true) {
		cout << "\nPlease enter your phone number: ";
		getline(cin, input);

		//trim string
		input.erase(input.find_last_not_of(" ") + 1);
		input.erase(0, input.find_first_not_of(" "));

		bool matched = true; //boolean value to check the phone number input

		if (!input.empty()) { //Check if the input is empty or not
			for (int i = 0; i < input.length(); i++) { //chech if the input contain character is number
				if (input[i] < 48 || input[i] > 57) {
					matched = false; //if countain, set the boolean value to be false and break the loop
					break;
				}
			}

			//Check if the input is correct
			if (matched == true) {
				phone = input; //if correct then set phone to be input
				break;
			}
			else {
				cerr << "This field can only have numbers." << endl; //printout error message if field contain anything but number or special character (+ or -)
			}
		}
		else {
			cerr << "The field cannot be empty." << endl; //printout error message if field empty
		}
	}

	//Create a new Guest account after getting all the require fields
	Account* newAccount = new GuestAccount(id, name, address, phone, 0, "Guest");
	this->accountList.push_back(newAccount); //add the account to the vector
	cout << "\nThe account " << newAccount->getId() << " with the information: \n\tName: " << newAccount->getName() << "\n\tAddress: " << newAccount->getAddress() << "\n\tPhone: " << newAccount->getPhone() << "\nhas been successfully added to the system\n";

	return true;
}
//Function to update an existed account in the system
bool AccountManager::updateAccount(string id) {

	Account* updateAcc = nullptr; //create a temporary account 
	string input, field, oldInfo;

	bool accountFound = false; //boolean value to check if the account match the id input exist

	//For loop to find the account that match the id input
	for (Account* acc : this->accountList) {
		if (acc->getId() == id) { //if found, then set the account to be the temporary acc for update
			updateAcc = acc;
			accountFound = true;
			break;
		}
	}

	//If no account that match the id is found then end the function and printout a message to inform the user
	if (!accountFound) {
		cout << "\nThe account does not exsist or have been deleted" << endl;
		return false;
	}

	string requestField = "\nWhich field you want to update on the Account " + updateAcc->getId()
		+ "\n1. Name"
		+ "\n2. Address"
		+ "\n3. Phone"
		+ "\n4. Exit";

	//If the account is found the start a while loop that will ask user what field they want to update
	while (true) {
		cout << requestField << endl;

		getline(cin, input); //get the input base for update field

		//trim string
		input.erase(input.find_last_not_of(" ") + 1);
		input.erase(0, input.find_first_not_of(" "));

		if (input == "1") { //input = 1 --> update customer name
			oldInfo = updateAcc->getName();

			//While true loop that ask for the name input
			while (true) {
				cout << "\nPlease enter the name you want to change to: ";
				getline(cin, field);

				//trim string
				field.erase(field.find_last_not_of(" ") + 1);
				field.erase(0, field.find_first_not_of(" "));

				if (!field.empty()) { //Check if the input is empty or not
					updateAcc->setName(field); //if not empty then set name to be input for new name and prinout appropriate message
					cout << "\nThe name of the account " << updateAcc->getId() << " had been succesfully change from " << oldInfo << " to " << updateAcc->getName() << endl;
					break;
				}
				else {
					cerr << "The field cannot be empty." << endl; //printout error message if field empty
				}
			}
		}
		else if (input == "2") { //input = 2 --> update customer address
			oldInfo = updateAcc->getAddress();

			//While true loop that ask for the address input
			while (true) {
				cout << "\nPlease enter the address you want to change to: ";
				getline(cin, field);

				//trim string
				field.erase(field.find_last_not_of(" ") + 1);
				field.erase(0, field.find_first_not_of(" "));

				if (!field.empty()) { //Check if the input is empty or not
					updateAcc->setAddress(field); //if not empty then set address to be input for new address and prinout appropriate message
					cout << "\nThe address of the account " << updateAcc->getId() << " had been succesfully change from " << oldInfo << " to " << updateAcc->getAddress() << endl;
					break;
				}
				else {
					cerr << "The field cannot be empty." << endl; //printout error message if field empty
				}
			}
		}
		else if (input == "3") { //input = 2 --> update customer phone
			oldInfo = updateAcc->getPhone();

			//While true loop that ask for the phone number input
			while (true) {
				cout << "\nPlease enter the phone number you want to change to: ";
				getline(cin, field);

				//trim string
				field.erase(field.find_last_not_of(" ") + 1);
				field.erase(0, field.find_first_not_of(" "));

				bool matched = true; //boolean value to check the phone number input

				if (!input.empty()) { //Check if the input is empty or not
					for (int i = 0; i < input.length(); i++) { //chech if the input contain character is number
						if (input[i] < 48 || input[i] > 57) {
							matched = false; //if countain, set the boolean value to be false and break the loop
							break;
						}
					}

					////Check if the input is correct
					if (matched == true) {
						updateAcc->setPhone(field); //if not empty then set phone number to be input for new address and prinout appropriate message
						cout << "\nThe phone number of the account " << updateAcc->getId() << " had been succesfully change from " << oldInfo << " to " << updateAcc->getPhone() << endl;
						break;
					}
					else {
						cerr << "This field can only have numbers." << endl; //printout error message if field contain anything but number
					}
				}
				else {
					cerr << "The field cannot be empty." << endl; //printout error message if field empty
				}
			}
		}
		else if (input == "4") { //If user want to stop update the fields
			cout << "\nExit\n" << endl;
			break; //Break the loop
		}
		else {
			cerr << "\nInvalid input." << endl;
		}
	}

	return true;
}

//Function display list of account sorted by name in alphabetical order
void AccountManager::displaySortedAccountName() {

	vector<Account*> accByName = this->accountList; //created a copy vector of the accountList

	//Sort the copied array and swap the value
	for (int i = 0; i < accByName.size() - 1; i++) {
		for (int j = i + 1; j < accByName.size(); j++) {
			if (accByName[i]->getName() > accountList[j]->getName()) {
				string temp = accByName[i]->getName();
				accByName[i]->getName() = accByName[j]->getName();
				accByName[j]->getName() = temp;
			}
		}
	}

	//Printout the array
	if (accByName.size() > 0) {
		cout << "\nID   : Name - Address - Phone Number - Number of Rental - Account Type\n";
		for (Account* acc : accByName) {
			acc->print();
			for (string itemRented : acc->getListOfRentals()) {
				cout << itemRented << endl;
			}
		}
	}
	else {
		cerr << "The store currently have no customer" << endl;
	}
}
//Function display list of account sorted by id in ascending order
void AccountManager::displaySortedAccountID() {

	vector<Account*> accById = this->accountList; //created a copy vector of the accountList

	//Sort the copied array and swap the value
	for (int i = 0; i < accById.size() - 1; i++) {
		for (int j = i + 1; j < accById.size(); j++) {
			if (accById[i]->getId() > accountList[j]->getId()) {
				string temp = accById[i]->getId();
				accById[i]->getId() = accById[j]->getId();
				accById[j]->getId() = temp;
			}
		}
	}

	//Printout the array
	if (accById.size() > 0) {
		cout << "\nID   : Name - Address - Phone Number - Number of Rental - Account Type\n";
		for (Account* acc : accById) {
			acc->print();
			for (string itemRented : acc->getListOfRentals()) {
				cout << itemRented << endl;
			}
		}
	}
	else {
		cerr << "The store currently have no customer" << endl;
	}
}
//Function display list of account sorted with the same level (same type)
void AccountManager::getAccountByLevel(string level) {

	vector<Account*> accountLevel; //created a temporary array to contain the account

	//Check the account is of the same type with the input level. If so, add the item to the temporary array
	for (Account* acc : this->accountList) {
		if (acc->getType() == level) {
			accountLevel.push_back(acc);
		}
	}

	//if the array is not empty then prinout the array
	if (accountLevel.size() > 0) {
		cout << "\nID   : Name - Address - Phone Number - Number of Rental - Account Type\n";
		for (Account* acc : accountLevel) {
			acc->print();
			for (string itemRented : acc->getListOfRentals()) {
				cout << itemRented << endl;
			}
		}
	}
	else { //if the array is empty, prinout a message saying that the store currently have no account of that level
		cerr << "The store currently have no customer of type " << level << endl;
	}
}
//Function display list of account that contain the name in searching
void AccountManager::searchAccount(string name) {

	vector<Account*> searchAccName;  //created a temporary array to contain the account

	//loop through the array and find the account that contain the string that user want to find
	for (Account* acc : this->accountList) {
		if (acc->getName().find(name) != string::npos) {
			searchAccName.push_back(acc);
		}
	}

	//if the array is not empty then prinout the array
	if (searchAccName.size() > 0) {
		cout << "ID   : Name - Address - Phone Number - Number of Rental - Account Type\n";
		for (Account* acc : searchAccName) {
			acc->print();
			for (string itemRented : acc->getListOfRentals()) {
				cout << itemRented << endl;
			}
		}
	}
	else { //if no account found, printout a message said that no account is found
		cout << "Cannot find the specified account" << endl;
	}
}
void AccountManager::searchAccount(char *id)
{
	vector<string> itemIDList;
	vector<string> itemIDNumber;
	
	for (Account *account : this->accountList)
	{
		itemIDList.push_back(account->getId());
	}
	for (auto ID: itemIDList)
	{
		itemIDNumber.push_back(ID.substr(1,3)+ID.substr(5, 8));
	}
	cout << "The ID search result is: "<<endl;
	for (auto ID: itemIDNumber)
	{
		if (ID.find(id))
		{
			cout << "I"+ ID.substr(0,2) + "-" +ID.substr(3,6) << endl;
		}
	}
}
/*//Function display an account with the id input
void AccountManager::searchAccount(const char* id) {

	bool accFound = false; //boolean value to check if the account in searching exist
	Account* searchAccId = nullptr; //create a temporary account

	for (Account* acc : this->accountList) { //loop through the array to find the account that match the id input
		if (strcmp(acc->getId().c_str(), id) == 0) { //if found, set the temporary Accounnt as the acc, and set the found value to true
			searchAccId = acc;
			accFound = true;
			break;
		}
	}

	if (accFound == false) { //if no account found, prinout a message saying no account match the input
		cout << "Cannot find the specified account" << endl;
	}
	else { //if found, prinout the account info
		cout << "\nID   : Name - Address - Phone Number - Number of Rental - Account Type\n";
		searchAccId->print();
		for (string itemRented : searchAccId->getListOfRentals()) {
			cout << itemRented << endl;
		}
	}
}*/

//Function to save the accountList to a text file
bool AccountManager::saveToFile() {
	ofstream outStream(this->customerFile); //open the file used to get the information

	//loop through the array and add the account info to the appropriate format
	for (Account* account : this->accountList) {
		outStream << account->toString() << endl;
		//for each accout, loop through their list of rental and add the item list to the file
		for (string itemID : account->getListOfRentals()) {
			outStream << itemID << endl;
		}
	}
	return true;
}

//Function to display list of item in rental of 1 account
vector<Item*> AccountManager::displayAllRental(string accountID, ItemManager* itemList) {

	vector<Item*> listOfItem; //created a temporary array to contain the item information

	cout << "\nID        : Title - Rental Type - Loan Duration - Available Copy - Rental Fee - Genre (for Record and DVD)\n";
	for (Account* account : this->accountList) { //loop through the account list to find the account that currently returning the item
		if (account->getId() == accountID) { //if found, get the account list of rental item and get each item information
			for (string itemID : account->getListOfRentals()) {
				listOfItem.push_back(itemList->getItemFromRental(itemID));
			}
		}
	}

	return listOfItem;
}
//Function to display list of item that is available for rent of 1 account
vector<Item*> AccountManager::displayAllAvailable(string accountID, ItemManager* itemList) {

	vector<Item*> availableItem = itemList->getItemList(); //created a temporary array that is a copy of the itemList

	for (Account* account : this->accountList) { //loop through the account list to find the account that currently renting the item
		if (account->getId() == accountID) { //if found, get the account list of rental item then compare the item in the rental list with the temp list
			for (string itemID : account->getListOfRentals()) {
				for (Item* item : availableItem) {
					if (item->getId() == itemID || item->getId().substr(0, 4) == itemID || item->getId().substr(0, 4) == itemID.substr(0, 4) || item->getNoOfCopy() == 0) { //if the item have the same id with the one in rental or is out of stock
						remove(availableItem.begin(), availableItem.end(), item); //remove the item from the temp array
						availableItem.resize(availableItem.size() - 1); //resize the array
					}
				}
			}
			break;
		}
	}

	//prinout the item available for renting
	cout << "\nID        : Title - Rental Type - Loan Duration - Available Copy - Rental Fee - Genre (for Record and DVD)\n";
	for (Item* item : availableItem) {
		item->print();
	}

	return availableItem;
}
//Function to display the account that have meet the requirement for promotion
vector<Account*> AccountManager::displayPromotableAccount() {

	vector<Account*> promatableAcc; //created a temporary array to contain the account that eligible for promotion
	bool promotable;

	for (Account* account : this->accountList) {
		promotable = account->promoteable(); //check if the account is promotable
		if (promotable) { //if so, add the info into the temprary list
			promatableAcc.push_back(account);
		}
	}

	//prinout the account that can be promote
	if (promatableAcc.size() > 0) {
		cout << "\nID   : Name - Address - Phone Number - Number of Rental - Account Type\n";
		for (Account* account : promatableAcc) {
			account->print();
		}
	}
	else {
		cout << "\nThere are currently no account that have meet the requirement for promotion\n";
	}

	return promatableAcc;
}

