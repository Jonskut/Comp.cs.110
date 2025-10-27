#include "queue.hh"
#include <iostream>
#include <string>


Queue::Queue(unsigned int cycle): first_(nullptr)
{
    cycle_ = cycle;
}

Queue::~Queue()
{
    while(first_ != nullptr)
    {
        Vehicle* data_to_destroy = first_;
        first_ = first_->next;
        delete data_to_destroy;
    }
}

void Queue::enqueue(const string &reg)
{
    if(is_green_)
    {
        std::cout << "GREEN: The vehicle " <<
                     reg << " need not stop to wait" << std::endl;
        return;
    }

    Vehicle* new_vehicle = new Vehicle{reg, nullptr};

    if (first_ == nullptr) {
        first_ = new_vehicle;
    } else {
        Vehicle* current = first_;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_vehicle;
    }
}


void Queue::switch_light()
{
    if (!is_green_)
    {
        is_green_ = true;
        print();
        if (first_ == nullptr)
        {
            return; // No vehicles waiting
        }

        unsigned int count = 0;
        while (first_ != nullptr && count < cycle_)
        {
            dequeue();
            ++count;
        }
        is_green_ = false;
        return;
    }

    //if green
    is_green_ = false;
    print();

}


void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    Vehicle* to_print = first_;
    string light_status = is_green_ ? "GREEN: " : "RED: ";
    std::cout << light_status;

    if(to_print == nullptr)
    {
        std::cout << "No vehicles waiting in traffic lights" << std::endl;
        return;
    }
    std::cout << "Vehicle(s) ";


    if(!is_green_)
    {
        while(to_print != nullptr)
        {
            std::cout << to_print->reg_num << ' ';
            to_print = to_print->next;
        }
        std::cout << "waiting in traffic lights" << endl;
    }
    else
    {
        unsigned int count = 0;
        while(to_print != nullptr && count < cycle_)
        {
            ++count;
            std::cout << to_print->reg_num << ' ';
            to_print = to_print->next;
        }
        std::cout << "can go on" << std::endl;
    }
}

// private method
void Queue::dequeue()
{
    if(!is_green_)
    {
        return;
    }
    if(first_ == nullptr)
    {
        return;
    }

    // Temp pointer so we can delete it later
    Vehicle* temp = first_;
    first_ = first_->next;

    delete temp;
}
