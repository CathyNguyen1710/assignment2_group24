#pragma once

#include "Account.h"

class RegularAccount :public Account
{
private:
	int totalBorrowItem;
	int totalReturnItem;
public:
	//Constructor
	RegularAccount();
	RegularAccount(string id, string name, string address, string phone, int noOfRentals);

	//Destructor
	~RegularAccount() {};

	//Getter
	int getTotalBorrowItem();
	int getTotalReturnItem();

	//Setter
	void setTotalBorrowItem(int totalBorrowItem);
	void setTotalReturnItem(int totalReturnItem);

	//Other function
	bool promote();

	void print();
};

