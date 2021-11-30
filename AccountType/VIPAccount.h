#pragma once

#include "Account.h"

class VIPAccount
{
public:
	VIPAccount();
	VIPAccount(string id, string name, string address, string phone, int noOfRentals);
	~VIPAccount() {};

	void print();
};

