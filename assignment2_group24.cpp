#include "AccountManager.h"
#include "ItemManager.h"
#include "AccountClass/Account.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
//#include <iomanip>

//#include <utility>

using namespace std;

//function to validate the item id input
bool checkItemID(string input) {
    //check if the id input is in the format Ixxx-yyyy or Ixxx or the word Exit
    if (input.length() == 9) { //if in format Ixxx-yyyy
        for (int i = 0; i < input.length(); i++) {
            if (i == 0) {
                if (input[i] != 'I') { //check if the 1st character is I
                    cerr << "\nId is not in the right format (Ixxx-yyyy) or (Ixxx). Please try again (missing I): " << endl;
                    return false;
                }
            }
            else if (i == 4) {
                if (input[i] != '-') { //check if the 5th character is -
                    cerr << "\nId is not in the right format (Ixxx-yyyy). Please try again (missing -):" << endl;
                    return false;
                }
            }
            else {
                if (input[i] > '9' || input[i] < '0') { //check if x and y characters are number
                    cerr << "\nId is not in the right format (Ixxx-yyyy) or (Ixxx). Please try again: " << endl;
                    return false;
                }
            }
        }
        return true;
    }
    else if (input.length() == 4) { //if in format Ixxx or Exit word
        if (input == "Exit") { //if input is Exit return true and break the loop
            return true;
        }
        else { //if in format Ixxx
            for (int i = 0; i < input.length(); i++) {
                if (i == 0) {
                    if (input[i] != 'I') { //check if the 1st character is I
                        cerr << "\nId is not in the right format (Ixxx-yyyy) or (Ixxx). Please try again (missing I): " << endl;
                        return false;
                    }
                }
                else {
                    if (input[i] > '9' || input[i] < '0') { //check if x characters are number
                        cerr << "\nId is not in the right format (Ixxx-yyyy) or (Ixxx). Please try again: " << endl;
                        return false;
                    }
                }
            }
            return true;
        }
    }
    else { //Prinout error message in input is invalid
        cerr << "\nItem id should has 9 characters (Ixxx-yyyy) or 4 characters (Ixxx)" << endl;
        return false;
    }
}
//function to validate the account id input
bool checkAccountID(string input) {
    //check if the id input is in the format Cxxx or the word Exit
    if (input.length() == 4) { //if in format Ixxx or Exit word
        if (input == "Exit") { //if input is Exit return true and break the loop
            return true;
        }
        else {
            for (int i = 0; i < input.length(); i++) {
                if (i == 0) {
                    if (input[i] != 'C') { //check if the 1st character is C
                        cerr << "\nId is not in the right format (Cxxx). Please try again (missing C): " << endl;
                        return false;
                    }
                }
                else {
                    if (input[i] > '9' || input[i] < '0') { //check if x characters are number
                        cerr << "\nId is not in the right format (Cxxx). Please try again: " << endl;
                        return false;
                    }
                }
            }
            return true;
        }
    }
    else { //Prinout error message in input is invalid
        cerr << "\nCustomer id should has 4 characters (Cxxx)" << endl;
        return false;
    }
}
//function to get the item id
string getItemID() {
    string input;
    string ask = "\nPlease enter the item id (Or write 'Exit' to return to the previous menu): ";

    //while loop the ask for the id
    while (true) {
        cout << ask;
        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        //if the id input is validated, return input and break the loop
        if (checkItemID(input)) {
            return input;
        }
    }
}
//function to get the account id
string getAccountID() {
    string input;
    string ask = "\nPlease enter the account id (Or write 'Exit' to return to the previous menu): ";

    //while loop the ask for the id
    while (true) {
        cout << ask;
        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        //if the id input is validated, return input and break the loop
        if (checkAccountID(input)) {
            return input;
        }
    }
}

//Function for CRUD of item (add, update, delete)
void itemSubMenu(ItemManager* itemList) {
    string input;

    string option = "\nChoose one of the options below\n"
        "1. Add an item\n"
        "2. Update an item\n"
        "3. Delete an item\n"
        "4. Exit\n";

    //While loop that ask user what they want to do
    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") { //if user choose 1: call function to add new item and then save it to file
            itemList->addItem();
            itemList->saveToFile();
        }
        else if (input == "2") { //if user choose 2: call function to update exsited item and then save it to file
            itemList->displaySortedItemID(); //display all items information
            string id = getItemID(); //get user input for the item they want to update

            if (id != "Exit") {
                itemList->updateItem(id);
                itemList->saveToFile();
            }

        }
        else if (input == "3") { //if user choose 3: call function to update delete item and then save it to file
            itemList->displaySortedItemID(); //display all items information
            string id = getItemID(); //get user input for the item they want to delete

            if (id != "Exit") {
                itemList->deleteItem(id);
                itemList->saveToFile();
            }
        }
        else if (input == "4") { //if user to 4: exit the CRUD sub menu
            cout << "\nExit\n" << endl;
            break;
        }
        else { //prinout error message if input is invalid
            cerr << "\nInvalid input." << endl;
        }
    }
}

//Function for CRUD of account (add, update)
void customerSubMenu(AccountManager* accountList) {
    string input;

    string option = "\nChoose one of the options below\n"
        "1. Add a customer\n"
        "2. Update a customer\n"
        "3. Exit\n";

    //While loop that ask user what they want to do
    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") { //if user choose 1: call function to add new account and then save it to file
            accountList->addAccount();
            accountList->saveToFile();
        }
        else if (input == "2") { //if user choose 2: call function to update exsited account and then save it to file
            accountList->displaySortedAccountID(); //display all accounts information
            string id = getAccountID(); //get user input for the account they want to delete

            if (id != "Exit") {
                accountList->updateAccount(id);
                accountList->saveToFile();
            }
        }
        else if (input == "3") { //if user to 3: exit the CRUD sub menu
            cout << "\nExit\n" << endl;
            break;
        }
        else { //prinout error message if input is invalid
            cerr << "\nInvalid input." << endl;
        }
    }
}

//Function used to promote a customer with the account id input
bool promoteCustomer(string accountID, AccountManager* accountList) {

    string type, promoteType;
    //loop through the list of account to find the account and it type
    for (Account* acc : accountList->getAccountList()) {
        if (acc->getId() == accountID) {
            type = acc->getType();
        }
    }

    //check for the type
    if (type == "Guest") { //if type = Guest --> promote to Regular
        promoteType = "Regular";
    }
    else if (type == "Regular") { //if type = Regular --> promote to VIP
        promoteType = "VIP";
    }

    if (accountList->promoteAccount(accountID)) { //check if the account is promotable
        cout << "You have meet the requirement to promote your " << type << " account into " << promoteType << " account. Promote sucessfully" << endl; //if true, promote the account and printout a message confirm
        return true;
    }
    else { //if false check if the account is Vip or have not meet the requirement and printout message accordingly
        if (type == "VIP") {
            cout << "You cannot promote your account any further" << endl;
        }
        else {
            cout << "You have not meet the requirement to promote your account" << endl;
        }
        return false;
    }
}
//Function used to promote multiple custumer
bool promoteCustomerRec(AccountManager* accountList) {
    vector<Account*> promotableAcc = accountList->displayPromotableAccount(); //get the list of all account that have meet the requirement to be promote

    //if no account have can be promote, return to the menu
    if (promotableAcc.size() == 0) {
        return false;
    }

    //If there is account that can be promote, get the account id to process to the promotion
    string accountID = getAccountID();

    if (accountID == "Exit") { //exit to the main menu
        return false;
    }

    promoteCustomer(accountID, accountList); //Call the function to promote the account base on the id input

    //Repeat the process until there is no available account for promotion or user input Exit
    while (accountID != "Exit") {
        return promoteCustomerRec(accountList);
    }

    return true;
}

//Function used to rent an Item
bool rentItemRec(AccountManager* accountList, string accountID, ItemManager* itemList) {
    vector<Item*> availableList = accountList->displayAllAvailable(accountID, itemList); //get the list of all the item that a particular account can rent

    string itemID;

    //Check if the account can rent any item in the store
    if (availableList.size() == 0) { //if no prinout a warning message
        cout << "\nThe account " << accountID << " have already rent all item from the store and therefore cannot rent anymore item\n";
        return false;
    }
    else { //If yes get the id of the item the account want to rent
        itemID = getItemID();
    }

    //If user input exit, return to main menu
    if (itemID == "Exit") {
        return false;
    }

    //Loop through the array to get the item that match the id input
    for (Account* account : accountList->getAccountList()) {
        if (account->getId() == accountID) { //if found then rent the item
            account->rentItem(itemID, itemList);
            break;
        }
    }

    itemList->saveToFile(); //update to file

    //Repeat the process until there is no available item for rent to this account or user input Exit
    while (itemID != "Exit") {
        return rentItemRec(accountList, accountID, itemList);
    }

    return true;
}
//Function to get the account that want to rent item(s)
bool rentItem(AccountManager* accountList, ItemManager* itemList) {
    accountList->displaySortedAccountID(); //display all available account
    string accountID = getAccountID(); //get user input

    //If user input exit, return to main menu
    if (accountID == "Exit") {
        return false;
    }

    //call the function to rent the item for the account match the id input
    return rentItemRec(accountList, accountID, itemList);
}

//Function used to return an Item
bool returnItemRec(AccountManager* accountList, string accountID, ItemManager* itemList) {
    vector<Item*> rentedList = accountList->displayAllRental(accountID, itemList); //get the list of all the item that a particular account currently rent

    string itemID;

    //Check if the account can rent any item in the store
    if (rentedList.size() == 0) { //if no prinout a warning message
        cout << "\nThe account " << accountID << " have not rent any item from the store and therefore cannot return any item\n";
        return false;
    }
    else { //If yes get the id of the item the account want to rent
        itemID = getItemID();
    }

    //If user input exit, return to main menu
    if (itemID == "Exit") {
        return false;
    }

    //Loop through the array to get the item that match the id input
    for (Account* account : accountList->getAccountList()) {
        if (account->getId() == accountID) {
            account->returnItem(itemID, itemList);
            break;
        }
    }

    itemList->saveToFile(); //update to file

    //Repeat the process until there is no available item for rent to this account or user input Exit
    while (itemID != "Exit") {
        return returnItemRec(accountList, accountID, itemList);
    }

    return true;
}
//Function to get the account that want to return item(s)
bool returnItem(AccountManager* accountList, ItemManager* itemList) {
    accountList->displaySortedAccountID(); //display all available account
    string accountID = getAccountID(); //get user input

    //If user input exit, return to main menu
    if (accountID == "Exit") {
        return false;
    }

    //call the function to return the item for the account match the id input
    return returnItemRec(accountList, accountID, itemList);
}

//Function for display sorted item sub menu
void displayItemSubMenu(ItemManager* itemList) {
    string input;

    //available option
    string option = "\nChoose one of the options below\n"
        "1. Sorted item by id\n"
        "2. Sorted item by title\n"
        "3. Exit\n";

    //while loop that get user input and prinout accordingly
    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") { //if input = 1 --> display sorted item based on id
            itemList->displaySortedItemID();
        }
        else if (input == "2") { //if input = 2 --> display sorted item based on title
            itemList->displaySortedItemTitle();
        }
        else if (input == "3") { //if input = 3 --> exit to main menu
            cout << "\nExit\n" << endl;
            break;
        }
        else { //display error message if input is invalid
            cerr << "\nInvalid input." << endl;
        }
    }
}

//Function call the method to display all item that are out of stock
void displayItemOutOfStock(ItemManager* itemList) {
    itemList->getAllNoStock();
}

//Function for display sorted item sub menu
void displayCustomerSubMenu(AccountManager* accountList) {
    string input;

    //available option
    string option = "\nChoose one of the options below\n"
        "1. Sorted customer by id\n"
        "2. Sorted customer by name\n"
        "3. Exit\n";

    //while loop that get user input and prinout accordingly
    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") { //if input = 1 --> display sorted account based on id
            accountList->displaySortedAccountID();
        }
        else if (input == "2") { //if input = 2 --> display sorted account based on name
            accountList->displaySortedAccountName();
        }
        else if (input == "3") { //if input = 3 --> exit to main menu
            cout << "Exit" << endl;
            break;
        }
        else { //display error message if input is invalid
            cerr << "\nInvalid input." << endl;
        }
    }
}

//Function that call method to display group of account with the same type/level
void displayCustomerByGroupSubMenu(AccountManager* accountList) {
    string input;

    //available option
    string option = "\nChoose one of the option below\n"
        "1. Guest Accounts\n"
        "2. Regular Accounts\n"
        "3. VIP Accounts\n"
        "4. Exit\n";

    //while loop that get user input and prinout accordingly
    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") { //if input = 1 --> display all Guest account
            accountList->getAccountByLevel("Guest");
        }
        else if (input == "2") { //if input = 2 --> display all Regular account
            accountList->getAccountByLevel("Regular");
        }
        else if (input == "3") { //if input = 3 --> display all VIP account
            accountList->getAccountByLevel("VIP");
        }
        else if (input == "4") { //if input = 4 --> exit to main menu
            cout << "\nExit\n" << endl;
            break;
        }
        else { //display error message if input is invalid
            cerr << "\nInvalid input." << endl;
        }
    }
}

//Function for search item sub menu
void searchItemSubMenu(ItemManager* itemList) {
    string input;

    //available option
    string option = "\nChoose one of the options below\n"
        "1. Search item by title\n"
        "2. Search item by id\n"
        "3. Exit\n";

    //while loop that get user input and prinout accordingly
    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") { //if input = 1 --> call method to search for item by title
            string title;
            cout << "Please enter the name you want to find: ";

            getline(cin, title); //get user input for title search

            //trim string
            title.erase(title.find_last_not_of(" ") + 1);
            title.erase(0, title.find_first_not_of(" "));

            if (title == "Exit") { //exit to the main menu
                break;
            }

            itemList->searchItem(title); //call the search method
        }
        else if (input == "2") { //if input = 2 --> call method to search for item by id
            string itemID = getItemID(); //get user input for id search

            if (itemID == "Exit") { //exit to the main menu
                break;
            }

            const char* id = itemID.c_str();
            itemList->searchItem(id); //call the search method
        }
        else if (input == "3") { //if input = 3 --> exit to the main menu
            cout << "\nExit\n\n" << endl;
            break;
        }
        else { //display error message if input is invalid
            cerr << "\nInvalid input." << endl;
        }
    }
}

//Function for search item sub menu
void searchCustomerSubMenu(AccountManager* accountList) {
    string input;

    //available option
    string option = "\nChoose one of the options below\n"
        "1. Search customer by name\n"
        "2. Search customer by id\n"
        "3. Exit\n";

    //while loop that get user input and prinout accordingly
    while (true) {
        cout << option << endl;

        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") { //if input = 1 --> call method to search for account by name
            string name;
            cout << "Please enter the name you want to find: ";

            getline(cin, name); //get user input for name search

            //trim string
            name.erase(name.find_last_not_of(" ") + 1);
            name.erase(0, name.find_first_not_of(" "));

            if (name == "Exit") { //exit to the main menu
                break;
            }

            accountList->searchAccount(name); //call the search method

        }
        else if (input == "2") { //if input = 2 --> call method to search for account by id
            string accID = getAccountID(); //get user input for id search

            if (accID == "Exit") { //exit to the main menu
                break;
            }

            const char* id = accID.c_str();
            accountList->searchAccount(id); //call the search method
        }
        else if (input == "3") { //if input = 3 --> exit to the main menu
            cout << "\nExit\n" << endl;
            break;
        }
        else { //display error message if input is invalid
            cerr << "\nInvalid input." << endl;
        }
    }
}

//Main Function
int main(int argc, char* argv[])
{
    ItemManager* itemList = nullptr; //read file and create an array of all Item

    AccountManager* accountList = nullptr; //read file and create an array of all Account

    if (argc == 1) {
        itemList = new ItemManager(); //read file and create an array of all Item

        accountList = new AccountManager(); //read file and create an array of all Account
    }
    else if (argc == 3) {
        itemList = new ItemManager(argv[1]); //read file and create an array of all Item

        accountList = new AccountManager(argv[2]); //read file and create an array of all Account
    }
    else {
        cout << "Please enter either\n 1/Only enter the the mainFileName.exe\n 2/Or mainFileName.exe itemFileName.txt customerFileName.txt\n";
        return 0;
    }

    cout << "\nWelcome to Genie’s video store\n";
    string input;

    //available option
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
        "12/ Exit.\n";
    //"13/ display all\n";

    cout << setprecision(3); //prinout double as x.xxx where x is number
    cout << fixed;

    //While true loop that ask for user choice from available option and call the function accordingly
    while (true) {
        cout << option << endl;
        getline(cin, input);

        //trim string
        input.erase(input.find_last_not_of(" ") + 1);
        input.erase(0, input.find_first_not_of(" "));

        if (input == "1") { //input = 1 --> call add, update, delete item submenu
            itemSubMenu(itemList);
        }
        else if (input == "2") { //input = 2 --> call add, update account submenu
            customerSubMenu(accountList);
        }
        else if (input == "3") { //input = 3 --> call promote function
            promoteCustomerRec(accountList);
            accountList->saveToFile();
        }
        else if (input == "4") { //input = 4 --> call rent function
            rentItem(accountList, itemList);
            accountList->saveToFile();
        }
        else if (input == "5") { //input = 5 --> call return function
            returnItem(accountList, itemList);
            accountList->saveToFile();
        }
        else if (input == "6") { //input = 6 --> call display sorted item function submenu
            displayItemSubMenu(itemList);
        }
        else if (input == "7") { //input = 7 --> call display all out of stock item
            displayItemOutOfStock(itemList);
        }
        else if (input == "8") { //input = 8 --> call display sorted account function submenu
            displayCustomerSubMenu(accountList);
        }
        else if (input == "9") { //input = 9 --> call display group of account by level function
            displayCustomerByGroupSubMenu(accountList);
        }
        else if (input == "10") { //input = 10 --> call search item function submenu
            searchItemSubMenu(itemList);
        }
        else if (input == "11") { //input = 11 --> call search account function submenu
            searchCustomerSubMenu(accountList);
        }
        /*else if (input == "13") { //input = 11 --> call search account function submenu
            accountList->displayAll();
        }*/
        else if (input == "12") { //input = 12 --> exit program

            //Printout team member
            cout << "\n\nASSIGNMENT 2 GROUP 24" << endl;
            cout << "s3819293, s3819293@rmit.edu.vn, Thi Nha Uyen, Nguyen" << endl;
            cout << "s3818221, s3818221@rmit.edu.vn, Khoi Nguyen, Truong" << endl;
            cout << "s3877256, s3877256@rmit.edu.vn, Phuong Nam, Nguyen" << endl;
            cout << "s3878451, s3878451@rmit.edu.vn, Hoang Long, Nguyen" << endl;

            break;
        }
        else { //display error message if input is invalid
            cerr << "\nInvalid input." << endl;
        }

    }

    return 0;

}