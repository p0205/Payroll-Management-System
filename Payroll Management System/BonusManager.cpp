#include "BonusManager.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>

void addBonusHeader()
{
    std::cout <<std::setw(55) << "+" <<setfill('-') << "-" <<std::setw(29) << "+" <<std::setfill(' ') <<std::endl
        <<std::setw(55) << "|" <<std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl                           
        <<std::setw(55) << "|" <<std::setw(19) << "Add Bonus" <<std::setw(11) << "|" <<std::endl
        <<std::setw(55) << "|" <<std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl
        <<std::setw(55) << "+" <<setfill('-') << "-" <<std::setw(29) << "+" <<std::setfill(' ') <<std::endl<<std::endl; 
}

void setBonusHeader()
{
    std::cout <<std::setw(55) << "+" <<setfill('-') << "-" <<std::setw(29) << "+" <<std::setfill(' ') <<std::endl
        <<std::setw(55) << "|" <<std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl                         
        <<std::setw(55) << "|" <<std::setw(19) << "Set Bonus" <<std::setw(11) << "|" <<std::endl
        <<std::setw(55) << "|" <<std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl
        <<std::setw(55) << "+" <<std::setfill('-') << "-" <<std::setw(29) << "+" <<std::setfill(' ') <<std::endl<<std::endl;
}

bool BonusManager::checkRepeatString(string input,string table,string column)
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

bool BonusManager::checkRepeatInt(int input,string table,string column)
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

bool BonusManager::isAnnualBonus(int bonusID)
{
    DatabaseConnection dbConn;
    bool annual;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT Frequency FROM BONUS WHERE BonusID = ?");
    ps->setInt(1,bonusID);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        if(rs->getString("Frequency") == "Annual")
            annual = true;
        else
            annual = false;
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return annual;
}

Bonus* BonusManager::searchBonus(int bonusID)
{
    DatabaseConnection dbConn;
    Bonus* bonus = new Bonus();
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM BONUS WHERE BonusID = ?");
    ps->setInt(1,bonusID);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {   
        bonus->bonusID = rs->getInt("BonusID");      
        bonus->name = rs->getString("Name");      
        bonus->frequency = rs->getString("Frequency");      
    }
    else
    {
        delete bonus;
        return nullptr;
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return bonus;
}

Bonus* BonusManager::searchBonuses()
{
    DatabaseConnection dbConn;
    Bonus* bonus = NULL;
    Bonus* head = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM BONUS");
    sql::ResultSet* rs = ps->executeQuery();
    while(rs->next())
    {   
        
        if(head == NULL)
        {
            bonus = new Bonus();
            head = bonus;
        }
        else
        {
            bonus->next = new Bonus();
            bonus = bonus->next; 
        }
        bonus->bonusID = rs->getInt("BonusID");      
        bonus->name = rs->getString("Name");      
        bonus->frequency = rs->getString("Frequency");      
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

Employee_Bonus* BonusManager::getEmployeeBonuses(int employeeID,int year, int month)
{
    Employee_Bonus* head = NULL;
    Employee_Bonus* empBonus = NULL;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT BonusID,Amount FROM EMPLOYEE_BONUS WHERE EmployeeID = ? AND YEAR(Date) = ? AND MONTH(Date) = ?");

    ps->setInt(1,employeeID);
    ps->setInt(2,year);
    ps->setInt(3,month);
    sql::ResultSet* rs = ps->executeQuery();

    while(rs->next())
    {
        if(head == NULL)
        {
            empBonus = new Employee_Bonus();
            head = empBonus;
        }
        else
        {
            empBonus->next = new Employee_Bonus();
            empBonus = empBonus->next;
        }
        empBonus->bonusID = rs->getInt("BonusID");
        empBonus->amount = rs->getDouble("Amount");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

void BonusManager::viewBonuses()
{
    Bonus* bonus = NULL;
    bonus = searchBonuses();
    if(bonus!=NULL)
    {
        std::cout << std::setw(24) << "+" << std::setfill('-') <<"-" << std::setw(107) << "+" << std::setfill(' ') << std::endl
                  << std::setw(28)  << "| ID " << std::setw(13) << "| Name" << std::setw(65) <<"| Frequency"  << std::setw(26) << "|" << std::endl
                  << std::setw(24) << "|" << std::setfill('-') <<"-" << std::setw(107) << "|" << std::setfill(' ') << std::endl;
        while(bonus!=NULL)
        {
            std::cout << std::left
                      << std::setw(23) << " " << "| "<< std::setw(9) << bonus->bonusID << " | " << std::setw(57) << bonus->name << " | "  << std::setw(34) << bonus->frequency  << "|" << std::endl;
            bonus = bonus->next;
        }
        std::cout << std::right
                  << std::setw(24) << "+" << std::setfill('-') <<"-" << std::setw(107) << "+" << std::setfill(' ') << std::endl;
    }
    else
    {
        std::cout << std::setw(82) << "No bonus available." << std::endl;
    }
    delete bonus;
}

void BonusManager::addBonus(std::string name, std::string frequency)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO BONUS(Name,Frequency) VALUES (?,?)");
    ps->setString(1,name);
    ps->setString(2,frequency);
    ps->executeUpdate();
    ps->close();
    delete ps;
}

void BonusManager::addBonus()
{
    Menu menu;
    std::string name, frequency;
    bool repeat;
    menu.displayLogo();
    addBonusHeader();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    do
    {
        std::cout << "\n\n" << std::setw(72)<< "Enter Bonus Name      : ";
        getline(std::cin,name);
        repeat = checkRepeatString(name,"BONUS","Name");
        if(repeat)
             std::cout << std::endl << std::setw(95)<< "The name already exists. Please use another name." << std::endl;
    } while (repeat);

    std::cout << "\n\n" << std::setw(72) << "Enter Frequency       : ";
    std::cin >> frequency;
    menu.displayLogo();
    addBonusHeader();
    std::cout << "\n\n" <<std::setw(81) <<  "NEW Bonus Preview\n\n" 
                <<std::setw(42) << " " <<std::setw(56) <<std::setfill('*') << "*"  <<std::setfill(' ') 
                << "\n\n"<<std::setw(72) << "Name           : " << name << std::endl
                << "\n\n"<<std::setw(72) << "Frequency      : " << frequency << std::endl;

    char confirm;
    std::cout << "\n\n" <<std::setw(97) << "Are you sure to add this bonus? Enter Y/y to confirm: ";
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        addBonus(name,frequency);
        std::cout << "\n" <<std::setw(87) << "[ New bonus is added successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" <<std::setw(103) << "[ Addition process has been cancelled. No changes have been made ]" << std::endl;
    }
}

void BonusManager::setBonus(int employeeID,int bonusID,double amount,std::string date)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO EMPLOYEE_BONUS(EmployeeID,BonusID,Amount,Date) VALUES (?,?,?,?)");
    ps->setInt(1,employeeID);
    ps->setInt(2,bonusID);
    ps->setDouble(3,amount);
    ps->setString(4,date);
    ps->executeUpdate();
    ps->close();
    delete ps;   
}

bool BonusManager::checkRepeatEmpBonus(int employeeID,int bonusID, int targetYear)
{
    bool repeat = false;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE_BONUS WHERE EmployeeID = ? AND BonusID = ? AND Year(Date)= ?");
    ps->setInt(1,employeeID);
    ps->setInt(2,bonusID);
    ps->setInt(3,targetYear);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
        repeat = true;
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return repeat;
}

Employee* BonusManager::searchEmployees(int bonusID, int targetYear)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE");
    sql::ResultSet* rs = ps->executeQuery();
    EmployeeManager em;
    Employee* employee = NULL;
    Employee* head = NULL;
    while(rs->next())
    {
        if(!checkRepeatEmpBonus(rs->getInt("EmployeeID"),bonusID,targetYear))
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

Employee* BonusManager::searchEmployeesByDepartment(int departmentID,int bonusID,int targetYear)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE WHERE DepartmentID = ?");
    ps->setInt(1,departmentID);
    sql::ResultSet* rs = ps->executeQuery();
    Employee* employee = NULL;
    Employee* head = NULL;
    DateManager dateManager;
    EmployeeManager em;
    while(rs->next())
    {
        if( !checkRepeatEmpBonus(rs->getInt("EmployeeID"),bonusID,targetYear))
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

bool BonusManager::isEmployeeInList(Employee* head, int targetID) 
{
    while (head != nullptr) {
        if (head->id == targetID) {
            return true; // Employee ID already exists in the list
        }
        head = head->next;
    }
    return false; // Employee ID not found in the list
}

bool BonusManager::isEmployeeInList(Employee* head, const std::string& targetName) 
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

Employee* BonusManager::getBonusEmployees(Bonus* bonus, int targetYear)
{
    Menu menu;
    DateManager dateManager;
    menu.displayLogo();
    setBonusHeader();
    std::cout << std::setw(60) << "Bonus : " << bonus->name << std::endl
              << std::setw(60) << "Year  : " << targetYear << std::endl
              << "\n" << std::setw(79) << "Set Bonus To " << std::endl
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
    char response,again;
    int departmentID,employeeID;
    string name;

    switch (choice)
    {
    case 1:
        //get all employee
        employee = searchEmployees(bonus->bonusID,targetYear);
        break;

    case 2:
        head = dm.searchDepartments();
        do
        {
            department = head;
            if(department!=NULL)
            {
                menu.displayLogo();
                setBonusHeader();
                std::cout << std::setw(92) << "Please choose a department from the list. " << std::endl
                //display all department available
                            << std::setw(38) << "+" << std::setfill('-') << "-" << std::setw(64) << "+" << std::setfill(' ') << std::endl
                            << std::setw(52) << "| Department ID" << setw(19) << "| Department Name"  << std::setw(32) << "|" << std::endl
                            << std::setw(38) << "|" << std::setfill('-') << "-" << std::setw(64) << "|" << std::setfill(' ') << std::endl;
                while(department!=NULL)
                {
                    std::cout << std::left << std::setw(37) << " " << "| " << std::setw(15) << department->departmentID << "| "  << std::setw(45) <<department->departmentName << " " << "|" << std::endl;
                    department = department->next;
                }
                std::cout << std::right;
                std::cout << std::setw(38) << "+" << std::setfill('-') <<"-" << std::setw(64) << "+" << std::setfill(' ') << std::endl;
         
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
        employee = searchEmployeesByDepartment(departmentID,bonus->bonusID,targetYear);
        break;

    case 3:
        menu.displayLogo();
        setBonusHeader();
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
                    setBonusHeader();
                    response = 'Z';

                    do {
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee ID              : ";
                        std::cin >> employeeID;
                        // Check if the user input already exists in the list
                        repeat = isEmployeeInList(employeeHead, employeeID);
                        if (repeat) {
                            std::cout << "\n" << std::right << std::setw(90) << "The employee already exists in the list. " << std::endl;
                        }
                    } while (repeat);

                    if(employeeHead == NULL) 
                    {
                        employee = em.searchEmployee(employeeID);
                        if(employee==NULL)
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
                    }
                    else
                    {
                        employee->next = em.searchEmployee(employeeID);
                        if(employee->next!=NULL)
                            employee = employee->next;
                        else
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
                    }
                }while(response == 'y' || response == 'Y');
            } 

            else if (choice == 2) 
            {
                menu.displayLogo();
                setBonusHeader();
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
                        employee = em.searchEmployee(employeeID);
                        if(employee==NULL)
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
                    }
                    else
                    {
                        employee->next = em.searchEmployee(employeeID);
                        if(employee->next!=NULL)
                            employee = employee->next;
                        else
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
                    }
                }while(response == 'y' || response == 'Y');
            }

            if (checkRepeatEmpBonus(employee->id, bonus->bonusID, targetYear))
            {
                employee = nullptr;
                std::cout << "\n" << std::setw(102) << "The bonus is already set to this employee for the chosen period." << std::endl;
            }

            if(employeeHead == NULL) 
                employeeHead = employee;

            std::cout << "\n" << std::right << std::setw(91) << "Enter Y to add another employee to the list : "; 
            std::cin >> again;
        } while (again == 'Y' || again == 'y');
        employee = employeeHead;
        break;

    default:
        break;
    }
    return employee;
}

void BonusManager::setBonus()
{
    Menu menu;
    int employeeID, bonusID;
    double amount;
    std::string date;
    bool repeat, validDate;
    menu.displayLogo();
    setBonusHeader();
    viewBonuses();
    Bonus* bonus = NULL;
    DateManager dateManager;
    int targetYear;

    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Bonus ID              : ";
        std::cin >> bonusID;
        bonus = searchBonus(bonusID);
        if(bonus==NULL)
            std::cout  << "\n\n" << std::setw(90) << "Invalid bonus ID. Please try again." << std::endl;
    } while (bonus==NULL);

    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Year                  : ";
        std::cin >> targetYear;
        if(targetYear<1900)
            std::cout << "\n"<< std::setw(90) << "Invalid year. Please enter a valid year." << std::endl;
    } while (targetYear<1900);

    Employee* head = NULL;
    menu.displayLogo();
    setBonusHeader();
    head = getBonusEmployees(bonus,targetYear);
    if(head==NULL)
    {
        menu.displayLogo();
        setBonusHeader();
        std::cout<< std::setw(81) << "No result is found. " << std::endl;
        return;
    }
    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Bonus Amount (RM)     : ";
        std::cin >> amount;
        if(amount<0)
            std::cout  << "\n\n" << std::setw(87) << "Invalid amount. Please try again." << std::endl;
    } while (amount<0);

    menu.displayLogo();
    setBonusHeader();
    Employee* employee = head;
    DepartmentManager dm;
    Department* department = NULL;
    Position* position = NULL;
    
    std::cout << std::right << std::setw(19) << "Choice : " << std::left << bonus->name << std::endl;
    std::cout << std::right << std::setw(22) << "Amount : RM " << std::left << amount << std::endl;
    std::cout << std::right << std::setw(19) << "Year   : " << std::left << targetYear << std::endl;
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
    std::cout << std::right << std::setw(10) << "+" << std::setfill('-') <<"-" << std::setw(138) << "+" << std::setfill(' ') << std::endl;
    char confirm;
    std::cout << "\n\n" <<std::setw(104) << "Are you sure to set bonus to this/these employee(s)? Enter Y/y to confirm: ";
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        employee = head;
        std::string date = dateManager.getCurrentDate();
        
        while(employee!=NULL)
        {
            setBonus(employee->id,bonus->bonusID,amount,date);
            employee = employee->next;
        }
        std::cout << "\n" <<std::setw(83) << "[ Bonus is set successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" <<std::setw(103) << "[ Set Bonus process has been cancelled. No changes have been made ]" << std::endl;
    }   
}