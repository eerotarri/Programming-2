#include "book.hh"

unsigned int const month_sizes[12] = { 31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31 };

Book::Book(string author, string name):
    author_(author), name_(name)
{  
}

void Book::print()
{
    cout << author_ << " : " << name_ << endl;
    if ( loaned_ ) {
        // Loan date
        cout << "- loaned: ";
        if(loaned_day_ < 10)
        {
            std::cout << "0";
        }
        std::cout << loaned_day_ << ".";
        if(loaned_month_ < 10)
        {
            std::cout << "0";
        }
        std::cout << loaned_month_ << ".";
        if(loaned_year_ < 10)
        {
            std::cout << "0";
        }
        std::cout << loaned_year_ << std::endl;
        // Return date
        cout << "- to be returned: ";
        if(due_day_ < 10)
        {
            std::cout << "0";
        }
        std::cout << due_day_ << ".";
        if(due_month_ < 10)
        {
            std::cout << "0";
        }
        std::cout << due_month_ << ".";
        if(due_year_ < 10)
        {
            std::cout << "0";
        }
        std::cout << due_year_ << std::endl;
    } else {
        cout << "- available" << endl;
    }
}

void Book::loan(Date date)
{
    if ( loaned_ ) {
        cout << "Already loaned: cannot be loaned" << endl;
    } else {
        loaned_ = true;
        loaned_day_ = date.day_;
        loaned_month_ = date.month_;
        loaned_year_ = date.year_;
        date.advance(28);
        due_day_ = date.day_;
        due_month_ = date.month_;
        due_year_ = date.year_;
    }
}

void Book::renew()
{
    if ( loaned_ ) {
        due_day_ += 28;
        while ( due_day_ > month_sizes[due_month_ - 1] )
        {
            if ( due_month_ == 2 && due_day_ == 29 )
            {
                return;
            }
            due_day_ -= month_sizes[due_month_ - 1];

            ++due_month_;

            if ( due_month_ > 12 )
            {
                due_month_ -= 12;
                ++due_year_;
            }
        }
    } else {
        cout << "Not loaned: cannot be renewed" << endl;
    }
}

void Book::give_back()
{
    loaned_ = false;
}

