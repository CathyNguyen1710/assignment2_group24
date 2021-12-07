#ifndef A2_VIPACCOUNT_H
#define A2_VIPACCOUNT_H

#include "Account.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class VIPAccount :public Account
{
private:
	int rewardPoint;
public:
	//Constructor
	VIPAccount();
	VIPAccount(string id, string name, string address, string phone, int noOfRentals);
	VIPAccount(Account* account);//Constructor used for promote from Regular acc to VIP acc

	//Destructor
	~VIPAccount() {};

	//Getter
	int getRewardPoint();

	//Setter
	void setRewardPoint(int rewardPoint);

	//Other function
	bool rentItem(string id, ItemManager* itemList);
	bool returnItem(string id, ItemManager* itemList);
	void addRentalList(string id);

	//
	void print();
	string toString();
};

#endif