#ifndef BOOK_HH
#define BOOK_HH

#include <iostream>
#include <string>
#include "date.hh"

using namespace std;

class Book
{
public:
    Book(string author, string name);
    // Prints out "Author : Name" and if the book is available
    void print();
    // Loans the book if possible
    void loan(Date date);
    // Renews the loan if loaned
    void renew();
    // Returns the books loan
    void give_back();
    bool is_leap_year() const;
private:
    // Name of the author
    string author_;
    // Name of the book
    string name_;
    // States if the book is already loaned
    bool loaned_ = false;
    // States the day the book was loaned
    unsigned int loaned_day_;
    unsigned int loaned_month_;
    unsigned int loaned_year_;
    // States the due date if there is one
    unsigned int due_day_;
    unsigned int due_month_;
    unsigned int due_year_;
};

#endif // BOOK_HH
