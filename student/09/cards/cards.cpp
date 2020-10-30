#include "cards.hh"
#include <iostream>

// TODO: Implement the methods here

Cards::Cards(): top_(nullptr) {
}

Cards::~Cards()
{
    while ( top_ != nullptr ) {
        Card_data* item_to_be_released = top_;
        top_ = top_->next;

        delete item_to_be_released;
    }
}

void Cards::add(int id)
{
    Card_data* new_data = new Card_data{id, nullptr};
    if ( top_ == nullptr ) {
        top_ = new_data;
    } else {
        new_data->next = top_;
        top_ = new_data;
    }
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    Card_data* item_to_be_printed = top_;
    int running_number = 1;

    while ( item_to_be_printed != nullptr ) {
        s << running_number << ". " << item_to_be_printed->data << "\n";
        ++running_number;
        item_to_be_printed = item_to_be_printed->next;
    }
}

bool Cards::remove(int &id)
{
    if ( top_ == nullptr ) {
        return false;
    }

    Card_data* item_to_remove = top_;

    id = item_to_remove->data;

    if ( top_->next == nullptr ) {
        top_ = nullptr;
    } else {
        top_ = top_->next;
    }

    delete item_to_remove;

    return true;
}

bool Cards::bottom_to_top()
{
    if ( top_ == nullptr ) {
        return false;
    }

    Card_data* start = top_;
    Card_data* last;
    int last_data;

    while ( start != nullptr ) {
        if ( start->next == nullptr ) {
            last_data = start->data;
            last = start;
        }
        start = start->next;
    }

    Card_data* new_item = new Card_data{last_data, top_};
    top_ = new_item;

    start = top_;

    while ( start != nullptr ) {
        if ( start->next == last ) {
            start->next = nullptr;
        } else {
            start = start->next;
        }
    }
    delete last;

    return true;
}

bool Cards::top_to_bottom()
{
//    if ( top_ == nullptr ) {
//        return false;
//    }

//    int item_to_shift = top_->data;

//    remove(item_to_shift);

//    Card_data* first = top_;
//    std::cout << top_->data;

//    Card_data* new_item = new Card_data{item_to_shift, nullptr};

//    while ( true) {
//        if ( first->next == nullptr ) {
//            first->next = new_item;
//            break;
//        } else {
//            first = first->next;
//        }
//    }

    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    // Stub
    s << "\n";
}

