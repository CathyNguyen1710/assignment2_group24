#pragma once

#include "Account.h"

class GuestAccount :public Account
{
private:
	int totalBorrowItem;
	int totalReturnItem;
public:
	//Constructor
	GuestAccount();
	GuestAccount(string id, string name, string address, string phone, int noOfRentals);

	//Destructor
	~GuestAccount() {};

	//Getter
	int getTotalBorrowItem();
	int getTotalReturnItem();

	//Setter
	void setTotalBorrowItem(int totalBorrowItem);
	void setTotalReturnItem(int totalReturnItem);

	//Other function
	bool promoteable(); //Use to promote from Guest acc to Regular acc when meet condition

	void print();
};

