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

//Destructor
ItemManager::~ItemManager() {
	for (Item* item : this->itemList) {
		//remove all dynamically allocated memory for item pointers
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

void ItemManager::setItemList(vector<Item *> itemList)
{
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

//Function for when returning an item
bool ItemManager::returnItem(string id) {
	//Loop through the item list to find the item with id match the id in param
	for (Item* item : this->getItemList()) {
		string itemID = item->getId();
		if (itemID == id || itemID.substr(0, 4) == id || itemID.substr(0, 4) == id.substr(0, 4)) { //check if the item id match
			//if matched
			item->setNoOfCopy(item->getNoOfCopy() + 1); //increase the number of copy
			item->setNoRented(item->getNoRented() - 1); //decrease the number if rented copy
			return true;
		}
	}

	return false; //if no item found matched the id then return false
}

//  Helper
bool isDigit(const char& ch)
{
	return (ch >= 48 && ch <= 57);
}

// helper to check if year is a number
bool isNumber(const string& str)
{
	size_t size = str.size();
	for (size_t t = 0; t < size - 1; t++)
	{
		if (!isdigit(str.at(t)))
			return false;
	}
	return true;
}

bool ItemManager::addItem()
{
	this->noOfItem++;
	string title, rentalType, loanType, noOfCopy, fee, genre;

	// generate item id - code part (3 digits)
	ostringstream streamID;
	streamID << "I" << setw(3) << setfill('0') << this->noOfItem;

	string year = "";

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
			streamID << "-" << year;
			break;
		}
		else
		{
			cerr << "Please only enter number for published year!" << endl;
			year.clear();
		}

	}

	string id = streamID.str();


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
			rentalType.clear();
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
		cout << "\nEnter the item's loan type (2-day, 1-week): ";
		cin >> loanType;
		cin.ignore();

		if (loanType == "2-day" || loanType == "1-week")
		{
			break;
		}
		else
		{
			cerr << "Please enter valid loan type!" << endl;
			loanType.clear();
		}
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

	if (rentalType == "Game")
	{
		Item *newItem = new Game(id, title, rentalType, loanType, stoi(noOfCopy), stod(fee));
		this->itemList.push_back(newItem);
		newItem->print();
		return true;
	}
	else if (rentalType == "Record")
	{
		Item *newItem = new Record(id, title, rentalType, loanType, stoi(noOfCopy), stod(fee), genre);
		this->itemList.push_back(newItem);
		newItem->print();
		return true;
	}
	else if (rentalType == "DVD")
	{
		Item *newItem = new DVD(id, title, rentalType, loanType, stoi(noOfCopy), stod(fee), genre);
		this->itemList.push_back(newItem);
		newItem->print();
		return true;
	}
	else
	{
		return false;
	}
}

bool ItemManager::updateItem(string id)
{
	//create a temporary account 
	Item* updateItem = nullptr;
	string field = "";

	int pos = 0; //int value for the position of the update item in the list
	bool itemFound = false; //boolean value to check if the item match the id input exist

	//For loop to find the item that match the id input
	for (Item* item : this->itemList) {
		if (item->getId() == id || item->getId().substr(0, 4) == id) { //if found, then set the item to be the temporary item for update
			updateItem = item;
			itemFound = true;
			break;
		}
		else {
			pos++;
		}
	}

	//If no item that match the id is found then end the function and printout a message to inform the user
	if (!itemFound) {
		cout << "\nThe item does not exsist or have been deleted" << endl;
		return false;
	}

	char choice = '0';
	
	string newValue = "";
	cout << "\nWhat do you want to update? (Note: you cannot change rental type!)" << endl;
	cout << "\t - "
		<< "Title: enter '1'." << endl;
	cout << "\t - "
		<< "Loan Type: enter '2'." << endl;
	cout << "\t - "
		<< "Genre: enter '3' (Only applied for Record and DVD)." << endl;
	cout << "\t - "
		<< "Copies in stock: enter '4'." << endl;
	cout << "\t - "
		<< "Rental fee: enter '5'." << endl;
	cout << "\t - "
		<< "Rental type: enter '6'." << endl;
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
		case '1':
			
			cout << "Enter new title: ";
			cin >> newValue;
			cin.ignore();
			if (!newValue.empty()) {
				string oldTitle = updateItem->getTitle();
				updateItem->setTitle(newValue);
				cout << "\nThe title of the item " << updateItem->getId() << " had been succesfully change from " << oldTitle << " to " << updateItem->getTitle() << endl;
				return true;
			}
		case '2':
			cout << "\nEnter the new loan type (2-day, 1-week): ";
			cin >> newValue;
			cin.ignore();
			
			if (newValue == "2-day" || newValue == "1-week") {
				string oldLoanType = updateItem->getLoanType();
				if (newValue == "2-day") {
					updateItem->setLoanType("2-day");
					cout << "\nThe type of loan of the item " << updateItem->getId() << " had been succesfully change from " << oldLoanType << " to " << updateItem->getLoanType() << endl;
					return true;
				}
				else if (newValue == "1-week") {
					updateItem->setLoanType("1-week");
					cout << "\nThe type of loan of the item " << updateItem->getId() << " had been succesfully change from " << oldLoanType << " to " << updateItem->getLoanType() << endl;
					return true;
				}
				else {
					cerr << "\nInvalid input." << endl; //prinout error message if the input is invalid
				}
			}
		case '3':
			cout << "\nEnter the new genre: ";
			cin >> newValue;
			cin.ignore();
			
			if (updateItem->getRentalType() == "Game") { //If the updated item is of Game type, prinout message warn user that Game dont have a genre
				cout << "\nThis item is of type Game and have no genre for it\n" << endl;
				return false;
			}
			else {
				string oldGenre = updateItem->getGenre();
				updateItem->setGenre(newValue);
				cout << "\nThe genre of the item " << updateItem->getId() << " had been succesfully change from " << oldGenre << " to " << updateItem->getGenre() << endl;
				return true;
			}
		case '4':
			cout << "\nEnter the new number of copies in stock: ";
			cin >> newValue;
			cin.ignore();
			if (!newValue.empty()) {
				int oldNoOfCopy = updateItem->getNoOfCopy();
				updateItem->setNoOfCopy(stoi(newValue));
				cout << "\nThe title of the item " << updateItem->getId() << " had been succesfully change from " << oldNoOfCopy << " to " << updateItem->getNoOfCopy() << endl;
				return true;
			}
		case '5':
			cout << "\nEnter the new rental fee: ";
			cin >> newValue;
			cin.ignore();
			return true;
			if (!newValue.empty()) {
				double oldRentalFee = updateItem->getFee();
				updateItem->setFee(stod(newValue));
				cout << "\nThe title of the item " << updateItem->getId() << " had been succesfully change from " << oldRentalFee << " to " << updateItem->getFee() << endl;
				return true;
			}
		case '6':
			cout << "\nEnter the new rental type (Game, Record, DVD): ";
			cin >> newValue;
			cin.ignore();

			//if input is valid (1, 2, 3 or Game, Record, DVD) then create a temporary Item of the choosen type and replace it with the updatedItem in the vector at the updatedItem position
			if (newValue == "Game" || newValue == "Record" || newValue == "DVD") {
				string oldRentalType = updateItem->getRentalType();
				string inputRental;

				Item* update;

				if (newValue == "Game") {
					update = new Game(updateItem->getId(), updateItem->getTitle(), "Game", updateItem->getLoanType(), updateItem->getNoOfCopy(), updateItem->getFee());
					this->itemList.erase(this->itemList.begin() + pos);
					this->itemList.insert(this->itemList.begin() + pos, update);
					cout << "\nThe type of rental of the item " << updateItem->getId() << " had been succesfully change from " << oldRentalType << " to " << updateItem->getRentalType() << endl;
					updateItem = update;
					return true;
				}
				else if (newValue == "Record" || newValue == "DVD") {
					string inputForGenre, genre;

					//Check if the updated item of type Record or DVD
					if (oldRentalType == "Record" || oldRentalType == "DVD") {
						//If true, then get the genre from the updatedItem
						genre = updateItem->getGenre();
					}
					else {
						//If false (updatedItem is originally a Game item), then ask the user for a Genre input
						while (true) {
							cout << "\nPlease enter the genre of this item: ";

							getline(cin, inputForGenre);

							//trim string
							inputForGenre.erase(inputForGenre.find_last_not_of(" ") + 1);
							inputForGenre.erase(0, inputForGenre.find_first_not_of(" "));

							if (!inputForGenre.empty()) { //Check if the input is empty or not
								genre = inputForGenre; //if not then set the genre as the input
								break;
							}
							else {
								cerr << "The field cannot be empty." << endl; //prinout error message if the input is empty
							}
						}
					}

					//Replace the old item with the new item create using the old item information and the updated information
					if (newValue == "Record") {
						update = new Record(updateItem->getId(), updateItem->getTitle(), "Record", updateItem->getLoanType(), updateItem->getNoOfCopy(), updateItem->getFee(), genre);
						this->itemList.erase(this->itemList.begin() + pos);
						this->itemList.insert(this->itemList.begin() + pos, update);
						cout << "\nThe type of rental of the item " << updateItem->getId() << " had been succesfully change from " << oldRentalType << " to " << updateItem->getRentalType() << endl;
						updateItem = update;
						return true;
					}
					else if (newValue == "DVD") {
						update = new DVD(updateItem->getId(), updateItem->getTitle(), "DVD", updateItem->getLoanType(), updateItem->getNoOfCopy(), updateItem->getFee(), genre);
						this->itemList.erase(this->itemList.begin() + pos);
						this->itemList.insert(this->itemList.begin() + pos, update);
						cout << "\nThe type of rental of the item " << updateItem->getId() << " had been succesfully change from " << oldRentalType << " to " << updateItem->getRentalType() << endl;
						updateItem = update;
						return true;
					}
					break;
				}
				else {
					cerr << "\nInvalid input." << endl; //prinout error message if the input is invalid
				}
			}
		case '7':
			return false;
		default:
			cerr << "Invalid input! Please only enter: " << endl;
			cerr << "Title: enter '1'." << endl;
			cerr << "Loan Type: enter '2'." << endl;
			cerr << "Genre: enter '3' (Only applied for Record and DVD)." << endl;
			cerr << "Copies in stock: enter '4'." << endl;
			cerr << "Rental fee: enter '5'." << endl;
			cerr << "Rental type: enter '6'." << endl;
			cerr << "Enter '7' to exit!" << endl;
			choice = 0;
			break;
		}
	}

	cerr << "No matching ID found!" << endl;
	return false;
}

bool ItemManager::deleteItem(string id)
{
	for (int i = 0; i < this->itemList.size(); i++)
	{
		Item *item = this->itemList[i];
		if (item->getId() == id)
		{
			delete item;
			this->itemList.erase(this->itemList.begin() + i);
			return true;
		}
	}
	cerr << "No matching ID found!" << endl;
	return false;
}

//Function display list of item sorted by title in alphabetical order
void ItemManager::displaySortedItemTitle() {

	vector<Item*> itemByTitle = this->itemList; //created a copy vector of the itemList

	//Sort the copied array by alphabetical order
	for (int i = 0; i < itemByTitle.size() - 1; i++)
	{
		for (int j = i + 1; j < itemByTitle.size(); j++)
		{
			if (itemByTitle[i]->getTitle() > itemByTitle[j]->getTitle())
			{
				Item* temp = itemByTitle[i];
				itemByTitle[i] = itemByTitle[j];
				itemByTitle[j] = temp;
			}
		}
	}

	//Printout the array
	if (itemByTitle.size() > 0) {
		cout << "\nID        : Title - Rental Type - Loan Duration - Available Copy - Rental Fee - Genre (for Record and DVD)\n";
		for (Item* item : itemByTitle) {
			item->print();
		}
	}
	else {
		cerr << "There is currently no item in the store" << endl;
	}
}
//Function display list of item sorted by id in ascending order
void ItemManager::displaySortedItemID() {

	vector<Item*> itemById = this->itemList; //created a copy vector of the itemList

	//Sort the copied array in ascending order
	for (int i = 0; i < itemById.size() - 1; i++)
	{
		for (int j = i + 1; j < itemById.size(); j++)
		{
			if (itemById[i]->getId() > itemById[j]->getId())
			{
				Item* temp = itemById[i];
				itemById[i] = itemById[j];
				itemById[j] = temp;
			}
		}
	}

	//Printout the array
	if (itemById.size() > 0) {
		cout << "\nID        : Title - Rental Type - Loan Duration - Available Copy - Rental Fee - Genre (for Record and DVD)\n";
		for (Item* item : itemById) {
			item->print();
		}
	}
	else {
		cerr << "There is currently no item in the store" << endl;
	}
}
//Function display list of item that is out of stock
void ItemManager::getAllNoStock() {

	vector<Item*> outOfStock; //create a temporary array to contain all the item that is out of stock

	//Check if item have stock = 0. If so, add the item to the temporary array
	for (Item* item : this->itemList) {
		if (item->getNoOfCopy() == 0) {
			outOfStock.push_back(item);
		}
	}

	//if the array is not empty then prinout the array
	if (outOfStock.size() > 0) {
		cout << "\nID        : Title - Rental Type - Loan Duration - Available Copy - Rental Fee - Genre (for Record and DVD)\n";
		for (Item* item : outOfStock) {
			item->print();
		}
	}
	else { //if the array is empty, prinout a message saying that no item is out of stock
		cerr << "There is currently no item that is out of stock in the store" << endl;
	}
}
//Function display list of item that contain the title in searching
void ItemManager::searchItem(string title) {

	vector<Item*> searchItemTitle; //create a temporary array to contain all the item in searching

	//loop through the array and find the item that contain the string that user want to find
	for (Item* item : this->itemList) {
		if (item->getTitle().find(title) != string::npos) {
			searchItemTitle.push_back(item); //add it to the temp array if matched
		}
	}

	//if found, printout all the item in the array
	if (searchItemTitle.size() > 0) {
		cout << "\nID        : Title - Rental Type - Loan Duration - Available Copy - Rental Fee - Genre (for Record and DVD)\n";
		for (Item* item : searchItemTitle) {
			item->print();
		}
	}
	else {//if no item found, printout a message said that no item is found
		cout << "\nCannot find the specified item" << endl;
	}
}
//Function display  an item with the id input
void ItemManager::searchItem(const char* id) {

	bool itemFound = false; //boolean value to check if the item in searching exist
	Item* searchItemId = nullptr; //create a temporary item

	for (Item* item : this->itemList) { //loop through the array to find the item that match the id input (can be of type Ixxx or Ixxx-yyyy)
		if (strcmp(item->getId().c_str(), id) == 0 || strcmp(item->getId().substr(0, 4).c_str(), id) == 0) { //if found, set the temporary Item as the item, and set the found value to true
			searchItemId = item;
			itemFound = true;
			break;
		}
	}

	if (itemFound == false) { //if no item found, prinout a message saying no item match the input
		cout << "\nCannot find the specified iten" << endl;
	}
	else {  //if found, prinout the item info
		cout << "\nID        : Title - Rental Type - Loan Duration - Available Copy - Rental Fee - Genre (for Record and DVD)\n";
		searchItemId->print();
	}
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

//Function for when an customer trying to return an item
Item* ItemManager::getItemFromRental(string itemID) {
	Item* itemFound = nullptr;  //create a temporary item

	for (Item* item : this->itemList) { //loop through the array to find the item that match the id input (can be of type Ixxx or Ixxx-yyyy)
		if (item->getId() == itemID || item->getId().substr(0, 4) == itemID || item->getId().substr(0, 4) == itemID.substr(0,4)) { //if found then set temp item as item and prinout the item info
			itemFound = item;
			itemFound->print();
			break;
		}
	}

	return itemFound;
}