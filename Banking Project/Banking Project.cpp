#include <iostream>
#include <fstream>
#include <map>
using namespace std;


class accounts
{
private:
    string fname, lname;
    int ph;
    float balance;
    int accno;
    static int nxtacno;
public:
    accounts() {};
    accounts(string fn, string ln, int ph, float bal);
    int getacno() { return accno; };

    static void setLastAccountNumber(int accno);
    static int getLastAccountNumber();
    float getbal() { return balance; }
    void withdraw(float cash) { balance -= cash; }
    void deposit(float cash) { balance += cash; }
    friend ofstream& operator <<(ofstream& ofs, accounts& ab);
    friend ifstream& operator >>(ifstream& ifs, accounts& ab);
    friend ostream& operator <<(ostream& out, accounts& ab);
};
int accounts::nxtacno = 0;


class bank
{
private:
    map <int, accounts> accn;
public:
    bank();

    accounts open_ac(string fn, string ln, int ph, float bal);
    accounts ac_details(int acc);
    accounts withdraw(int acc, float cash);
    accounts deposit(int acc, float cash);
    void AccFinder(int acc);
    void close(int acc);
    ~bank();
};

void interface()
{
    cout << "----------------BANKING SYSTEM-----------------\n\n";
    cout << "Select option :- \n";
    cout << "1) Open Account\n2) Account Details\n3) Wtihdraw\n4) Deposit\n5) Close Account\n6) Exit";
    cout << "\n\nSelect Option - ";
}

int bal()
{
    float balance;
    cout << "Deposit minimum 500Rs to open account :\nDeposit amount - ";
    cin >> balance;
    if (balance >= 500)
    {
        return balance;
    }
    else
    {
        cout << "\nTo open account please deposite minimum 500 Rs\n";
        cout << "Please try again\n\n";
        bal();
    }
}

int main()
{
main:;
    string fname, lname;
    int phone;
    float balance;
    int acc;
    accounts ac;
    bank bk;
    interface();
    short int opt;
    cin >> opt;
    cout << "\n";
    switch (opt)
    {
    case 1:
    {
        cout << "------------------OPEN ACCOUNT----------------\n";
        cout << "Enter your details to open account :\n";
        cout << "First Name - ";
        cin >> fname;
        cout << "Last Name - ";
        cin >> lname;
        cout << "Phone Number - ";
        cin >> phone;
        cout << "\n";
        balance = bal();
        cout << "\n";
        ac = bk.open_ac(fname, lname, phone, balance);
        cout << "Account Created succefully..\n";
        cout << ac << "\n";
        goto main;
    }
    case 2:
    {
        cout << "----------------ACCOUNT DETAILS------------------\n";
    accdet:;
        cout << "Enter account no. - ";
        cin >> acc;
        cout << "\n";
        try
        {
            bk.AccFinder(acc);
        }
        catch (int)
        {
            cout << "Account not found.\nPlease enter correct Account No. and Try Again.\n\n";
            goto accdet;
        }
        ac = bk.ac_details(acc);
        cout << ac << "\n";
        goto main;
    }
    case 3:
    {
        cout << "-----------------WITHDRAW----------------\n";
    wdraw1:;
        cout << "Enter Account no. - ";
        cin >> acc;
        try
        {
            bk.AccFinder(acc);
        }
        catch (int)
        {
            cout << "Account not found.\nPlease enter correct Account No.\n\n";
            goto wdraw1;
        }
        ac = bk.ac_details(acc);
        cout << "Account balance - " << ac.getbal();
        float cash;
    wdraw:;
        cout << "\nEnter Amount - ";
        cin >> cash;
        if (ac.getbal() - cash >= 500)
        {
            ac = bk.withdraw(acc, cash);
            cout << "Amount Withdrawed succefully!!!\n\n";
        }
        else if (ac.getbal() - cash < 500 && ac.getbal() - cash >= 0)
        {
            cout << "Minimum balance of 500Rs should be maintained.\nPlease Try again\n";
            goto wdraw;
        }
        else
        {
            cout << "Not enough balance.\nPlease try again\n";
            goto wdraw;
        }
        cout << ac << "\n";
        goto main;
    }
    case 4:
    {
        cout << "----------------DEPOSIT----------------\n";
    dep:;
        float cash;
        cout << "Enter account no. - ";
        cin >> acc;
        try
        {
            bk.AccFinder(acc);
        }
        catch (int)
        {
            cout << "Account not found.\nPlease enter correct Account No.\n\n";
            goto dep;
        }
        cout << "Enter Amount - ";
        cin >> cash;
        ac = bk.deposit(acc, cash);
        cout << "Amount deposited succefully!!!\n\n";
        cout << ac << "\n";
        goto main;
    }
    case 5:
    {
        cout << "----------------CLOSE ACCOUNT-----------------\n";
    close:;
        cout << "Enter account No. - ";
        cin >> acc;
        try
        {
            bk.AccFinder(acc);
        }
        catch (int)
        {
            cout << "Account not found.\nPlease enter correct Account No.\n\n";
            goto close;
        }
        bk.close(acc);
        cout << "Account closed successfully.\n\n";
        goto main;
    }
    case 6:
    {
        cout << "Thank you for Banking with us :))\n";
        exit(0);
    }
    default:
    {
        cout << "Invalid input.\nPlease try again....\n\n";
        goto main;
    }
    }
}
accounts::accounts(string fn, string ln, int ph, float bal)
{
    fname = fn;
    lname = ln;
    this->ph = ph;
    balance = bal;
    nxtacno++;
    accno = nxtacno;
}
void accounts::setLastAccountNumber(int accno)
{
    nxtacno = accno;
}
int accounts::getLastAccountNumber()
{
    return nxtacno;
}
ofstream& operator <<(ofstream& ofs, accounts& ab)
{
    ofs << ab.accno << endl;
    ofs << ab.fname << endl;
    ofs << ab.lname << endl;
    ofs << ab.ph << endl;
    ofs << ab.balance << endl;
    return ofs;
}
ifstream& operator >>(ifstream& ifs, accounts& ab)
{
    ifs >> ab.accno >> ab.fname >> ab.lname >> ab.ph >> ab.balance;
    return ifs;
}
ostream& operator <<(ostream& out, accounts& ab)
{
    out << "Account Details are as follows : -\n";
    out << "Account No. - " << ab.accno << "\n";
    out << "Name - " << ab.fname << " " << ab.lname << "\n";
    out << "Phone No. - " << ab.ph << "\n";
    out << "Balance - " << ab.balance << "\n";
    return out;
}
bank::bank()
{
    accounts objac;
    ifstream ifs("data.txt");
    if (!ifs)
    {
        return;
    }
    while (!ifs.eof())
    {
        ifs >> objac;
        accn.insert(pair<int, accounts>(objac.getacno(), objac));
    }
    accounts::setLastAccountNumber(objac.getacno());
    ifs.close();
}
accounts bank::open_ac(string fn, string ln, int ph, float bal)
{
    ofstream outfile;
    accounts newac(fn, ln, ph, bal);
    accn.insert(pair<int, accounts>(newac.getacno(), newac));

    outfile.open("Data.txt", ios::trunc);
    map<int, accounts>::iterator itr;
    for (itr = accn.begin(); itr != accn.end(); itr++)
    {
        outfile << itr->second;
    }
    outfile.close();
    return newac;
}
accounts bank::ac_details(int acc)
{
    map <int, accounts>::iterator itr = accn.find(acc);
    return itr->second;
}
accounts bank::withdraw(int acc, float cash)
{
    map <int, accounts>::iterator itr = accn.find(acc);
    itr->second.withdraw(cash);
    return itr->second;
}
accounts bank::deposit(int acc, float cash)
{
    map <int, accounts>::iterator itr = accn.find(acc);
    itr->second.deposit(cash);
    return itr->second;
}
void bank::close(int acc)
{
    map <int, accounts>::iterator itr = accn.find(acc);
    accn.erase(acc);
}
void bank::AccFinder(int acc)
{
    if (accn.find(acc) == accn.end())
    {
        throw 747;
    }
}
bank::~bank()
{
    ofstream ofs;
    ofs.open("data.txt", ios::trunc);
    map <int, accounts>::iterator itr;
    for (itr = accn.begin(); itr != accn.end(); itr++)
    {
        ofs << itr->second;

    }
    ofs.close();
}