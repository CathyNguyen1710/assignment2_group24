#pragma once

#include "Item.h"

class Record :public Item
{
private:
	string genres;
public:
	//Constructor
	Record();
	Record(string id, string title, string rentType, string loanType, int noOfCopies, double fee, string genres);

	//Destructor
	~Record() {};

	//Getter
	string getGenres();

	//Setter
	void setGenres(string genres);

	//Other function
	void print();
};

