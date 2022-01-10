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
ItemManager::ItemManager()
{
	this->itemFile = "items.txt"; //Default constructor will read the file items.txt
	this->noOfItem = 0;			  //set the number of item to 0

	ifstream inStream(itemFile); //open file

	//Check if the file exist
	if (!inStream)
	{
		cerr << "File not found" << endl;
	}

	string line;
	vector<string> itemListData; //vector list to store data fields

	//While loop to read each line of data
	while (getline(inStream, line))
	{
		istringstream stream(line);
		string fields;

		this->noOfItem++; //increase the size of array

		//While loop that get data fields seperate by ',' from the line and but it in the vector
		while (getline(stream, fields, ','))
		{
			itemListData.push_back(fields);
		}

		//Check for the data Type to create the appropiate account and then push it inside the list of account
		if (itemListData[2] == "Game")
		{
			Item *newItem = new Game(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]));
			this->itemList.push_back(newItem);
		}
		else if (itemListData[2] == "Record")
		{
			Item *newItem = new Record(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]), itemListData[6]);
			this->itemList.push_back(newItem);
		}
		else if (itemListData[2] == "DVD")
		{
			Item *newItem = new DVD(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]), itemListData[6]);
			this->itemList.push_back(newItem);
		}

		itemListData.clear(); //clear the data in the vector to reused for the next line
	}

	inStream.close(); //close file after read
}
ItemManager::ItemManager(string itemFile)
{
	this->itemFile = itemFile; //Read file base on the file name in param
	this->noOfItem = 0;		   //set the number of item to 0

	ifstream inStream(itemFile); //open file

	//Check if the file exist
	if (!inStream)
	{
		cerr << "File not found" << endl;
	}

	string line;
	vector<string> itemListData; //vector list to store data fields

	//While loop to read each line of data
	while (getline(inStream, line))
	{
		istringstream stream(line);
		string fields;

		this->noOfItem++; //increase the size of array

		//While loop that get data fields seperate by ',' from the line and but it in the vector
		while (getline(stream, fields, ','))
		{
			itemListData.push_back(fields);
		}

		//Check for the data Type to create the appropiate account and then push it inside the list of account
		if (itemListData[2] == "Game")
		{
			Item *newItem = new Game(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]));
			this->itemList.push_back(newItem);
		}
		else if (itemListData[2] == "Record")
		{
			Item *newItem = new Record(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]), itemListData[6]);
			this->itemList.push_back(newItem);
		}
		else if (itemListData[2] == "DVD")
		{
			Item *newItem = new DVD(itemListData[0], itemListData[1], itemListData[2], itemListData[3], stoi(itemListData[4]), stod(itemListData[5]), itemListData[6]);
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

//Other function
bool ItemManager::returnItem(string id)
{
	return false;
}

bool ItemManager::addItem()
{
	this->noOfItem++;
	string title, rentalType, loanType, noOfCopy, fee, genre;

	// generate item id - code part (3 digits)
	ostringstream streamID;
	streamID << "I" << setw(3) << setfill('0') << this->noOfItem;
	//    cout << "Stream ID: " << streamID;
	//    int code = stoi((this->itemList.back())->getId().substr(1, 3));
	string id = streamID.str();

	id.append("-");

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
			id += year;
			cout << "Item's ID: " << id;
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
	char choice = '0';
	Item *item = new Item();
	for (Item *i : this->getItemList())
	{
		if (i->getId() == id)
		{
			item = i;
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
				 << "Enter '6' to exit!" << endl;

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
					item->setTitle(newValue);
					return true;
				case '2':
					cout << "\nEnter the new loan type: ";
					cin >> newValue;
					cin.ignore();
					item->setLoanType(newValue);
					return true;
				case '3':
					cout << "\nEnter the new genre: ";
					cin >> newValue;
					cin.ignore();
					item->setGenre(newValue);
					return true;
				case '4':
					cout << "\nEnter the new number of copies in stock: ";
					cin >> newValue;
					cin.ignore();
					item->setNoOfCopy(stoi(newValue));
					return true;
				case '5':
					cout << "\nEnter the new rental fee: ";
					cin >> newValue;
					cin.ignore();
					item->setFee(stod(newValue));
					return true;
				case '6':
					return false;
				default:
					cerr << "Invalid input! Please only enter: " << endl;
					cerr << "Title: enter '1'." << endl;
					cerr << "Loan Type: enter '2'." << endl;
					cerr << "Genre: enter '3' (Only applied for Record and DVD)." << endl;
					cerr << "Copies in stock: enter '4'." << endl;
					cerr << "Rental fee: enter '5'." << endl;
					cerr << "Enter '6' to exit!" << endl;
					choice = 0;
					break;
				}
			}
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
void ItemManager::displaySortedItemTitle()
{
	//sort function by Title
	for (int i = 0; i < this->getItemList().size(); i++)
	{
		for (int j = i + 1; j < this->getItemList().size(); j++)
		{
			if (this->getItemList()[i]->getTitle() > this->getItemList()[j]->getTitle())
			{
				string temp = this->getItemList()[i]->getTitle();

				this->getItemList()[i]->getTitle() = this->getItemList()[j]->getTitle();
				this->getItemList()[j]->getTitle() = temp;
			}
		}
	}
	for (Item *item : this->getItemList())
	{
		cout << item->getTitle();
	}
}

void ItemManager::displaySortedItemID()
{
	//sort function by Title
	for (int i = 0; i < this->getItemList().size(); i++)
	{
		for (int j = i + 1; j < this->getItemList().size(); j++)
		{
			if (this->getItemList()[i]->getId() > this->getItemList()[j]->getId())
			{
				string temp = this->getItemList()[i]->getId();
				this->getItemList()[i]->getId() = this->getItemList()[j]->getId();
				this->getItemList()[j]->getId() = temp;
			}
		}
	}
	for (Item *item : this->getItemList())
	{
		cout << item->getId();
	}
}

void ItemManager::getAllNoStock()
{
	cout << "sort by no of stock = 0" << endl;
}

void ItemManager::searchItem(string title)
{
	for (Item *item : this->itemList)
	{
		if (item->getTitle() == title)
		{
			item->print();
			break;
		}
	}
}

void ItemManager::searchItem(string id)
{
	for (Item *item : this->itemList)
	{
		if (item->getId() == id)
		{
			item->print();
			break;
		}
	}
}

bool ItemManager::saveToFile()
{
	ofstream outStream(this->itemFile);

	for (Item *item : this->itemList)
	{
		outStream << item->toString() << endl;
	}
	return true;
}

//Function to save the itemList to a text file
bool ItemManager::saveToFile()
{
	ofstream outStream(this->itemFile); //open the file used to get the information

	//loop through the array and add the item info to the appropriate format
	for (Item *item : this->itemList)
	{
		outStream << item->toString() << endl;
	}
	return true;
}

void ItemManager::getItemFromRental(string itemID)
{
}

//
void ItemManager::print()
{
	cout << "print item manager" << endl;
}
