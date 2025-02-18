/*************************************************************************
** Author : Ally Cooper
** Program : HW2
** Date Created : February 15, 2025
** Date Last Modified : February 18, 2025
** Usage : No command line arguments
**
** Problem:
Define a Check struct and a CheckBook class with various functionalities.
Implement functions for depositing, writing checks, displaying checks,
and handling checkbook size dynamically.
*************************************************************************/

#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<cstdlib>
using namespace std;

struct Check {
    int CheckNum;
    string CheckMemo;
    float CheckAmount;

    bool operator>(float amount) const {
        return CheckAmount > amount;
    }

    friend ostream& operator<<(ostream& os, const Check& check) {
        os << "Check Number: " << check.CheckNum << ", Amount: $" << check.CheckAmount
           << ", Memo: " << check.CheckMemo;
        return os;
    }
};

class CheckBook {
private:
    float balance;
    Check* chkPtr;
    float lastDeposit;
    int numOfChecks;
    int checkBookSize;
    static string memos[6];

    void doubleCheckBook() {
        Check* temp = new Check[checkBookSize * 2];
        for (int i = 0; i < checkBookSize; i++) {
            temp[i] = chkPtr[i];
        }
        delete[] chkPtr;
        chkPtr = temp;
        checkBookSize *= 2;
        cout << "Warning: Checkbook size doubled to " << checkBookSize << " checks.\n";
    }

public:
    CheckBook() : balance(0), numOfChecks(0), checkBookSize(4) {
        chkPtr = new Check[checkBookSize];
    }

    CheckBook(float initialBalance) : balance(initialBalance), numOfChecks(0), checkBookSize(2) {
        chkPtr = new Check[checkBookSize];
    }

    ~CheckBook() {
        delete[] chkPtr;
    }

    void deposit(float amount) {
        balance += amount;
        lastDeposit = amount;
    }

    bool writeCheck(float amount) {
        if (amount > balance) return false;
        if (numOfChecks >= checkBookSize / 2) doubleCheckBook();

        chkPtr[numOfChecks].CheckNum = numOfChecks + 1;
        chkPtr[numOfChecks].CheckAmount = amount;
        chkPtr[numOfChecks].CheckMemo = memos[rand() % 6];
        balance -= amount;
        numOfChecks++;
        return true;
    }

    void displayChecks() const {
        for (int i = numOfChecks - 1; i >= 0; i--) {
            cout << chkPtr[i] << endl;
        }
    }
};

string CheckBook::memos[6] = {"wedding", "baby shower", "pizza", "children hospital", "barber shop", "plumber"};

void checkTest(CheckBook& book, float balance) {
    while (balance > 0.1) {
        float amount = (rand() % 20) + 1;
        if (!book.writeCheck(amount)) break;
        balance -= amount;
    }
    book.displayChecks();
}

int main() {
    srand(time(0));
    CheckBook myCheckBook(500);
    checkTest(myCheckBook, 500);
    return 0;
}
