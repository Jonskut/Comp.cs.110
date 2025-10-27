#include <iostream>
#include <memory>
#include "cards.hh"

using namespace std;

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
    if (top_ == nullptr) {
        return false; // List is empty
    }

    // Store the data of the top node to return it
    id = top_->data;

    // Temp pointer to top so we can delete it later (no memory leaks)
    shared_ptr<Card_data> temp = top_;
    top_ = top_->next;

    // Delete the node
    temp->next = nullptr;

    return true;
}

void Cards::reverse()
{
    if (top_ == nullptr || top_->next == nullptr) {
        return; // No need to reverse if there's 0 or 1 element
    }

    shared_ptr<Card_data> current = top_;
    shared_ptr<Card_data> prev = nullptr;
    shared_ptr<Card_data> next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    top_ = prev;
}

