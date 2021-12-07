#ifndef A2_ACCOUNT_H
#define A2_ACCOUNT_H

#include "../ItemManager.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Account
{
private:
	string id;
	string name;
	string address;
	string phone;
	int noOfRentals;
	int totalBorrowItem;
	int totalReturnItem;

protected:
	vector<string> listOfRentals;

public:
	//Constructor
	Account();
	Account(string id, string name, string address, string phone, int noOfRentals);
	
	//Destructor
	~Account() {};

	//Getter
	string getId();
	string getName();
	string getAddress();
	string getPhone();
	int getNoOfRentals();
	int getTotalBorrowItem();
	int getTotalReturnItem();
	vector<string> getListOfRentals();

	//Setter
	void setId(string id);
	void setName(string name);
	void setAddress(string address);
	void setPhone(string phone);
	void setNoOfRentals(int noOfRentals);
	void setTotalBorrowItem(int totalBorrowItem);
	void setTotalReturnItem(int totalReturnItem);
	void setListOfRentals(vector<string>& listOfRentals);

	//Other function
	bool rentItem(string id, ItemManager* itemList);
	bool returnItem(string id, ItemManager* itemList);
	void addRentalList(string id);
	void addRentalList(string id, ItemManager* itemList);
	
	//
	void print();
	string toString();
};

#endif