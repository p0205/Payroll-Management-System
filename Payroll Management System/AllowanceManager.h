#ifndef ALLOWANCEMANAGER_H
#define ALLOWANCEMANAGER_H
#include "Allowance.h"
#include "DatabaseConnection.h"
#include "Employee_Allowance.h"
#include "Menu.h"
#include <string>

class AllowanceManager
{
    public:
    bool checkRepeatString(std::string input,std::string table,std::string column);
    bool checkRepeatInt(int input,std::string table,std::string column);
    Allowance* searchAllowance(int allowanceID);
    Allowance* searchAllowances();
    void viewAllowances();
    void addAllowance(std::string name, std::string frequency,int isExempted);
    void addAllowance();
    bool isEmployeeInList(Employee* head, int targetID) ;
    bool isEmployeeInList(Employee* head, const std::string& targetName) ;  
    Employee* getAllowanceEmployees(int allowanceID);  
    Employee* searchEmployees(int allowanceID);
    Employee* searchEmployeesByDepartment(int departmentID,int allowanceID);
    Employee_Allowance* getEmployeeAllowances(int employeeID);
    Employee_Allowance* getAllowanceEmp(int allowanceID);
    bool checkExistEmpAllowance(int employeeID,int allowanceID, std::string currentDate);

    void allocateAllowance(int employeeID,int allowanceID,double amount,std::string date);
    void allocateAllowance();
    void allocateNewAllowance();


    // void updateAllowance();
    // void updateEmpAllowance();
    // void updateEmpAllowance(Employee* employee);
    // void updateEmpAllowance(int employeeID,int allowanceID, double amount);
    // void updateAllAllowance();
    // void updateAllAllowance(int allowanceID, double amount);

    // void removeAllowance();
    // void removeEmpAllowance(int employeeID,int allowanceID);
    // void removeEmpAllowance();
    // void removeEmpAllowance(Employee* employee);
    // void removeAllAllowance();
    // void removeAllAllowance(int allowanceID);

    void allocateAllowanceToNewEmp(Employee* employee);

};

#endif