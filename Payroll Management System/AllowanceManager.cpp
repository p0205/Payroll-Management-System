#include "AllowanceManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <iterator> 
#include <algorithm> 

void addAllowanceHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(22) << "Add Allowance" << setw(8) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

void allocateAllowanceHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(24) << "Allocate Allowance" << setw(6) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

void updateAllowanceHeader()
{
    std::cout << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << std::setfill(' ') << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl                           
                << std::setw(55) << "|" << std::setw(23) << "Update Allowance" << setw(7) << "|" << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl
                << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << setfill(' ') << std::endl << std::endl; 
}

void removeAllowanceHeader()
{
    std::cout << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << std::setfill(' ') << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl                           
                << std::setw(55) << "|" << std::setw(23) << "Remove Allowance" << setw(7) << "|" << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl
                << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << setfill(' ') << std::endl << std::endl; 
}

bool AllowanceManager::checkRepeatString(std::string input,std::string table,std::string column)
{
    DatabaseConnection dbConn;
    bool repeat;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM " + table + " WHERE " + column + " = ?");
    ps->setString(1,input);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
        repeat = true;
    else
        repeat = false;
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return repeat;
}

bool AllowanceManager::checkRepeatInt(int input,std::string table,std::string column)
{
    DatabaseConnection dbConn;
    bool repeat;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM " + table + " WHERE " + column + " = ?");
    ps->setInt(1,input);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
        repeat = true;
    else
        repeat = false;
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return repeat;
}

Allowance* AllowanceManager::searchAllowance(int allowanceID)
{
    DatabaseConnection dbConn;
    Allowance* allowance = new Allowance();
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM ALLOWANCE WHERE AllowanceID = ?");
    ps->setInt(1,allowanceID);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {   
        allowance->allowanceID = rs->getInt("AllowanceID");
        allowance->frequency = rs->getString("Frequency");
        allowance->name = rs->getString("Name");
    }
    else
    {
        delete allowance;
        return nullptr;
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return allowance;
}

Allowance* AllowanceManager::searchAllowances()
{
    DatabaseConnection dbConn;
    Allowance* allowance = NULL;
    Allowance* head = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM ALLOWANCE");
    sql::ResultSet* rs = ps->executeQuery();
    while(rs->next())
    {   
        
        if(head == NULL)
        {
            allowance = new Allowance();
            head = allowance;
        }
        else
        {
            allowance->next = new Allowance();
            allowance = allowance->next; 
        }
        allowance->allowanceID = rs->getInt("AllowanceID");      
        allowance->name = rs->getString("Name");      
        allowance->frequency = rs->getString("Frequency");      
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

void AllowanceManager::viewAllowances()
{
    Allowance* allowance = NULL;
    allowance = searchAllowances();
    if(allowance!=NULL)
    {
        std::cout << std::setw(24) << "+" << std::setfill('-') <<"-" << std::setw(107) << "+" << std::setfill(' ') << std::endl
                  << std::setw(28)  << "| ID " << std::setw(13) << "| Name" << std::setw(65) <<"| Frequency"  << std::setw(26) << "|" << std::endl
                  << std::setw(24) << "|" << std::setfill('-') <<"-" << std::setw(107) << "|" << std::setfill(' ') << std::endl;
        while(allowance!=NULL)
        {
            std::cout << std::left
                      << std::setw(23) << " " << "| "<< std::setw(9) << allowance->allowanceID << " | " << std::setw(57) << allowance->name << " | "  << std::setw(34) << allowance->frequency  << "|" << std::endl;
            allowance = allowance->next;
        }
        std::cout << std::right
                  << std::setw(24) << "+" << std::setfill('-') <<"-" << std::setw(107) << "+" << std::setfill(' ') << std::endl;
    }
    else
    {
        std::cout << std::setw(82) << "No allowance available." << std::endl;
    }
    delete allowance;
}

void AllowanceManager::addAllowance(std::string name, std::string frequency,int isExempted)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO ALLOWANCE(Name,Frequency,IsExempted) VALUES (?,?,?)");
    ps->setString(1,name);
    ps->setString(2,frequency);
    ps->setInt(3,isExempted);
    ps->executeUpdate();
    ps->close();
    delete ps;
}

void AllowanceManager::addAllowance()
{
    std::string name, frequency;
    bool repeat;
    Menu menu;
    int strlength,isExempted;
    menu.displayLogo();
    addAllowanceHeader();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Allowance Name  : ";
        getline(std::cin,name);
        repeat = checkRepeatString(name,"ALLOWANCE","Name");
        strlength = name.length();
        if(repeat)
            std::cout << std::endl << std::setw(95)<< "The name already exists. Please use another name." << std::endl;
        if(strlength > 30)
            std::cout << "\n"<< std::setw(85) << "The name is too long. Please use a shorter name." << std::endl;
    } while (repeat||strlength > 30);

    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Frequency (`M` for monthly OR `A` for annually) : ";
        std::cin >> frequency;
        if(frequency!="M"&&frequency!="m"&&frequency!="A"&&frequency!="a")
        {
            std::cout << std::endl << std::setw(76) << "Please enter a valid choice." << std::endl;
        }
    } while (frequency!="M"&&frequency!="m"&&frequency!="A"&&frequency!="a");

    if(frequency=="M"||frequency=="m")
        frequency = "Monthly";
    else if(frequency=="A"||frequency=="a")
        frequency = "Annually";

    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter `1` if this allowance is tax-exempt; otherwise, enter `0` : ";
        std::cin >> isExempted;
        if(isExempted!=1&&isExempted!=0)
        {
            std::cout << std::endl << std::setw(76) << "Please enter a valid choice." << std::endl;
        }
    } while (isExempted!=1&&isExempted!=0);


    menu.displayLogo();
    addAllowanceHeader();
    std::cout << "\n\n" <<std::setw(83) <<  "NEW Allowance Preview\n\n" 
                <<std::setw(42) << " " <<std::setw(56) <<std::setfill('*') << "*"  <<std::setfill(' ') 
                << "\n\n"<<std::setw(72) << "Name           : " << name << std::endl
                << "\n\n"<<std::setw(72) << "Frequency      : " << frequency << std::endl
                << "\n\n"<<std::setw(72) << "Tax-exempt     : " ;
                
    if(isExempted==1)
        std::cout   << "True" << std::endl;
    else
        std::cout   << "False" << std::endl;
             

    char confirm;
    std::cout << "\n\n" <<std::setw(97) << "Are you sure to add this allowance? Enter Y/y to confirm: ";
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        addAllowance(name,frequency,isExempted);
        std::cout << "\n" <<std::setw(89) << "[ New allowance is added successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" <<std::setw(103) << "[ Addition process has been cancelled. No changes have been made ]" << std::endl;
    }
}

Employee_Allowance* AllowanceManager::getEmployeeAllowances(int employeeID)
{
    Employee_Allowance* head = NULL;
    Employee_Allowance* empAllowance = NULL;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT AllowanceID,Amount FROM EMPLOYEE_ALLOWANCE WHERE EmployeeID = ?");

    ps->setInt(1,employeeID);
    sql::ResultSet* rs = ps->executeQuery();

    while(rs->next())
    {
        if(head == NULL)
        {
            empAllowance = new Employee_Allowance();
            head = empAllowance;
        }
        else
        {
            empAllowance->next = new Employee_Allowance();
            empAllowance = empAllowance->next;
        }
        empAllowance->allowanceID = rs->getInt("AllowanceID");
        empAllowance->amount = rs->getDouble("Amount");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

Employee_Allowance* AllowanceManager::getAllowanceEmp(int allowanceID)
{
    Employee_Allowance* head = NULL;
    Employee_Allowance* empAllowance = NULL;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT EmployeeID,Amount FROM EMPLOYEE_ALLOWANCE WHERE AllowanceID = ?");

    ps->setInt(1,allowanceID);
    sql::ResultSet* rs = ps->executeQuery();

    while(rs->next())
    {
        if(head == NULL)
        {
            empAllowance = new Employee_Allowance();
            head = empAllowance;
        }
        else
        {
            empAllowance->next = new Employee_Allowance();
            empAllowance = empAllowance->next;
        }
        empAllowance->employeeID = rs->getInt("EmployeeID");
        empAllowance->amount = rs->getDouble("Amount");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

Employee* AllowanceManager::searchEmployees(int allowanceID)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE");
    sql::ResultSet* rs = ps->executeQuery();
    EmployeeManager em;
    Employee* employee = NULL;
    Employee* head = NULL;
    DateManager dateManager;
    std::string currentDate = dateManager.getCurrentDate();
    while(rs->next())
    {
        if(!checkExistEmpAllowance(rs->getInt("EmployeeID"),allowanceID,currentDate))//if the employee have no the allowance
        {
            if(head == NULL)
            {
                employee = new Employee();
                head = employee;
            }
            else
            {
                employee->next = new Employee();
                employee = employee->next;
            }
            em.EmployeeTransform(rs,employee);
        }
    } 
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

Employee* AllowanceManager::searchEmployeesByDepartment(int departmentID,int allowanceID)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE WHERE DepartmentID = ?");
    ps->setInt(1,departmentID);
    sql::ResultSet* rs = ps->executeQuery();
    Employee* employee = NULL;
    Employee* head = NULL;
    EmployeeManager em;
        DateManager dateManager;
    std::string currentDate = dateManager.getCurrentDate();

    while(rs->next())
    {
        if(!checkExistEmpAllowance(rs->getInt("EmployeeID"),allowanceID,currentDate))//if the employee have no the allowance
        {
            if(head == NULL)
            {
                employee = new Employee();
                head = employee;
            }
            else
            {
                employee->next = new Employee();
                employee = employee->next;
            }
            em.EmployeeTransform(rs,employee);
        }
    } 
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

bool AllowanceManager::checkExistEmpAllowance(int employeeID,int allowanceID, std::string currentDate) //check whether the employee has allowance for this month
{
    bool exist;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT AllowanceID,Amount FROM EMPLOYEE_ALLOWANCE WHERE EmployeeID = ? AND AllowanceID = ? AND YEAR(`Date`) = YEAR(?) AND MONTH(`Date`) = MONTH(?)");
    ps->setInt(1,employeeID);
    ps->setInt(2,allowanceID);
    ps->setString(3,currentDate);
    ps->setString(4,currentDate);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
        exist = true;
    else
        exist = false;
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return exist;
}

bool AllowanceManager::isEmployeeInList(Employee* head, int targetID) 
{
    while (head != nullptr) {
        if (head->id == targetID) {
            return true; // Employee ID already exists in the list
        }
        head = head->next;
    }
    return false; // Employee ID not found in the list
}

bool AllowanceManager::isEmployeeInList(Employee* head, const std::string& targetName) 
{
    Employee* current = head;
    while (current != nullptr) {
        if (current->name == targetName) {
            return true; // Employee name already exists in the list
        }
        current = current->next;
    }
    return false; // Employee name not found in the list
}

Employee* AllowanceManager::getAllowanceEmployees(int allowanceID)
{
    Menu menu;
    DateManager dateManager;
    menu.displayLogo();
    allocateAllowanceHeader();
    std::cout << std::setw(81) << "Allocate Allowance To: " << std::endl
              << std::setw(53) << "*" << std::setfill('*') << std::setw(35) << "*" << std::setfill(' ') << std::endl << std::endl
              << std::setw(70) << "1. All employees" << std::endl
              << std::setw(88) << "2. All employees in one department" << std::endl
              << std::setw(77) << "3. Specific employee(s)" << std::endl;
    int choice;
    do
    {
        std::cout << std::endl << std::setw(70) << "Choice: ";
        std::cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3)
            std::cout << std::endl << std::setw(84) << "Please enter a valid choice." << endl;
    }while (choice!=1&&choice!=2&&choice!=3);

    DepartmentManager dm;
    Department* head = NULL;
    Department* department = NULL;
    EmployeeManager em;
    Employee* employee = NULL;
    Employee* employeeHead = NULL;
    char response;
    int departmentID,employeeID;
    string name;
    char again;
    bool repeat = false;


    switch (choice)
    {
    case 1:
        //get all employee
        employee = searchEmployees(allowanceID);
        break;

    case 2:
        head = dm.searchDepartments();
        do
        {
            department = head;
            if(department!=NULL)
            {
                menu.displayLogo();
                allocateAllowanceHeader();
                std::cout << std::setw(92) << "Please choose a department from the list. " << std::endl
                //display all department available
                            << std::setw(38) << "+" << std::setfill('-') <<"-" << std::setw(64) << "+" << std::setfill(' ') << std::endl
                            << std::setw(52) << "| Department ID" << setw(19) <<"| Department Name"  << std::setw(32) << "|" << std::endl
                            << std::setw(38) << "|" << std::setfill('-') <<"-" << std::setw(64) << "|" << std::setfill(' ') << std::endl;
                while(department!=NULL)
                {
                    std::cout << std::left << std::setw(37) << " " << "| " << std::setw(15) << department->departmentID << "| "  << std::setw(45) <<department->departmentName << " " << "|" << std::endl;
                    department = department->next;
                }
                std::cout << std::right;
                std::cout << std::setw(38) << "+" << std::setfill('-') << "-" << std::setw(64) << "+" << std::setfill(' ') << std::endl;
         
                //user enter department ID
                std::cout  << "\n\n"<< std::setw(72) << "Enter Department ID     : ";
                std::cin >> departmentID;

                //search department
                department = head;
                while(department!=NULL)
                {
                    //if found, break
                    if(departmentID == department->departmentID)
                        break;
                    else
                        department = department->next;
                }
                //if department not found 
                if(department == NULL)
                {
                    response = 'Z';
                    std::cout << endl << setw(94) << "The department is not found. Enter Y/y to retry: ";
                    std::cin >> response;
                    if(response != 'y'&&response!='Y')
                    {
                        menu.handleEmolumentMenu();
                        return 0;
                    }
                }
            }
        } while (response == 'y' || response =='Y');
        
        //pass the found department ID to get all employees in that department
        employee = searchEmployeesByDepartment(departmentID,allowanceID);
        break;

    case 3:
        menu.displayLogo();
        allocateAllowanceHeader();
        choice = em.IDorName();
        //get an employee 
        do {
            bool repeat = false;
            if (choice == 1) 
            {
                // For Employee ID
                do
                {
                    menu.displayLogo();
                    allocateAllowanceHeader();
                    response = 'Z';

                    do {
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee ID              : ";
                        std::cin >> employeeID;
                        // Check if the user input already exists in the list
                        repeat = isEmployeeInList(employeeHead, employeeID);
                        if (repeat) {
                            std::cout << std::right << std::setw(90) << "The employee already exists in the list. " << std::endl;
                        }
                    } while (repeat);

                    if(employeeHead == NULL) 
                    {
                        employee = em.searchEmployee(employeeID);
                    }
                    else
                    {
                        employee->next = em.searchEmployee(employeeID);
                        employee = employee->next;
                    }

                    if (employee == NULL) 
                    {
                        std::cout << "\n" << std::setw(90) << "The employee is not found. Enter Y/y to retry: ";
                        std::cin >> response;
                        if (response != 'y' && response != 'Y') 
                        {
                            if (employeeHead == NULL)
                                menu.handleEmolumentMenu();
                            else
                                break;
                        }
                    }
                }while(response == 'y' || response == 'Y');
            } 

            else if (choice == 2) 
            {
                menu.displayLogo();
                allocateAllowanceHeader();
                response = 'Z';
                do
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    do {
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee Name            : ";
                        getline(cin, name);

                        // Check if the user input already exists in the list
                        repeat = isEmployeeInList(employeeHead, name);
                        if (repeat) {
                            std::cout << "\n" << std::right << std::setw(90) << "The employee already exists in the list. " << std::endl;
                        }
                    } while (repeat);

                    if(employeeHead == NULL) 
                    {
                        employee = em.searchEmployee(name);
                    }
                    else
                    {
                        employee->next = em.searchEmployee(name);
                        employee = employee->next;
                    }
                
                    if (employee == NULL) 
                    {
                        std::cout << "\n" << std::setw(90) << "The employee is not found. Enter Y/y to retry: ";
                        std::cin >> response;
                        if (response != 'y' && response != 'Y') 
                        {
                            if (employeeHead == NULL)
                                menu.handleEmolumentMenu();
                            else
                                break;
                        }
                    }
                }while(response == 'y' || response == 'Y');
            }
    std::string currentDate = dateManager.getCurrentDate();

            if (checkExistEmpAllowance(employee->id, allowanceID,currentDate))
            {
                employee = nullptr;
                std::cout << "\n" << std::setw(95) << "The allowance is already allocated to this employee." << std::endl;
            }

            if(employeeHead == NULL) 
                employeeHead = employee;

            std::cout << std::right << "\n" << std::setw(91) << "Enter Y to add another employee to the list : "; 
            std::cin >> again;
        } while (again == 'Y' || again == 'y');
        
        employee = employeeHead;

        break;
    default:
        break;
    }
    return employee;

}

void AllowanceManager::allocateAllowance(int employeeID,int allowanceID,double amount,std::string date)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO EMPLOYEE_ALLOWANCE(EmployeeID,AllowanceID,Amount,`Date`) VALUES (?,?,?,?)");
    ps->setInt(1,employeeID);
    ps->setInt(2,allowanceID);
    ps->setDouble(3,amount);
    ps->setString(4,date);
    ps->executeUpdate();
    ps->close();
    delete ps;   
}

// void AllowanceManager::allocateAllowance()
// {
//     int employeeID, allowanceID;
//     double amount;
//     std::string date;
//     bool repeat, validDate;
//     Menu menu;
//     menu.displayLogo();
//     allocateAllowanceHeader();
//     viewAllowances();
//     Allowance* allowance = NULL;
//     DateManager dateManager;
//     int targetYear,targetMonth;
//     do
//     {
//         std::cout << "\n\n" << std::setw(72) << "Enter Allowance ID           : ";
//         std::cin >> allowanceID;
//         allowance = searchAllowance(allowanceID);
//         if(allowance==NULL)
//             std::cout  << "\n\n" << std::setw(90) << "Invalid allowance ID. Please try again." << std::endl;
//     } while (allowance==NULL);
//     do
//     {
//         std::cout << "\n\n" << std::setw(72) << "Enter Allowance Amount (RM)  : ";
//         std::cin >> amount;
//         if(amount<0||amount>999999.99)
//             std::cout  << "\n\n" << std::setw(87)<< "Invalid amount. Please try again." << std::endl;
//     } while (amount<0||amount>999999.99);
//     menu.displayLogo();
//     allocateAllowanceHeader();
//         // ~ get employee pointer
//     Employee* head = NULL;
//     head = getAllowanceEmployees(allowanceID);
//     menu.displayLogo();
//     allocateAllowanceHeader();
//     if(head==NULL)
//     {
//         std::cout << "\n\n" << std::setw(86) << "No allowance allocation is needed. " << std::endl;
//         return;
//     }
//     Employee* employee = head;
//     DepartmentManager dm;
//     Department* department = NULL;
//     Position* position = NULL;
//     std::cout << std::right << std::setw(27) << "Choice         : " << std::left << allowance->name << " Allowance" << std::endl;
//     std::cout << std::right << std::setw(30) << "Amount         : RM " << std::left << amount << std::endl;
//     std::cout << std::right << std::setw(27) << "Effective Date : " << std::left << dateManager.getCurrentDate() << std::endl;
//     std::cout << std::right << std::setw(10) << "+" << std::setfill('-') << "-" << std::setw(138) << "+" << std::setfill(' ') << std::endl
//               << std::setw(24) << "| Employee Name" << std::setw(50) << "| Department"  << std::setw(40) << "| Position" << std::setw(35)  << "|" << std::endl
//               << std::setw(10) << "|" << std::setfill('-') << "-" << std::setw(138) << "|" << std::setfill(' ') << std::endl;   
//     while(employee!=NULL) 
//     {
//         //get department name and position name
//         department = dm.searchDepartment(employee->departmentID);
//         position = dm.searchPosition(employee->positionID);
//         std::cout << std::left << std::setw(9) << " " << "| " << std::setw(51) << employee->name << "| "  << std::setw(40) << department->departmentName << "| "  << std::setw(42) << position->positionName << "| " << std::endl;
//         //proceed to next element
//         employee = employee->next;
//     }
//     std::cout << std::right << std::setw(10) << "+" << std::setfill('-') <<"-" << std::setw(138) << "+" << std::setfill(' ') << std::endl;
//     char confirm;
//     std::cout << "\n\n" <<std::setw(104) << "Are you sure to allocate allowance to this/these employee(s)? Enter Y/y to confirm: ";
//     std::cin >> confirm;
//     if(confirm == 'Y'|| confirm=='y')
//     {
//         std::string date = dateManager.getCurrentDate();
//         employee = head;
//         while(employee!=NULL)
//         {
//             allocateAllowance(employee->id,allowanceID,amount,date);
//             employee = employee->next;
//         }
//         std::cout << "\n" <<std::setw(90) << "[ Allowance is allocated successfully ]" << std::endl;
//     }
//     else
//     {
//         std::cout << "\n" <<std::setw(103) << "[ Allocation process has been cancelled. No changes have been made ]" << std::endl;
//     }   
// }

// void AllowanceManager::updateAllowance()
// {
//     Menu menu;
//     char response;
//     menu.displayLogo();
//     updateAllowanceHeader();
//     std::cout << std::setw(81) << "Update Allowance of: " << std::endl
//               << std::setw(53) << "*" << std::setfill('*') << std::setw(35) << "*" << std::setfill(' ') << std::endl << std::endl
//               << std::setw(77) << "1. All employees    " << std::endl
//               << std::setw(77) << "2. Specific employee" << std::endl;
//     int choice;
//     do
//     {
//         std::cout << std::endl << std::setw(70) << "Choice: ";
//         std::cin >> choice;
//         if(choice!=1&&choice!=2)
//             std::cout << std::endl << std::setw(84) << "Please enter a valid choice." << endl;
//     }while (choice!=1&&choice!=2);
//     switch (choice)
//     {
//         case 1:
//             updateAllAllowance();
//             break;
//         case 2:
//             updateEmpAllowance();
//             break;
//     default:
//         break;
//     }
// }

// void AllowanceManager::updateEmpAllowance()
// {
//     Menu menu;
//     EmployeeManager em;
//     Employee* employee = NULL;
//     int employeeID;
//     char response;
//     menu.displayLogo();
//     updateAllowanceHeader();
//     do {
//         std::cout << "\n\n" << std::setw(72) << "Enter Employee ID              : ";
//         std::cin >> employeeID;
//         employee = em.searchEmployee(employeeID);
//         if (employee==NULL) 
//         {
//             std::cout << "\n" << std::setw(90) << "The employee is not found. Enter Y/y to retry: ";
//             std::cin >> response;
//             if (response != 'y' && response != 'Y') 
//             {
//                     menu.handleEmolumentMenu();
//             }
//         }
//     } while (response == 'y' || response == 'Y');
//     updateEmpAllowance(employee);
// }

// void AllowanceManager::updateEmpAllowance(Employee* employee)
// {
//     Menu menu;
//     menu.displayLogo();
//     updateAllowanceHeader();
//     //show allowance and amount 
//     Employee_Allowance* head = NULL;
//     head = getEmployeeAllowances(employee->id);
//     if(head == NULL)
//     {
//         std::cout << "\n\n" << std::setw(94) << "There is no allowance allocated to this employee." << std::endl;
//         return;
//     }
//     std::cout << std::setw(48) << "Employee ID   : " << employee->id << std::endl;
//     std::cout << std::setw(48) << "Employee Name : " << employee->name << std::endl;
//     std::cout << std::right << std::setw(31) << "+" << std::setfill('-') << "-" << std::setw(83) << "+" << std::setfill(' ') << std::endl
//                     << std::setw(62) << "| Allowance ID | Allowance Name " << std::setw(37) << "|" << " Amount (RM) " << std::setw(3) << "|" << std::endl
//                     << std::setw(31) << "|" << std::setfill('-') << "-" << std::setw(83) << "|" << std::setfill(' ') << std::endl;
//     Employee_Allowance* empAllowance = head;
//     Allowance* allowance = NULL;
//     while(empAllowance!=NULL)
//     {
//         allowance = searchAllowance(empAllowance->allowanceID);
//         std::cout << std::left << std::setw(30) << " " << "| "  << std::setw(13) << allowance->allowanceID  << "| " << std::setw(51) << allowance->name << "| "  << std::setw(14) << empAllowance->amount << "| "  << std::endl;
//         empAllowance = empAllowance->next;
//     }
//     std::cout << std::setw(31) << std::right << "+" << std::setfill('-') << "-" << std::setw(83) << "+" << std::setfill(' ') << std::endl;
//     int allowanceID;
//     do
//     {
//         std::cout << "\n\n" << std::setw(72) << std::right << "Please enter the Allowance ID that want to update : ";
//         std::cin >> allowanceID;
//         allowance = searchAllowance(allowanceID);
//         if(allowance == NULL)
//             std::cout << "\n" << std::right << std::setw(90) << "Please enter the Allowance ID in the list." << std::endl;
//     } while (allowance == NULL);
//     double amount = 0;
//     do
//     {
//         std::cout << "\n\n" << std::setw(72) << std::right << "Enter updated Allowance Amount(RM) : ";
//         std::cin >> amount;
//         if(amount<0||amount>999999.99)
//             std::cout << "\n" << std::setw(84) << "Please enter a valid amount. " << std::endl; 
//     } while (amount<0||amount>999999.99);
//     menu.displayLogo();
//     updateAllowanceHeader();
//     std::cout << "\n\n" << std::setw(83) <<  "Updated Allowance Preview\n\n" 
//                 << std::setw(42) << " " << std::setw(56) << std::setfill('*') << "*"  <<std::setfill(' ') 
//                 << "\n\n"<< std::setw(72) << "Employee ID           : " << employee->id << std::endl
//                 << "\n\n"<< std::setw(72) << "Employee Name         : " << employee->name << std::endl
//                 << "\n\n"<< std::setw(72) << "Allowance             : " << allowance->name << std::endl
//                 << "\n\n"<< std::setw(72) << "Updated Amount (RM)   : " << amount << std::endl
//                 << "\n\n\n"<< std::setw(90) << "Are you sure to update? Enter 'Y' to update : " ;
//     char choice;
//     std::cin >> choice;
//     if(choice=='Y'||choice=='y')
//     {
//         updateEmpAllowance(employee->id,allowanceID,amount); 
//         std::cout << "\n" << std::setw(92) << "[ Allowance Amount is updated successfully ]" << std::endl;
//     }
//     else
//     {
//         std::cout << "\n" << std::setw(102) << "[ Update process has been cancelled. No changes have been made ]" << std::endl;
//     }
//     std::cout << "\n" << std::setw(45) << "+" << std::setw(50) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl
//                 << std::setw(45) << "|" << std::setw(44) <<  "Press 'A' to update another Allowance" << std::setw(6) << "|"<< std::endl
//                 << std::setw(45) << "|" << std::setw(43) <<  "Press 'P' to return to Previous menu" << std::setw(7) << "|"<< std::endl
//                 << std::setw(45) << "|" << std::setw(39) <<  "Press 'M' to return to Main Menu" << std::setw(11) << "|"<< std::endl
//                 << std::setw(45) << "+" << std::setw(50) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl << std::endl; 
//     bool valid; 
//     do
//     {
//         std::cout << std::setw(69) << "Choice: ";
//         std::cin >> choice;
//       if(choice=='A'||choice=='a'||choice=='P'|| choice=='p'|| choice=='M'|| choice=='m')
//         valid = true;    
//       else
//       {
//         valid = false;
//         std::cout << std::setw(90) << "Invalid choice. Please enter a valid choice.\n" << std::endl;
//       }
//     } while (!valid);
//     if(choice == 'a'||choice =='A')
//         updateEmpAllowance(employee);
//     else if(choice == 'P'||choice =='p')
//         menu.handleEmolumentMenu();
//     else if(choice=='M'||choice =='m')
//         menu.adminMainMenu(); 
// }

// void AllowanceManager::updateEmpAllowance(int employeeID,int allowanceID, double amount)
// {
//     DatabaseConnection dbConn;
//     sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE EMPLOYEE_ALLOWANCE SET Amount = ? WHERE EmployeeID = ? AND AllowanceID = ?");
//     ps->setDouble(1,amount);
//     ps->setInt(2,employeeID);
//     ps->setInt(3,allowanceID);
//     ps->executeUpdate();
//     ps->close();
//     delete ps;   
// }

// void AllowanceManager::updateAllAllowance(
// {
//     Menu menu;
//     AllowanceManager am;
//     Allowance* allowance = NULL;
//     int allowanceID;
//     char response, choice;
//     menu.displayLogo();
//     updateAllowanceHeader();
//     viewAllowances();
//     do {
//         std::cout << "\n\n" << std::setw(72) << "Enter Allowance ID                 : ";
//         std::cin >> allowanceID;
//         allowance = searchAllowance(allowanceID);
//         if (allowance==NULL) 
//         {
//             std::cout << "\n" << std::setw(90) << "The allowance is not found. Enter Y/y to retry : ";
//             std::cin >> response;
//             if (response != 'y' && response != 'Y') 
//             {
//                     menu.handleEmolumentMenu();
//             }
//         }
//     } while (response == 'y' || response == 'Y');
//     EmployeeManager em;
//     Employee* employee = NULL;
//     Employee_Allowance* empAllowance = NULL;
//     empAllowance = getAllowanceEmp(allowanceID);
//     DepartmentManager dm;
//     Department* department = NULL;
//     Position* position = NULL;
//     if(empAllowance!=NULL)
//     {
//         double amount = 0;
//         do
//         {
//             std::cout << "\n\n" << std::setw(72) << std::right << "Enter updated Allowance Amount(RM) : ";
//             std::cin >> amount;
//             if(amount<0||amount>999999.99)
//                 std::cout << "\n" << std::setw(84) << "Please enter a valid amount. " << std::endl; 
//         } while (amount<0||amount>999999.99);
//         menu.displayLogo();
//         updateAllowanceHeader();
//         std::cout << "\n\n" << std::setw(83) <<  "Updated Allowance Preview\n\n" 
//                     << std::setw(42) << " " << std::setw(56) << std::setfill('*') << "*"  <<std::setfill(' ') 
//                     << "\n\n"<< std::setw(36) << "Allowance              : " << allowance->name << std::endl
//                     << "\n\n"<< std::setw(36) << "Updated Amount (RM)    : " << amount << std::endl
//                     << "\n\n"<< std::setw(36) << "Affected Employee(s)   : " << std::endl;
//         std::cout << std::right << std::setw(10) << "+" << std::setfill('-') << "-" << std::setw(138) << "+" << std::setfill(' ') << std::endl
//                 << std::setw(24) << "| Employee Name" << std::setw(50) << "| Department"  << std::setw(40) << "| Position" << std::setw(35)  << "|" << std::endl
//                 << std::setw(10) << "|" << std::setfill('-') << "-" << std::setw(138) << "|" << std::setfill(' ') << std::endl; 
//         while(empAllowance!=NULL) 
//         {
//             employee = em.searchEmployee(empAllowance->employeeID);
//             //get department name and position name
//             department = dm.searchDepartment(employee->departmentID);
//             position = dm.searchPosition(employee->positionID);
//             std::cout << std::left << std::setw(9) << " " << "| " << std::setw(51) << employee->name << "| "  << std::setw(40) << department->departmentName << "| "  << std::setw(42) << position->positionName << "| " << std::endl;
//             //proceed to next element
//             empAllowance = empAllowance->next;
//         }
//         std::cout << std::right << std::setw(10) << "+" << std::setfill('-') <<"-" << std::setw(138) << "+" << std::setfill(' ') << std::endl;
//         std::cout << "\n\n\n"<< std::setw(90) << "Are you sure to update? Enter 'Y' to update : " ;
//         std::cin >> choice;
//         if(choice=='Y'||choice=='y')
//         {
//             updateAllAllowance(allowanceID,amount); 
//             std::cout << "\n" << std::setw(92) << "[ Allowance Amount is updated successfully ]" << std::endl;
//         }
//         else
//         {
//             std::cout << "\n" << std::setw(102) << "[ Update process has been cancelled. No changes have been made ]" << std::endl;
//         }
//     }
//     else
//     {
//         std::cout << "\n\n" << std::setw(97) << "[ The allowance is not yet allocated to any employee ]" << std::endl;
//     }
//     std::cout << "\n" << std::setw(45) << "+" << std::setw(50) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl
//                 << std::setw(45) << "|" << std::setw(44) <<  "Press 'A' to update another Allowance" << std::setw(6) << "|"<< std::endl
//                 << std::setw(45) << "|" << std::setw(43) <<  "Press 'P' to return to Previous menu" << std::setw(7) << "|"<< std::endl
//                 << std::setw(45) << "|" << std::setw(39) <<  "Press 'M' to return to Main Menu" << std::setw(11) << "|"<< std::endl
//                 << std::setw(45) << "+" << std::setw(50) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl << std::endl; 
//     bool valid; 
//     do
//     {
//         std::cout << std::setw(69) << "Choice: ";
//         std::cin >> choice;
//       if(choice=='A'||choice=='a'||choice=='P'|| choice=='p'|| choice=='M'|| choice=='m')
//         valid = true;    
//       else
//       {
//         valid = false;
//         std::cout << std::setw(90) << "Invalid choice. Please enter a valid choice.\n" << std::endl;
//       }
//     } while (!valid);
//     if(choice == 'a'||choice =='A')
//         updateAllAllowance();
//     else if(choice == 'P'||choice =='p')
//         menu.handleEmolumentMenu();
//     else if(choice=='M'||choice =='m')
//         menu.adminMainMenu(); 
// }

// void AllowanceManager::updateAllAllowance(int allowanceID, double amount)
// {
//     DatabaseConnection dbConn;
//     DateManager dateManager;
//     std::string currentDate = dateManager.getCurrentDate();
//     sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE EMPLOYEE_ALLOWANCE SET Amount = ?, EffectiveDate = ? WHERE AllowanceID = ?");
//     ps->setDouble(1,amount);
//     ps->setString(2,currentDate);
//     ps->setInt(3,allowanceID);
//     ps->executeUpdate();
//     ps->close();
//     delete ps;   
// }

// void AllowanceManager::removeAllowance()
// {
//     Menu menu;
//     char response;
//     menu.displayLogo();
//     removeAllowanceHeader();
//     std::cout << std::setw(81) << "Remove Allowance of: " << std::endl
//               << std::setw(53) << "*" << std::setfill('*') << std::setw(35) << "*" << std::setfill(' ') << std::endl << std::endl
//               << std::setw(77) << "1. All employees    " << std::endl
//               << std::setw(77) << "2. Specific employee" << std::endl;
//     int choice;
//     do
//     {
//         std::cout << std::endl << std::setw(70) << "Choice: ";
//         std::cin >> choice;
//         if(choice!=1&&choice!=2)
//             std::cout << std::endl << std::setw(84) << "Please enter a valid choice." << endl;
//     }while (choice!=1&&choice!=2);
//     switch (choice)
//     {
//         case 1:
//             removeAllAllowance();
//             break;
//         case 2:
//             removeEmpAllowance();
//             break;
//     default:
//         break;
//     }
// }

// void AllowanceManager::removeEmpAllowance(int employeeID,int allowanceID)
// {
//     DatabaseConnection dbConn;
//     sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM EMPLOYEE_ALLOWANCE WHERE EmployeeID = ? AND AllowanceID = ?");
//     ps->setInt(1,employeeID);
//     ps->setInt(2,allowanceID);
//     ps->executeUpdate();
//     ps->close();
//     delete ps;   
// }

// void AllowanceManager::removeEmpAllowance()
// {
//     Menu menu;
//     EmployeeManager em;
//     Employee* employee = NULL;
//     int employeeID;
//     char response;
//     menu.displayLogo();
//     removeAllowanceHeader();
//     do {
//         std::cout << "\n\n" << std::setw(72) << "Enter Employee ID              : ";
//         std::cin >> employeeID;
//         employee = em.searchEmployee(employeeID);
//         if (employee==NULL) 
//         {
//             std::cout << "\n" << std::setw(90) << "The employee is not found. Enter Y/y to retry: ";
//             std::cin >> response;
//             if (response != 'y' && response != 'Y') 
//             {
//                     menu.handleEmolumentMenu();
//             }
//         }
//     } while (response == 'y' || response == 'Y');
//     removeEmpAllowance(employee);
// }

// void AllowanceManager::removeEmpAllowance(Employee* employee)
// {
//     Menu menu;
//     char choice;
//     menu.displayLogo();
//     removeAllowanceHeader();
//     //show allowance and amount 
//     Employee_Allowance* head = NULL;
//     head = getEmployeeAllowances(employee->id);
//     if(head == NULL)
//     {
//         std::cout << "\n\n" << std::setw(94) << "There is no allowance allocated to this employee." << std::endl;
//         return;
//     }
//     std::cout << std::setw(48) << "Employee ID   : " << employee->id << std::endl;
//     std::cout << std::setw(48) << "Employee Name : " << employee->name << std::endl;
//     std::cout << std::right << std::setw(31) << "+" << std::setfill('-') << "-" << std::setw(83) << "+" << std::setfill(' ') << std::endl
//                     << std::setw(62) << "| Allowance ID | Allowance Name " << std::setw(37) << "|" << " Amount (RM) " << std::setw(3) << "|" << std::endl
//                     << std::setw(31) << "|" << std::setfill('-') << "-" << std::setw(83) << "|" << std::setfill(' ') << std::endl;
//     Employee_Allowance* empAllowance = head;
//     Allowance* allowance = NULL;
//     while(empAllowance!=NULL)
//     {
//         allowance = searchAllowance(empAllowance->allowanceID);
//         std::cout << std::left << std::setw(30) << " " << "| "  << std::setw(13) << allowance->allowanceID  << "| " << std::setw(51) << allowance->name << "| "  << std::setw(14) << empAllowance->amount << "| "  << std::endl;
//         empAllowance = empAllowance->next;
//     }
//     std::cout << std::setw(31) << std::right << "+" << std::setfill('-') << "-" << std::setw(83) << "+" << std::setfill(' ') << std::endl;
//     vector<int> deletedIDs;
//     int allowanceID;
//     do
//     {
//         do
//         {
//             std::cout << "\n\n" << std::setw(96) << std::right << "Please enter the Allowance ID that want to delete and -1 to terminate : ";
//             std::cin >> allowanceID;
//             allowance = searchAllowance(allowanceID);
//             if(allowanceID!=-1 && allowance == NULL)
//                 std::cout << "\n" << std::right << std::setw(90) << "Please enter the Allowance ID in the list." << std::endl;
//         } while (allowanceID!=-1 && allowance == NULL);
//         if(allowanceID!=-1)
//             deletedIDs.push_back(allowanceID);
//     } while (allowanceID!=-1);
//     if(deletedIDs.empty())
//     {
//         std::cout << "\n" << std::setw(102) << "[ Removal process has been cancelled. No changes have been made ]" << std::endl;
//     }
//     else
//     {
//         std::cout << "\n\n\n"<< std::setw(96) << "Are you sure to remove this/these allowance(s) from the employee? Enter 'Y' to remove : " ;
//         std::cin >> choice;
//         if(choice=='Y'||choice=='y')
//         {
//             for(const int& allowanceID: deletedIDs)
//                 removeEmpAllowance(employee->id,allowanceID); 
//             std::cout << "\n" << std::setw(88) << "[ Allowance is removed successfully ]" << std::endl;
//         }
//         else
//         {
//             std::cout << "\n" << std::setw(102) << "[ Removal process has been cancelled. No changes have been made ]" << std::endl;
//         }
//     }
//     std::cout << "\n" << std::setw(45) << "+" << std::setw(50) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl
//                 << std::setw(45) << "|" << std::setw(44) <<  "Press 'A' to remove another Allowance" << std::setw(6) << "|"<< std::endl
//                 << std::setw(45) << "|" << std::setw(43) <<  "Press 'P' to return to Previous menu" << std::setw(7) << "|"<< std::endl
//                 << std::setw(45) << "|" << std::setw(39) <<  "Press 'M' to return to Main Menu" << std::setw(11) << "|"<< std::endl
//                 << std::setw(45) << "+" << std::setw(50) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl << std::endl; 
//     bool valid; 
//     do
//     {
//         std::cout << std::setw(69) << "Choice: ";
//         std::cin >> choice;
//       if(choice=='A'||choice=='a'||choice=='P'|| choice=='p'|| choice=='M'|| choice=='m')
//         valid = true;    
//       else
//       {
//         valid = false;
//         std::cout << std::setw(90) << "Invalid choice. Please enter a valid choice.\n" << std::endl;
//       }
//     } while (!valid);
//     if(choice == 'a'||choice =='A')
//         removeEmpAllowance(employee);
//     else if(choice == 'P'||choice =='p')
//         menu.handleEmolumentMenu();
//     else if(choice=='M'||choice =='m')
//         menu.adminMainMenu(); 
// }

// void AllowanceManager::removeAllAllowance()
// {
//     Menu menu;
//     Allowance* allowance = NULL;
//     int allowanceID;
//     char response, choice;
//     menu.displayLogo();
//     removeAllowanceHeader();
//     viewAllowances();
//     do {
//         std::cout << "\n\n" << std::setw(72) << "Enter Allowance ID              : ";
//         std::cin >> allowanceID;
//         allowance = searchAllowance(allowanceID);
//         if (allowance==NULL) 
//         {
//             std::cout << "\n" << std::setw(90) << "The allowance is not found. Enter Y/y to retry: ";
//             std::cin >> response;
//             if (response != 'y' && response != 'Y') 
//             {
//                     menu.handleEmolumentMenu();
//             }
//         }
//     } while (response == 'y' || response == 'Y');
//     EmployeeManager em;
//     Employee_Allowance* empAllowance = NULL;
//     empAllowance = getAllowanceEmp(allowanceID);
//     DepartmentManager dm;
//     Department* department = NULL;
//     Position* position = NULL;
//     if(empAllowance!=NULL)
//     {    
//         menu.displayLogo();
//         updateAllowanceHeader();
//         std::cout << "\n\n" << std::setw(83) <<  "Removed Allowance Preview\n\n" 
//                     << std::setw(42) << " " << std::setw(56) << std::setfill('*') << "*"  << std::setfill(' ') 
//                     << "\n\n"<< std::setw(36) << "Allowance              : " << allowance->name << std::endl
//                     << "\n\n"<< std::setw(36) << "Affected Employee(s)   : " <<  std::endl;
//         std::cout << std::right << std::setw(10) << "+" << std::setfill('-') << "-" << std::setw(138) << "+" << std::setfill(' ') << std::endl
//                 << std::setw(24) << "| Employee Name" << std::setw(50) << "| Department"  << std::setw(40) << "| Position" << std::setw(35)  << "|" << std::endl
//                 << std::setw(10) << "|" << std::setfill('-') << "-" << std::setw(138) << "|" << std::setfill(' ') << std::endl; 
//         while(empAllowance!=NULL) 
//         {
//             Employee* employee = em.searchEmployee(empAllowance->employeeID);
//             //get department name and position name
//             department = dm.searchDepartment(employee->departmentID);
//             position = dm.searchPosition(employee->positionID);
//             std::cout << std::left << std::setw(9) << " " << "| " << std::setw(51) << employee->name << "| "  << std::setw(40) << department->departmentName << "| "  << std::setw(42) << position->positionName << "| " << std::endl;
//             //proceed to next element
//             empAllowance = empAllowance->next;
//         }
//         std::cout << std::right << std::setw(10) << "+" << std::setfill('-') <<"-" << std::setw(138) << "+" << std::setfill(' ') << std::endl;
//         std::cout << "\n\n\n"<< std::setw(96) << "Are you sure to remove this allowance from all employees? Enter 'Y' to remove : " ;
//         std::cin >> choice;
//         if(choice=='Y'||choice=='y')
//         {
//             removeAllAllowance(allowanceID); 
//             std::cout << "\n" << std::setw(88) << "[ Allowance is removed successfully ]" << std::endl;
//         }
//         else
//         {
//             std::cout << "\n" << std::setw(102) << "[ Removal process has been cancelled. No changes have been made ]" << std::endl;
//         }
//     }
//     else
//     {
//         std::cout << "\n\n" << std::setw(97) << "[ The allowance is not yet allocated to any employee ]" << std::endl;
//     }
//     std::cout << "\n" << std::setw(45) << "+" << std::setw(50) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl
//                 << std::setw(45) << "|" << std::setw(44) <<  "Press 'A' to remove another Allowance" << std::setw(6) << "|"<< std::endl
//                 << std::setw(45) << "|" << std::setw(43) <<  "Press 'P' to return to Previous menu" << std::setw(7) << "|"<< std::endl
//                 << std::setw(45) << "|" << std::setw(39) <<  "Press 'M' to return to Main Menu" << std::setw(11) << "|"<< std::endl
//                 << std::setw(45) << "+" << std::setw(50) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl << std::endl; 
//     bool valid; 
//     do
//     {
//         std::cout << std::setw(69) << "Choice : ";
//         std::cin >> choice;
//       if(choice=='A'||choice=='a'||choice=='P'|| choice=='p'|| choice=='M'|| choice=='m')
//         valid = true;    
//       else
//       {
//         valid = false;
//         std::cout << std::setw(90) << "Invalid choice. Please enter a valid choice.\n" << std::endl;
//       }
//     } while (!valid);
//     if(choice == 'a'||choice =='A')
//         removeAllAllowance();
//     else if(choice == 'P'||choice =='p')
//         menu.handleEmolumentMenu();
//     else if(choice=='M'||choice =='m')
//         menu.adminMainMenu(); 
// }

// void AllowanceManager::removeAllAllowance(int allowanceID)
// {
//     DatabaseConnection dbConn;
//     sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM EMPLOYEE_ALLOWANCE WHERE AllowanceID = ?");
//     ps->setInt(1,allowanceID);
//     ps->executeUpdate();
//     ps->close();
//     delete ps;   
// }

void AllowanceManager::allocateAllowanceToNewEmp(Employee* employee)
{
    Menu menu;
    char choice;
    struct AllowanceAmount
    {
        int allowanceID;
        double amount ;
    };
        //store allowance allocated to employee
        vector<AllowanceAmount> allowanceAmounts;

        AllowanceAmount allowanceAmount;
        Allowance* allowance = NULL;
        do
        {
            menu.displayLogo();
            allocateAllowanceHeader();
            choice = 'Z'; //reser the value of choice
            viewAllowances();  //display Allowance Type
            do
            {
                std::cout << "\n\n" << std::setw(72) << "Enter Allowance ID     : ";
                std::cin >> allowanceAmount.allowanceID;
                allowance = searchAllowance(allowanceAmount.allowanceID);
                if(allowance==NULL)
                {
                    std::cout << "\n\n" << std::setw(90) << "Invalid allowance ID. Please try again." << std::endl;
                }
            } while (allowance==NULL);

            std::cout << "\n\n" << std::setw(72) << "Enter Amount (RM)      : ";
            std::cin >> allowanceAmount.amount;
            allowanceAmounts.push_back(allowanceAmount);
            std::cout << "\n\n" << std::setw(72) << "Enter 'Y' to allocate another allowance : ";
            std::cin >> choice;
        } while (choice=='Y'||choice=='y');

    menu.displayLogo();
    allocateAllowanceHeader();
    //display assign allowance
    std::cout << std::setw(48) << "Employee ID   : " << employee->id << std::endl;
    std::cout << std::setw(48) << "Employee Name : " << employee->name << std::endl;
    std::cout << std::right << std::setw(31) << "+" << std::setfill('-') << "-" << std::setw(83) << "+" << std::setfill(' ') << std::endl
                    << std::setw(62) << "| Allowance ID | Allowance Name " << std::setw(37) << "|" << " Amount (RM) " << std::setw(3) << "|" << std::endl
                    << std::setw(31) << "|" << std::setfill('-') << "-" << std::setw(83) << "|" << std::setfill(' ') << std::endl;
    for(const AllowanceAmount& allowanceAmount : allowanceAmounts )
    {
        allowance = searchAllowance(allowanceAmount.allowanceID);
        std::cout << std::left << std::setw(30) << " " << "| "  << std::setw(13) << allowanceAmount.allowanceID  << "| " << std::setw(51) << allowance->name << "| "  << std::setw(14) << allowanceAmount.amount << "| "  << std::endl;
    }
    std::cout << std::setw(31) << std::right << "+" << std::setfill('-') << "-" << std::setw(83) << "+" << std::setfill(' ') << std::endl;

    //ask confirmation
    DateManager dateManager;
    std::cout << "\n\n" << std::setw(90) << "Are you sure to allocate this/these allowance(s) to this employee? Enter 'Y' to add: ";
    std::cin >> choice;
    if(choice == 'Y'|| choice=='y')
    {
        //insert data
        std::string date = dateManager.getCurrentDate();
        for(const AllowanceAmount& allowanceAmount : allowanceAmounts )
            allocateAllowance(employee->id,allowanceAmount.allowanceID,allowanceAmount.amount,date);
        std::cout << "\n" <<std::setw(90) << "[ Allowance is allocated successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" <<std::setw(103) << "[ Allocation process has been cancelled. No changes have been made ]" << std::endl;
    }   
}

void AllowanceManager::allocateNewAllowance()
{
    std::cout << std::fixed << std::setprecision(2); 
    int employeeID;
    char response;
    double amount = 0;
    Menu menu;
    EmployeeManager em;
    DateManager dateManager;
    menu.displayLogo();
    allocateAllowanceHeader();

    viewAllowances();
    int allowanceID;
    Allowance* allowance = NULL;
    do
    {
        
        std::cout << "\n\n" << std::setw(72) << "Enter Allowance ID          : ";
        std::cin >> allowanceID;
        allowance = searchAllowance(allowanceID);
        if(allowance==NULL)
            std::cout << "\n\n" << std::setw(93) << "Invalid allowance ID. Please try again." << std::endl;
    } while (allowance==NULL);

    Employee* head = getAllowanceEmployees(allowanceID);
    Employee* employee = head;

    menu.displayLogo();
    allocateAllowanceHeader();

    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Allowance Amount (RM) : ";
        std::cin >> amount;
        if(amount<0||amount>999999.99)
            std::cout  << "\n\n" << std::setw(87) << "Invalid amount. Please try again." << std::endl;
    } while (amount<0||amount>999999.99);

    std::string date = dateManager.getCurrentDate();

    menu.displayLogo();
    allocateAllowanceHeader();
    //display 


    DepartmentManager dm;
    Department* department = NULL;
    Position* position = NULL;
    std::cout << std::right << std::setw(19) << "Choice : " << std::left << allowance->name << std::endl;
    std::cout << std::right << std::setw(22) << "Amount : RM " << std::left << amount << std::endl;
    std::cout << std::right << std::setw(10) << "+" << std::setfill('-') << "-" << std::setw(138) << "+" << std::setfill(' ') << std::endl
              << std::setw(24) << "| Employee Name" << std::setw(50) << "| Department"  << std::setw(40) << "| Position" << std::setw(35)  << "|" << std::endl
              << std::setw(10) << "|" << std::setfill('-') << "-" << std::setw(138) << "|" << std::setfill(' ') << std::endl;   

    while(employee!=NULL) 
    {
        //get department name and position name
        department = dm.searchDepartment(employee->departmentID);
        position = dm.searchPosition(employee->positionID);

        std::cout << std::left << std::setw(9) << " " << "| " << std::setw(51) << employee->name << "| "  << std::setw(40) << department->departmentName << "| "  << std::setw(42) << position->positionName << "| " << std::endl;
        //proceed to next element
        employee = employee->next;
    }

    char confirm;
    std::cout << std::right << "\n\n" <<std::setw(104) << "Are you sure to allocate allowance to this employee? Enter Y/y to confirm: ";
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        while(employee!=NULL)
        {
            allocateAllowance(employee->id,allowanceID,amount,date);
            employee = employee->next;
        }
        std::cout << std::right << "\n" <<std::setw(90) << "[ Allowance is allocated successfully ]" << std::endl;
    }
    else
    {
        std::cout << std::right << "\n" <<std::setw(105) << "[ Allocation process has been cancelled. No changes have been made ]" << std::endl;
    }   
}

void AllowanceManager::allocateAllowance()
{
    Menu menu;
    menu.displayLogo();
    allocateAllowanceHeader();
    viewAllowances();
    int allowanceID;
    Allowance* allowance = NULL;
    do
    {
        
        std::cout << "\n\n" << std::setw(72) << "Enter Allowance ID          : ";
        std::cin >> allowanceID;
        allowance = searchAllowance(allowanceID);
        if(allowance==NULL)
            std::cout << "\n\n" << std::setw(93) << "Invalid allowance ID. Please try again." << std::endl;
    } while (allowance==NULL);


    struct Employee_Allowance
    {
        int employeeID;
        std::string employeeName,departmentName,PositionName;
        double amount;
    };
    
    char delimiter;
    int year, month, day;
    DateManager dateManager;
    std::string currentDate = dateManager.getCurrentDate();
    // std::istringstream dateStream(currentDate);
    // dateStream >> year >> delimiter >> month >> delimiter >> day && delimiter == '-';

    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT b.EmployeeID, e.Name, b.Amount, d.DepartmentName, p.PositionName FROM ( SELECT ed.EmployeeID, ed.Amount, ed.`Date` FROM EMPLOYEE_ALLOWANCE ed JOIN ( SELECT EmployeeID, MAX(`Date`) AS LatestDate FROM EMPLOYEE_ALLOWANCE WHERE AllowanceID = ? GROUP BY EmployeeID) a ON ed.EmployeeID = a.EmployeeID AND ed.`Date` = a.LatestDate WHERE ed.AllowanceID = ?) b JOIN EMPLOYEE e ON b.EmployeeID = e.EmployeeID JOIN DEPARTMENT d ON e.DepartmentID = d.DepartmentID JOIN POSITION p ON e.PositionID = p.PositionID ORDER BY b.EmployeeID");
    ps->setInt(1,allowanceID);
    ps->setInt(2,allowanceID);
    sql::ResultSet* rs = ps->executeQuery();

    vector<Employee_Allowance> empAllowances;

    menu.displayLogo();
    allocateAllowanceHeader();
    bool exist;
    if(rs->next())
    {
        Employee_Allowance empAllowance;
        exist = checkExistEmpAllowance(rs->getInt("EmployeeID"),allowanceID,currentDate);
        if(!exist)
        {
            std::cout << std::setw(10) << "Choice: " << allowance->name << " Allowance" << std::endl;
            std::cout << " +" << std::setfill('-') <<"-" << std::setw(152) << "+" << std::setfill(' ') << std::endl
                        << " | Employee ID | Employee Name" << std::setw(50) << "| Department"  << std::setw(35) <<"| Position"   << std::setw(40) <<"| Allowance Amount (RM)|" << std::endl
                        << " |" << std::setfill('-') << "-" << std::setw(152) << "|" << std::setfill(' ') << std::endl;  

            //display
            std::cout << std::left << " | " << std::setw(12) << rs->getInt("EmployeeID") << "| " << std::setw(51) << rs->getString("Name") << "| "  << std::setw(35) << rs->getString("DepartmentName") << "| "  << std::setw(24) << rs->getString("PositionName") << "| "  << std::right << std::setw(20) << rs->getString("Amount") << " " << "|" << std::endl;
            //insert into vector
            empAllowance.employeeID = rs->getInt("EmployeeID");
            empAllowance.employeeName = rs->getString("Name");
            empAllowance.departmentName = rs->getString("DepartmentName");
            empAllowance.PositionName = rs->getString("PositionName");
            empAllowance.amount = rs->getInt("Amount");
            empAllowances.push_back(empAllowance);
        }
        else
        {
            char response;
            std::cout << "\n" << std::setw(99) << "No allowance allocation is needed. Or Enter 'Y' to add new allocation record : " ;
            std::cin >> response;
            if(response=='Y'||response=='y')
            {
                allocateNewAllowance();
            }
            else
                menu.handleEmolumentMenu();
        }
        while(rs->next())
        {
            Employee_Allowance empAllowance;
            exist = checkExistEmpAllowance(rs->getInt("EmployeeID"),allowanceID,currentDate);
            if(!exist)
            {
                //display
                std::cout << std::left << " | " << std::setw(12) << rs->getInt("EmployeeID") << "| " << std::setw(51) << rs->getString("Name") << "| "  << std::setw(35) << rs->getString("DepartmentName") << "| "  << std::setw(24) << rs->getString("PositionName") << "| "  << std::right << std::setw(20) << rs->getString("Amount") << " " << "|" << std::endl;
 
                //insert into vector
                empAllowance.employeeID = rs->getInt("EmployeeID");
                empAllowance.employeeName = rs->getString("Name");
                empAllowance.departmentName = rs->getString("DepartmentName");
                empAllowance.PositionName = rs->getString("PositionName");
                empAllowance.amount = rs->getDouble("Amount");
                empAllowances.push_back(empAllowance);
            }
        }
        //end display 
        std::cout << std::right << " +" << std::setfill('-') << "-" << std::setw(152) << "+" << std::setfill(' ') << std::endl;

        char choice = 'o'; // initialize char
        while(choice!='Z'&&choice!='z'&&choice!='Y'&&choice!='y' && !empAllowances.empty())
        {
            std::cout << "\n\n" << std::right << std::setw(43) << "+" << std::setw(59) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl
                << std::right << std::setw(43) << "|" << std::left << std::setw(1) << " " << std::setw(57) <<  "Enter 'Y' to allocate allowance to all of these employees" << std::setw(7) << "|"<< std::endl
                << std::right << std::setw(43) << "|" << std::left << std::setw(1) << " " << std::setw(57) <<  "Enter 'A' to add new allowance allocation " << std::setw(7) << "|"<< std::endl
                << std::right << std::setw(43) << "|" << std::left << std::setw(1) << " " << std::setw(57) <<  "Enter 'U' to update allowance amount of employee" << std::setw(15) << "|"<< std::endl
                << std::right << std::setw(43) << "|" << std::left << std::setw(1) << " " << std::setw(57) <<  "Enter 'R' to remove employee from the list" << std::setw(20) << "|"<< std::endl
                << std::right << std::setw(43) << "|" << std::left << std::setw(1) << " " << std::setw(57) <<  "Enter 'Z' to exit" << std::setw(30) << "|"<< std::endl
                << std::right << std::setw(43) << "+" << std::setw(59) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl ;  

            do
            {
                std::cout << "\n" << std::setw(72) << "Choice : " ;
                std::cin >> choice;
                if(choice!='Y'&&choice!='y'&&choice!='U'&&choice!='u'&&choice!='R'&&choice!='r'&&choice!='Z'&&choice!='z'&&choice!='a'&&choice!='A')
                    std::cout << "\n" << std::setw(76) << "Please enter a valid choice." << std::endl;
            } while (choice!='Y'&&choice!='y'&&choice!='U'&&choice!='u'&&choice!='R'&&choice!='r'&&choice!='Z'&&choice!='z'&&choice!='a'&&choice!='A');

            if(choice == 'Z'|| choice =='z')
                menu.handleEmolumentMenu();

            else if(choice == 'Y'|| choice =='y')
            {
                for(const Employee_Allowance& empAllowance : empAllowances)
                    allocateAllowance(empAllowance.employeeID, allowanceID ,empAllowance.amount,currentDate);
                
                std::cout << "\n" <<std::setw(90) << "[ Allowance is allocated successfully ]" << std::endl;
            }
            else
            {
                if(choice == 'A'|| choice =='a')
                {
                    int employeeID;
                    double amount = 0;
                    std::vector<Employee_Allowance>::iterator it;
                    EmployeeManager em;
                    DepartmentManager dm;
                    Employee* employee = NULL;
                    Department* department = NULL;
                    Position* position = NULL;
                    menu.displayLogo();
                    allocateAllowanceHeader();
                    do
                    {
                        
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee ID           : ";
                        std::cin >> employeeID;
                        employee = em.searchEmployee(employeeID);
                        if(employee!=NULL)
                        {
                            it = std::find_if(empAllowances.begin(), empAllowances.end(), [employeeID](const Employee_Allowance& empAllowance) {
                                return empAllowance.employeeID == employeeID;
                            });
                            if(it != empAllowances.end())
                                std::cout << "\n" << std::setw(90) << "The employee is already in the list. " << std::endl;
                        }
                        else
                        {
                            std::cout << std::endl << std::setw(88) << "Please enter a valid employee ID." << std::endl;
                        }
                    } while (employee==NULL || it != empAllowances.end());
                                        
                    department = dm.searchDepartment(employee->departmentID);
                    position = dm.searchPosition(employee->positionID);
                    do
                    {
                        std::cout << "\n\n" << std::setw(72) << "Enter Allowance Amount (RM) : ";
                        std::cin >> amount;
                        if(amount<0||amount>999999.99)
                            std::cout  << "\n\n" << std::setw(88) << "Invalid amount. Please try again." << std::endl;
                    } while (amount<0||amount>999999.99);

                    empAllowance.employeeID = employee->id;
                    empAllowance.employeeName = employee->name;
                    empAllowance.departmentName = department->departmentName;
                    empAllowance.PositionName = position->positionName;
                    empAllowance.amount = amount;
                    empAllowances.push_back(empAllowance);
                }            
                else
                {
                    int employeeID;
                    std::vector<Employee_Allowance>::iterator it;

                    do
                    {
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee ID        : ";
                        std::cin >> employeeID;
                        it = std::find_if(empAllowances.begin(), empAllowances.end(), [employeeID](const Employee_Allowance& empAllowance) {
                            return empAllowance.employeeID == employeeID;
                        });

                        if(it == empAllowances.end())
                            std::cout << "\n" << std::setw(88) << "Please enter a valid employee ID in the list. " << std::endl;
                    } while (it == empAllowances.end());
                
                    if(choice == 'U'|| choice =='u')
                    {
                        double newAmount = 0;
                        do
                        {
                            std::cout << "\n\n" << std::setw(72) << "Enter Updated Amount (RM): ";
                            std::cin >> newAmount;
                        } while (newAmount < 0 || newAmount>999999.99);
                        
                            // Update the amount
                            it->amount = newAmount;
                    }
                    else if(choice == 'R'|| choice =='r')
                    {
                            empAllowances.erase(it); // Remove the element
                    }

                }
                menu.displayLogo();
                allocateAllowanceHeader();

                if(empAllowances.empty())
                {
                    char response;
                    std::cout << "\n" << std::setw(99) << "No allowance allocation is needed. Or Enter 'Y' to add new allocation record : " ;
                    std::cin >> response;
                    if(response=='Y'||response=='y')
                        allocateNewAllowance();
                    else
                        menu.handleEmolumentMenu();
                }

                //display updated list
                std::cout << std::setw(10) << "Choice: " << allowance->name << " Allowance" << std::endl;
                std::cout << " +" << std::setfill('-') <<"-" << std::setw(152) << "+" << std::setfill(' ') << std::endl
                            << " | Employee ID | Employee Name" << std::setw(50) << "| Department"  << std::setw(35) <<"| Position"   << std::setw(40) <<"| Allowance Amount (RM)|" << std::endl
                            << " |" << std::setfill('-') << "-" << std::setw(152) << "|" << std::setfill(' ') << std::endl;  
                for(const Employee_Allowance& empAllowance : empAllowances)
                        std::cout << std::left << " | " << std::setw(12) << empAllowance.employeeID << "| " << std::setw(51) << empAllowance.employeeName << "| "  << std::setw(35) << empAllowance.departmentName << "| "  << std::setw(24) << empAllowance.PositionName << "| "  << std::right << std::setw(20) << empAllowance.amount << " " << "|" << std::endl;
                        
                std::cout << std::right << " +" << std::setfill('-') << "-" << std::setw(152) << "+" << std::setfill(' ') << std::endl;
            }
        }
    }
    else
    {
        menu.displayLogo();
        allocateAllowanceHeader();

        char confirm;
        std::cout << "\n" << std::setw(99) << "No allowance allocation is needed. Or Enter 'Y' to add new allocation record : " ;
        std::cin >> confirm;
        if(confirm=='Y'||confirm=='y')
        {
            allocateNewAllowance();
        }
        else
        {
            menu.handleEmolumentMenu();
        }
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    
}

