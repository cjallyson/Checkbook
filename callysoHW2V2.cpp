/* *************************************************************************
** Author : Ally Cooper
** Program : HW2
** Date Created : February 15, 2025
** Date Last Modified : February 18, 2025
** Usage : No command line arguments
**
** Problem:
Define a Check struct and a CheckBook class to simulate check writing.
Include various member functions, overloading operators, and dynamic memory handling.
************************************************************************* */

#include <iostream>
#include <string>
using namespace std;

struct Check {
    int CheckNum;
    string CheckMemo;
    float CheckAmount;

    bool operator>(float amount) const {
        return CheckAmount > amount;
    }

    friend ostream& operator<<(ostream& os, const Check& c) {
        os << "Check Number: " << c.CheckNum << " | Memo: " << c.CheckMemo << " | Amount: " << c.CheckAmount;
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

    bool writeCheck(Check c) {
        if (!(c > balance)) {
            if (numOfChecks >= checkBookSize / 2) {
                checkBookSize *= 2;
                Check* temp = new Check[checkBookSize];
                for (int i = 0; i < numOfChecks; i++) {
                    temp[i] = chkPtr[i];
                }
                delete[] chkPtr;
                chkPtr = temp;
                cout << "New checkbook ordered, size doubled.\n";
            }

            chkPtr[numOfChecks] = c;
            balance -= c.CheckAmount;
            numOfChecks++;
            return true;
        }
        return false;
    }

    void displayChecks() const {
        for (int i = numOfChecks - 1; i >= 0; i--) {
            cout << chkPtr[i] << endl;
        }
    }
};

void checkTest(CheckBook& cb, float balance) {
    while (balance > 0) {
        Check c = { rand() % 1000, "Test Memo", (float)(rand() % 100 + 1) };
        if (!cb.writeCheck(c)) break;
        balance -= c.CheckAmount;
    }
    cb.displayChecks();
}

int main() {
    CheckBook myCheckBook(1000);
    checkTest(myCheckBook, 1000);
    return 0;
}
