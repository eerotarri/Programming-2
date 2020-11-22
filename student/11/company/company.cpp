/*
#############################################################################
# COMP.CS.110 Programming 2: Autumn 2020                                    #
# Project3: Company                                                         #
# File: company.cpp                                                         #
# Description: Company hierarchy -class datastructure                       #
#       Datastructure is populated with Employee-structs and provides some  #
#       query-functions.                                                    #
#                                                                           #
# Program author                                                            #
# Name: Eero Tarri                                                          #
# Student number: 283568                                                    #
# UserID: tarri                                                             #
# E-Mail: eero.tarri@tuni.fi                                                #
#############################################################################
*/

#include "company.hh"

Company::Company()
{

}

// Dismantles the vector "employees_"
Company::~Company()
{
    for (auto emp : employees_) {
        emp->boss_ = nullptr;
        for (auto sub : emp->subordinates_) {
            sub = nullptr;
        }
        delete emp;
    }
}

// Creates new employee with information from given stream and
void Company::addNewEmployee(const std::string &id, const std::string &dep,
                             const double &time, std::ostream &output)
{
    // Creates new employee and adds it to vector "employess_"
    if (employeeExists(id)) {
        output << "Error. Employee already added." << std::endl;
    } else {
        Employee* new_employee = new Employee{};
        new_employee->id_ = id;
        new_employee->department_ = dep;
        new_employee->time_in_service_ = time;
        employees_.push_back(new_employee);
    }
}

// Prints a list of all employees in alphabetical order in
// format "<ID>, <DEPARTMENT>, <TIME IN SERVICE>"
void Company::printEmployees(std::ostream &output) const
{
    // Prints the employee
    for (auto obj : sortByID(employees_)) {
        output << obj->id_ << ", " << obj->department_
               << ", " << obj->time_in_service_ << std::endl;
    }
}

// Completes employees infromation by linking boss-subordinate
// relationships to each other
void Company::addRelation(const std::string &subordinate,
                          const std::string &boss, std::ostream &output)
{
    Employee* boss_object_ptr = getPointer(boss);
    Employee* employee_object_ptr = getPointer(subordinate);
    if (employeeExists(boss)){
        employee_object_ptr->boss_ = boss_object_ptr;
        boss_object_ptr->subordinates_.push_back(employee_object_ptr);
    }
}

// Prints the boss of given <ID>
void Company::printBoss(const std::string &id, std::ostream &output) const
{
    if (!employeeExists(id)) {
        printNotFound(id, output);
    } else {
        Employee* employee_object_ptr = getPointer(id);

        if (employee_object_ptr->boss_ == nullptr) {
            output << employee_object_ptr->id_ << " has no bosses." << std::endl;
        } else {
            output << employee_object_ptr->id_ << " has 1 bosses:" << std::endl;
            output << employee_object_ptr->boss_->id_ << std::endl;
        }
    }
}

// Prints direct subordinates of given boss <ID>
void Company::printSubordinates(const std::string &id, std::ostream &output) const
{
    if (!employeeExists(id)) {
        printNotFound(id, output);
    } else {

        size_t v_size = getPointer(id)->subordinates_.size();
        if (v_size == 0) {
            output << id << " has no subordinates." << std::endl;
        } else {
            output << id << " has " << v_size << " subordinates:" << std::endl;

            // sub: subordinate of the common boss
            for (Employee* sub : sortByID(getPointer(id)->subordinates_)) {
                output << sub->id_ << std::endl;
            }
        }
    }
}

// Prints all the colleagues (employess with the same boss)
void Company::printColleagues(const std::string &id, std::ostream &output) const
{
    if (!employeeExists(id)) {
        printNotFound(id, output);
    } else {
        if (getPointer(id)->boss_ == nullptr) {
            output << id << " has no colleagues." << std::endl;
        } else {
            size_t v_size = getPointer(id)->boss_->subordinates_.size();
            if (v_size == 0) {
                output << id << " has no colleagues." << std::endl;
            } else {
                output << id << " has " << v_size-1 << " colleagues:" << std::endl;

                // sub: subordinate of the common boss
                for (Employee* sub : sortByID(getPointer(id)->boss_->subordinates_)) {
                    if (sub->id_ != id) {
                         output << sub->id_ << std::endl;
                    }
                }
            }
        }
    }
}

// Prints all the employees in the same department and hierarchy.
// (all of the subordinates of the highest ranking officer in line-management)
void Company::printDepartment(const std::string &id, std::ostream &output) const
{
    if (!employeeExists(id)) {
        printNotFound(id, output);
    } else {
        Employee* boss_of_hierarchy = getPointer(id);
        std::vector<Employee*> colleagues;

        // Checks who is the highest ranking boss in the department
        while (boss_of_hierarchy->department_ == getPointer(id)->department_ &&
               boss_of_hierarchy->boss_ != nullptr) {

            if (boss_of_hierarchy->boss_->department_ == boss_of_hierarchy->department_) {
                boss_of_hierarchy = boss_of_hierarchy->boss_;
            } else {
                break;
            }
        }

        colleagues.push_back(boss_of_hierarchy);
        addSubordinates(colleagues, boss_of_hierarchy, ALL);

        if (colleagues.size() == 1) {
            output << id << " has no department colleagues." << std::endl;
        } else {
            output << id << " has " << colleagues.size()-1 << " department colleagues:" << std::endl;

            // e: employee in the list of colleagues
            for (auto e : sortByID(colleagues)) {
                if (e->id_ != id) {
                    output << e->id_ << std::endl;
                }
            }
        }
    }
}

// Finds out the person with the most time in service under the <ID>'s
// line-management
void Company::printLongestTimeInLineManagement(const std::string &id, std::ostream &output) const
{
    if (!employeeExists(id)) {
        printNotFound(id, output);
    } else {
        Employee* longest = getPointer(id);
        std::vector<Employee*> line_management;
        addSubordinates(line_management, getPointer(id), ALL);

        // Check who has mos years in line management
        for (auto e : line_management) {
            if (e->time_in_service_ > longest->time_in_service_) {
                longest = e;
            }
        }

        // Prints output
        output << "With the time of " << longest->time_in_service_ << ", "
               << longest->id_ << " is the longest-served employee in ";
        if (longest == getPointer(id)) {
            output << "their line management." << std::endl;
        } else {
            output << id << "'s line management." << std::endl;
        }
    }
}

// Finds out the person with the least time in service under the <ID>'s
// line-management
void Company::printShortestTimeInLineManagement(const std::string &id, std::ostream &output) const
{
    if (!employeeExists(id)) {
        printNotFound(id, output);
    } else {
        Employee* shortest = getPointer(id);
        std::vector<Employee*> line_management;
        addSubordinates(line_management, getPointer(id), ALL);

        // Check who has mos years in line management
        for (auto e : line_management) {
            if (e->time_in_service_ < shortest->time_in_service_) {
                shortest = e;
            }
        }

        // Prints output
        output << "With the time of " << shortest->time_in_service_ << ", "
               << shortest->id_ << " is the shortest-served employee in ";
        if (shortest == getPointer(id)) {
            output << "their line management." << std::endl;
        } else {
            output << id << "'s line management." << std::endl;
        }
    }
}

// Prints all of the bosses n times up
// i.e. 2 would be boss and that bosses boss
void Company::printBossesN(const std::string &id, const int n, std::ostream &output) const
{
    if (n < 1) {
        output << "Error. Level can't be less than 1." << std::endl;
    } else if (!employeeExists(id)) {
        printNotFound(id, output);
    } else {

        if (getPointer(id)->boss_ == nullptr) {
            output << id << " has no bosses." << std::endl;
        } else {
            std::vector<Employee*> bosses;
            addBosses(bosses, getPointer(id), n);
            IdSet boss_ids = VectorToIdSet(bosses);
            output << id << " has " << boss_ids.size() << " bosses:" << std::endl;

            // b: id's of the bosses
            for (auto b : boss_ids) {
                output << b << std::endl;
            }
        }
    }
}

// Prints all of the subordinates n times down
void Company::printSubordinatesN(const std::string &id, const int n, std::ostream &output) const
{
    if (n < 1) {
        output << "Error. Level can't be less than 1." << std::endl;
    } else if (!employeeExists(id)) {
        printNotFound(id, output);
    } else {
        std::vector<Employee*> subs;
        addSubordinates(subs, getPointer(id), n);
        size_t v_size = subs.size();

        if (v_size == 0) {
            output << id << " has no subordinates." << std::endl;
        } else {
            output << id << " has " << v_size << " subordinates:" << std::endl;

            // sub: subordinate of the boss being examined
            for (Employee* sub : sortByID(subs)) {
                output << sub->id_ << std::endl;
            }
        }
    }
}

// Returns the pointer in employees_ of parameter id
Employee *Company::getPointer(const std::string &id) const
{
    Employee* employee_object_ptr;
    for (auto it = employees_.begin(); it != employees_.end(); it++) {
        if ((*it)->id_ == id) {
            employee_object_ptr = *it;
        }
    }
    return employee_object_ptr;
}

// Prints if id is not found
void Company::printNotFound(const std::string &id, std::ostream &output) const
{
    output << "Error. " << id << " not found." << std::endl;
}

IdSet Company::VectorToIdSet(const std::vector<Employee *> &container) const
{
    IdSet set_of_ids;
    for (auto it = container.begin(); it != container.end(); it++) {
        set_of_ids.insert((*it)->id_);
    }

    return set_of_ids;
}

bool Company::employeeExists(const std::string& id) const
{
    std::vector<Employee*>::const_iterator it;
    bool exists = false;

    // Check if the employee already exists
    for (it = employees_.begin(); it != employees_.end(); it++) {
        if ((*it)->id_ == id) {
            exists = true;
        }
    }

    return exists;
}

// Sorts a vector of Employee pointers by the attribute id_
std::vector<Employee*> Company::sortByID(const std::vector<Employee*>& container) const
{
    IdSet ids = VectorToIdSet(container);
    std::vector<Employee*> sorted_container;
    Employee* obj_ptr;

    // While loop until all the employees have been printed
    while (ids.size() > 0) {
        std::string first_value = *(ids.begin());

        // Finds which employee comes first alphabetically
        for (auto idset_it = ids.begin(); idset_it != ids.end(); idset_it++) {
            if (*idset_it < first_value) {
                first_value = *idset_it;
            }
        }

        // Find the object
        for (auto vector_it = container.begin(); vector_it != container.end() ; vector_it++) {
            if ((*vector_it)->id_ == first_value) {
                obj_ptr = *vector_it;
            }
        }
        sorted_container.push_back(obj_ptr);
        ids.erase(ids.find(first_value));
    }
    return sorted_container;
}

// Recursively adds subordinates to a vector n times
void Company::addSubordinates(std::vector<Employee*>& container, Employee* boss, const int& n) const
{
    int count = n;
    if (boss->subordinates_.size() != 0) {
        for (auto sub : boss->subordinates_) {
            if (boss->department_ == sub->department_) {
                container.push_back(sub);
                count -= 1;
                if (count != 0) {
                    addSubordinates(container, sub, count);
                }
            }
        }
    }
}

// Recursively adds bosses to a vector n times
void Company::addBosses(std::vector<Employee*>& container, Employee* subordinate, int n) const
{
    Employee* boss = subordinate->boss_;
    if (boss != nullptr) {
        container.push_back(subordinate->boss_);
        n -= 1;
        if (n != 0) {
            addBosses(container, boss, n);
        }
    }
}
