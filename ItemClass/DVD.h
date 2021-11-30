#pragma once

#include "Item.h"

class DVD :public Item
{
private:
	string genres;
public:
	//Constructor
	DVD();
	DVD(string id, string title, string rentType, string loanType, int noOfCopies, double fee, string genres);

	//Destructor
	~DVD() {};

	//Getter
	string getGenres();

	//Setter
	void setGenres(string genres);

	//Other function
	void print();
};

