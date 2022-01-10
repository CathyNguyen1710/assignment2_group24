#include "Item.h"

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

// Constructor
Item::Item()
{
    this->id = "";
    this->title = "";
    this->loanType = "";
    this->noOfCopy = 0;
    this->fee = 0;
}
Item::Item(string id, string title, string rentalType, string loanType, int noOfCopy, double fee)
{
    this->id = id;
    this->title = title;
    //    this->rentalType = rentalType;
    this->loanType = loanType;
    this->noOfCopy = noOfCopy;
    this->fee = fee;
    this->noRented = 0;
}

// Destructor
Item::~Item()
{
}

// Getter
string Item::getId()
{
    return this->id;
}
string Item::getTitle()
{
    return this->title;
}
string Item::getRentalType()
{
    return this->rentalType;
}
string Item::getLoanType()
{
    return this->loanType;
}
int Item::getNoOfCopy()
{
    return this->noOfCopy;
}
double Item::getFee()
{
    return this->fee;
}
int Item::getNoRented()
{
    return this->noRented;
}
string Item::getGenre()
{
    return string();
}

// Setter
void Item::setId(string id)
{
    this->id = id;
}
void Item::setTitle(string title)
{
    this->title = title;
}
void Item::setRentalType(string rentalType)
{
    this->rentalType = rentalType;
}
void Item::setLoanType(string loadType)
{
    this->loanType = loadType;
}
void Item::setNoOfCopy(int noOfCopy)
{
    this->noOfCopy = noOfCopy;
}
void Item::setFee(double fee)
{
    this->fee = fee;
}
void Item::setNoRented(int noRented)
{
    this->noRented = noRented;
}
void Item::setGenre(string genre)
{
    return;
}

// Other functions
void Item::print()
{
    return;
}
string toString()
{
    return string();
}
