#pragma once

#include "Item.h"

#include <iostream>
#include <string>

using namespace std;

class Game : public Item
{
public:
	//Constructor
	Game();
	Game(string id, string title, string rentalType, string loanType, int noOfCopy, double fee);

	//Destructor
	~Game() {};

	//Other function
	void print();
	string toString();
};