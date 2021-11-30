#pragma once

#include "Item.h"

class Games:public Item
{
public:
	//Constructor
	Game();
	Game(string id, string title, string rentType, string loanType, int noOfCopies, double fee);

	//Destructor
	~Game() {};

	//Other function
	void print();
};

