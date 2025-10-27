#include "hospital.hh"
#include "utils.hh"
#include <iostream>
#include <algorithm>

Hospital::Hospital()
{
}

Hospital::~Hospital()
{
}

void Hospital::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not utils::is_numeric(day, false) or
        not utils::is_numeric(month, false) or
        not utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    utils::today.print();
    std::cout << std::endl;
}

void Hospital::recruit(Params params)
{
    std::string specialist_id = params.at(0);
    if( staff_.find(specialist_id) != staff_.end() )
    {
        std::cout << ALREADY_EXISTS << specialist_id << std::endl;
        return;
    }
    std::shared_ptr<Person> new_specialist = std::make_shared<Person>(specialist_id);
    staff_.insert({specialist_id, new_specialist});
    std::cout << STAFF_RECRUITED << std::endl;
}

void Hospital::print_all_staff(Params)
{
    if( staff_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( std::map< std::string, std::shared_ptr<Person> >::const_iterator iter = staff_.begin();
         iter != staff_.end();
         ++iter )
    {
        std::cout << iter->first << std::endl;
    }
}

void Hospital::add_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string strength = params.at(1);
    std::string dosage = params.at(2);
    std::string patient = params.at(3);
    if( not utils::is_numeric(strength, true) or
        not utils::is_numeric(dosage, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    std::map< std::string, std::shared_ptr<Person> >::const_iterator
            patient_iter = all_patients_.find(patient);
    if( patient_iter == all_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->add_medicine(medicine, stoi(strength), stoi(dosage));
    std::cout << MEDICINE_ADDED << patient << std::endl;
}

void Hospital::remove_medicine(Params params)
{
    std::string medicine = params.at(0);
    std::string patient = params.at(1);
    std::map< std::string, std::shared_ptr<Person> >::const_iterator
            patient_iter = current_patients_.find(patient);
    if( patient_iter == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient << std::endl;
        return;
    }
    patient_iter->second->remove_medicine(medicine);
    std::cout << MEDICINE_REMOVED << patient << std::endl;
}

auto Hospital::find_care_periods_by_id(const std::string& patient_id)
{
    auto return_iterator = care_periods_.end();
    for (auto it = care_periods_.begin(); it != care_periods_.end(); ++it)
    {
        if (it->first == patient_id)
        {
            return_iterator = it;
            break;
        }
    }
    return return_iterator;
}

void Hospital::enter(Params params)
{
    std::string patient_id = params.at(0);

    // Patient is already currently hospitalized
    if( current_patients_.find(patient_id) != current_patients_.end() )
    {
        std::cout << ALREADY_EXISTS << patient_id << std::endl;
        return;
    }

    std::shared_ptr<Person> new_patient = std::make_shared<Person>(patient_id);
    current_patients_.insert({patient_id, new_patient});

    // Patient hasn't been hospitalized before
    auto it = find_care_periods_by_id(patient_id);

    if( it == care_periods_.end() )
    {
        std::shared_ptr<CarePeriod> new_care_period =
                std::make_shared<CarePeriod>(utils::today, new_patient);
        care_periods_.push_back({patient_id, {new_care_period}});
        all_patients_.insert({patient_id, new_patient});
    }
    // Patient has been hospitalized before
    else
    {
        std::shared_ptr<CarePeriod> new_care_period =
                std::make_shared<CarePeriod>(utils::today, new_patient);

        auto it = find_care_periods_by_id(patient_id);
        it->second.push_back(new_care_period);
    }
    std::cout << PATIENT_ENTERED << std::endl;
}

void Hospital::leave(Params params)
{
    std::string patient_id = params.at(0);

    // Couldn't find patient
    if( current_patients_.find(patient_id) == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    // Set end date for care
    auto care_periods_it = find_care_periods_by_id(patient_id);

//    auto care_periods_it = care_periods_.find(patient_id);
        if (care_periods_it != care_periods_.end())
        {
            for (auto& care_period : care_periods_it->second)
            {
                if( care_period->get_end_date().is_default() )
                {
                    care_period->set_end_date(utils::today);
                }
            }
        }

    current_patients_.erase(patient_id);
    std::cout << PATIENT_LEFT << std::endl;
}

void Hospital::assign_staff(Params params)
{
    std::string specialist_id = params.at(0);
    std::string patient_id = params.at(1);

    // Couldn't find staff
    if( staff_.find(specialist_id) == staff_.end() )
    {
        std::cout << CANT_FIND << specialist_id << std::endl;
        return;
    }

    // Couldn't find patient
    if( current_patients_.find(patient_id) == current_patients_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }

    // Assign specialist to patient
    auto care_periods_it = find_care_periods_by_id(patient_id);

//    auto care_periods_it = care_periods_.find(patient_id);
    if( care_periods_it != care_periods_.end() )
    {
        for( auto& care_period : care_periods_it->second )
        {
            if( care_period->get_end_date().is_default())
            {
                care_period->set_specialists(specialist_id);
            }
        }
    }
    std::cout << STAFF_ASSIGNED << patient_id << std::endl;
}

void Hospital::print_patient_info(Params params)
{
    // Print information stored in care_periods_ (dates and specialists)
    std::string patient_id = params.at(0);
    auto it = find_care_periods_by_id(patient_id);

    if( it == care_periods_.end() )
    {
        std::cout << CANT_FIND << patient_id << std::endl;
        return;
    }
    for( const auto& care_period : it->second)
    {
        care_period->print_patient();
    }

    // Print current medicine information
    auto person_to_print = all_patients_.find(patient_id);

    std::cout << "* Medicines:";
    person_to_print->second->print_medicines("  - ");
}

void Hospital::print_care_periods(Params params)
{
    std::string staff_id = params.at(0);
    if( staff_.find(staff_id) == staff_.end() )
    {
        std::cout << CANT_FIND << staff_id << std::endl;
        return;
    }

    bool found_care_period = false;

    for( const auto& pair : care_periods_ )
    {
        const std::vector< std::shared_ptr<CarePeriod> >&
                care_periods = pair.second;

        for( const auto& care_period : care_periods )
        {
            if( care_period->print_staff(staff_id) )
            {
                found_care_period = true;
            }
        }
    }

    if (!found_care_period)
    {
        std::cout << "None" << std::endl;
    }
}


void Hospital::print_all_medicines(Params)
{
    // Store medicines in a structure for easy handling
    std::map<std::string, std::vector<std::string>> all_medicines;

    for( const auto& pair : all_patients_ )
    {
        const std::vector<std::string>&
                medicines = pair.second->get_medicines();

        for( const std::string& medicine : medicines )
        {
            all_medicines[medicine].push_back(pair.first);
        }
    }

    // Print all medicines
    if( all_medicines.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }
    for( const auto& pair : all_medicines )
    {
        std::cout << pair.first << " prescribed for" << std::endl;

        const std::vector<std::string>& patients = pair.second;
        for( const std::string& patient : patients )
        {
            std::cout << "* " << patient << std::endl;
        }
    }
}


void Hospital::print_all_patients(Params)
{
    if( !all_patients_.empty() )
    {
        for( const auto& pair : all_patients_ )
        {
            // Print name
            std::cout << pair.first << std::endl;
            // Convert to vector so it can be fed
            // to print_patient_info as a param
            std::vector<std::string> param;
            param.push_back(pair.first);

            print_patient_info(param);
        }
    }
    else
    {
        std::cout << "None" << std::endl;
    }
}

void Hospital::print_current_patients(Params)
{
    if( !current_patients_.empty() )
    {
        for( const auto& pair : current_patients_ )
        {
            // Print name
            std::cout << pair.first << std::endl;
            // Convert to vector so it can be fed
            // to print_patient_info as a param
            std::vector<std::string> param;
            param.push_back(pair.first);

            print_patient_info(param);
        }
    }
    else
    {
        std::cout << "None" << std::endl;
    }
}


