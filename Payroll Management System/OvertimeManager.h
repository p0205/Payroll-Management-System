#ifndef OVERTIMEMANAGER_H
#define OVERTIMEMANAGER_H
#include "Overtime.h"
#include "DatabaseConnection.h"
#include "Employee_Overtime.h"
#include "Menu.h"

class OvertimeManager
{
    public:
    void viewOvertimeType();
    double getEmpHourRate(int employeeID);
    Overtime* getOvertime(int overtimeID);
    void computeOvertime();
    void assignOvertime(int employeeID,int overtimeID,double employeeHourRate,int overtimeHours,double amount,std::string date);
    Employee_Overtime* getEmployeeOvertimes(int employeeID,int year,int month);
};

#endif