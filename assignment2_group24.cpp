#include "AccountManager.h"
#include "ItemManager.h"
#include "AccountClass/Account.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include <utility>

using namespace std;

//Function for validate Item ID
bool checkItemID(string input) {
    if (input.length() == 9) {
        for (int i = 0; i < input.length(); i++) {
            if (i == 0) {
                if (input[i] != 'I') {
                    cerr << "Id is not in the right format (Ixxx-xxxx). Please try again (missing I): " << endl;
                    return false;
                }
            }
            else if (i == 4) {
                if (input[i] != '-') {
                    cerr << "Id is not in the right format (Ixxx-xxxx). Please try again (missing -):" << endl;
                    return false;
                }
            }
            else {
                if (input[i] > '9' || input[i] < '0') {
                    cerr << "Id is not in the right format (Ixxx-xxxx). Please try again: " << endl;
                    return false;
                }
            }
        }
        return true;
    }
    else {
        cerr << "item id should has 9 characters (Ixxx-xxxx)" << endl;
        return false;
    }
}

//Function for validate Account ID
bool checkAccountID(string input) {
    if (input.length() == 4) {
        for (int i = 0; i < input.length(); i++) {
            if (i == 0) {
                if (input[i] != 'C') {
                    cerr << "Id is not in the right format (Cxxx). Please try again (missing C): " << endl;
                    return false;
                }
            }
            else {
                if (input[i] > '9' || input[i] < '0') {
                    cerr << "Id is not in the right format (Cxxx). Please try again: " << endl;
                    return false;
                }
            }
        }
        return true;
    }
    else {
        cerr << "customer id should has 4 characters (Cxxx)" << endl;
        return false;
    }
}

//Function to get Item ID
string getItemID() {
    string input;
    string ask = "Please enter the item id: ";

    while (true) {
        cout << ask;
        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (checkItemID(input) == true) {
            return input;
        }
    }
}

//Function to get Account ID
string getAccountID() {
    string input;
    string ask = "Please enter the account id: ";

    while (true) {
        cout << ask;
        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (checkAccountID(input) == true) {
            return input;
        }
    }
}

void itemSubMenu(ItemManager* itemList) {
    string input;

    string option = "Choose one of the options below\n"
        "1. Add an item\n"
        "2. Update an item\n"
        "3. Delete an item\n"
        "4. Exit\n";

    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") {
            cout << "Add an item" << endl;
        }
        else if (input == "2") {
            cout << "Update an item" << endl;
        }
        else if (input == "3") {
            cout << "Delete an item" << endl;
        }
        else if (input == "4") {
            cout << "Exit" << endl;
            break;
        }
        else {
            cerr << "Error message" << endl;
        }
    }
}

void customerSubMenu(AccountManager* accountList) {
    string input;

    string option = "Choose one of the options below\n"
        "1. Add a customer\n"
        "2. Update a customer\n"
        "3. Exit\n";

    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") {
            accountList->addAccount();
        }
        else if (input == "2") {
            string id = getAccountID();

            //trim string
            input.erase(input.find_last_not_of(" ") + 1);
            input.erase(0, input.find_first_not_of(" "));

            accountList->updateAccount(id);
        }
        else if (input == "3") {
            cout << "Exit" << endl;
            break;
        }
        else {
            cerr << "Error message" << endl;
        }
    }
}

void promoteCustomer(AccountManager* accountList) {
    string id = getAccountID();
    accountList->promoteAccount(id);
}

void rentItem(AccountManager* accountList, ItemManager* itemList) {
    string accountID = getAccountID();

    string itemID = getItemID();

    for (Account* account : accountList->getAccountList()) {
        if (account->getId() == accountID) {
            account->rentItem(itemID, itemList);
        }
    }
}

void returnItem(AccountManager* accountList, ItemManager* itemList) {
    string accountID = getAccountID();
    string itemID = getItemID();
    
    for (Account* account : accountList->getAccountList()) {
        if (account->getId() == accountID) {
            account->returnItem(itemID, itemList);

        }

    }
    
}

void displayItemSubMenu(ItemManager* itemList) {
    string input;

    string option = "Choose one of the options below\n"
        "1. Sorted item by id\n"
        "2. Sorted item by title\n"
        "3. Exit\n";

    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") {

            itemList->displaySortedItemID();
        }
        else if (input == "2") {

            cout << "Sorted item by id" << endl;
            itemList->displaySortedItemID();
        }
        else if (input == "2") {
            cout << "Sorted item by title" << endl;
            itemList->displaySortedItemTitle();
        }
        else if (input == "3") {
            cout << "Exit" << endl;
            break;
        }
        else {
            cerr << "Error message" << endl;
        }
    }
}

void displayItemOutOfStock(ItemManager* itemList) {
    cout << "7" << endl;
}

void displayCustomerSubMenu(AccountManager* accountList) {
    string input;

    string option = "Choose one of the options below\n"
        "1. Sorted customer by id\n"
        "2. Sorted customer by name\n"
        "3. Exit\n";

    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") {

            accountList->displaySortedAccountID();
        }
        else if (input == "2") {

            cout << "Sorted customer by id" << endl;
            accountList->displaySortedAccountID();
        }
        else if (input == "2") {
            cout << "Sorted customer by name" << endl;

            accountList->displaySortedAccountName();
        }
        else if (input == "3") {
            cout << "Exit" << endl;
            break;
        }
        else {
            cerr << "Error message" << endl;
        }
    }
}

void displayCustomerByGroupSubMenu(AccountManager* accountList) {
    string input;

    string option = "Choose one of the option below\n"
        "1. Guest Accounts\n"
        "2. Regular Accounts\n"
        "3. VIP Accounts\n"
        "4. Exit\n";

    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") {
            cout << "Guest Accounts" << endl;
        }
        else if (input == "2") {
            cout << "Regular Accounts" << endl;
        }
        else if (input == "3") {
            cout << "VIP Accounts" << endl;
        }
        else if (input == "4") {
            cout << "Exit" << endl;
            break;
        }
        else {
            cerr << "Error message" << endl;
        }
    }
}

void searchItemSubMenu(ItemManager* itemList) {
    string input;

    string option = "Choose one of the options below\n"
        "1. Search item by title\n"
        "2. Search item by id\n"
        "3. Exit\n";

    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") {
            cout << "Search item by title" << endl;
            itemList->searchItem(input);
        }
        else if (input == "2") {
            cout << "Search item by id" << endl;
            itemList->searchItem(input);
        }
        else if (input == "3") {
            cout << "Exit" << endl;
            break;
        }
        else {
            cerr << "Error message" << endl;
        }
    }
}

void searchCustomerSubMenu(AccountManager* accountList) {
    string input;

    string option = "Choose one of the options below\n"
        "1. Search customer by name\n"
        "2. Search customer by id\n"
        "3. Exit\n";

    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") {
            cout << "Search customer by name" << endl;
            accountList->searchAccount(input);
        }
        else if (input == "2") {
            cout << "Search customer by id" << endl;
            accountList->searchAccount(input);
        }
        else if (input == "3") {
            cout << "Exit" << endl;
            break;
        }
        else {
            cerr << "Error message" << endl;
        }
    }
}

int main()
{
    ItemManager* itemList = new ItemManager();

    AccountManager* accountList = new AccountManager();

    cout << "Welcome to Genies video store" << "\n\n";
    string input;

    string option = "\nPlease choose from an option below:\n"
        "1/ Add a new item, update or delete an existing item\n"
        "2/ Add new customer or update an existing customer\n"
        "3/ Promote an existing customer\n"
        "4/ Rent an item\n"
        "5/ Return an item\n"
        "6/ Display all item(s)\n"
        "7/ Display out of stock item(s)\n"
        "8/ Display all customers(s)\n"
        "9/ Display a group of customer(s)\n"
        "10/ Search item(s)\n"
        "11/ Search customer(s)\n"
        "Exit.\n";

    while (true) {
        cout << option << endl;
        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") {
            itemSubMenu(itemList);
        }
        else if (input == "2") {
            customerSubMenu(accountList);
        }
        else if (input == "3") {
            promoteCustomer(accountList);
        }
        else if (input == "4") {
            rentItem(accountList, itemList);
        }
        else if (input == "5") {
            returnItem(accountList, itemList);
        }
        else if (input == "6") {
            displayItemSubMenu(itemList);
        }
        else if (input == "7") {
            displayItemOutOfStock(itemList);
        }
        else if (input == "8") {
            displayCustomerSubMenu(accountList);
        }
        else if (input == "9") {
            displayCustomerByGroupSubMenu(accountList);
        }
        else if (input == "10") {
            searchItemSubMenu(itemList);
        }
        else if (input == "11") {
            searchCustomerSubMenu(accountList);
        }
        else if (input == "Exit") {

            //Printout team member
            cout << "\n\nASSIGNMENT 2 GROUP 24" << endl;
            cout << "s3819293, s3819293@rmit.edu.vn, Thi Nha Uyen, Nguyen" << endl;
            cout << "s3818221, s3818221@rmit.edu.vn, Khoi Nguyen, Truong" << endl;
            cout << "s3877256, s3877256@rmit.edu.vn, Phuong Nam, Nguyen" << endl;
            cout << "s3878451, s3878451@rmit.edu.vn, Hoang Long, Nguyen" << endl;

            break;
        }
        else {
            cerr << "Error message" << endl;
        }

    }

    return 0;

}
