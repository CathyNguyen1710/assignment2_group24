#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>

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
	~ItemManager() {};

	//Getter
	vector<Item*> getItemList();
	int getNoOfItem();
	string getItemFile();

	//Setter
	void setItemList(vector<Item*> itemList);
	void setNoOfItem(int noOfItem);
	void setItemFile(string itemFile);

	//Other function
	void print();
};

