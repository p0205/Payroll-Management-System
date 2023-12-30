#include <iostream>
using namespace std;
#include <iomanip>
#include <fstream>
#include "Menu.h"

void Menu::managerMainMenu()
{
    int choice;
    displayLogo();
    cout << setw(106) << "Welcome to PayrollXpert! Please choose an operation from main menu.\n\n";
    cout << setw(45) << "+" << setw(49) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(29) <<  "Main Menu" <<setw(20) << "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "---------------Menu---------------" << setw(7) << "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) << "1. Manage Employee" << setw(16)<< "|" << endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(35) << "2. Manage Department" << setw(14) << "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(30) << "3. Manage Leave" << setw(19) << "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) << "4. Generate Report" << setw(16)<< "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(22) << "5. Exit" << setw(27)<< "|"<< endl;
    cout << setw(45) << "+" << setw(49) << setfill('-') << "+" << setfill(' ')  << endl;
    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5)
        {
            cout << endl << setw(76) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5);
   switch (choice)
    {
        case 1:
            employeeMenu();
            break;

        case 2:
            departmentMenu();
            break;

        case 3:
            LeaveMenu();
            break;

        case 4:
            generateReportMenu("Manager");
            break;
            
        case 5:
            exitPage();

        default:
            break;
    }    
}

void Menu::adminMainMenu()
{
    int choice;
    displayLogo();
    cout << setw(106) << "Welcome to PayrollXpert! Please choose an operation from main menu.\n\n";
    cout << setw(45) << "+" << setw(49) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(29) <<  "Main Menu" <<setw(20) << "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "---------------Menu---------------" << setw(7) << "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(36) << "1. Administer Salary " << setw(13) << "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(35) << "2. Handle Emolument " << setw(14) << "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(35) << "3. Conduct Deduction" << setw(14) << "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(28) << "4. Pay Salary" << setw(21) << "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) << "5. Generate Report" << setw(16)<< "|"<< endl;
    cout << setw(45) << "|" << setw(49) << "|"<< endl;
    cout << setw(45) << "|" << setw(22) << "6. Exit" << setw(27)<< "|"<< endl;
    cout << setw(45) << "+" << setw(49) << setfill('-') << "+" << setfill(' ')  << endl;



    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6)
        {
            cout << endl << setw(76) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6);

    SalaryManager sm;
    char response;
   switch (choice)
    {

        case 1:
            administerSalaryMenu();
            break;

        case 2:
            handleEmolumentMenu();
            break;

        case 3:
            conductDeductionMenu();
            break;

        case 4:
            sm.paySalary();
            response = backToMenu();
            adminMainMenu();
            break;
        case 5:
            generateReportMenu("Admin");
            break;
            
        case 6:
            exitPage();
        default:
            break;
    }    
}

void Menu::displayLogo()
{
    system("clear");
    ifstream inputFile("Logo.txt");

    if (inputFile.is_open()) {
      string line;
      while (getline(inputFile, line)) {
        // Display each line on the console
        cout << setw(98) << line << endl;
      }
      cout << endl;
      inputFile.close();
    } else {
      cout << "Failed to open the file." << endl ;
    }   
}

char Menu::backToMenu()
{
    char choice;
    bool valid = true;

    cout << "\n\n\n" << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" <<setw(43) <<  "Press 'P' to return to Previous menu" <<setw(7) << "|"<< endl;
    cout << setw(45) << "|" <<setw(39) <<  "Press 'M' to return to Main Menu" <<setw(11) << "|"<< endl;
    cout  << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl << endl;  

    do
    {
      cout << setw(69) << "Choice: ";
      cin >> choice;
      if(choice=='P'|| choice=='p'|| choice=='M'|| choice=='m')
        valid = true;    
      else
      {
        valid = false;
        cout << setw(90) << "Invalid choice. Please enter a valid choice.\n" << endl;
      }
    } while (!valid);
    return choice;
}

void Menu::exitPage()
{
    displayLogo();
    cout << "\n\n" << setw(86) << "Thanks for using PayrollXpert! " << endl; 
    exit(1);
}

void Menu::employeeMenu()
{
    EmployeeManager em;
    DependantManager dm;
    int choice;
    displayLogo();
    cout << setw(90) << "Please choose an operation from menu.\n\n";
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" <<setw(32) <<  "Manage Employee" <<setw(18) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "---------------Menu---------------" << setw(8) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(31) << "1. Add Employee" << setw(19)<< "|" << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(34) << "2. Delete Employee" << setw(16) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(35) << "3. Update Employee " << setw(15) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(35) << "4. Search Employee " << setw(15) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) << "5. View Employees" << setw(17) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(32) << "6. Add Dependant" << setw(18)<< "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(35) << "7. Delete Dependant" << setw(15)<< "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(35) << "8. Update Dependant" << setw(15)<< "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(36) << "9. Back to Main Menu" << setw(14)<< "|"<< endl; 
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(23) << "10. Exit" << setw(27)<< "|"<< endl;  
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7&&choice!=8&&choice!=9&&choice!=10)
        {
            cout << endl << setw(76) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7&&choice!=8&&choice!=9&&choice!=10);

    switch (choice)
    {
    case 1:
        em.addEmployee();
        empBackToMenu();
        break;
    case 2:
        em.deleteEmployee();
        empBackToMenu();
        break;
    case 3:
        em.updateEmployee();
        break;
    case 4:
        em.viewEmployee();
        empBackToMenu();
        break;
    case 5:
        em.viewEmployeeList();
        break;
    case 6:
        dm.addDependant();
        empBackToMenu();
        break;
    case 7:
        dm.deleteDependant();
        empBackToMenu();
        break;
    case 8:
        dm.updateDependant();
        empBackToMenu();
       break;
    case 9:
        managerMainMenu();
        break;
    case 10:
        exitPage();
        break;
    default:
        break;
    }   
}

void Menu::departmentMenu()
{
  DepartmentManager dm;
    int choice;
    displayLogo();
    cout << setw(90) << "Please choose an operation from menu.\n\n";
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) <<  "Manage Department" <<setw(17) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "---------------Menu---------------" << setw(8) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(31-5) << "1. Add Department" << setw(24)<< "|" << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(34-5) << "2. Delete Department" << setw(21) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(35-5) << "3. Update Department " << setw(20) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(30) << "4. Search Department " << setw(20) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(29) << "5. View Departments " << setw(21) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(29-5) << "6. Add Position" << setw(26)<< "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(32-5) << "7. Delete Position" << setw(23)<< "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(26) << "8. View Positions" << setw(24)<< "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(37) << "9. Add Department's Position" << setw(13) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(34-5) << "10. Back to Main Menu" << setw(21)<< "|"<< endl;    
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(16) << "11. Exit" << setw(34)<< "|"<< endl; 
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7&&choice!=8&&choice!=9&&choice!=10&&choice!=11)
        {
            cout << endl << setw(76) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7&&choice!=8&&choice!=9&&choice!=10&&choice!=11);

  switch (choice)
    {
    case 1:
        dm.addDepartment();
        departmentBackToMenu();
        break;
    case 2:
        dm.deleteDepartment();
        departmentBackToMenu();
        break;
    case 3:
        dm.updateDepartment();
        break;
    case 4:
        dm.viewDepartment();
        departmentBackToMenu();
        break;
    case 5:
        dm.viewDepartmentList();
        departmentBackToMenu();
        break;
    case 6:
        dm.addPosition();
        departmentBackToMenu();
        break;
    case 7:
        dm.deletePosition();
        departmentBackToMenu();
        break;
    case 8:
        dm.viewPositionList();
        departmentBackToMenu();
       break;
    case 9:
        dm.addDept_Position();
        departmentBackToMenu();
       break;
    case 10:
        managerMainMenu();
       break;
    case 11:
        exitPage();
        break;
    default:
        break;
    }
}

void Menu::administerSalaryMenu()
{
    SalaryManager sm;
    int choice;
    displayLogo();
    cout << setw(90) << "Please choose an operation from menu.\n\n";
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" <<setw(33) <<  "Administer Salary" <<setw(17) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "---------------Menu---------------" << setw(8) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(35) << "1. Update Basic Salary" << setw(15) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(36) << "2. Add Salary Schedule " << setw(14) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(39) << "3. Delete Salary Schedule " << setw(11) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) << "4. Back to Main Menu" << setw(17)<< "|"<< endl;   
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(20) << "5. Exit" << setw(30)<< "|"<< endl;  
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;

    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5)
        {
            cout << endl << setw(76) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5);

  switch (choice)
    {
    case 1:
        sm.updateBasicSalary();
        administerSalaryBackToMenu();
        break;
    case 2:
        sm.addSalarySchedule();
        administerSalaryBackToMenu();
        break;
    case 3:
        sm.deleteSalarySchedule();
        administerSalaryBackToMenu();
        break;
    case 4:
        adminMainMenu();
        break;
    case 5:
        exitPage();
        break;

    default:
        break;
    }

}

void Menu::handleEmolumentMenu()
{
    int choice;
    AllowanceManager am;
    BonusManager bm;
    OvertimeManager om;
    displayLogo();
    cout << setw(90) << "Please choose an operation from menu.\n\n";
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" <<setw(33) <<  "Handle Emolument" <<setw(17) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "---------------Menu---------------" << setw(8) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(31) << "1. Add Allowance" << setw(19)<< "|" << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(36) << "2. Allocate Allowance" << setw(14) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(28) << "3. Add Bonus " << setw(22) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(27) << "4. Set Bonus" << setw(23) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(34) << "5. Compute Overtime" << setw(16) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(35) << "6. Back to Main Menu" << setw(15)<< "|"<< endl;    
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(22) << "7. Exit" << setw(28)<< "|"<< endl; 
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7)
        {
            cout << endl << setw(76) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7);
    switch (choice)
    {
        case 1:      
            am.addAllowance();
            handleEmolumentBackToMenu();
            break;

        case 2:
            am.allocateAllowance();
            handleEmolumentBackToMenu();
            break;

        case 3:
            bm.addBonus();
            handleEmolumentBackToMenu();
            break;

        case 4:
            bm.setBonus();
            handleEmolumentBackToMenu();
            break;

        case 5:
            om.computeOvertime();
            handleEmolumentBackToMenu();
            break;

        case 6:
            adminMainMenu();
            break;
            
        case 7:
            exitPage();
            break;

        default:
            break;
    }
}

void Menu::conductDeductionMenu()
{
    DeductionManager dm;
    LeaveManager lm;
    int choice;
    displayLogo();
    cout << setw(90) << "Please choose an operation from menu.\n\n";
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) <<  "Conduct Deduction" <<setw(17) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "---------------Menu---------------" << setw(8) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(30) << "1. Add Deduction" << setw(20)<< "|" << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) << "2. Assign Deduction" << setw(17) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(34) << "3. Back to Main Menu" << setw(16)<< "|"<< endl;    
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(21) << "4. Exit" << setw(29)<< "|"<< endl; 
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4)
        {
            cout << endl << setw(76) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4);
    switch (choice)
    {
    case 1:
        dm.addDeduction();
        conductDeductionBackToMenu();
        break;
    case 2:
        dm.assignDeduction();
        conductDeductionBackToMenu();
        break;
    case 3:
        adminMainMenu();
        break;
    case 4:
        exitPage();
        break;
    default:
        break;
    }
}

void Menu::generateReportMenu(std::string role)
{   
    LeaveManager lm;
    SalaryManager sm;
    int choice;
    displayLogo();
    cout << setw(90) << "Please choose an operation from menu.\n\n";
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" <<setw(33) <<  "Generate Report" <<setw(17) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "---------------Menu---------------" << setw(8) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(30) << "1. Print Payslip" << setw(20)<< "|" << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(40) << "2. Produce Payroll Summary" << setw(10) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(34) << "3. Back to Main Menu" << setw(16)<< "|"<< endl;    
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(21) << "4. Exit" << setw(29)<< "|"<< endl; 
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4)
        {
            cout << endl << setw(76) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4);
  switch (choice)
    {
    case 1:
        sm.printPaySlip(role);
        generateReportBackToMenu(role);
        break;
    case 2:
        sm.producePayrollReport();
        generateReportBackToMenu(role);
        break;
    case 3:
        if(role == "Admin")
            adminMainMenu();
        else if(role == "Manager")
            managerMainMenu();
        break;
    case 4:
        exitPage();
        break;

    default:
        break;
    }
}

void Menu::LeaveMenu()
{
    LeaveManager lm;
    displayLogo();
    int choice;
    std::cout << std::setw(90) << "Please choose an operation from menu.\n\n"
              << std::setw(45) << "+" << std::setw(50) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl
              << std::setw(45) << "|" << std::setw(50) << "|"<< std::endl
              << std::setw(45) << "|" << std::setw(36) <<  "Manage Employee Leave" << std::setw(14) << "|"<< std::endl
              << std::setw(45) << "|" << std::setw(50) << "|"<< std::endl
              << std::setw(45) << "|" << std::setw(42) <<  "---------------Menu---------------" << std::setw(8) << "|"<< std::endl
              << std::setw(45) << "|" << std::setw(50) << "|"<< std::endl
              << std::setw(45) << "|" << std::setw(35) << "1. Assign Leave Quota" << std::setw(15) << "|"<< std::endl
              << std::setw(45) << "|" << std::setw(50) << "|"<< std::endl
              << std::setw(45) << "|" << std::setw(37) << "2. Manage Leave Request" << std::setw(13) << "|"<< std::endl
              << std::setw(45) << "|" << std::setw(50) << "|"<< std::endl
              << std::setw(45) << "|" << std::setw(34) << "3. Back to Main Menu" << std::setw(16) << "|"<< std::endl   
              << std::setw(45) << "|" << std::setw(50) << "|"<< endl
              << std::setw(45) << "|" << std::setw(21) << "4. Exit" << std::setw(29)<< "|"<< std::endl
              << std::setw(45) << "+" << std::setw(50) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl;
    do
    {
        std::cout << std::endl << std::setw(70) << "Choice: ";
        std::cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4)
        {
            std::cout << std::endl << std::setw(76) << "Please enter a valid choice." << std::endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4);
  switch (choice)
    {
    case 1:
        lm.assignLeaveQuota();
        manageLeaveBackToMenu();
        break;
    case 2:
        lm.manageLeaveRequest();
        manageLeaveBackToMenu();
        break;
    case 3:
        managerMainMenu();
        break;
    case 4:
        exitPage();
        break;
    default:
        break;
    }
}

void Menu::empBackToMenu()
{
  char choice = backToMenu(); 
  if(choice == 'P'||choice =='p')
    employeeMenu();
  else if(choice=='M'||choice =='m')
    managerMainMenu(); 
}

void Menu::departmentBackToMenu()
{
    char choice = backToMenu(); 
    if(choice == 'P'||choice =='p')
        departmentMenu();
    else if(choice=='M'||choice =='m')
        managerMainMenu();
}

void Menu::administerSalaryBackToMenu()
{
    char choice = backToMenu(); 
    if(choice == 'P'||choice =='p')
        administerSalaryMenu();
    else if(choice=='M'||choice =='m')
        adminMainMenu();   
}

void Menu::handleEmolumentBackToMenu() 
{
    char choice = backToMenu(); 
    if(choice == 'P'||choice =='p')
        handleEmolumentMenu();
    else if(choice=='M'||choice =='m')
        adminMainMenu();     
}

void Menu::conductDeductionBackToMenu() 
{
    char choice = backToMenu(); 
    if(choice == 'P'||choice =='p')
        conductDeductionMenu();
    else if(choice=='M'||choice =='m')
        adminMainMenu();     
}

void Menu::generateReportBackToMenu(std::string role) 
{
    char choice = backToMenu(); 
    if(choice == 'P'||choice =='p')
        generateReportMenu(role);
    else if(choice=='M'||choice =='m')
    {
        if(role == "Admin")
            adminMainMenu();
        else if(role == "Manager")
            managerMainMenu();     
    }
}

void Menu::manageLeaveBackToMenu()
{
    char choice = backToMenu(); 
    if(choice == 'P'||choice =='p')
        LeaveMenu();
    else if(choice=='M'||choice =='m')
        managerMainMenu();
}
