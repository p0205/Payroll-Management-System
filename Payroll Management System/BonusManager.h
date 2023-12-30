#ifndef BONUSMANAGER_H
#define BONUSMANAGER_H
#include "Bonus.h"
#include "Employee_Bonus.h"
#include "DatabaseConnection.h"
#include "Menu.h"
#include <string>

class BonusManager
{
    public:
    bool checkRepeatString(string input,string table,string column);
    bool checkRepeatInt(int input,string table,string column);
    bool isAnnualBonus(int bonusID);
    Bonus* searchBonus(int bonusID);
    Bonus* searchBonuses();
    Employee_Bonus* getEmployeeBonuses(int employeeID,int year, int month);
    void viewBonuses();
    void addBonus(std::string name, std::string frequency);
    void addBonus();
    void setBonus(int employeeID,int bonusID,double amount,std::string date);
    void setBonus();
    bool isEmployeeInList(Employee* head, int targetID) ;
    bool isEmployeeInList(Employee* head, const std::string& targetName) ;    
    bool checkRepeatEmpBonus(int employeeID,int bonusID, int targetYear);
    Employee* searchEmployees(int bonusID, int targetYear);
    Employee* searchEmployeesByDepartment(int departmentID,int bonusID,int targetYear);
    Employee* getBonusEmployees(Bonus* bonus, int targetYear);
};

#endif