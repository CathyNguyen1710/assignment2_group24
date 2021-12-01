#pragma once

#include <iostream>
#include <string>

class Item
{
private:
	string id;
	string title;
	string rentalType;
	string loadType;
	int noOfCopy;
	double fee;
	int noRented;

public:
	//Constructor
	Item(); //default constructor
	Item(string id, string title, string rentalType, string loanType, int noOfCopy, double fee);

	//Destructor
	~Item() {};

	//Getter
	string getId();
	string getTitle();
	string getRentalType();
	string getLoadType();
	int getNoOfCopy();
	double getFee();
	int getNoRented();

	//Setter
	void setId(string id);
	void setTitle(string title);
	void setRentalType(string rentalType);
	void setLoadType(string loadType);
	void setNoOfCopy(int noOfCopy);
	void setFee(double fee);
	void setNoRented(int noRented);

	//Other function
	void print();
};

