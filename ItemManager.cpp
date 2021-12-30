#include "ItemManager.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>

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
bool mycomp(string a, string b){
	//returns 1 if string a is alphabetically 
	//less than string b
	//quite similar to strcmp operation
	return a<b;
}

vector<string> alphabeticallySort(vector<string> a){
	int n=a.size();
	//mycomp function is the defined function which 
	//sorts the strings in alphabetical order
	sort(a.begin(),a.end(),mycomp);
	return a;
}

void ItemManager::displaySortedItemTitle() {
	vector<string> itemNameList;
	for (Item* item : this->getItemList()) 
	{
		itemNameList.push_back(item->getTitle());
	}
	alphabeticallySort(itemNameList);
	cout << "The item list is: ";
	for (auto itemName: itemNameList){
		cout << itemName;
	}
	cout << endl;
}

void ItemManager::displaySortedItemID() {
	vector<string> itemIDList;
	vector<int> itemIDNumber;
	for (Item* item : this->getItemList()) {
		itemIDList.push_back(item->getId());
	}
	
	for (string ID: itemIDList){
		string IDString = ID.substr(1,3)+ID.substr(5, 8);
		int IDInt;
		if (sscanf(IDString.c_str(), "%d", &IDInt) !=1)
			itemIDNumber.push_back(IDInt);
	}
	sort(itemIDNumber.begin(), itemIDNumber.end());
	for (auto ID: itemIDNumber)
	{
	cout << "I" << to_string(ID)[0] << to_string(ID)[1] << to_string(ID)[2]
    << "-" << to_string(ID)[3] << to_string(ID)[4] << to_string(ID)[5] << to_string(ID)[6];
	}
	
}
void ItemManager::getAllNoStock() 
{
	cout << "sort by no of stock = 0" << endl;
}


void ItemManager::searchItem(string title) 
{
	vector <string> titleSearchResult;
	for (Item* item : this->getItemList()) 
	{
		if (item->getTitle().find(title))
		{
			titleSearchResult.push_back(item->getTitle());
		}
	}
	cout << "The title search result is: " << endl;
	for (auto titleResult: titleSearchResult)
	{
		cout << titleResult << endl;
	}
	
}

void ItemManager::searchItem(char* id) 
{
	vector<string> itemIDList;
	vector<string> itemIDNumber;
	vector<string> IDSearchResult;
	
	for (Item* item : this->getItemList()) 
	{
		itemIDList.push_back(item->getId());
	}
	for (auto ID: itemIDList){
		itemIDNumber.push_back(ID.substr(1,3)+ID.substr(5, 8));
	}
	
	for (auto ID: itemIDNumber){
		if (ID.find(id)){
			IDSearchResult.push_back("I"+ ID.substr(0,2) + "-" +ID.substr(3,6));	
		}
	}
	cout << "The ID search result is: "<<endl;
	for (auto ID: IDSearchResult){
		cout << ID << endl;
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

void ItemManager::displayAll() 
{
	for (Item* item : this->getItemList()) 
	{
		item->print();
	}
}

void ItemManager::getItemFromRental(string itemID) 
{
	for (Item* item : this->itemList) 
	{
		if (item->getId() == itemID) 
		{
			item->print();
		}
	}
}

//
void ItemManager::print() {
	cout << "print item manager" << endl;
}