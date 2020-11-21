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

}

void Company::addRelation(const std::string &subordinate, const std::string &boss, std::ostream &output)
{
    Employee* boss_object = nullptr;
    Employee* employee_object = nullptr;
    if (employee_exists(boss)){
        for (auto it = employees_.begin(); it != employees_.end(); it++) {
            if (it->first == subordinate) {
                employee_object = it->second;
            } else if (it->first == boss) {
                boss_object = it->second;
            }
        }
        employee_object->boss_ = boss_object;
        boss_object->subordinates_.push_back(employee_object);

    }
}

void Company::printBoss(const std::string &id, std::ostream &output) const
{

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
