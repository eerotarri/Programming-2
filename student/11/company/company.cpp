﻿#include "company.hh"

Company::Company()
{

}

Company::~Company()
{

}

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

void Company::printEmployees(std::ostream &output) const
{
    // Prints the employee
    for (auto obj : sortByID(employees_)) {
        output << obj->id_ << ", " << obj->department_
               << ", " << obj->time_in_service_ << std::endl;
    }
}

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

void Company::printBoss(const std::string &id, std::ostream &output) const
{
    Employee* employee_object_ptr = getPointer(id);

    if (employee_object_ptr->boss_ == nullptr) {
        output << employee_object_ptr->id_ << " has no bosses." << std::endl;
    } else {
        output << employee_object_ptr->id_ << " has 1 bosses" << std::endl;
        output << employee_object_ptr->boss_->id_ << std::endl;
    }
}

void Company::printSubordinates(const std::string &id, std::ostream &output) const
{

}

void Company::printColleagues(const std::string &id, std::ostream &output) const
{

}

void Company::printDepartment(const std::string &id, std::ostream &output) const
{

}

void Company::printLongestTimeInLineManagement(const std::string &id, std::ostream &output) const
{

}

void Company::printShortestTimeInLineManagement(const std::string &id, std::ostream &output) const
{

}

void Company::printBossesN(const std::string &id, const int n, std::ostream &output) const
{

}

void Company::printSubordinatesN(const std::string &id, const int n, std::ostream &output) const
{

}

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

void Company::printNotFound(const std::string &id, std::ostream &output) const
{

}

IdSet Company::VectorToIdSet(const std::vector<Employee *> &container) const
{
    IdSet set_of_ids;
    for (auto it = container.begin(); it != container.end(); it++) {
        set_of_ids.insert((*it)->id_);
    }

    return set_of_ids;
}

void Company::printGroup(const std::string &id, const std::string &group, const IdSet &container, std::ostream &output) const
{

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
