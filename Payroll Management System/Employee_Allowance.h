#ifndef EMPLOYEE_ALLOWANCE_H
#define EMPLOYEE_ALLOWANCE_H
#include <string>

class Employee_Allowance
{
    public:
    int employeeID, allowanceID;
    std::string date;
    double amount;
    Employee_Allowance* next;
};

#endif