#pragma once

#include <iostream>
#include <string>
#include <vector>

class Account
{
private:
	string id;
	string name;
	string address;
	string phone;
	int noOfRentals;

protected:
	vector<string> listOfRentals;

public:
	Account();
	Account(string id, string name, string address, string phone, int noOfRentals);
	~Account();

	string getId();
	string getName();
	string getAddress();
	string getPhone();
	int getNoOfRentals();
	vector<string> getNoOfRentals();

	void setId(string id);
	void setName(string name);
	void setAddress(string address);
	void setPhone(string phone);
	void setNoOfRentals(int noOfRentals);
	void setListOfRentals(vector<string>& listOfRentals);
};

