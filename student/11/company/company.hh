/*
#############################################################################
# COMP.CS.110 Programming 2: Autumn 2020                                    #
# Project3: Company                                                         #
# File: company.hh                                                          #
# Description: Company hierarchy -class datastructure                       #
#       Datastructure is populated with Employee-structs and provides some  #
#       query-functions.                                                    #
# Notes: * This is a part of an exercise program                            #
#        * Student's aren't allowed to alter public interface!              #
#        * All changes to private side are allowed.                         #
#                                                                           #
# Program author                                                            #
# Name: Eero Tarri                                                          #
# Student number: 283568                                                    #
# UserID: tarri                                                             #
# E-Mail: eero.tarri@tuni.fi                                                #
#############################################################################
*/
#ifndef COMPANY_HH
#define COMPANY_HH

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <map>


// Named constants to improve readability in other modules.
const std::string EMPTY = "";
const double NO_TIME = -1.0;
const int ALL = 100;

// Struct for an employee.
struct Employee
{
    std::string id_ = EMPTY;
    std::string department_ = EMPTY;
    double time_in_service_ = NO_TIME;
    Employee* boss_ = nullptr;
    std::vector<Employee*> subordinates_;
};


using IdSet = std::set<std::string>;

/*  Class: Company
 *  Description: Datastructure for Employee-structs
 */
class Company
{
public:
    Company();
    ~Company();

    /* Description: Adds a new Employee to the datastructure.
     * Parameters:
     *  Param1: Employee's ID string
     *  Param2: Employee's department
     *  Param3: Employee's time in service
     *  Param4: Output-stream for error-printing
     * Errormessages:
     *  If employees's ID is already in datastructure:
     *      "Error. Employee already added."
     */
    void addNewEmployee(const std::string& id, const std::string& dep, const double& time,
                        std::ostream &output);

    /* Description: Prints all stored Employees: ID, department and time in service
     * Parameters:
     *  Param1: Output-stream for printing
     * Errormessages:
     *  None.
     */
    void printEmployees(std::ostream &output) const;



    /*
     * All the following functions have the same error messages:
     *  If ID wasn't found in datastructure:
     *      "Error. <ID> not found."
     *  If the printing list is empty:
     *      "Error. <ID> has no <group's name>."
     * -------------------------------------------------------------------
     */

    /* Description: Adds new boss-subordinate relation
     * Parameters:
     *  Param1: ID of the subordinate
     *  Param2: ID of the boss
     *  Param3: Output-stream for error-printing
     */
    void addRelation(const std::string& subordinate,
                     const std::string& boss,
                     std::ostream& output);

    /* Description: Prints the direct boss of the employee.
     * Parameters:
     *  Param1: ID of the employee
     *  Param2: Output-stream for printing
     */
    void printBoss(const std::string& id,
                   std::ostream& output) const;

    /* Description: Prints direct subordinates for the employee.
     * Parameters:
     *  Param1: ID of the employee
     *  Param2: Output-stream for printing
     */
    void printSubordinates(const std::string& id,
                           std::ostream& output) const;

    /* Description: Prints the colleagues for the employee.
     *  (Employees who shares their direct boss)
     * Parameters:
     *  Param1: ID of the employee
     *  Param2: Output-stream for printing
     */
    void printColleagues(const std::string& id,
                         std::ostream& output) const;

    /* Description: Prints all-level colleagues for the employee.
     *  (Employees who share their department and belong to the same hierarchy)
     * Parameters:
     *  Param1: ID of the person
     *  Param2: Output-stream for printing
     */
    void printDepartment(const std::string& id,
                         std::ostream& output) const;

    /* Description: Prints the employee with the longest time in service
     *  in the ID's line management.
     * Parameters:
     *  Param1: ID of the employee
     *  Param2: Output-stream for printing
     */
    void printLongestTimeInLineManagement(const std::string& id,
                                          std::ostream& output) const;

    /* Description: Prints the employee with the shortest time in service
     *  in the ID's line management.
     * Parameters:
     *  Param1: ID of the employee
     *  Param2: Output-stream for printing
     */
    void printShortestTimeInLineManagement(const std::string& id,
                                           std::ostream& output) const;


    /* The following functions have additional errormessage:
     *  If Param2's value is less than 1:
     *      "Error. Level can't be less than 1."
     * ---------------------------------------------------------------
     */

    /* Description: Prints the amount and names of bosses in given
     *  distance from the employee.
     * Parameters:
     *  Param1: ID of the employee
     *  Param2: Maximum distance from the employee. (n-1 times "hierarchy")
     *  Param3: Output-stream for printing
     */
    void printBossesN(const std::string& id, const int n,
                      std::ostream& output) const;

    /* Description: Prints the amount and names of subordinates in given
     *  distance from the employee.
     * Parameters:
     *  Param1: ID of the employee
     *  Param2: Maximum distance from the employee. (n-1 times "hierarchy")
     *  Param3: Output-stream for printing
     */
    void printSubordinatesN(const std::string& id, const int n,
                            std::ostream& output) const;

private:

    /* The following functions are meant to make project easier.
     * You can implement them if you want and/or create your own.
     * Anyway it would be a good idea to implement more functions
     * to make things easier and to avoid "copy-paste-coding"
     */

    // Return a pointer for ID.
    Employee* getPointer(const std::string& id) const;

    // Printing errors.
    void printNotFound(const std::string& id,
                       std::ostream& output) const;

    // Turns a vector of employees to a set of IDs.
    IdSet VectorToIdSet(const std::vector<Employee*> &container) const;

    // To check if the person can be found in employees_.
    // Takes the person to be checked as argument and
    // returns true if it exists.
    bool employeeExists(const std::string& id) const;

    // Sorts the container alphabetically by employees ID.
    // Returns the sorted container.
    std::vector<Employee*> sortByID(const std::vector<Employee*>& container) const;
    
    // Recursively adds bosses or subordinates to vector n-times.
    void addSubordinates(std::vector<Employee*>& container, Employee* boss, const int& n, bool is_dep=false) const;
    void addBosses(std::vector<Employee*>& container, Employee* subordinate, int n) const;

    // Data of existing employees
    std::vector<Employee*> employees_;

};

#endif // COMPANY_HH
