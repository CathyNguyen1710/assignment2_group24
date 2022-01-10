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

//Other Function
//Function used to promote an account when meet the requirement
bool AccountManager::promoteAccount(string id) {
	bool matched = false; //boolean to check if the vector have the account with the id input 

	//Loop through the vector of accout to check for the account that match the id input
	for (Account* account : this->accountList) {
		if (account->getId() == id) { //if found a match
			bool promotable = account->promoteable(); //chech if the account is promotable
			if (promotable == true) {
				//If promotable, check if the account if of type Guest or type Regular
				if (account->getType() == "Guest") { //if the current account is type Guest -> promote to Regular
					RegularAccount* promoteAcc = new RegularAccount(account); //Create a new Regular account based on the info

					remove(this->accountList.begin(), this->accountList.end(), acc); //Remove the old account type from the vector

					this->accountList.push_back(promoteAcc); //Add the promote account

					cout << "\nAccount with id " << id << " is successfully promoted to Regular Account\n" << endl;

					matched = true; //set match value to true

					break;
				}
				else if (account->getType() == "Regular") { //if the current account is type Regular -> promote to VIP
					VIPAccount* promoteAcc = new VIPAccount(account); //Create a new Regular account based on the info

					remove(this->accountList.begin(), this->accountList.end(), acc); //Remove the old account type from the vector

					this->accountList.push_back(promoteAcc); //Add the promote account

					cout << "\nAccount with id " << id << " is successfully promoted to VIP Account\n" << endl;

					matched = true; //set match value to true

					break;
				}
			}
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



void AccountManager::displaySortedAccountName()
{
	//sort function by Name
	for (int i = 0; i < accountList.size(); i++ ){
		for (int j = i+1; j < accountList.size(); j++ ){
			if (accountList[i]->getName()>accountList[j]->getName()){
				string temp = accountList[i]->getName();
				accountList[i]->getName() = accountList[j]->getName();
				accountList[j]->getName() = temp;
			}
		}	
	}
	
	for (Account *ac : accountList)
	{
		cout << ac->toString();
	}
}

void AccountManager::displaySortedAccountID()
{
	//sort function by ID
	for (int i = 0; i < accountList.size(); i++ ){
		for (int j = i+1; j < accountList.size(); j++ ){
			if (accountList[i]->getId()>accountList[j]->getId()){
				string temp = accountList[i]->getId();
				accountList[i]->getId() = accountList[j]->getId();
				accountList[j]->getId() = temp;
			}
		}	
	}
	for (Account *ac : accountList)
	{
		cout << ac->toString();
	}
}
void AccountManager::getAccountByLevel(string level)
{
	cout<< "All accounts of level "<<level <<"is: "<< endl;
	for (Account *account : accountList)
	{
		if (account->getType()  == level){
			cout<< account<< endl;
		}
	}
}
void AccountManager::searchAccount(string name)
{
	for (Account *account : this->accountList)
	{
		if (account->getName() == name)
		{
			cout << account-> toString();
			break;
		}
	}
	cout << "search by name" << name << endl;
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


void AccountManager::print() {
	cout << "print acc manager" << endl;
}
