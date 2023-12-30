#ifndef EMPLOYEE_OVERTIME_H
#define EMPLOYEE_OVERTIME_H
#include <string>

class Employee_Overtime
{
    public:
    int ID, employeeID, overtimeID;
    std::string date;
    double employeeHourRate, overtimeHours,amount;
    Employee_Overtime* next;
};

#endif