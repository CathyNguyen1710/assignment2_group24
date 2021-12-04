#pragma once

#include "Account.h"

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

	//
	void print();
	string toString();
};

