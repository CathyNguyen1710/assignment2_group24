#ifndef A2_ITEMMANAGER_H
#define A2_ITEMMANAGER_H

#include "ItemClass/Item.h"
#include "ItemClass/DVD.h"
#include "ItemClass/Game.h"
#include "ItemClass/Record.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class ItemManager
{
private:
	vector<Item*> itemList;
	int noOfItem;
	string itemFile; //file name
public:
	//Constructor
	ItemManager();
	ItemManager(string itemFile); //Use to read from item file

	//Destructor
	~ItemManager();

	//Getter
	vector<Item*> getItemList();
	int getNoOfItem();
	string getItemFile();

	//Setter
	void setItemList(vector<Item*> itemList);
	void setNoOfItem(int noOfItem);
	void setItemFile(string itemFile);

	//Other function
	bool returnItem(string id);

	bool addItem();
	bool updateItem(string id);
	bool deleteItem(string id);

	void displaySortedItemTitle();
	void displaySortedItemID();
	void getAllNoStock();
	void searchItem(string title);
	void searchItem(char* id);

	bool saveToFile();

	void getItemFromRental(string itemID);

	void print();
};

#endif