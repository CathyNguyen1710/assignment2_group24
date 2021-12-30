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
	string type;
	//int totalBorrowItem;

protected:
	vector<string> listOfRentals;

public:
	//Constructor
	Account();
	Account(string id, string name, string address, string phone, int noOfRentals, string type);
	
	//Destructor
	~Account() {};

	//Getter
	string getId();
	string getName();
	string getAddress();
	string getPhone();
	int getNoOfRentals();
	string getType();
	//int getTotalBorrowItem();
	vector<string> getListOfRentals();

	//Setter
	void setId(string id);
	void setName(string name);
	void setAddress(string address);
	void setPhone(string phone);
	void setNoOfRentals(int noOfRentals);
	void setType(string type);
	//void setTotalBorrowItem(int totalBorrowItem);
	void setListOfRentals(vector<string>& listOfRentals);

	//Other function
	virtual bool rentItem(string id, ItemManager* itemList) = 0;
	virtual bool returnItem(string id, ItemManager* itemList) = 0;
	virtual void addRentalList(string id) = 0;
	virtual bool promoteable() = 0;
	
	//
	void print();
	virtual string toString() = 0;
};

#endif