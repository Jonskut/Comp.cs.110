#ifndef BOOK_HH
#define BOOK_HH

#include "date.hh"
#include <iostream>

using namespace std;

class Book
{
public:
    // constructor
    Book(const string& author, const string& title);
    void print() const;
    void loan(Date date);
    void renew();
    void give_back();

private:
    // attributes
    string author_;
    string title_;
    bool is_loaned_;
    Date date_loaned_;
    Date date_return_;

    string get_author() const;
    string get_title() const;
};

#endif // BOOK_HH
