#include "company.hh"

Company::Company()
{

}

Company::~Company()
{

}

void Company::addNewEmployee(const std::string &id, const std::string &dep,
                             const double &time, std::ostream &output)
{
    if (employee_exists(id)) {
        output << "Error. Employee already added." << std::endl;
    } else {
        Employee* new_employee = new Employee{};
        new_employee->id_ = id;
        new_employee->department_ = dep;
        new_employee->time_in_service_ = time;
        employees_.insert({id, new_employee});
    }
}

void Company::printEmployees(std::ostream &output) const
{
    for (auto it = employees_.begin(); it != employees_.end(); it++) {
        output << it->second->id_<< ", " << it->second->department_ << ", "
               << it->second->time_in_service_ << std::endl;
    }
}

void Company::addRelation(const std::string &subordinate,
                          const std::string &boss, std::ostream &output)
{
    Employee* boss_object_ptr = getPointer(boss);
    Employee* employee_object_ptr = getPointer(subordinate);
    if (employee_exists(boss)){
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
        if (it->first == id) {
            employee_object_ptr = it->second;
        }
    }
    return employee_object_ptr;
}

void Company::printNotFound(const std::string &id, std::ostream &output) const
{

}

IdSet Company::VectorToIdSet(const std::vector<Employee *> &container) const
{

}

void Company::printGroup(const std::string &id, const std::string &group, const IdSet &container, std::ostream &output) const
{

}

bool Company::employee_exists(const std::string& id) const
{
    std::map<std::string, Employee*>::const_iterator it;
    bool exists = false;

    // Check if the employee already exists
    for (it = employees_.begin(); it != employees_.end(); it++) {
        if (it->first == id) {
            exists = true;
        }
    }

    return exists;
}
