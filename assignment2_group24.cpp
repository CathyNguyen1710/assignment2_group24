#include "AccountManager.h"
#include "ItemManager.h"
#include "AccountClass/Account.h"

#include <iostream>
#include <string>

using namespace std;

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


int main(int argc, char* argv[])
{
    cout << "Welcome to Genie’s video store" << "\n\n";
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
            cout << "Call function 1" << endl;
        }
        else if (input == "2") {
            cout << "Call function 2" << endl;
        }
        else if (input == "3") {
            cout << "Call function 3" << endl;
        }
        else if (input == "4") {
            cout << "Call function 4" << endl;
        }
        else if (input == "5") {
            cout << "Call function 5" << endl;
        }
        else if (input == "6") {
            cout << "Call function 6" << endl;
        }
        else if (input == "7") {
            cout << "Call function 7" << endl;
        }
        else if (input == "8") {
            cout << "Call function 8" << endl;
        }
        else if (input == "9") {
            cout << "Call function 9" << endl;
        }
        else if (input == "10") {
            cout << "Call function 10" << endl;
        }
        else if (input == "11") {
            cout << "Call function 11" << endl;
        }
        else if (input == "Exit") {
            //cout << "Exit" << endl;

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

