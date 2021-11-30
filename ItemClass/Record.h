#pragma once

#include "Item.h"

class Record
{
private:
	string genres;
public:
	Record();
	Record(string id, string title, string rentType, string loanType, int noOfCopies, double fee, string genres);

	string getGenres();

	void setGenres(string genres);

	void print();
};

