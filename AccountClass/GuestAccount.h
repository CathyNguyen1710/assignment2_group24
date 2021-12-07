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
	int totalVideoReturn;
public:
	//Constructor
	GuestAccount();
	GuestAccount(string id, string name, string address, string phone, int noOfRentals);

	//Destructor
	~GuestAccount() {};

	//Getter
	int getTotalVideoReturn();

	//Setter
	void setTotalVideoReturn(int totalVideoReturn);

	//Other function
	bool promoteable(); //Use to promote from Guest acc to Regular acc when meet condition*
	bool rentItem(string id, ItemManager* itemList);
	bool returnItem(string id, ItemManager* itemList);
	void addRentalList(string id, ItemManager* itemList);

	//
	void print();
	string toString();
};

#endif