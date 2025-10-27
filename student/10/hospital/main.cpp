/* Hospital
 *
 * Description:
 *      This program is an implementation of a hospital "database" with
 * commands to write, print, and remove information about the hospital's
 * patients, staff (also called specialists) and specifics about them.
 *      Specifics include:
 *          - A patients care periods (start and end date) including staff
 *            assigned to the patient during said care period
 *          - Medicine prescripted for patients, including strength and dosage
 *          - Data about current patients
 *          - Data about all patients entered in an instance of the program
 *          - Data about all staff recruited in an instance of the program
 *      The commands for manipulating the above data are:
 *          - Recruit staff : RECRUIT R
            - Take patient to hospital : ENTER E
            - Take patient from hospital : LEAVE L
            - Assign staff for a patient : ASSIGN_STAFF AS
            - Add medicine for a patient : ADD_MEDICINE AM
            - Remove medicine from a patient : REMOVE_MEDICINE RM
            - Print patient's info : PRINT_PATIENT_INFO PPI
            - Print care periods per staff : PRINT_CARE_PERIODS PCPS
            - Print all used medicines : PRINT_ALL_MEDICINES PAM
            - Print all staff : PRINT_ALL_STAFF PAS
            - Print all patients : PRINT_ALL_PATIENTS PAP
            - Print current patients : PRINT_CURRENT_PATIENTS PCP
            - Set date : SET_DATE SD
            - Advance date : ADVANCE_DATE AD
            - Read : READ_FROM RF
            - Quit : QUIT Q
            - Help : HELP H
 *
 * Written by
 * Name: Jonatan Tevaniemi
 * Student number: 150176680
 * Username: cnjote
 * E-Mail: jonatan.tevaniemi@tuni.fi
 *
 * Notes about the program and its implementation:
 *      - Dynamic memory management is handled using shared pointers
 *      - Functions are commented in their header files
 *
 */

#include "cli.hh"
#include "hospital.hh"
#include <string>

const std::string PROMPT = "Hosp> ";


int main()
{
    Hospital* hospital = new Hospital();
    Cli cli(hospital, PROMPT);
    while ( cli.exec() ){}

    delete hospital;
    return EXIT_SUCCESS;
}
