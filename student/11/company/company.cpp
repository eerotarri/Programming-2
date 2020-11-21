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
    std::map<std::string, Employee*>::iterator it;
    // Check if the employee already exists
    bool employee_exists = false;
    for (it = employees_.begin(); it != employees_.end(); it++) {
        if ( it->first == id ) {
            employee_exists = true;
        }
    }
    if (employee_exists) {
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
