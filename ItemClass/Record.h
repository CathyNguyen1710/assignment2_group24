#pragma once

#include "Item.h"

class Record :public Item
{
private:
	string genre;
public:
	//Constructor
	Record();
	Record(string id, string title, string rentalType, string loanType, int noOfCopy, double fee, string genre;

	//Destructor
	~Record() {};

	//Getter
	string getGenre();

	//Setter
	void setGenre(string genre);

	//Other function
	void print();
};

