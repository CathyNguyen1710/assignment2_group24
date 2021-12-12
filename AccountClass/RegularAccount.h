#ifndef A2_REGULARACCOUNT_H
#define A2_REGULARACCOUNT_H

#include "Account.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class RegularAccount :public Account
{
private:
	int totalReturnItem;

public:
	//Constructor
	RegularAccount();
	RegularAccount(string id, string name, string address, string phone, int noOfRentals, string type);
	RegularAccount(Account* account);//Constructor used for promote from Guest acc to Regular acc

	//Destructor
	~RegularAccount() {};

	//Getter
	int getTotalReturnItem();

	//Setter
	void setTotalReturnItem(int totalReturnItem);

	//Other function
	bool promoteable(); //Use to promote from Regular acc to VIP acc when meet condition
	bool rentItem(string id, ItemManager* itemList);
	bool returnItem(string id, ItemManager* itemList);
	void addRentalList(string id);

	//
	void print();
	string toString();
};

#endif