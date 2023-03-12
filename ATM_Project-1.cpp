#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Account {
public:
    int accountNumber;
    string password;
    double balance;
};

class ATM {
public:
    void login(int accountNumber, string password);
    void deposit(double amount);
    void withdraw(double amount);
    void balanceInquiry();
};

int main() {
    // Load accounts from file
    vector<Account> accounts;
    ifstream inFile("accounts.txt");
    if (inFile.is_open()) {
        Account account;
        while (inFile >> account.accountNumber >> account.password >> account.balance) {
            accounts.push_back(account);
        }
        inFile.close();
    }
    
    // Prompt user for account number and password
    int accountNumber;
    string password;
    cout << "Enter account number: ";
    cin >> accountNumber;
    cout << "Enter password";
	cin >> password;
// Check if account exists
bool accountExists = false;
int accountIndex;
for (int i = 0; i < accounts.size(); i++) {
    if (accounts[i].accountNumber == accountNumber && accounts[i].password == password) {
        accountExists = true;
        accountIndex = i;
        break;
    }
}

// If account doesn't exist, prompt user to create a new one
if (!accountExists) {
    char createAccount;
    cout << "Account not found. Would you like to create a new account? (y/n)";
    cin >> createAccount;
    if (createAccount == 'y' || createAccount == 'Y') {
        Account newAccount;
        newAccount.accountNumber = accountNumber;
        newAccount.password = password;
        newAccount.balance = 0;
        accounts.push_back(newAccount);
        accountIndex = accounts.size() - 1;
        cout << "New account created successfully!" << endl;
    } else {
        cout << "Exiting program..." << endl;
        return 0;
    }
}

// Create ATM object for current account
ATM atm;
atm.login(accounts[accountIndex].accountNumber, accounts[accountIndex].password);

// Prompt user for ATM actions
char action;
do {
    cout << endl << "Choose an action:" << endl;
    cout << "1. Deposit" << endl;
    cout << "2. Withdraw" << endl;
    cout << "3. Balance Inquiry" << endl;
    cout << "4. Exit" << endl;
    cin >> action;
    switch (action) {
        case '1':
            double depositAmount;
            cout << "Enter amount to deposit: ";
            cin >> depositAmount;
            atm.deposit(depositAmount);
            accounts[accountIndex].balance += depositAmount;
            break;
        case '2':
            double withdrawAmount;
            cout << "Enter amount to withdraw: ";
            cin >> withdrawAmount;
            atm.withdraw(withdrawAmount);
            accounts[accountIndex].balance -= withdrawAmount;
            break;
        case '3':
            atm.balanceInquiry();
            break;
        case '4':
            break;
        default:
            cout << "Invalid action. Please try again." << endl;
            break;
    }
} while (action != '4');

// Save accounts to file
ofstream outFile("accounts.txt");
if (outFile.is_open()) {
    for (int i = 0; i < accounts.size(); i++) {
        outFile << accounts[i].accountNumber << " " << accounts[i].password << " " << accounts[i].balance << endl;
    }
    outFile.close();
}

cout << "Exiting program..." << endl;
return 0;
}
