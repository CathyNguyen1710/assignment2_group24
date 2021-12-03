#include "AccountManager.h"

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

//Destructor
AccountManager::~AccountManager() {
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