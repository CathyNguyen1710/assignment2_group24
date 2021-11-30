#pragma once

#include "Item.h"

class Games
{
public:
	Game();
	Game(string id, string title, string rentType, string loanType, int noOfCopies, double fee);

	void print();
};

