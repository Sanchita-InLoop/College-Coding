#include <iostream>
#include <string>

using namespace std;

class BankManager;

class BankAccount {
private:
    int accountNumber;
    string accountHolder;
    double balance;

public:

    BankAccount() : accountNumber(0), accountHolder(""), balance(0.0) {}

    BankAccount(int accNo, string name, double initialBalance) {
        accountNumber = accNo;
        accountHolder = name;
        balance = initialBalance;
    }

    friend class BankManager;
};

class BankManager {
public:
    void displayAccountCount(int totalAccounts) {
        cout << "Total accounts in system: " << totalAccounts << endl;
    }

    void displayAccount(const BankAccount& acc) {
        if (acc.accountNumber == 0) return;
        cout << "Acc No: " << acc.accountNumber
             << " | Holder: " << acc.accountHolder
             << " | Balance: Rs." << acc.balance << endl;
    }

   void transfer(BankAccount& from, BankAccount& to, double amount) {
        if (hasSufficientBalance(from, amount)) {
            from.balance -= amount;
            to.balance += amount;
            cout << "Successfully transferred ₹" << amount
                 << " from " << from.accountHolder << " to " << to.accountHolder << endl;
        } else {
            cout << "Transfer failed: Insufficient balance in " << from.accountHolder << "'s account." << endl;
        }
    }

    bool hasSufficientBalance(const BankAccount& acc, double amount) {
        return acc.balance >= amount;
    }
};

int main() {
    const int MAX_ACCOUNTS = 2;
    BankAccount accounts[MAX_ACCOUNTS] = {
        BankAccount(101, "Sanchita", 50000.0),
        BankAccount(102, "Arjun", 30000.0)
    };

    BankManager manager;

    cout << "Banking System Status" << endl;
    manager.displayAccountCount(MAX_ACCOUNTS);

    cout << "\nInitial Account Details:" << endl;
    for(int i = 0; i < MAX_ACCOUNTS; i++) {
        manager.displayAccount(accounts[i]);
    }

    cout << "\nAttempting Transfer..." << endl;

    manager.transfer(accounts[0], accounts[1], 15000.0);

    cout << "\nUpdated Account Details:" << endl;
    for(int i = 0; i < MAX_ACCOUNTS; i++) {
        manager.displayAccount(accounts[i]);
    }

    cout << "\nChecking Balance for a 10k Purchase for Account 1 (Sanchita)..." << endl;
    if (manager.hasSufficientBalance(accounts[0], 10000.0)) {
        cout << "Sanchita can afford it." << endl;
    } else {
        cout << "Sanchita cannot afford it." << endl;
    }

    return 0;
}