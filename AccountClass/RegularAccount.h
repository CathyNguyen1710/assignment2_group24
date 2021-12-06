#pragma once

#include "Account.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RegularAccount :public Account
{
private:
	int totalBorrowItem;
	int totalReturnItem;
public:
	//Constructor
	RegularAccount();
	RegularAccount(string id, string name, string address, string phone, int noOfRentals);
	RegularAccount(Account* account);//Constructor used for promote from Guest acc to Regular acc

	//Destructor
	~RegularAccount() {};

	//Getter
	int getTotalBorrowItem();
	int getTotalReturnItem();

	//Setter
	void setTotalBorrowItem(int totalBorrowItem);
	void setTotalReturnItem(int totalReturnItem);

	//Other function
	bool promoteable(); //Use to promote from Regular acc to VIP acc when meet condition

	//
	void print();
	string toString();
};

