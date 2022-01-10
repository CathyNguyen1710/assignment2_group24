#pragma once

#include "Item.h"

#include <iostream>
#include <string>

using namespace std;

class DVD: public Item
{
protected:
	string genre;
public:
	//Constructor
	DVD();
	DVD(string id, string title, string rentalType, string loanType, int noOfCopy, double fee, string genre);

	//Destructor
	~DVD() {};

	//Getter
	string getGenre();

	//Setter
	void setGenre(string genre);

	//Other function
	void print();
	string toString();
};

