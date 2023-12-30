#ifndef EMPLOYEE_DEDUCTION_H
#define EMPLOYEE_DEDUCTION_H
#include <string>

class Employee_Deduction
{
    public:
    int ID, employeeID, deductionID;
    std::string date;
    double amount;
    Employee_Deduction* next;
};

#endif