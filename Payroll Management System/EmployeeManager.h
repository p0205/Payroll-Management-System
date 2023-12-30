#include "Employee.h"
#include "Menu.h"
#include "DatabaseConnection.h"
#include "DepartmentManager.h"
#include <string>
#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

class EmployeeManager
{
    public:
    int IDorName();
    void EmployeeTransform(sql::ResultSet* rs,Employee * employee);
    bool isEmployeeInList(Employee* head, int targetID);
    bool isEmployeeInList(Employee* head, const std::string& targetName);
    bool checkRepeatString(string input,string table,string column);
    bool checkRepeatInt(int input,string table,string column);
    void addEmployee();
    void deleteEmployee(Employee* employee);
    void deleteEmployee();
    Employee* searchEmployee(int id);   
    Employee* searchEmployee(string name);
    int updateEmployeeMenu();
    void updateEmployee(string column, int data, int employeeID);
    void updateEmployee(string column, string data, int employeeID);
    void updateEmployee(string column, char data, int employeeID);
    void updateEmployee(Employee* employee);
    void updateEmployee();
    void viewEmployee(Employee * employee);
    void viewEmployee();
    Employee* searchEmployees();
    int filterEmpMenu();
    void filterPosition();
    void filterDepartment();
    void filterSalary();
    void filterSalary(double minSalary, double maxSalary, string order);
    void viewAllEmployees();
    void viewEmployeeList();
    int getEmployeeCategory(int employeeID);
    int getTotalEmployees();
    int getTotalEmployeesByDepartment(int departmentID);
};

#endif