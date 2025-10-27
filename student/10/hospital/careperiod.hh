/* Class CarePeriod
 * ----------
 * COMP.CS.110 SPRING 2024
 * ----------
 * Class for describing a patient's care period in hospital.
 *
 * */
#ifndef CAREPERIOD_HH
#define CAREPERIOD_HH

#include "person.hh"
#include "date.hh"
#include <string>
#include <set>
#include <memory>

class CarePeriod
{
public:
    /**
      * @brief CarePeriod
      * @param start date given as a string (ddmmyyyy)
      * @param patient whose care period will be created
      */
    CarePeriod(const std::string& start, std::shared_ptr<Person> patient);

    /**
      * @brief CarePeriod
      * @param start date given as a Date object
      * @param patient whose care period will be created
      */
    CarePeriod(const Date& start, std::shared_ptr<Person> patient);

    /**
      * @brief destructor
      */
    ~CarePeriod();

    // Getters and setters
    const Date& get_end_date() const;
    void set_end_date(const Date& end_date);

    const std::set<std::string> get_specialists() const;
    void set_specialists(const std::string specialist_id);

    /*
     * This function prints a patients care periods and their assigned staff
     */
    void print_patient() const;

    /*
     * param staff_id as string
     * return false if specialist has never had an assigned patient
     */
    bool print_staff(std::string staff_id) const;

private:
    std::shared_ptr<Person> patient_;
    std::set<std::string> specialists_;
    Date start_;
    Date end_;

    // More attributes and methods
};

#endif // CAREPERIOD_HH
