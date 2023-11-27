#include <stdio.h>
#include <iostream>
using namespace std;

class Account {
    private:
        string accountNumber, accountHolder;
        double balance;
    public:
        Account() {
            accountNumber = "0000";
            accountHolder = " ";
            balance = 0;
        }
        Account(string num, string name, double bal) {
            accountNumber = num;
            accountHolder = name;
            balance = bal;
        }

        string getNumber() {
            return accountNumber;
        }
        string getName() {
            return accountHolder;
        }
        double getBalance() {
            return balance;
        }
        void deposit(double amount) {
            balance += amount;
        }
        void withdraw(double amount) {
            balance -= amount;
        }

        friend ostream& operator <<(ostream& os, Account& ac) {
            os << "\nAccount Details for Account (ID: " << ac.getNumber() << "):";
            os << "\n\tHolder: " << ac.getName();
            os << "\n\tBalance: $" << ac.getBalance() << endl;
            return os;
        }
        void displayDetails() {
            cout << (*this);
        }
};

class SavingsAccount: public Account {
    private:
        double interestRate;
    public:
        SavingsAccount() : Account() {
            interestRate = 0;
        }
        SavingsAccount(string num, string name, double balance, double interest) : Account(num, name, balance) {
            interestRate = interest;
        }

        double getInterestRate() {
            return interestRate;
        }

        void withdraw(double amount) {
            double curBalance = (*this).Account::getBalance();
            if (((curBalance - amount) > 500)) {
                (*this).Account::withdraw(amount);
            }
        }

        friend ostream& operator <<(ostream& os, SavingsAccount& sc) {
            os << "\nAccount Details for Savings Account (ID: " << sc.getNumber() << "):";
            os << "\n\tHolder: " << sc.getName();
            os << "\n\tBalance: $" << sc.getBalance();
            os << "\n\tInterest Rate: " << sc.getInterestRate() * 100.00 << "%" << endl;
            return os;
        }
        void displayDetails() {
            cout << (*this);
        }
};

class CurrentAccount: public Account {
    private:
        double overdraftLimit;
    public:
        CurrentAccount() : Account() {
            overdraftLimit = 0;
        }
        CurrentAccount(string num, string name, double bal, double limit) : Account(num, name, bal) {
            overdraftLimit = limit;
        }

        double getOverdraftLimit() {
            return overdraftLimit;
        }

        void withdraw(double amount) {
            double curBalance = (*this).Account::getBalance();
            if (((curBalance - amount) <= (curBalance + overdraftLimit)) && ((curBalance - amount) >= -overdraftLimit)) {
                (*this).Account::withdraw(amount);
            }
        }

        CurrentAccount operator+(SavingsAccount& b) {
            CurrentAccount result(this->getNumber(), this->getName(), this->getBalance() + 300, this->getOverdraftLimit());
            b.withdraw(300);
            return result;
        }
        friend ostream& operator <<(ostream& os, CurrentAccount& ca) {
            os << "\nAccount Details for Current Account (ID: " << ca.getNumber() << "):";
            os << "\n\tHolder: " << ca.getName();
            os << "\n\tBalance: $" << ca.getBalance();
            os << "\n\tOverdraft Limit: $" << ca.getOverdraftLimit() << endl;
            return os;
        }
        void displayDetails() {
            cout << (*this);
        }
};

int main() {
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);
    
    savings.displayDetails();
    current.displayDetails();
    
    savings.deposit(500);
    current.withdraw(1000);
    cout << "\nAccount Details after deposit and withdrawal:";

    savings.displayDetails();
    current.displayDetails();

    // Transfer 300 from savings to current
    current = current + savings;
    cout << "\nAccount Details after transfer:";

    savings.displayDetails();
    current.displayDetails();
    return 0;
}