#include <iostream>
using namespace std;

// ---------------- Base Class ----------------
class BankAccount {
protected:
    int accountNumber;
    string accountHolderName;

private:
    double balance;   

public:
    BankAccount(int accNo, string name, double bal) {
        accountNumber = accNo;
        accountHolderName = name;
        balance = bal;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Amount Deposited Successfully!" << endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawal Successful!" << endl;
        } else {
            cout << "Insufficient Balance!" << endl;
        }
    }

    double getBalance() {
        return balance;
    }

    void displayAccountInfo() {
        cout << "\n--- Account Info ---" << endl;
        cout << "Account No: " << accountNumber << endl;
        cout << "Holder Name: " << accountHolderName << endl;
        cout << "Balance: ₹" << balance << endl;
    }

    virtual void calculateInterest() {
        cout << "No interest for base account." << endl;
    }
};

// ---------------- Savings Account ----------------
class SavingsAccount : public BankAccount {
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double bal, double rate)
        : BankAccount(accNo, name, bal) {
        interestRate = rate;
    }

    void calculateInterest() {
        double interest = getBalance() * interestRate / 100;
        cout << "Savings Interest: ₹" << interest << endl;
    }
};

// ---------------- Checking Account ----------------
class CheckingAccount : public BankAccount {
    double overdraftLimit;

public:
    CheckingAccount(int accNo, string name, double bal, double limit)
        : BankAccount(accNo, name, bal) {
        overdraftLimit = limit;
    }

    void withdraw(double amount) {
        if (amount <= getBalance() + overdraftLimit) {
            cout << "Withdrawal Allowed (Overdraft if needed)" << endl;
        } else {
            cout << "Overdraft limit exceeded!" << endl;
        }
    }
};

// ---------------- Fixed Deposit Account ----------------
class FixedDepositAccount : public BankAccount {
    int term; // months

public:
    FixedDepositAccount(int accNo, string name, double bal, int t)
        : BankAccount(accNo, name, bal) {
        term = t;
    }

    void calculateInterest() {
        double rate = 6.5;
        double interest = (getBalance() * rate * term) / (100 * 12);
        cout << "FD Interest: ₹" << interest << endl;
    }
};

// ---------------- Main Program ----------------
int main() {

    BankAccount *account = NULL;
    int choice;

    cout << "==== Banking System ====" << endl;
    cout << "1. Create Savings Account" << endl;
    cout << "2. Create Checking Account" << endl;
    cout << "3. Create Fixed Deposit Account" << endl;
    cout << "Enter choice: ";
    cin >> choice;

    int accNo;
    string name;
    double bal;

    cout << "Enter Account Number: ";
    cin >> accNo;
    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Initial Balance: ";
    cin >> bal;

    if (choice == 1) {
        double rate;
        cout << "Enter Interest Rate: ";
        cin >> rate;
        account = new SavingsAccount(accNo, name, bal, rate);
    }
    else if (choice == 2) {
        double limit;
        cout << "Enter Overdraft Limit: ";
        cin >> limit;
        account = new CheckingAccount(accNo, name, bal, limit);
    }
    else if (choice == 3) {
        int term;
        cout << "Enter Term (in months): ";
        cin >> term;
        account = new FixedDepositAccount(accNo, name, bal, term);
    }
    else {
        cout << "Invalid Choice!" << endl;
        return 0;
    }

    int option;
    do {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Display Account" << endl;
        cout << "4. Calculate Interest" << endl;
        cout << "5. Exit" << endl;
        cout << "Choice: ";
        cin >> option;

        double amt;

        switch(option) {
        case 1:
            cout << "Enter amount: ";
            cin >> amt;
            account->deposit(amt);
            break;

        case 2:
            cout << "Enter amount: ";
            cin >> amt;
            account->withdraw(amt);
            break;

        case 3:
            account->displayAccountInfo();
            break;

        case 4:
            account->calculateInterest();
            break;

        case 5:
            cout << "Thank you!" << endl;
            break;

        default:
            cout << "Invalid Input!" << endl;
        }

    } while(option != 5);

    return 0;
}
