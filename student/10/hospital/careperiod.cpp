#include "careperiod.hh"
#include <iostream>

CarePeriod::CarePeriod(const std::string& start, std::shared_ptr<Person> patient):
    patient_(patient), start_(start)
{
    // Parse string data to integers for Date::set
    unsigned int day = stoi( start.substr(0, 2) );
    unsigned int month = stoi( start.substr(2, 2) );
    unsigned int year = stoi( start.substr(4, 4) );

    // Set start date
    start_.set(day, month, year);
}

CarePeriod::CarePeriod(const Date &start, std::shared_ptr<Person> patient):
    patient_(patient), start_(start)
{
}

CarePeriod::~CarePeriod()
{
}

void CarePeriod::print_patient() const
{
    // Print dates
    std::cout << "* Care period: ";
    start_.print();
    std::cout << " - ";
    if( end_.is_default() )
    {
        std::cout << std::endl;
    }
    else
    {
        end_.print();
        std::cout << std::endl;
    }

    // Print assigned staff
    std::cout << "  - Staff: ";
    if( specialists_.empty() )
    {
        std::cout << "None" << std::endl;
    }
    else
    {
        for( auto specialist : specialists_ )
            std::cout << specialist << ' ';
        std::cout << std::endl;
    }
}

bool CarePeriod::print_staff(std::string staff_id) const
{
    if (specialists_.find(staff_id) == specialists_.end())
    {
        return false;
    }

    // Print dates
    start_.print();
    std::cout << " - ";
    if( end_.is_default() )
    {
        std::cout << std::endl;
    }
    else
    {
        end_.print();
        std::cout << std::endl;
    }
    std::cout << "* Patient: " << patient_->get_id() << std::endl;
    return true;
}



void CarePeriod::set_end_date(const Date &end_date)
{
    end_ = end_date;
}

void CarePeriod::set_specialists(const std::string specialist_id)
{
    specialists_.insert(specialist_id);
}

const std::set<std::string> CarePeriod::get_specialists() const
{
    return specialists_;
}

const Date& CarePeriod::get_end_date() const
{
    return end_;
}
