#include "cards.hh"

Cards::Cards(): top_(nullptr)
{

}

Card_data *Cards::get_topmost()
{
    Card_data* top_item = top_;
    return top_item;
}

void Cards::add(int id)
{
    Card_data* new_card = new Card_data{id, nullptr};

    new_card->next = top_;
    top_ = new_card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    Card_data* data_to_print = top_;
    int count = 1;

    while(data_to_print != nullptr)
    {
        s << count << ':' << ' ';
        s << data_to_print->data << std::endl;
        data_to_print = data_to_print->next;
        ++count;
    }
}


bool Cards::remove(int &id)
{
    if (top_ == nullptr)
    {
        return false; // List is empty
    }

    // Store the data of the top node to return it
    id = top_->data;

    // Temp pointer to top so we can delete it later (no memory leaks)
    Card_data* temp = top_;
    top_ = top_->next;

    // Delete the node
    delete temp;

    return true;
}


bool Cards::bottom_to_top()
{
    if (top_ == nullptr || top_->next == nullptr)
    {
        return false; // No need to reverse if there's 0 or 1 element
    }

    Card_data* second_last = nullptr;
    Card_data* bottom = top_;
    while(bottom->next != nullptr)
    {
        second_last = bottom;
        bottom = bottom->next;
    }

    second_last->next = nullptr;
    bottom->next = top_;
    top_ = bottom;

    return true;
}


bool Cards::top_to_bottom()
{
    if (top_ == nullptr || top_->next == nullptr)
    {
        return false; // No need to reverse if there's 0 or 1 element
    }

    Card_data* bottom = top_;
    while(bottom->next != nullptr)
    {
        bottom = bottom->next;
    }

    // Move first node to the end
    bottom->next = top_;
    top_ = top_->next;
    bottom->next->next = nullptr;

    return true;
}


void Cards::print_from_bottom_to_top(std::ostream &s)
{
    int count = node_count(top_);
    recursive_print(top_, s, count);
}

Cards::~Cards()
{
    while(top_ != nullptr)
    {
        Card_data* data_to_delete = top_;
        top_ = top_->next;

        delete data_to_delete;
    }
}

int Cards::node_count(Card_data *top)
{
    int count = 1;
    while(top != nullptr)
    {
        ++ count;
        top = top->next;
    }
    return count;
}

void Cards::recursive_print(Card_data *top, std::ostream &s, int count)
{
    --count;
    if(top == nullptr)
    {
        return;
    }
    else if(top->next != nullptr)
    {
        recursive_print(top->next, s, count);
    }
    if(top != nullptr)
    {
        s << count << ':' << ' ' << top->data << std::endl;
    }
}
