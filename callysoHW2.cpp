/*************************************************************************
** Author : Ally Cooper
** Program : HW2
** Date Created : February 15, 2025
** Date Last Modified : February 18, 2025
** Usage : No command line arguments
**
** Problem:
** This program simulates a checkbook system using a struct and a class.
** It allows for deposits, writing checks, and dynamically expanding the checkbook.
*************************************************************************/

#include <iostream>
#include <string>
using namespace std;

// Struct to represent a Check
struct Check {
    int CheckNum;
    string CheckMemo;
    float CheckAmount;

    // Overloaded operator to compare check amount with a float
    bool operator>(float amount) const {
        return CheckAmount > amount;
    }

    // Overloaded << operator for printing Check details
    friend ostream& operator<<(ostream& os, const Check& check) {
        os << "Check Number: " << check.CheckNum << ", Memo: " << check.CheckMemo << ", Amount: $" << check.CheckAmount;
        return os;
    }
};

// Class to manage the CheckBook
class CheckBook {
private:
    float balance;
    Check* chkPtr;
    float lastDeposit;
    int numOfChecks;
    int checkBookSize;

    void expandCheckBook() {
        // Function to double the checkbook size when half of it is used
        if (numOfChecks >= checkBookSize / 2) {
            checkBookSize *= 2;
            Check* newChkPtr = new Check[checkBookSize];
            for (int i = 0; i < numOfChecks; i++) {
                newChkPtr[i] = chkPtr[i];
            }
            delete[] chkPtr;
            chkPtr = newChkPtr;
            cout << "Warning: Checkbook size doubled to " << checkBookSize << " checks." << endl;
        }
    }

public:
    // Default constructor
    CheckBook() : balance(0), numOfChecks(0), checkBookSize(4), chkPtr(new Check[4]) {}

    // Constructor with initial balance
    CheckBook(float initialBalance) : balance(initialBalance), numOfChecks(0), checkBookSize(2), chkPtr(new Check[2]) {}

    // Destructor
    ~CheckBook() {
        delete[] chkPtr;
    }

    // Function to deposit money into the checkbook
    void deposit(float amount) {
        balance += amount;
        lastDeposit = amount;
        cout << "Deposited: $" << amount << ", New Balance: $" << balance << endl;
    }

    // Function to write a check
    bool writeCheck(float amount) {
        if (amount > balance) {
            cout << "Insufficient funds! Cannot write check." << endl;
            return false;
        }
        balance -= amount;
        chkPtr[numOfChecks].CheckNum = numOfChecks + 1;
        chkPtr[numOfChecks].CheckMemo = "Expense";
        chkPtr[numOfChecks].CheckAmount = amount;
        numOfChecks++;
        expandCheckBook();
        cout << "Check written for $" << amount << " | Remaining Balance: $" << balance << endl;
        return true;
    }

    // Function to display all checks written
    void displayChecks() const {
        cout << "Check History:" << endl;
        for (int i = numOfChecks - 1; i >= 0; i--) {
            cout << chkPtr[i] << endl;
        }
    }
};

// Function to test writing checks until balance is exhausted
void checkTest(CheckBook& cb, float balance) {
    while (balance > 0) {
        float checkAmount = 10.0; // Writing small checks for testing
        if (!cb.writeCheck(checkAmount)) break;
        balance -= checkAmount;
    }
    cb.displayChecks();
}

// Main function
int main() {
    CheckBook myCheckBook(200.0); // Initialize checkbook with $200 balance
    checkTest(myCheckBook, 200.0);
    return 0;
}
