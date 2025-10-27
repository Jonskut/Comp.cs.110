#include "account.hh"
#include <iostream>
#include <string>

using namespace std;

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit), balance_(0)
{
    generate_iban();
}

string Account::get_owner() const
{
    return owner_;
}

string Account::get_iban() const
{
    return iban_;
}

int Account::get_balance() const
{
    return balance_;
}


// set credit limit for account
void Account::set_credit_limit(int limit)
{
    if ( has_credit_ )
    {
        credit_limit_ = limit;
    }
    else
    {
        cout << "Cannot set credit limit: the account has no credit card" << endl;
    }
}


// print account details
void Account::print() const
{
    cout << get_owner() << " : " << get_iban() <<  " : " << get_balance() << " euros" << endl;
}


// save money to account
void Account::save_money(int amount)
{
    balance_ += amount;
}


// remove money from account
bool Account::take_money(int amount)
{
    if ( has_credit_ )
    {
        if ( ((credit_limit_ + balance_) - amount) > 0 )
        {
            balance_ -= amount;
            cout << amount << " Euros taken: new balance of " << get_iban() <<
                    " is " << get_balance() << " euros" << endl;
            return true;
        }
        else
        {
            cout << "Cannot take money: credit limit overflow" << endl;
            return false;
        }
    }
    else
    {
        if ( (balance_ - amount) > 0 )
        {
            balance_ -= amount;
            cout << amount << " Euros taken: new balance of " << get_iban() <<
                    " is " << get_balance() << " euros" << endl;
            return true;
        }
        else
        {
            cout << "Cannot take money: balance underflow" << endl;
            return false;
        }
    }
}


// transfer money from current account to other
void Account::transfer_to(Account& account_name, int amount)
{
    bool successful_transfer;
    successful_transfer = take_money(amount);

    if ( successful_transfer )
    {
        account_name.save_money(amount);
    }
    else
    {
        cout << "Transfer from " << get_iban() << " failed" << endl;
    }

}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
