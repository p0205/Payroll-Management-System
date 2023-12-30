#ifndef DEPENDANTMANAGER_H
#define DEPENDANTMANAGER_H
#include "DatabaseConnection.h"
#include "Menu.h"
#include "Dependant.h"
#include "Employee.h"
#include "EmployeeManager.h"

#include "Employee_Dependant.h"

class DependantManager
{
    public:
    void addDependant();
    void deleteDependant();
    int updateDependantMenu();
    void updateDependant(string column, int data, int dependantID);
    void updateDependant(string column, string data, int dependantID);
    void updateDependant(int employeeID,int dependantID);
    void updateDependant();

    Employee_Dependant* searchDependants(int employeeID);
    void addEmpDependant(int employeeID,int dependantID,string relationship);
    void updateEmpDependant(int employeeID,int dependantID,string relationship);
    Dependant* searchDependant(int dependentID);
    void viewDependants(Employee_Dependant* employeeDepedant);

    void viewDependant(Dependant* dependant);

};

#endif