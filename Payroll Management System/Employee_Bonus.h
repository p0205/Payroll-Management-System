#ifndef EMPLOYEE_BONUS_H
#define EMPLOYEE_BONUS_H
#include <string>

class Employee_Bonus
{
    public:
    int ID, employeeID,bonusID;
    std::string date;
    double amount;
    Employee_Bonus* next;
};

#endif