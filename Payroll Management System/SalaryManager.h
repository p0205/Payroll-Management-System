#ifndef SALARY_MANAGER_H
#define SALARY_MANAGER_H
#include "Salary.h"
#include "Salary_Schedule.h"
#include "Employee.h"
#include "DatabaseConnection.h"
#include "Menu.h"
#include <string>

class SalaryManager
{
    public:
    void updateBasicSalaryHeader();
    void addSalaryScheduleHeader();
    void deleteSalaryScheduleHeader();
    void printPaySlipHeader();
    void paySalaryHeader();
    void producePayrollReportHeader();

    bool checkRepeatInt(int input,string table,string column);

    void updateBasicSalary();

    void addSalarySchedule();
    void deleteSalarySchedule();
    Salary_Schedule* searchSalarySchedule(int year, int month);
    
    //for calculation
    double getTotalAllowance(int employeeID);
    double getTravellingAllowance(int employeeID);
    double getTotalBonus(int employeeID, int targetYear, int targetMonth);
    double getTotalOvertime(int employeeID, int targetYear, int targetMonth);
    double getTotalDeduction(int employeeID, int targetYear, int targetMonth);

    void producePayrollReport();
    void PayrollReportByDepartment(std::string startDate, std::string endDate); //new
    void PayrollReportByEmployee(std::string startDate, std::string endDate); //new
    bool checkExistEmpSalary(int employeeID,int salaryID);
    Employee* searchEmployees(int salaryID);
    Employee* searchEmployeesByDepartment(int departmentID,int salaryID);
    Employee* getSalaryEmployees(int salaryID);
    void printPaySlip(std::string role);
    void addSalary(Salary* salary);
    Salary* searchSalary(int employeeID, int salaryID);
    void paySalary();
};

#endif