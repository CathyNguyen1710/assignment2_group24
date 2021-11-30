#pragma once

#include "Item.h"

class DVD
{
private:
	string genres;
public:
	DVD();
	DVD(string id, string title, string rentType, string loanType, int noOfCopies, double fee, string genres);

	string getGenres();

	void setGenres(string genres);

	void print();
};

