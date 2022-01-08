//
//  Game.hpp
//  testing
//
//  Created by Thai Nam Hoang on 08/01/2022.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Item.hpp"

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

#endif /* Game_hpp */
