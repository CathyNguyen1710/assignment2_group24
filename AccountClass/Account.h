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

	//
	void print();
};

#endif