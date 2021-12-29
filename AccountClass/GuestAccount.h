#ifndef A2_GUESTACCOUNT_H
#define A2_GUESTACCOUNT_H

#include "Account.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class GuestAccount :public Account
{
private:
	int totalReturnItem;

public:
	//Constructor
	GuestAccount();
	GuestAccount(string id, string name, string address, string phone, int noOfRentals, string type);

	//Destructor
	~GuestAccount() {};

	//Getter
	int getTotalReturnItem();

	//Setter
	void setTotalReturnItem(int totalReturnItem);

	//Other function
	bool promoteable(); //Use to promote from Guest acc to Regular acc when meet condition*
	bool rentItem(string id, ItemManager* itemList);
	bool returnItem(string id, ItemManager* itemList);
	void addRentalList(string id);

	//
	string toString();
};

#endif