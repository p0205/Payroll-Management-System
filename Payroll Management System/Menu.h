#ifndef MENU_H
#define MENU_H
#include "AccountManager.h"
#include "EmployeeManager.h"
#include "DepartmentManager.h"
#include "DependantManager.h"
#include "AllowanceManager.h"
#include "SalaryManager.h"
#include "BonusManager.h"
#include "OvertimeManager.h"
#include "LeaveManager.h"
#include "DeductionManager.h"
#include "DateManager.h"

class Menu
{
    public:
    void managerMainMenu();
    void adminMainMenu();
    void displayLogo();
    char backToMenu();
    void exitPage();
    void employeeMenu();
    void departmentMenu();
    void administerSalaryMenu();
    void handleEmolumentMenu();
    void conductDeductionMenu();
    void generateReportMenu(std::string role);
    void LeaveMenu();
    void empBackToMenu();
    void departmentBackToMenu();
    void administerSalaryBackToMenu();
    void handleEmolumentBackToMenu() ;
    void conductDeductionBackToMenu();
    void generateReportBackToMenu(std::string role);
    void manageLeaveBackToMenu();
};

#endif