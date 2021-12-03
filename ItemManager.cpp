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

}
ItemManager::ItemManager(string itemFile) {

}

//Destructor
ItemManager::~ItemManager() {
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