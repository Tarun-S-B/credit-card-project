#include <bits/stdc++.h>
using namespace std;

class User
{
private:
    int id;
    string name;
    string email;

public:
    User(int id, string &name, string &email)
        : id(id), name(name), email(email) {}

    int getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    string getEmail()
    {
        return email;
    }

    void setEmail(string &newEmail)
    {
        email = newEmail;
    }
};

class Transaction
{
private:
    int userId;
    double amount;
    string description;

public:
    Transaction(int userId, double amount, string description)
        : userId(userId), amount(amount), description(description) {}

    int getUserId()
    {
        return userId;
    }

    double getAmount()
    {
        return amount;
    }

    string getDescription()
    {
        return description;
    }
};

class System
{
private:
    vector<User> users;
    vector<Transaction> transactions;

public:
    void viewMenu()
    {
        cout << "1. New User" << endl;
        cout << "2. Renewal or Replacement" << endl;
        cout << "3. Transaction" << endl;
        cout << "4. Monthly Statement Generation" << endl;
        cout << "0. Shut Down" << endl;
    }

    void newUserMenu()
    {
        int id;
        string name, email;

        cout << "Enter User ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter User Name: ";
        getline(cin, name);
        cout << "Enter User Email: ";
        cin >> email;

        users.push_back(User(id, name, email));
        cout << "New user added successfully!" << endl;
    }

    void replacementMenu()
    {
        int userId;
        string newEmail;
        cout << "Enter User ID for Renewal/Replacement: ";
        cin >> userId;
        cout << "Enter New Email: ";
        cin >> newEmail;

        for (auto user : users)
        {
            if (user.getId() == userId)
            {
                user.setEmail(newEmail);
                cout << "Email updated successfully!" << endl;
                return;
            }
        }
        cout << "User ID not found." << endl;
    }

    void transactionMenu()
    {
        int userId;
        double amount;
        string description;

        cout << "Enter User ID: ";
        cin >> userId;
        cout << "Enter Transaction Amount: ";
        cin >> amount;
        cin.ignore();
        cout << "Enter Transaction Description: ";
        getline(cin, description);

        transactions.push_back(Transaction(userId, amount, description));
        cout << "Transaction recorded successfully!" << endl;
    }

    void statementGenMenu()
    {
        int userId;
        cout << "Enter User ID for Statement Generation: ";
        cin >> userId;

        double totalAmount = 0.0;
        cout << "Monthly Statement for User ID: " << userId << endl;
        cout << "---------------------------------" << endl;
        for (auto &transaction : transactions)
        {
            if (transaction.getUserId() == userId)
            {
                cout << "Amount: " << transaction.getAmount()
                     << ", Description: " << transaction.getDescription() << endl;
                totalAmount += transaction.getAmount();
            }
        }
        cout << "---------------------------------" << endl;
        cout << "Total Amount: " << totalAmount << endl;
    }
};

int main()
{
    System system;
    int choice;
    do
    {
        system.viewMenu();
        cin >> choice;

        switch (choice)
        {
        case 0:
            cout << "Shutting Down.." << endl;
            break;
        case 1:
            system.newUserMenu();
            break;
        case 2:
            system.replacementMenu();
            break;
        case 3:
            system.transactionMenu();
            break;
        case 4:
            system.statementGenMenu();
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 0);

    return 0;
}