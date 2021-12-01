#pragma once

#include "Item.h"

class Game:public Item
{
public:
	//Constructor
	Game();
	Game(string id, string title, string rentalType, string loanType, int noOfCopy, double fee, string genre);

	//Destructor
	~Game() {};

	//Other function
	void print();
};

