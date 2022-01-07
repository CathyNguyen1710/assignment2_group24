#ifndef A2_ACCOUNTMANAGER_H
#define A2_ACCOUNTMANAGER_H

#include "AccountClass/Account.h"
#include "AccountClass/GuestAccount.h"
#include "AccountClass/RegularAccount.h"
#include "AccountClass/VIPAccount.h"
#include "ItemManager.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class AccountManager
{
private:
	vector<Account* > accountList;
	int noOfAccount;
	string customerFile; //file name
public:
	//Constructor
	AccountManager();
	AccountManager(string customerFile); //Use to read from customer file

	//Destructor
	~AccountManager();

	//Getter
	vector<Account*> getAccountList();
	int getNoOfAccount();
	string getCustomerFile();

	//Setter
	void setAccountList(vector<Account*> accountList);
	void setNoOfAccount(int noOfAccount);
	void setCustomerFile(string customerFile);

	//Other function
	bool promoteAccount(string id);

	bool addAccount();
	bool updateAccount(string id);

	void displaySortedAccountName();
	void displaySortedAccountID();
	void getAccountByLevel(string level);
	void searchAccount(string accountName);
	void searchAccount(char* id);

	bool saveToFile();

	void print();
};

#endif