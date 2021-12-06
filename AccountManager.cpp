#include "AccountManager.h"
#include "AccountClass/Account.h"
#include "AccountClass/GuestAccount.h"
#include "AccountClass/RegularAccount.h"
#include "AccountClass/VIPAccount.h"

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

//Constructor
AccountManager::AccountManager() {

}
AccountManager::AccountManager(string customerFile) {

}

//Getter
vector<Account*> AccountManager::getAccountList() {
	return this->accountList;
}
int AccountManager::getNoOfAccount() {
	return this->noOfAccount;
}
string AccountManager::getCustomerFile() {
	return this->customerFile;
}

//Setter
void AccountManager::setAccountList(vector<Account*> accountList) {
	this->accountList = accountList;
}
void AccountManager::setNoOfAccount(int noOfAccount) {
	this->noOfAccount = noOfAccount;
}
void AccountManager::setCustomerFile(string customerFile) {
	this->customerFile = customerFile;
}

//Other function
bool AccountManager::addAccount() {
	return true;
}
bool AccountManager::updateAccount(string id) {
	return true;
}
bool AccountManager::saveToFile() {
	return true;
}
void AccountManager::displaySortedAccountName() {
	cout << "sort by name" << endl;
}
void AccountManager::displaySortedAccountID() {
	cout << "sort by id" << endl;
}
void AccountManager::getAccountByLevel(string level) {
	cout << "find by level" << endl;
}
void AccountManager::searchAccount(string name) {
	cout << "search by name" << endl;
}
void AccountManager::searchAccount(char* id) {
	cout << "search by id" << endl;
}

//
void AccountManager::print() {
	cout << "print acc manager" << endl;
}