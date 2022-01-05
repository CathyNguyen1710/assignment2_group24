#include "ItemManager.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

//Constructors (Read file)
ItemManager::ItemManager() {
	this->itemFile = "items.txt"; //Default constructor will read the file items.txt
	this->noOfItem = 0; //set the number of item to 0

	ifstream inStream(itemFile); //open file

	//Check if the file exist
	if (!inStream) {
		cerr << "File not found" << endl;
	}

	string line;
	vector<string> itemListData; //vector list to store data fields

	//While loop to read each line of data
	while (getline(inStream, line)) {
		istringstream stream(line);
		string fields;

		this->noOfItem++; //increase the size of array

		//While loop that get data fields seperate by ',' from the line and but it in the vector
		while (getline(stream, fields, ',')) {
			itemListData.push_back(fields);
		}

		//Check for the data Type to create the appropiate account and then push it inside the list of account
		if (itemListData[2] == "Game") {
			Item* newItem = new Game(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]));
			this->itemList.push_back(newItem);

		}
		else if (itemListData[2] == "Record") {
			Item* newItem = new Record(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]), itemListData[6]);
			this->itemList.push_back(newItem);
		}
		else if (itemListData[2] == "DVD") {
			Item* newItem = new DVD(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]), itemListData[6]);
			this->itemList.push_back(newItem);
		}

		itemListData.clear(); //clear the data in the vector to reused for the next line
	}

	inStream.close(); //close file after read
}
ItemManager::ItemManager(string itemFile) {
	this->itemFile = itemFile; //Read file base on the file name in param
	this->noOfItem = 0; //set the number of item to 0

	ifstream inStream(itemFile); //open file

	//Check if the file exist
	if (!inStream) {
		cerr << "File not found" << endl;
	}

	string line;
	vector<string> itemListData; //vector list to store data fields

	//While loop to read each line of data
	while (getline(inStream, line)) {
		istringstream stream(line);
		string fields;

		this->noOfItem++; //increase the size of array

		//While loop that get data fields seperate by ',' from the line and but it in the vector
		while (getline(stream, fields, ',')) {
			itemListData.push_back(fields);
		}

		//Check for the data Type to create the appropiate account and then push it inside the list of account
		if (itemListData[2] == "Game") {
			Item* newItem = new Game(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]));
			this->itemList.push_back(newItem);

		}
		else if (itemListData[2] == "Record") {
			Item* newItem = new Record(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]), itemListData[6]);
			this->itemList.push_back(newItem);
		}
		else if (itemListData[2] == "DVD") {
			Item* newItem = new DVD(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]), itemListData[6]);
			this->itemList.push_back(newItem);
		}

		itemListData.clear(); //clear the data in the vector to reused for the next line
	}

	inStream.close(); //close file after read
}

// destructor
ItemManager::~ItemManager()
{
	for (Item *item : this->itemList)
	{
		// remove all dynamically allocated memory for item pointers
		delete item;
	}
}

// Getter
vector<Item *> ItemManager::getItemList()
{
	return this->itemList;
}
int ItemManager::getNoOfItem()
{
	return this->noOfItem;
}
string ItemManager::getItemFile()
{
	return this->itemFile;
}

//Setter

void ItemManager::setItemList(vector<Item*> itemList) {
	this->itemList = itemList;
}
void ItemManager::setNoOfItem(int noOfItem)
{
	this->noOfItem = noOfItem;
}
void ItemManager::setItemFile(string itemFile)
{
	this->itemFile = itemFile;
}


//Other function
bool ItemManager::returnItem(string id) {
	return false;
}

bool ItemManager::addItem()
{
	this->noOfItem++;
	string title, rentalType, loanType, noOfCopy, fee, genre;

	// generate item id - code part (3 digits)
	ostringstream streamID;
	streamID << "I" << setw(3) << setfill('0') << this->noOfItem;
	int code = stoi((this->itemList.back())->getId().substr(1, 3));
	string id = code.str();

	id.append("-");

	string year = "";

	// helper to check if year is a number
	bool isNumber(const string &str)
	{
		size_t size = str.size();
		for (size_t t = 0; t < size; t++)
		{
			if (!isDigit(str.at(t)))
				return false;
		}
		return true;
	}

	// get year input
	while (true)
	{
		cout << ">> A valid Item ID has a 3-digit unique code followed by the published year! Ex: I001-2021. The ID has been generated automatically." << endl;
		cout << "\nEnter the published year (4 digits): ";
		cin >> year;
		cin.ignore();

		if (year.size() != 4)
		{
			cerr << "Please 4 digits for the year!" << endl;
			continue;
		}

		if (isNumber(year))
		{
			id += year;
			break;
		}
		else
		{
			cerr << "Please only enter number for published year!" << endl;
			year.clear();
		}
	}

	// get item tile
	while (true)
	{
		cout << "\nEnter the item's title: ";
		cin >> title;
		cin.ignore();
		break;
	}

	// get item rental type
	while (true)
	{
		cout << "\nEnter the item's rental type (Game, Record, DVD): ";
		cin >> rentalType;
		cin.ignore();

		if (rentalType == "Game" || rentalType == "Record" || rentalType == "DVD")
		{
			break;
		}
		else
		{
			cerr << "Please enter valid rental type!" << endl;
			year.clear();
		}
	}

	if (rentalType == "Record" || rentalType == "DVD")
	{
		// get item genre
		while (true)
		{
			cout << "\nEnter the item's genre: ";
			cin >> genre;
			cin.ignore();
			break;
		}
	}

	// get item loan type
	while (true)
	{
		cout << "\nEnter the item's loan type: ";
		cin >> loanType;
		cin.ignore();
		break;
	}

	// get item number of copy
	while (true)
	{
		cout << "\nEnter the item's number of copy: ";
		cin >> noOfCopy;
		cin.ignore();

		if (isNumber(noOfCopy))
		{
			break;
		}
		else
		{
			cerr << "Please enter valid number of copy!" << endl;
			noOfCopy.clear();
		}
	}

	// get item fee
	while (true)
	{
		cout << "\nEnter the item's fee: ";
		cin >> fee;
		cin.ignore();
		break;
	}

	switch (rentalType)
	{
	case "Game":
		Item *newItem = new Game(id, title, rentalType, loanType, stoi(noOfCopy), stod(fee));
		this->itemList.push_back(newItem);
		newItem->print();
		return true;
	case "Record":
		Item *newItem = new Record(id, title, rentalType, loanType, stoi(noOfCopy), stod(fee), genre);
		this->itemList.push_back(newItem);
		return true;
	case "DVD":
		Item *newItem = new DVD(id, title, rentalType, loanType, stoi(noOfCopy), stod(fee), genre);
		this->itemList.push_back(newItem);
		return true;
	default:
		return false;
	}
}

bool ItemManager::updateItem(string id)
{
	char choice = 0;
	Item *&item = new Item();
	for (Item *i : this->getItemList())
	{
		if (i->getId() == id)
		{
			item = i;
			break;
		}
	}
	string newValue = "";
	cout << "\nWhat do you want to update? (Note: you cannot change rental type!)" << endl;
	cout << "\t - "
		 << "Title: enter '1'." << endl;
	cout << "\t - "
		 << "Loan Type: enter '2'." << endl;
	cout << "\t - "
		 << "Rental Type: enter '3'." << endl;
	cout << "\t - "
		 << "Genre: enter '4' (Only applied for Record and DVD)." << endl;
	cout << "\t - "
		 << "Copies in stock: enter '5'." << endl;
	cout << "\t - "
		 << "Rental fee: enter '6'." << endl;
	cout << "\t - "
		 << "Enter '7' to exit!" << endl;

	// ask for user's choice, only break the loop if user enters correct letters
	while (true)
	{
		cout << "\nEnter your choice: ";
		cin >> choice;
		cin.ignore();

		switch (choice)
		{
		case "1":
		case "2":
		case "3":
		case "4":
		case "5":
		case "6":
			break;
		case "7":
			return false;
		default:
			cerr << "Invalid input! Please only enter: " << endl;
			// cerr << "'I' to update ID." << endl;
			cerr << "'T' to update Title." << endl;
			cerr << "'L' to update Loan type." << endl;
			cerr << "'G' to update Genre." << endl;
			cerr << "'C' to update Copies in stock." << endl;
			cerr << "'F' to update Rental fee. " << endl;
			cerr << "'E' to Exit! " << endl;
			choice = 0;
			break;
		}
	}

	string newId = item->getId();
	string newTitle = item->getTitle();
	string newLoanType = item->getLoanType();
	string newRentalType = newValue;
	int newNoOfCopy = item->getNoOfCopy();
	double newFee = item->getFee();

	switch (choice)
	{
	case '1':
		cout << "Enter new title: ";
		cin >> newValue;
		cin.ignore();
		item->setTitle(newValue);
		return true;
	case '2':
		cout << "\nEnter the new loan type: ";
		cin >> newValue;
		cin.ignore();
		item->setLoanType(newValue);
		return true;
  case '3':
		cout << "\nEnter the new rental type: ";
		cin >> newValue;
		cin.ignore();

		switch (newValue)
		{
		case "Game":
			deleteItem(itemList, newId);
			Item *newItem = new Game(newId, newTitle, newRentalType, newLoanType, newNoOfCopy, newFee);
			this->itemList.push_back(newItem);
			newItem->print();
			return true;
		case "Record":
			string newGenre = item->getGenre();
			if (!newGenre || newGenre.size() == 0)
			{
				cout << "\nEnter the new genre: ";
				cin >> newGenre;
				cin.ignore();
				break;
			}
			deleteItem(itemList, newId);
			Item *newItem = new Record(newId, newTitle, newRentalType, newLoanType, newNoOfCopy, newFee, newGenre);
			this->itemList.push_back(newItem);
			newItem->print();
			return true;
		case "DVD":
			string newGenre = item->getGenre();
			deleteItem(itemList, newId);
			Item *newItem = new DVD(newId, newTitle, newRentalType, newLoanType, newNoOfCopy, newFee, newGenre);
			this->itemList.push_back(newItem);
			newItem->print();
			return true;
		default:
			break;
		}
	case "4":
		cout << "\nEnter the new genre: ";
		cin >> newValue;
		cin.ignore();
		item->setGenre(newValue);
		return true;
	case '5':
		cout << "\nEnter the new number of copies in stock: ";
		cin >> newValue;
		cin.ignore();
		item->setNoOfCopy(stoi(newValue));
		return true;
	case '6':
		cout << "\nEnter the new rental fee: ";
		cin >> newValue;
		cin.ignore();
		item->setFee(stod(newValue));
		return true;
	default:
		return false;
	}

	return false;
}

bool ItemManager::deleteItem(string id)
{
	for (Item *item : this->itemList)
	{
		if (item->getId() == id)
		{
			this->itemList.erase(find(this->itemList.begin(), this->itemList.end(), item));
			delete item;
			return true;
		}
		else
		{
			cerr << "No matching ID found!" << endl;
			return false;
		}
	}
}
void ItemManager::displaySortedItemTitle() {
	//sort function by Title
	for (int i = 0; i < this->getItemList().size(); i++ ){
		for (int j = i+1; j < this->getItemList().size(); j++ ){
			if (this->getItemList()[i]->getTitle()>this->getItemList()[j]->getTitle()){
				string temp = this->getItemList()[i]->getTitle();

				this->getItemList()[i]->getTitle() = this->getItemList()[j]->getTitle();
				this->getItemList()[j]->getTitle() = temp;
			}
		}	
	}
	for (Item* item : this->getItemList()) {
		cout << item->getTitle();
	}

}

void ItemManager::displaySortedItemID() 
{
	//sort function by Title
	for (int i = 0; i < this->getItemList().size(); i++ ){
		for (int j = i+1; j < this->getItemList().size(); j++ ){
			if (this->getItemList()[i]->getId()>this->getItemList()[j]->getId()){
				string temp = this->getItemList()[i]->getId();
				this->getItemList()[i]->getId() = this->getItemList()[j]->getId();
				this->getItemList()[j]->getId() = temp;
			}
		}
	}
	for (Item* item : this->getItemList()) {
		cout << item->getId();
	}
}

void ItemManager::getAllNoStock() 
{
	cout << "sort by no of stock = 0" << endl;
}


void ItemManager::searchItem(string title) 
{
	for (Item* item : this->itemList)
	{
		if (item->getTitle() == title)
		{	
			cout << title;
			break;
		}
	}
}

void ItemManager::searchItem(string id) 
{
	for (Item* item : this->itemList)
	{
		if (item->getId() == id)
		{
			cout << id;
			break;
		}
	}
	
}


bool ItemManager::saveToFile() 
{
	ofstream outStream(this->itemFile);

	for (Item* item : this->itemList) 
	{
		outStream << item->toString() << endl;
	}
	return true;
}



//Function to save the itemList to a text file
bool ItemManager::saveToFile() {
	ofstream outStream(this->itemFile); //open the file used to get the information

	//loop through the array and add the item info to the appropriate format
	for (Item* item : this->itemList) {
		outStream << item->toString() << endl;
	}
	return true;
}

void ItemManager::getItemFromRental(string itemID) {

}

//
void ItemManager::print()
{
	cout << "print item manager" << endl;
}
