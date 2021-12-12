#include "ItemManager.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

//Constructor
ItemManager::ItemManager() {
	this->itemFile = "items.txt";
	this->noOfItem = 0;

	ifstream inStream(itemFile);

	if (!inStream) {
		cerr << "Error" << endl;
	}

	string line;
	vector<string> itemListData;

	while (getline(inStream, line)) {
		istringstream stream(line);
		string fields;

		while (getline(stream, fields, ',')) {
			itemListData.push_back(fields);
		}

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
		else {
			cout << "error" << endl;
		}

		itemListData.clear();
	}

	inStream.close();
}
ItemManager::ItemManager(string itemFile) {
	this->itemFile = itemFile;
	this->noOfItem = 0;

	ifstream inStream(itemFile);

	if (!inStream) {
		cerr << "Error" << endl;
	}

	string line;
	vector<string> itemListData;

	while (getline(inStream, line)) {
		istringstream stream(line);
		string fields;

		while (getline(stream, fields, ',')) {
			itemListData.push_back(fields);
		}

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
		else {
			cout << "error" << endl;
		}

		itemListData.clear();
	}

	inStream.close();
}

//destructor
ItemManager::~ItemManager() {
	for (Item* item : this->itemList) {
		//remove all dynamically allocated memory for item pointers
		delete item;
	}
}

//Getter
vector<Item*> ItemManager::getItemList() {
	return this->itemList;
}
int ItemManager::getNoOfItem() {
	return this->noOfItem;
}
string ItemManager::getItemFile() {
	return this->itemFile;
}

//Setter
void ItemManager::setItemList(vector<Item*> itemList) {
	this->itemList = itemList;
}
void ItemManager::setNoOfItem(int noOfItem) {
	this->noOfItem = noOfItem;
}
void ItemManager::setItemFile(string itemFile) {
	this->itemFile = itemFile;
}

//Other function
bool ItemManager::returnItem(string id) {
	for (Item* item : this->getItemList()) {
		if (item->getId() == id) {
			item->setNoOfCopy(item->getNoOfCopy() + 1);
			item->setNoRented(item->getNoRented() - 1);
			return true;
		}
	}

	return false;
}

bool ItemManager::addItem() {
	return true;
}
bool ItemManager::updateItem(string id) {
	return true;
}
bool ItemManager::deleteItem(string id) {
	return true;
}

void ItemManager::displaySortedItemTitle() {
	cout << "sort by title" << endl;
}
void ItemManager::displaySortedItemID() {
	cout << "sort by id" << endl;
}
void ItemManager::getAllNoStock() {
	cout << "sort by no of stock = 0" << endl;
}
void ItemManager::searchItem(string title) {
	cout << "search by title" << endl;
}
void ItemManager::searchItem(char* id) {
	cout << "search by id" << endl;
}

bool ItemManager::saveToFile() {
	ofstream outStream(this->itemFile);

	for (Item* item : this->itemList) {
		outStream << item->toString() << endl;
	}
	return true;
}

void ItemManager::displayAll() {
	for (Item* item : this->getItemList()) {
		item->print();
	}
}

void ItemManager::getItemFromRental(string itemID) {
	for (Item* item : this->itemList) {
		if (item->getId() == itemID) {
			item->print();
		}
	}
}

//
void ItemManager::print() {
	cout << "print item manager" << endl;
}