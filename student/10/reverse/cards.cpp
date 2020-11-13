#include <iostream>
#include <memory>
#include "cards.hh"


Cards::Cards(): top_( nullptr ) {
}


void Cards::add(int id) {
    std::shared_ptr<Card_data> new_card 
            = std::make_shared<Card_data>(Card_data{id, top_});
    top_ = new_card;
}

void Cards::print(std::ostream& s) {
   std::shared_ptr<Card_data> to_be_printed = top_;
   int nr = 1;

   while( to_be_printed != 0 ) {
      s << nr << ": " << to_be_printed->data << std::endl;
      to_be_printed = to_be_printed->next;
      ++nr;
   }
}

bool Cards::remove(int &id)
{
    if ( top_ == nullptr ) {
        return false;
    }

    std::shared_ptr<Card_data> removable_ptr = top_;

    id = removable_ptr->data;

    if ( top_->next == nullptr ) {
        top_ = nullptr;
    } else {
        top_ = top_->next;
    }

    return true;
}

void Cards::reverse()
{
    if ( top_ == nullptr || top_->next == nullptr ) {
        return;
    }

    std::shared_ptr<Card_data> prev;
    std::shared_ptr<Card_data> current = top_->next;
    std::shared_ptr<Card_data> next = current->next;

    top_->next = nullptr;
    prev = top_;
    while ( current != nullptr ) {
        top_ = current;
        top_->next = prev;
        prev = top_;
        current = next;
        if ( current != nullptr ) {
            next = current->next;
        }
    }
}
