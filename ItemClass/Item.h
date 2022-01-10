#ifndef A2_ITEM_H
#define A2_ITEM_H

#include <iostream>
#include <string>

using namespace std;

class Item
{
protected:
	string id;
	string title;
	string rentalType;
	string loanType;
	int noOfCopy;
	double fee;
	int noRented;

public:
	// Constructor
	Item(); // default constructor
	Item(string id, string title, string rentalType, string loanType, int noOfCopy, double fee);

	// Destructor
	~Item() {};

	// Getter
	string getId();
	string getTitle();
	string getRentalType();
	string getLoanType();
	int getNoOfCopy();
	double getFee();
	int getNoRented();
    virtual string getGenre();

	// Setter
	void setId(string id);
	void setTitle(string title);
	void setRentalType(string rentalType);
	void setLoanType(string loadType);
	void setNoOfCopy(int noOfCopy);
	void setFee(double fee);
	void setNoRented(int noRented);
    virtual void setGenre(string genre);

	// Other functions
	virtual void print();
	virtual string toString();
};

#endif
