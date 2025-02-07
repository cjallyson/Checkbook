#include <iostream>
#include <string>

using namespace std;

// Constants
const int N = 5; // Maximum checks per checkbook
const int MAX_ALL_CHECKS = 10; // Global limit on all checks

// Struct implementation for Question 1
struct Check {
    int checkNum;       // Check number
    string checkMemo;   // Memo for the check (description)
    float checkAmount;  // Amount of the check
};

// Class implementation for Question 2
class CheckClass {
private:
    static int number;  // Static variable to track the total number of checks
    int checkNum;       // Check number
    string checkMemo;   // Memo for the check
    float checkAmount;  // Amount of the check

public:
    // Default constructor to initialize the check with default values
    CheckClass() : checkNum(number), checkMemo(""), checkAmount(0.0) {
        number++;  // Increment the static variable number for each new check
    }

    // Getter for check number
    int getCheckNum() const { return checkNum; }

    // Getter for memo
    string getCheckMemo() const { return checkMemo; }

    // Getter for check amount
    float getCheckAmount() const { return checkAmount; }

    // Setter for memo
    void setCheckMemo(string memo) { checkMemo = memo; }

    // Setter for check amount
    void setCheckAmount(float amount) { checkAmount = amount; }
};

// Initialize the static variable
int CheckClass::number = 0;

// CheckBook class to manage a checkbook
class CheckBook {
private:
    float balance;        // Balance of the checkbook
    CheckClass checks[N]; // Array to hold checks in the checkbook
    float lastDeposit;    // Last deposited amount
    int numOfChecks;      // Counter to track the number of checks written
    const int checkLimit = N; // Limit of checks the checkbook can hold

public:
    static int allChecks; // Static variable to track all checks written across all checkbooks

    // Default constructor to initialize checkbook with a balance of 0 and no checks written
    CheckBook() : balance(0), numOfChecks(0), lastDeposit(0) {}

    // Constructor to initialize the checkbook with a given balance
    CheckBook(float initialBalance) : balance(initialBalance), numOfChecks(0), lastDeposit(0) {}

    // Deposit function to add money to the balance
    void deposit(float amount) {
        balance += amount;  // Increase balance by the deposit amount
        lastDeposit = amount; // Record the last deposit amount
    }

    // Function to display all checks written in the checkbook, in reverse order (most recent first)
    void displayChecks() {
        // Loop through the checks array and display the details in reverse order
        for (int i = numOfChecks - 1; i >= 0; i--) {
            cout << checks[i].getCheckAmount() << " " << checks[i].getCheckNum() << " " << checks[i].getCheckMemo() << endl;
        }
    }

    // Getter for allChecks to get the total checks written across all checkbooks
    int getAllChecks() const {
        return allChecks;
    }

    // Function to write a check
    bool writeCheck(float amount) {
        // Check if conditions are met: numOfChecks < checkLimit, allChecks < MAX_ALL_CHECKS, and balance >= amount
        if (numOfChecks < checkLimit && allChecks < MAX_ALL_CHECKS && balance >= amount) {
            // Ask for memo for the check
            string memo;
            cout << "Memo? ";
            cin >> memo;

            // Store the details of the check in the current check in the checks array
            checks[numOfChecks].setCheckMemo(memo);
            checks[numOfChecks].setCheckAmount(amount);

            // Update the balance by subtracting the check amount
            balance -= amount;
            // Increment the number of checks written and the total checks written across all checkbooks
            numOfChecks++;
            allChecks++;

            return true; // Return true indicating the check was successfully written
        }

        return false; // Return false if the conditions are not met
    }
};

// Initialize the static variable
int CheckBook::allChecks = 0;

// Main function to test the CheckBook system
int main() {
    // Create two checkbook instances with different initial balances
    CheckBook cb1(1000), cb2(500);

    // Write 10 checks: 5 for each checkbook
    for (int i = 0; i < 10; i++) {
        cb1.writeCheck(150); // Write a check of $150 in cb1
        cb2.writeCheck(130); // Write a check of $130 in cb2
    }

    // Display the details of the checks written in cb1
    cout << "cb1 check details" << endl;
    cb1.displayChecks();

    // Display the details of the checks written in cb2
    cout << "cb2 check details" << endl;
    cb2.displayChecks();

    // Output the total number of checks written across all checkbooks
    cout << cb1.getAllChecks() << endl;
    cout << cb2.getAllChecks() << endl;

    return 0; // End of main function
}
