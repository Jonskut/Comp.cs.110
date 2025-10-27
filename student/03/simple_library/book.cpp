#include "book.hh"
#include "date.hh"
#include <iostream>

using namespace std;

Book::Book(const string& author, const string& title):
    author_(author), title_(title)
{
    is_loaned_ = false;
}

string Book::get_author() const
{
    return author_;
}

string Book::get_title() const
{
    return title_;
}

void Book::loan(Date date)
{
    if ( is_loaned_ )
    {
        cout << "Already loaned: cannot be loaned" << endl;
    }
    else
    {
        is_loaned_ = true;
        date_loaned_ = date;
        date_return_ = date;
        date_return_.advance(28);
    }

}

void Book::renew()
{
    if ( is_loaned_ )
    {
        date_return_.advance(28);
    }
    else
    {
        cout << "Not loaned: cannot be renewed" << endl;
    }
}

void Book::give_back()
{
    is_loaned_ = false;
}

void Book::print() const
{
    cout << get_author() << " : " << get_title() << endl;

    if ( is_loaned_ )
    {
        cout << "- loaned: ";
        date_loaned_.print();

        cout << "- to be returned: ";
        date_return_.print();
    }
    else
    {
        cout << "- available" << endl;
    }
}
