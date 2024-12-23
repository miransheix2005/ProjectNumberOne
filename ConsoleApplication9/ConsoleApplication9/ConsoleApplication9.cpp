#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

#define red "\x1B[31m"
#define reset "\033[0m"
#define blue "\x1B[34m"
#define green "\x1B[32m"
#define yellow "\x1B[33m"

// Structures for Entities
struct Bank
{
    int BankID;
    string BankName;
    string Address;
};

struct BankBranch
{
    int BranchID;
    string BranchAddress;
    int BankID; // Foreign key
};

struct Account
{
    int AccID;
    string AccType;
    double Balance;
    int BranchID; // Foreign key
};

struct Loan
{
    int LoanID;
    string LoanType;
    double Amount;
    int BranchID; // Foreign key
};

struct Customer
{
    int CustID;
    string Name;
    string Phone;
    string Address;
};

struct Cust_ACC
{
    int CustID; // Foreign key
    int AccID; // Foreign key
    string Date;
};

struct Cust_Loan
{
    int CustID; // Foreign key
    int LoanID; // Foreign key
    string Date;
};

const int maxEntries = 100;
Bank banks[maxEntries];
int bankCount = 0;
BankBranch branches[maxEntries];
int branchCount = 0;
Account accounts[maxEntries];
int accountCount = 0;
Loan loans[maxEntries];
int loanCount = 0;
Customer customers[maxEntries];
int customerCount = 0;
Cust_ACC cust_acc[maxEntries];
int custAccCount = 0;
Cust_Loan cust_loan[maxEntries];
int custLoanCount = 0;

void AdminMenu();
void UserMenu();

void ManageBanks();
void ViewBanks();
void AddBank();
void RemoveBank();

void ManageCustomers();
void ViewCustomers();
void AddCustomer();
void RemoveCustomer();

void ManageAccounts();
void AddAccount();
void RemoveAccount();
void ViewAccounts();

void AddLoan();
void SaveData();
void LoadData();
void ClearData();
int IsDublicated(int id);

//for fixing getline error
void clearInput()
{
    cin.clear();
    cin.ignore();
}

// Entry Point
void main()
{
    LoadData();
    while (true)
    {
        string username, password;

        cout << "\n Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;

        if (username == "Admin" && password == "12345")
        {
            AdminMenu();
        }
        else if (username == "User" && password == "54321")
        {
            UserMenu();
        }
        else
        {
            cout << red << "Invalid password or username please try again later" << reset << endl;
        }

        SaveData();
    }
}


void AdminMenu()
{
    int choice;
    do
    {
        cout << blue << "\n Admin Menu" << reset << endl;
        cout << "1. Manage Banks" << endl;
        cout << "2. View Banks" << endl;
        cout << "3. Manage Customers" << endl;
        cout << "4. View Customers" << endl;
        cout << "5. Manage Account" << endl;
        cout << "6. View Account" << endl;
        cout << "7. Add Loan" << endl;
        cout << "8. Clear Data" << endl;
        cout << "0. Exit & Save" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: ManageBanks();
            break;
        case 2: ViewBanks();
            break;
        case 3: ManageCustomers();
            break;
        case 4: ViewCustomers();
            break;
        case 5: ManageAccounts();
            break;
        case 6: ViewAccounts();
            break;
        case 7: ClearData();
            break;
        case 0: cout << blue << "Exiting..." << reset << endl;
            break;
        default: cout << red << "Invalid choice!" << reset << endl;
        }
    }
    while (choice != 0);
}


void UserMenu()
{
    int choice;
    do
    {
        cout << blue << "\n User Menu" << reset << endl;
        cout << "1. View Banks" << endl;
        cout << "2. View Customers" << endl;
        cout << "3. View Account" << endl;
        cout << "0. Exit & Save" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1: ViewBanks();
            break;
        case 2: ViewCustomers();
            break;
        case 3: ViewAccounts();
            break;
        case 0: cout << "Exiting..." << endl;
            break;
        default: cout << red << "Invalid choice!" << reset << endl;
        }
    }
    while (choice != 0);
}

// banks
void ManageBanks()
{
    char input;
    cout << "Would you like to add(a) or remove(r) ? ";
    cin >> input;

    if (input == 'a')
    {
        AddBank();
    }
    else if ('r')
    {
        RemoveBank();
    }
}

void AddBank()
{
    if (bankCount >= maxEntries)
    {
        cout << "Bank list is full!" << endl;
        return;
    }

    Bank b;
    cout << "Enter Bank ID: ";
    cin >> b.BankID;
    clearInput();
    cout << "Enter Bank Name: ";
    getline(cin, b.BankName);
    cout << "Enter Bank Address: ";
    getline(cin, b.Address);

    if (IsDublicated(b.BankID))
    {
        return;
    }

    banks[bankCount++] = b;
    cout << green << "Bank added successfully!" << reset << endl;
}

void RemoveBank()
{
    if (bankCount == 0)
    {
        cout << "No banks to remove!" << endl;
        return;
    }

    int id;
    cout << "Enter the Bank ID to remove: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < bankCount; i++)
    {
        if (banks[i].BankID == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "Bank not found!" << endl;
        return;
    }

    for (int i = index; i < bankCount - 1; i++)
    {
        banks[i] = banks[i + 1];
    }
    bankCount--;
    cout << "Bank removed successfully!" << endl;
}

void ViewBanks()
{
    cout << "\nBanks List:" << endl;
    for (int i = 0; i < bankCount; i++)
    {
        cout << "ID: " << banks[i].BankID << ", Name: " << banks[i].BankName << ", Address: " << banks[i].Address << endl;
    }
}

// customers
void ManageCustomers()
{
    char input;
    cout << "Would you like to add(a) or remove(r) ? ";
    cin >> input;

    if (input == 'a')
    {
        AddCustomer();
    }
    else if ('r')
    {
        RemoveCustomer();
    }
}

void AddCustomer()
{
    if (customerCount >= maxEntries)
    {
        cout << "Customer list is full!" << endl;
        return;
    }

    Customer c;
    cout << "Enter Customer ID: ";
    cin >> c.CustID;
    clearInput();
    cout << "Enter Customer Name: ";
    getline(cin, c.Name);
    cout << "Enter Phone: ";
    getline(cin, c.Phone);
    cout << "Enter Address: ";
    getline(cin, c.Address);

    customers[customerCount++] = c;
    cout << green << "Customer added successfully!" << reset << endl;
}

void RemoveCustomer()
{
    if (customerCount == 0)
    {
        cout << "No customer to remove!" << endl;
        return;
    }

    int id;
    cout << "Enter the customer ID to remove: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].CustID == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "customer not found!" << endl;
        return;
    }

    for (int i = index; i < customerCount - 1; i++)
    {
        customers[i] = customers[i + 1];
    }

    customerCount--;
    cout << "customer removed successfully!" << endl;
}

void ViewCustomers()
{
    cout << "\nCustomers List:" << endl;
    for (int i = 0; i < customerCount; i++)
    {
        cout << "ID: " << customers[i].CustID << ", Name: " << customers[i].Name
            << ", Phone: " << customers[i].Phone << ", Address: " << customers[i].Address << endl;
    }
}

// accounts
void ManageAccounts()
{
    char input;
    cout << "Would you like to add(a) or remove(r) ? ";
    cin >> input;

    if (input == 'a')
    {
        AddAccount();
    }
    else if ('r')
    {
        RemoveAccount();
    }
}

void AddAccount()
{
    if (accountCount >= maxEntries)
    {
        cout << "Account list is full!" << endl;
        return;
    }

    Account a;
    cout << "Enter Account ID: ";
    cin >> a.AccID;
    clearInput();
    cout << "Enter Account Type: ";
    getline(cin, a.AccType);
    cout << "Enter Balance: ";
    cin >> a.Balance;
    cout << "Enter Branch ID: ";
    cin >> a.BranchID;

    if (a.Balance >= 1000)
    {
        accounts[accountCount++] = a;
        cout << green << "Account added successfully!" << reset << endl;
    }
    else
    {
        cout << red << "Balance must be at least 1000!" << reset << endl;
    }
}

void RemoveAccount()
{
    if (accountCount == 0)
    {
        cout << "No account to remove!" << endl;
        return;
    }

    int id;
    cout << "Enter the account ID to remove: ";
    cin >> id;

    int index = -1;
    for (int i = 0; i < accountCount; i++)
    {
        if (accounts[i].AccID == id)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        cout << "account not found!" << endl;
        return;
    }

    for (int i = index; i < accountCount - 1; i++)
    {
        accounts[i] = accounts[i + 1];
    }

    accountCount--;
    cout << "account removed successfully!" << endl;
}

void ViewAccounts()
{
}


// add loan
void AddLoan()
{
    if (loanCount >= maxEntries)
    {
        cout << "Loan list is full!" << endl;
        return;
    }

    Loan l;
    cout << "Enter Loan ID: ";
    cin >> l.LoanID;
    clearInput();
    cout << "Enter Loan Type: ";
    getline(cin, l.LoanType);
    cout << "Enter Amount: ";
    cin >> l.Amount;
    cout << "Enter Branch ID: ";
    cin >> l.BranchID;

    loans[loanCount++] = l;
    cout << green << "Loan added successfully!" << reset << endl;
}

int IsDublicated(int id)
{
    int dublicationCount = 0;
    for (int i = 0; i < bankCount; i++)
    {
        if (banks[i].BankID == id)
        {
            dublicationCount++;
        }
    }
    if (dublicationCount != 0)
    {
        cout << red << "\n Error: This id is already used" << reset;
        return 1;
    }
    else
    {
        return 0;
    }
}

// save the data file
void SaveData()
{
    ofstream outFile("banking_data.txt");
    if (!outFile)
    {
        cout << red << "Error saving data to file!" << reset << endl;
        return;
    }

    // outFile << bankCount << " : ";
    for (int i = 0; i < bankCount; i++)
    {
        outFile << "Bank ID: " << banks[i].BankID << " | " << "Bank Name: " << banks[i].BankName << " | " << "Bank Address: " << banks[i].Address << endl;
    }

    for (int i = 0; i < customerCount; i++)
    {
        outFile << customers[i].CustID << " | " << customers[i].Name << " | " << customers[i].Phone << " | " << customers[i].Address << endl;
    }

    outFile.close();
}

// load the data file
void LoadData()
{
    ifstream inFile("banking_data.txt");
    if (!inFile)
    {
        cerr << red << "No data file found. Starting fresh!" << reset << endl;
        return;
    }

    inFile >> bankCount;
    for (int i = 0; i < bankCount; i++)
    {
        inFile >> banks[i].BankID;
        inFile.ignore();
        getline(inFile, banks[i].BankName, ' ');
        getline(inFile, banks[i].Address);
    }

    inFile >> customerCount;
    for (int i = 0; i < customerCount; i++)
    {
        inFile >> customers[i].CustID;
        inFile.ignore();
        getline(inFile, customers[i].Name, ' ');
        getline(inFile, customers[i].Phone, ' ');
        getline(inFile, customers[i].Address);
    }

    inFile.close();
}

// clear the data file
void ClearData()
{
    ofstream outFile("banking_data.txt");
    if (!outFile)
    {
        cout << red << "Error clearing file data!" << reset << endl;
        return;
    }
    outFile.close();
    bankCount = 0;
    cout << green << "File data cleared" << reset << endl;
}
