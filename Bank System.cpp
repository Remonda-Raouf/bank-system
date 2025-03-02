#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <cctype>
using namespace std;

// create struct to create accounts
struct Account
{
    string name;
    string id;
    double balance;
    string password;
};

// array to store account
vector<Account> accounts;

// create new account
void createAccount()
{
    Account newAcc;
    cout << "\nEnter your name: ";
    cin.ignore();
    getline(cin, newAcc.name);
    while (true)
    {
        cout << "Enter a unique ID (14_Digit): ";
        getline(cin, newAcc.id);
        newAcc.id.erase(remove(newAcc.id.begin(), newAcc.id.end(), ' '), newAcc.id.end());//remove spaces
        bool f = true;
        for (char c : newAcc.id)
        {
            if (!isdigit(c))
            {
                f = false;
                break;
            }
        }
        // ID component of 14 digits 
        if (newAcc.id.size() != 14  || !f)
        {
            cout << "\033[31m" << "Invalid ID , must be 14 digit and not use charactars " << "\033[0m" << endl;
            continue;
        }
        bool exist = false;
        for (const auto& acc : accounts)
        {
            if (acc.id == newAcc.id)
            {
                exist = true;
                break;
            }
        }
        if (exist)
        {
            cout << "\033[33m" << "Account ID already exists, Try again" << "\033[0m" << endl;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        cout << "Set a strong password ( >= 6 Charactar): ";
        getline(cin, newAcc.password);
        newAcc.password.erase(remove(newAcc.password.begin(), newAcc.password.end(), ' '), newAcc.password.end());//remove spaces
        // password equal or greater than 6 digits
        if (newAcc.password.size() < 6)
        {
            cout << "\033[31m" << "Enter a 6_Digit Password" << "\033[0m" << endl;
        }
        else
        {
            break;
        }
    }
    while (true)
    {
        cout << "Enter initial deposit (>= 1000) : ";
        cin >> newAcc.balance;
        if (cin.fail())
        {
            cout << "\033[31m" << "Fail Input" << "\033[0m" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        // balance must at least 1000 
        if (newAcc.balance < 1000)
        {
            cout << "\033[31m" << "Enter Balance equal or greater than 1000" << "\033[0m" << endl;
        }
        else
        {
            break;
        }
    }

    accounts.push_back(newAcc);
    cout << "\033[32m" << "Account created successfully" << "\033[0m" << endl;
}

// login to account
int login()
{
    string accNum;
    string password;
    cout << "\nEnter ID: ";
    cin.ignore();
    getline(cin, accNum);
    accNum.erase(remove(accNum.begin(), accNum.end(), ' '), accNum.end());//remove spaces
    bool f = true;
    for (char c : accNum)
    {
        if (!isdigit(c))
        {
            f = false;
            break;
        }
    }
    if (accNum.size() != 14 || !f)
    {
        cout << "\033[31m" << "Invalid ID , must be 14 digit and not use charactar" << "\033[0m" << endl;
        return -1;
    }
    cout << "Enter password: ";
    getline(cin, password);
   password.erase(remove(password.begin(), password.end(), ' '), password.end());//remove spaces
        for (size_t i = 0; i < accounts.size(); i++)
        {
            // print data after login
            if (accounts[i].id == accNum && accounts[i].password == password)
            {
                cout << "\nAccount ID: " << accNum << endl;
                cout << "Balance: " << accounts[i].balance << endl;
                cout << "\033[32m" << "Login successful" << "\033[0m" << endl;
                return i;
                break;
            }
        }
    
    cout << "\033[31m" << "Invalid ID or password" << "\033[0m" << endl;
    return -1;
}

// deposit money
void deposit(int index)
{
    double amount;
    cout << "Enter deposit amount: ";
    cin >> amount;
    if (cin.fail())
    {
        cout << "\033[31m" << "Fail Input" << "\033[0m" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (amount > 0)
    {
        accounts[index].balance += amount;
        cout << "\033[32m" << "Deposit successful, New balance: " << "\033[0m" << accounts[index].balance << endl;
    }
    else
    {
        cout << "\033[31m" << "Invalid deposit amount" << "\033[0m" << endl;
    }
}

// withdraw money
void withdraw(int index)
{
    double amount;
    cout << "Enter withdrawal amount: ";
    cin >> amount;
    if (cin.fail())
    {
        cout << "\033[31m" << "Fail Input" << "\033[0m" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }
    if (amount > 0 && amount <= (accounts[index].balance - 20))
    {
        accounts[index].balance -= (amount + 20);
        cout << "\033[32m" << "Withdrawal successful, New balance: " << "\033[0m" << accounts[index].balance << endl;
    }
    else
    {
        cout << "\033[31m" << "Invalid withdrawal amount or insufficient funds" << "\033[0m" << endl;
    }
}

// check balance
void checkBalance(int index)
{ 
    cout << "\033[33m" << "\n---- Account Details ----" << "\033[0m" << endl;
    cout << "\033[33m" << "Account Name : " << "\033[0m" << accounts[index].name << endl;
    cout << "\033[33m" << "ID: " << "\033[0m" << accounts[index].id << endl;
    cout << "\033[33m" << "Balance: "<< "\033[0m" << accounts[index].balance << endl;
}

// transfer money from account to another account 
void transferMoney(int senderIndex)
{
    string receiverID;
    cout << "Enter recipient's ID: ";
    cin.ignore();
    getline(cin, receiverID);
    receiverID.erase(remove(receiverID.begin(), receiverID.end(), ' '), receiverID.end());//remove spaces
    bool f = true;
    for (char c : receiverID)
    {
        if (!isdigit(c))
        {
            f = false;
            break;
        }
    }
    if (receiverID.size() != 14 || !f)
    {
        cout << "\033[31m" << "Invalid ID , must be 14 digit and not use charactars" << "\033[0m" << endl;
        return;
    }
    if (receiverID == accounts[senderIndex].id)
    {
        cout << "\033[31m" << "Cannot transfer to the same account" << "\033[0m" << endl;
        return;
    }
    double amount;

    // find  recipient account
    int receiverIndex = -1;
    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].id == receiverID)
        {
            receiverIndex = i;
            break;
        }
    }

    // verify  validity of  receiving account
    if (receiverIndex == -1)
    {
        cout << "\033[34m" << "Recipient account not found" << "\033[0m" << endl;
        return;
    }

    // enter amount to transfer
    cout << "Enter amount to transfer: ";
    cin >> amount;
    if (cin.fail())
    {
        cout << "\033[31m" << "Fail Input" << "\033[0m" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
       return;
    }

    // verify validity of the amount
    if (amount > 0 && amount <= (accounts[senderIndex].balance - 50)) // 50 bank transfer fees 
    {
        accounts[senderIndex].balance -= (amount + 50);  // deduct amount from sender
        accounts[receiverIndex].balance += amount;  // add amount to recipient

        cout << "\033[32m" << "Transfer successful" << "\033[0m" << endl;
        cout << "Your new balance: " << accounts[senderIndex].balance << endl;
    }
    else
    {
        cout << "\033[31m" << "Invalid amount or insufficient balance" << "\033[0m" << endl;

    }
}

// close account
void closeAccount()
{
    string accNum;
    cout << "\nEnter ID to close: ";
    cin.ignore();
    getline(cin, accNum);
    accNum.erase(remove(accNum.begin(), accNum.end(), ' '), accNum.end());//remove spaces
    bool f = true;
    for (char c : accNum)
    {
        if (!isdigit(c))
        {
            f = false;
            break;
        }
    }
    if (accNum.size() != 14 || !f)
    {
        cout << "\033[31m" << "Invalid ID , must be 14 digit" << "\033[0m" << endl;
        return;
    }

    for (size_t i = 0; i < accounts.size(); i++)
    {
        if (accounts[i].id == accNum)
        {
            cout << "\033[34m" << "Are you sure to close account ? y : n" << "\033[0m" << endl;
            char confirm;
            cin >> confirm;
            if (cin.fail())
            {
                cout << "\033[31m" << "Fail Input" << "\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return;
            }
            if (confirm == 'y' || confirm == 'Y')
            {
                accounts.erase(accounts.begin() + i);
                cout << "\033[32m" << "Account closed successfully" << "\033[0m" << endl;
            }
            else if (confirm == 'n' || confirm == 'N')
            {
                cout << "\033[37m" << "account deletion canceled" << "\033[0m" << endl;
            }
            else
            {
                cout << "\033[36m" << "Invalid Choice" << "\033[0m" << endl;
            }
            return;
        }
    }
    cout << "\033[31m" << "account not found" << "\033[0m" << endl;
}

// user menu after login
void userMenu(int index)
{
    while (true)
    {
        cout << "\033[34m" << "\n--- Account Menu ---" << "\033[0m" << endl;
        cout << "1. Deposit Money\n";
        cout << "2. Withdraw Money\n";
        cout << "3. Check Balance\n";
        cout << "4. Transfer Money\n";
        cout << "5. Logout\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        if (cin.fail())
        {
            cout << "\033[31m" << "Fail Input" << "\033[0m" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice)
        {
        case 1:
            deposit(index);
            break;
        case 2:
            withdraw(index);
            break;
        case 3:
            checkBalance(index);
            break;
        case 4:
            transferMoney(index);
            break;
        case 5:
            cout << "Logging out\n";
            return;
        default:
            cout << "\033[41m" << "Invalid choice, Try again" << "\033[0m" << endl;
        }
    }
}

// main menu
void run()
{
    while (true)
    {
        cout << "\033[33m" << "\n--- Banking System ---" << "\033[0m" << endl;
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Close Account\n";
        cout << "4. Exit\n";
        cout << "\033[1;31m" << "Enter your choice: " << "\033[0m";
        int choice;
        cin >> choice;
        if (cin.fail())
        {
            cout << "\033[31m" << "Fail Input" << "\033[0m" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 2:
        {
            int index = login();
            if (index != -1)
            {
                userMenu(index);
            }
            break;
        }
        case 3:
            closeAccount();
            break;
        case 4:
            cout << "\033[35m" << "Exiting system" "\033[0m" << endl;
            return;
        default:
            cout << "\033[41m" << "Invalid choice, Try again" << "\033[0m" << endl;
        }
    }
}

// start main function
int main()
{
    system("color 8F");
    run();
    return 0;
}