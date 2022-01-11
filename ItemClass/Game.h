#pragma once

#include <stdio.h>
#include "Item.h"

using namespace std;

class Game: public Item
{
public:
    // Constructor
    Game();
    Game(string id, string title, string rentalType, string loanType, int noOfCopy, double fee);

    // Destructor
    ~Game();

    // Other functions
    void print();
    string toString();
};