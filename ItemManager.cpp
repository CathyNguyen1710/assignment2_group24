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

	if (!inStream()) {
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
			Item* newItem = new Game(itemListData[0], itemListData[1], itemListData[2], itemListData[3], itemListData[4], itemListData[5]);
		}
		else if (itemListData[2] == "Record") {
			Item* newItem = new Record(itemListData[0], itemListData[1], itemListData[2], itemListData[3], itemListData[4], itemListData[5], itemListData[6]);
		}
		else if (itemListData[2] == "DVD") {
			Item* newItem = new DVD(itemListData[0], itemListData[1], itemListData[2], itemListData[3], itemListData[4], itemListData[5], itemListData[6]);
		}
		else {
			cout << "error" << endl;
		}

		itemListData.clear;
	}

	inStream.close();
}
ItemManager::ItemManager(string itemFile) {
	this->itemFile = itemFile;
	this->noOfItem = 0;

	ifstream inStream(itemFile);

	if (!inStream()) {
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
			Item* newItem = new Game(itemListData[0], itemListData[1], itemListData[2], itemListData[3], itemListData[4], itemListData[5]);
		}
		else if (itemListData[2] == "Record") {
			Item* newItem = new Record(itemListData[0], itemListData[1], itemListData[2], itemListData[3], itemListData[4], itemListData[5], itemListData[6]);
		}
		else if (itemListData[2] == "DVD") {
			Item* newItem = new DVD(itemListData[0], itemListData[1], itemListData[2], itemListData[3], itemListData[4], itemListData[5], itemListData[6]);
		}
		else {
			cout << "error" << endl;
		}

		itemListData.clear;
	}

	inStream.close();
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
bool ItemManager::addItem() {
	return true;
}
bool ItemManager::updateItem(string id) {
	return true;
}
bool ItemManager::deleteItem(string id) {
	return true;
}
bool ItemManager::returnItem(string id) {
	return true;
}
bool ItemManager::saveToFile() {
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

//
void ItemManager::print() {
	cout << "print item manager" << endl;
}