#include "ItemClass/Item.h"

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

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

	/*//Other function
	bool addItem();
	bool updateItem(string id);
	bool deleteItem(string id);
	bool returnItem(string id);
	bool savrToFile();
	void displaySortedItemTitle();
	void displaySortedItemID();
	void getAllNoStock();
	void searchItem(string title);
	void searchItem(char* id);

	//
	void print();*/
};

