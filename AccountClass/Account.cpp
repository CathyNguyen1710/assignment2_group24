#include "Account.h"

using namespace std;

Account::Account() {

}

Account::Account(string id, string name, string address, string phone, int noOfRentals) {
    this->id = id;
    this->name = name;
    this->address = address;
    this->phone = phone;
    this->noOfRentals = noOfRentals;
}

//Getter
string Account::getId() {
    return this->id;
}
string Account::getName() {
    return this->name;
}
string Account::getAddress() {
    return this->address;
}
string Account::getPhone() {
    return this->phone;
}
int Account::getNoOfRentals() {
    return this->noOfRentals;
}
vector<string> Account::getListOfRentals() {
    return this->listOfRentals;
}

//Setter
void Account::setId(string id) {
    this->id = id;
}
void Account::setName(string name) {
    this->name = name;
}
void Account::setAddress(string address) {
    this->address = address;
}
void Account::setPhone(string phone) {
    this->phone = phone;
}
void Account::setNoOfRentals(int noOfRentals) {
    this->noOfRentals = noOfRentals;
}
void Account::setListOfRentals(vector<string>& listOfRentals) {
    this->getListOfRentals = listOfRentals;
}