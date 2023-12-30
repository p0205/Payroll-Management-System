#ifndef SALARY_H
#define SALARY_H
#include <string>

class Salary
{
    public:
    int salaryID, employeeID;
    double basicSalary,totalAllowance,totalBonus,totalOvertime,grossSalary,totalDeduction,netSalary;
    std::string paymentStatus;
    Salary* next;
};

#endif