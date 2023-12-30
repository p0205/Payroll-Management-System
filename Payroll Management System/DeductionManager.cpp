#include "DeductionManager.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cmath>
#include <vector>
#include <iterator> 
#include <algorithm> 



void addDeductionHeader()
{
   std::cout <<std::setw(55) << "+" <<std::setfill('-') << "-" <<std::setw(29) << "+" << std::setfill(' ') <<std::endl
     <<std::setw(55) << "|" << std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl                          
     <<std::setw(55) << "|" <<std::setw(21) << "Add Deduction" <<std::setw(9) << "|" <<std::endl
     <<std::setw(55) << "|" << std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl
     <<std::setw(55) << "+" <<std::setfill('-') << "-" <<std::setw(29) << "+" << std::setfill(' ') <<std::endl <<std::endl; 
}

void DeductionManager::assignDeductionHeader()
{
   std::cout << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << std::setfill(' ') << std::endl
     << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl                           
     << std::setw(55) << "|" << std::setw(23) << "Assign Deduction" <<std::setw(7) << "|" << std::endl
     << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl
     << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << std::setfill(' ') << std::endl << std::endl; 
}

bool DeductionManager::checkRepeatString(string input,string table,string column)
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

bool DeductionManager::checkRepeatInt(int input,string table,string column)
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

bool DeductionManager::checkValidChar(char response)
{
    bool valid = true;
    if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
        valid = false;
    return valid;
}

bool DeductionManager::checkValidDouble(double input, double max)
{
    bool valid = true;
    if(input<0 || input > max)
        valid = false;
    return valid;
}

Deduction* DeductionManager::searchDeduction(int deductionID)
{
    DatabaseConnection dbConn;
    Deduction* deduction = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM DEDUCTION WHERE DeductionID = ?");
    ps->setInt(1,deductionID);
    sql::ResultSet* rs = ps->executeQuery();

    if(rs->next())
    {
        deduction = new Deduction();
        deduction->deductionID = rs->getInt("DeductionID");      
        deduction->name = rs->getString("Name");      
        deduction->type = rs->getString("Type");      
        deduction->description = rs->getString("Description");      
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return deduction;
}

Deduction* DeductionManager::searchDeductions()
{
    DatabaseConnection dbConn;
    Deduction* deduction = NULL;
    Deduction* head = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM DEDUCTION");

    sql::ResultSet* rs = ps->executeQuery();

    while(rs->next())
    {   
        
        if(head == NULL)
        {
            deduction = new Deduction();
            head = deduction;
        }
        else
        {
            deduction->next = new Deduction();
            deduction = deduction->next; 
        }
        deduction->deductionID = rs->getInt("DeductionID");      
        deduction->name = rs->getString("Name");      
        deduction->type = rs->getString("Type");      
        deduction->description = rs->getString("Description"); 
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

Employee_Deduction* DeductionManager::getEmployeeDeductions(int employeeID,int year,int month)
{
    Employee_Deduction* head = NULL;
    Employee_Deduction* empDeduction = NULL;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT DeductionID,Amount FROM EMPLOYEE_DEDUCTION WHERE EmployeeID = ? AND YEAR(Date) = ? AND MONTH(Date) = ? AND DeductionID <> 400001 AND DeductionID <> 400004 AND DeductionID <> 400006 AND  DeductionID <> 400010 AND DeductionID <> 400011");
    ps->setInt(1,employeeID);
    ps->setInt(2,year);
    ps->setInt(3,month);

    sql::ResultSet* rs = ps->executeQuery();

    while(rs->next())
    {
        if(head == NULL)
        {
            empDeduction = new Employee_Deduction();
            head = empDeduction;
        }
        else
        {
            empDeduction->next = new Employee_Deduction();
            empDeduction = empDeduction->next;
        }
        empDeduction->deductionID = rs->getInt("DeductionID");
        empDeduction->amount = rs->getDouble("Amount");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

void DeductionManager::viewDeductions()
{
    Deduction* deduction = NULL;
    deduction = searchDeductions();
    if(deduction!=NULL)
    {
        std::cout << std::setw(24) << "+" << std::setfill('-') <<"-" << std::setw(107) << "+" << std::setfill(' ') << std::endl
                  << std::setw(28)  << "| ID " << std::setw(13) << "| Name" << std::setw(60) <<"| Type"  << std::setw(31) << "|" << std::endl
                  << std::setw(24) << "|" << std::setfill('-') <<"-" << std::setw(107) << "|" << std::setfill(' ') << std::endl;
        while(deduction!=NULL)
        {
            if(deduction->deductionID!=400001&&deduction->deductionID!=400004&&deduction->deductionID!=400006&&deduction->deductionID!=400011&&deduction->deductionID!=400012)
            {
                std::cout << std::left
                      << std::setw(23) << " " << "| "<< std::setw(9) << deduction->deductionID << " | " << std::setw(57) << deduction->name << " | "  << std::setw(34) << deduction->type  << "|" << std::endl;
            }            
            deduction = deduction->next;
        }
        std::cout << std::right
                  << std::setw(24) << "+" << std::setfill('-') <<"-" << std::setw(107) << "+" << std::setfill(' ') << std::endl;
    }
    else
    {
        std::cout << std::setw(82) << "No deduction available." << std::endl;
    }
    delete deduction;
}

void DeductionManager::addDeduction(std::string deductionName, std::string type, std::string description)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO DEDUCTION(Name,Type,Description) VALUES (?,?,?)");
    ps->setString(1,deductionName);
    ps->setString(2,type);
    ps->setString(3,description);
    ps->executeUpdate();
    ps->close();
    delete ps;
}

void DeductionManager::addDeduction(std::string deductionName, std::string type)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO DEDUCTION(Name,Type) VALUES (?,?)");
    ps->setString(1,deductionName);
    ps->setString(2,type);
    ps->executeUpdate();
    ps->close();
    delete ps;
}

void DeductionManager::addDeduction()
{
    std::string deductionName, type, description = "";
    bool repeat;
    int strlength;
    Menu menu;
    menu.displayLogo();
    addDeductionHeader();
    
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    do
    {
        std::cout << "\n\n" << std::setw(70) << "Enter Deduction Name            : ";
        getline(std::cin,deductionName);
        repeat = checkRepeatString(deductionName,"DEDUCTION","Name");
        strlength = deductionName.length();
        if(repeat)
            std::cout  << "\n" << std::setw(90)  << "The name already exists. Please use another name." << std::endl;
        if(strlength>50)
            std::cout << "\n"<< std::setw(85) << "The name is too long. Please use a shorter name." << std::endl;
    } while (repeat||strlength>50);

    std::cout  << "\n\n" << std::setw(70) << "Enter Deduction Type            : ";
    getline(std::cin,type);

    char response;
    std::cout  << "\n\n" << std::setw(90) << "Any description? Enter Y/y to write description: ";
    std::cin  >> response;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    if(response=='Y'||response=='y')
    {
        do
        {
            std::cout << "\n\n" << std::setw(70) << "Enter Deduction Description     : ";
            getline(std::cin,description); 
            strlength = description.length();
            if(strlength>150)
                std::cout << "\n"<< std::setw(85) << "The description is too long. " << std::endl;
        } while (strlength>150);
    }
    menu.displayLogo();
    addDeductionHeader();
    std::cout << "\n\n" <<std::setw(83) <<  "NEW Deduction Preview\n\n" 
                <<std::setw(42) << " " <<std::setw(56) <<std::setfill('*') << "*"  <<std::setfill(' ') 
                << "\n\n"<<std::setw(68) << "Name             : " << deductionName << std::endl
                << "\n\n"<<std::setw(68) << "Type             : " << type << std::endl
                << "\n\n"<<std::setw(68) << "Description      : " << description << std::endl;
                 

    char confirm;
    std::cout << "\n\n" <<std::setw(97) << "Are you sure to add this deduction? Enter Y/y to confirm: ";
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        if(response=='Y'||response=='y')
            addDeduction(deductionName,type,description);
        else
            addDeduction(deductionName,type);
        std::cout << "\n" <<std::setw(89) << "[ New deduction is added successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" <<std::setw(103) << "[ Addition process has been cancelled. No changes have been made ]" << std::endl;
    }
}

void DeductionManager::assignDeduction(int employeeID, int deductionID, double amount, std::string date)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO EMPLOYEE_DEDUCTION(EmployeeID,DeductionID,Amount,`Date`) VALUES (?,?,?,?)");
    ps->setInt(1,employeeID);
    ps->setInt(2,deductionID);
    ps->setDouble(3,amount);
    ps->setString(4,date);
    ps->executeUpdate();
    ps->close();
    delete ps; 
}

void DeductionManager::assignDeduction()
{
    int employeeID, deductionID;
    double amount = 0;
    std::string date;
    bool valid , validDate;
    Menu menu;
    EmployeeManager em;
    Employee* employee = NULL;
    Deduction* deduction = NULL;
    SalaryManager sm;
    menu.displayLogo();
    assignDeductionHeader();
    viewDeductions();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
        do
        {
            valid = true;
            std::cout  << "\n\n" << std::setw(72) << "Enter Deduction ID          : ";
            std::cin >> deductionID;
            if(deductionID == 400008)
                assignDeduction_MTD();
            else if(deductionID == 400002)
                assignDeduction_EPF();
            else if(deductionID == 400005)
                assignDeduction_Socso();
            else if(deductionID == 400007)
                assignDeduction_EIS();
            else if(deductionID==400003)
            {
                LeaveManager leaveManager;
                leaveManager.conductDeduction_Leave();
            }
            else if(deductionID == 400009)
                assignDeduction_Zakat();
            else if(deductionID == 400010)
                assignDeduction_TaxRelief();
            else
            {
                std::cout << "\n" << std::setw(90) << "Please enter deduction ID in the list. " << std::endl;
                valid = false;
            }
        } while (!valid);
}

double DeductionManager::getEmployeeEPF(double amount,int age)
{
    double epf;
    if(amount<=5000)
    {
        if(age>=60)
            epf = 0;
        else
            epf = amount * 0.11;
    }
    else
    {
        if(age>=60)
            epf = 0;
        else
            epf = amount * 0.11;
    }
    //round up to nearest integer
    epf = std::ceil(epf);
    return epf;
}

double DeductionManager::getEmployerEPF(double amount,int age)
{
    double epf = 0;
    if(amount<=5000)
    {
        if(age>=60)
            epf = amount * 0.04;
        else
            epf = amount * 0.13;
    }
    else
    {
        if(age>=60)
            epf = amount * 0.04;
        else
             epf = amount * 0.12;
    }
    //round up to nearest integer
    epf = std::ceil(epf);
    return epf;
}

double DeductionManager::getEmployerSosco(double basicSalary)
{
    double amount = 0, threshold;
    ifstream file("EmployerSosco.txt");
    if(!file)
    {
        std::cout << "The file is not found. \n";
    }
    while(file >> threshold >> amount)
    {
        if(basicSalary < threshold)
            return amount;
    }
    file.close();
    return 86.65;
}

double DeductionManager::getEmployeeSosco(double basicSalary)
{
    double amount = 0, threshold;
    ifstream file("EmployeeSosco.txt");
    if(!file)
    {
        std::cout << "The file is not found. \n";
    }
    while(file >> threshold >> amount)
    {
        if(basicSalary < threshold)
            return amount;
    }
    file.close();
    return 24.75;  
}

double DeductionManager::getEIS(double basicSalary)
{
    double amount = 0, threshold;
    ifstream file("EIS.txt");
    if(!file)
    {
        std::cout << "The file is not found. \n";
    }
    while(file >> threshold >> amount)
    {
        if(basicSalary < threshold)
            return amount;
    }
    file.close();
    return 9.9; 
}

double DeductionManager::searchEmpDeduction(int employeeID,int deductionID, int targetYear, int targetMonth)
{
    DatabaseConnection dbConn;
    double amount = 0;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT Amount FROM EMPLOYEE_DEDUCTION WHERE EmployeeID = ? AND DeductionID = ? AND YEAR(Date) = ? AND MONTH(Date) = ?");
    ps->setInt(1,employeeID);
    ps->setInt(2,deductionID);
    ps->setInt(3,targetYear);
    ps->setInt(4,targetMonth);
    sql::ResultSet* rs = ps->executeQuery();
    while(rs->next())
    {
        amount += rs->getDouble("Amount");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return amount;
}

bool DeductionManager::checkRepeatEmpDeduction(int employeeID,int deductionID, int targetYear, int targetMonth)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT Amount FROM EMPLOYEE_DEDUCTION WHERE EmployeeID = ? AND DeductionID = ? AND YEAR(Date) = ? AND MONTH(Date) = ?");
    ps->setInt(1,employeeID);
    ps->setInt(2,deductionID);
    ps->setInt(3,targetYear);
    ps->setInt(4,targetMonth);
    sql::ResultSet* rs = ps->executeQuery();
    int year, month, day;
    char delimiter;
    bool repeat = false;
    if(rs->next())
    {
        repeat = true;
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return repeat;
}

Employee* DeductionManager::searchEmployees(int deductionID, int targetYear, int targetMonth)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE");
    sql::ResultSet* rs = ps->executeQuery();
    EmployeeManager em;
    Employee* employee = NULL;
    Employee* head = NULL;
    DateManager dateManager;
    while(rs->next())
    {
        if(dateManager.isAfterHireDate(rs->getString("DateOfHire"),targetYear,targetMonth) && !checkRepeatEmpDeduction(rs->getInt("EmployeeID"),deductionID,targetYear,targetMonth))
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

Employee* DeductionManager::searchEmployeesByDepartment(int departmentID,int deductionID,int targetYear, int targetMonth)
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
        if(dateManager.isAfterHireDate(rs->getString("DateOfHire"),targetYear,targetMonth) && !checkRepeatEmpDeduction(rs->getInt("EmployeeID"),deductionID,targetYear,targetMonth))
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

Employee* DeductionManager::getDeductionEmployees(int deductionID, int targetYear, int targetMonth) //return one or a list of employee pointer
{
    Menu menu;
    DateManager dateManager;
    menu.displayLogo();
    assignDeductionHeader();
    std::cout << std::setw(81) << "Assign Deduction To: " << std::endl
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
        employee = searchEmployees(deductionID,targetYear,targetMonth);
        break;

    case 2:
        head = dm.searchDepartments();
        do
        {
            department = head;
            if(department!=NULL)
            {
                menu.displayLogo();
                assignDeductionHeader();
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
                    std::cout << std::endl << std::setw(94) << "The department is not found. Enter Y/y to retry: ";
                    std::cin >> response;
                    if(response != 'y'&&response!='Y')
                    {
                        menu.conductDeductionMenu();
                        return 0;
                    }
                }
            }
        } while (response == 'y' || response =='Y');
        
        //pass the found department ID to get all employees in that department
        employee = searchEmployeesByDepartment(departmentID,deductionID,targetYear,targetMonth);
        break;

    case 3:
        menu.displayLogo();
        assignDeductionHeader();
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
                    assignDeductionHeader();
                    response = 'Z';

                    do {
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee ID              : ";
                        std::cin >> employeeID;
                        // Check if the user input already exists in the list
                        repeat = em.isEmployeeInList(employeeHead, employeeID);
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
                                menu.conductDeductionMenu();
                            else
                                break;
                        }
                    }
                }while(response == 'y' || response == 'Y');
            } 

            else if (choice == 2) 
            {
                menu.displayLogo();
                assignDeductionHeader();
                response = 'Z';
                do
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    do {
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee Name            : ";
                        getline(cin, name);

                        // Check if the user input already exists in the list
                        repeat = em.isEmployeeInList(employeeHead, name);
                        if (repeat) {
                            std::cout << std::right << std::setw(90) << "The employee already exists in the list. " << std::endl;
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
                                menu.conductDeductionMenu();
                            else
                                break;
                        }
                    }
                }while(response == 'y' || response == 'Y');
            }

            if (!dateManager.isAfterHireDate(employee->dateOfHire, targetYear, targetMonth) || checkRepeatEmpDeduction(employee->id, deductionID, targetYear, targetMonth))
            {
                employee = nullptr;
                std::cout << std::right << std::setw(108) << "The deduction is already conducted to this employee for the chosen period." << std::endl;
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

double DeductionManager::getAccumulatedDeduction(int employeeID, int deductionID, int targetYear, int targetMonth)
{
    double amount = 0;
    for(int i = 1 ; i < targetMonth ; i++)
        amount += searchEmpDeduction(employeeID,deductionID,targetYear,i);
    return amount;
}

int DeductionManager::getNoOfQualifyingChildren(Employee* employee)
{
    double C = 0;
    DependantManager dm;
    DateManager dateManager;
    Employee_Dependant* empDependant = dm.searchDependants(employee->id);
    if(empDependant==NULL)
    {
        return 0;
    }
    else
    {
        while(empDependant!=NULL)
        {
            if(empDependant->relationship=="Child")
            {
                Dependant* dependant = dm.searchDependant(empDependant->dependantID);
                if(dependant->isDisabled)
                {
                    if(dependant->isStudyingDiplomaOrHigher)
                        C += 7;
                    else
                        C += 3;
                }
                else if(dateManager.calculateAge(dependant->dateOfBirth) < 18  && dependant->maritalStatus == "Single")
                {
                    C += 1;
                }
                else if(dateManager.calculateAge(dependant->dateOfBirth) >=18 && dependant->isStudyingDiplomaOrHigher && dependant->maritalStatus=="Single")
                    C += 4;
            }
            empDependant = empDependant->next;
        }
    }
    return C;
}

double DeductionManager::getAccumulatedAdditionalRemuneration(int employeeID, int targetYear , int targetMonth)
{
    double total = 0;
    DatabaseConnection dbConn;
    char delimiter;
    int year, month, day;
    sql::PreparedStatement* psAllowance = dbConn.prepareStatement("SELECT Amount, `Date` FROM Employee_Allowance WHERE EmployeeID = ? AND AllowanceID IN (SELECT AllowanceID FROM ALLOWANCE WHERE IsExempted = 0)");
    psAllowance->setInt(1,employeeID);
    sql::ResultSet* rsAllowance = psAllowance->executeQuery();

    struct Employee_Allowance
    {
        double amount;
        std::string date;
    };
 
    std::vector<Employee_Allowance> empAllowances;
    while (rsAllowance->next()) {
        Employee_Allowance empAllowance;
        empAllowance.amount = rsAllowance->getDouble("Amount");
        empAllowance.date = rsAllowance->getString("Date");

        empAllowances.push_back(empAllowance);
    }


    for(const Employee_Allowance& empAllowance : empAllowances)
    {
        std::istringstream iss(empAllowance.date);
        if (iss >> year >> delimiter >> month >> delimiter >> day && delimiter == '-')
        {
            if( year == targetYear && month < targetMonth)
            {
                total += empAllowance.amount;
            }
        }
    }

    rsAllowance->close();
    psAllowance->close();
    delete rsAllowance;
    delete psAllowance;

    sql::PreparedStatement* psBonus = dbConn.prepareStatement("SELECT EmployeeID, Amount, `Date` FROM EMPLOYEE_BONUS WHERE EmployeeID = ?");
    psBonus->setInt(1,employeeID);
    sql::ResultSet* rsBonus = psBonus->executeQuery();
    struct Employee_Bonus
    {
        double amount;
        std::string date;
    };
 
    std::vector<Employee_Bonus> empBonuses;
    while (rsBonus->next()) {
        Employee_Bonus empBonus;
        empBonus.amount = rsBonus->getDouble("Amount");
        empBonus.date = rsBonus->getString("Date");

        empBonuses.push_back(empBonus);
    }

    for(const Employee_Bonus& empBonus : empBonuses)
    {
        std::istringstream iss(empBonus.date);
        if (iss >> year >> delimiter >> month >> delimiter >> day && delimiter == '-')
        {
            //if year equal to target year and month is previous of target month
            if(year == targetYear && month < targetMonth)
            {
                total+= empBonus.amount;
            }
        }
    }
    
    rsBonus->close();
    psBonus->close();
    delete rsBonus;
    delete psBonus;
    return total;
}

double DeductionManager::getAccumulatedNormalRemuneration(int employeeID, int targetYear , int targetMonth) //sum of basic salary for current year
{
    double total = 0;
    DatabaseConnection dbConn;
    char delimiter;
    int year, month, day;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT SUM(BasicSalary) AS `TotalSalary` FROM SALARY WHERE EmployeeID = ? AND SalaryID IN (SELECT SalaryID FROM SALARY_SCHEDULE WHERE Year = ? AND Month < ? )");
    ps->setInt(1,employeeID);
    ps->setInt(2,targetYear);
    ps->setInt(3,targetMonth);
    
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
        total = rs->getDouble("TotalSalary");
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return total;
}

double DeductionManager::getCurrentNormalRemuneration(int employeeID, int targetYear , int targetMonth)
{
    double total = 0;
    DatabaseConnection dbConn;
    char delimiter;
    int year, month, day;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT BasicSalary FROM SALARY WHERE EmployeeID = ? AND SalaryID IN (SELECT SalaryID FROM SALARY_SCHEDULE WHERE Year = ? AND Month = ? ) ");
    ps->setInt(1,employeeID);
    ps->setInt(2,targetYear);
    ps->setInt(3,targetMonth);
    
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
        total = rs->getDouble("BasicSalary");
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return total;

    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return total;

}

double DeductionManager::getCurrentAdditionalRemuneration(int employeeID, int targetYear , int targetMonth)
{
    double total = 0;
    DatabaseConnection dbConn;
    char delimiter;
    int year, month, day;
    sql::PreparedStatement* psAllowance = dbConn.prepareStatement("SELECT Amount, `Date` FROM Employee_Allowance WHERE EmployeeID = ? AND AllowanceID IN (SELECT AllowanceID FROM ALLOWANCE WHERE IsExempted = 0)");
    psAllowance->setInt(1,employeeID);
    sql::ResultSet* rsAllowance = psAllowance->executeQuery();

    struct Employee_Allowance
    {
        double amount;
        std::string date;
    };
 
    std::vector<Employee_Allowance> empAllowances;
    while (rsAllowance->next()) {
        Employee_Allowance empAllowance;
        empAllowance.amount = rsAllowance->getDouble("Amount");
        empAllowance.date = rsAllowance->getString("Date");

        empAllowances.push_back(empAllowance);
    }


    for(const Employee_Allowance& empAllowance : empAllowances)
    {
        std::istringstream iss(empAllowance.date);
        if (iss >> year >> delimiter >> month >> delimiter >> day && delimiter == '-')
        {
            if( year == targetYear && month == targetMonth)
            {
                total += empAllowance.amount;
            }
        }
    }

    rsAllowance->close();
    psAllowance->close();
    delete rsAllowance;
    delete psAllowance;

    sql::PreparedStatement* psBonus = dbConn.prepareStatement("SELECT Amount, `Date` FROM EMPLOYEE_BONUS WHERE EmployeeID = ?");
    psBonus->setInt(1,employeeID);
    sql::ResultSet* rsBonus = psBonus->executeQuery();
    struct Employee_Bonus
    {
        double amount;
        std::string date;
    };
 
    std::vector<Employee_Bonus> empBonuses;
    while (rsBonus->next()) {
        Employee_Bonus empBonus;
        empBonus.amount = rsBonus->getDouble("Amount");
        empBonus.date = rsBonus->getString("Date");

        empBonuses.push_back(empBonus);
    }

    for(const Employee_Bonus& empBonus : empBonuses)
    {
        std::istringstream iss(empBonus.date);
        if (iss >> year >> delimiter >> month >> delimiter >> day && delimiter == '-')
        {
            if(year == targetYear && month == targetMonth)
            {
                total+= empBonus.amount;
            }
        }
    }
    rsBonus->close();
    psBonus->close();
    delete rsBonus;
    delete psBonus;
    return total;
}

double DeductionManager::calculatePforNormalRemuneration(Employee* employee, int targetYear, int targetMonth) //complete
{
    /*
        P : total chargeable income for a year
        Y : accumulated gross normal remuneration + gross additional remuneration for current year, including amount paid by previous employment
        K : total EPF of Y

        Y1 : gross normal remuneration for current month
        K1 : total EPF of Y1

        Y2 : Estimated remuneration as Y1 for subsequent months
        K2 : total EPF of Y2 (if K1 < K2, K2=K1)

        LP : Total allowableDeduction for current year
        LP1 : allowableDeduction for current month

        D : deduction for individual
        S : deduction for spouse
        Du : deduction for disabled person
        Su : deduction for disabled spouse
        C : Number of qualifying children
    */
    double Q = 0, Y = 0, K = 0, Y1 = 0, K1 = 0,Y2 = 0, K2 = 0, Kt = 0, Yt = 0, LP = 0, LP1 = 0, P = 0;
    // ~ get Y:  accumulated gross normal and additional remuneration from current year //getAccumulatedNormalRemuneration(int employeeID,int targetYear, int targetMonth) (BasicSalary + VOLA + BIK)+ //getAccumulatedAdditionalRemuneration();
    // ~ get K: accumulated EPF //getAccumulatedDeduction (int employeeID, int deductionID , int targetYear, int targetMonth)
    // ~ get Y1: gross normal remuneration for current month , including VOLA& BIK //getCurrentRemuneration(int employeeID,int targetYear, int targetMonth) (BasicSalary + VOLA + BIK)
    // ~ get K1: EPF for normal remuneration for current month //searchEmpDeduction(int employeeID, int deductionID , int targetYear, int targetMonth)
    // ~ get Y2 = Y1,  estimated remuneration for subsequent months 
    // ~ get K2: 4000 - (K+K1) 
    //     if K1<K2 , K2 = K1
    Y = getAccumulatedNormalRemuneration(employee->id,targetYear,targetMonth) + getAccumulatedAdditionalRemuneration(employee->id,targetYear,targetMonth);
    K = getAccumulatedDeduction(employee->id,400002,targetYear,targetMonth);

    Y1 = employee->basicSalary;
    K1 = searchEmpDeduction(employee->id,400002,targetYear,targetMonth);


    //if has additional remuneration , calculate 2 P 
    // first call this function with Yt&Kt = 0
    // second call this function with value of Yt&Kt
    //if no additional remuneration, just let  Yt&Kt = 0
    // ~ get Kt = additional remuneration for current month if any //getCurrentAddtionalRemuneration()
    // ~ get Kt = EPF of addtional remuneration for current month if any //getEmployeeEPF(additionalRemuneration)

    //if(Kt != 0)
    //use another way to calculate 
    Kt = 0;

    DateManager dateManager;
    int employeeAge = dateManager.calculateAge(employee->dateofBirth);
    Yt = 0;

    // ~ get LP = accumulated allowable Deduction for current year excluding current month //getAccumulatedDeduction (int employeeID, int deductionID , int targetYear, int targetMonth)
    // ~ get LP1 = allowable deduction for current month //searchEmpDeduction(int employeeID, int deductionID , int targetYear, int targetMonth)
    LP = getAccumulatedDeduction(employee->id,400010,targetYear,targetMonth);
    LP1 = searchEmpDeduction(employee->id,400010,targetYear,targetMonth);

    Y2 = Y1;
    //calculate k2
    K2 = (4000-( K + K1 + Kt))/(12-targetMonth);
    if(K1<K2)
        K2 = K1;

    double C = 0,D = 9000 ,S=0, Du = 0, Su = 0;

    // ~ Determine number of qualifying children //getNoOfQualifyingChildren 
    C =  getNoOfQualifyingChildren(employee);

    // ~ isDisabled 
    if(employee->isDisabled)
        Du = 6000;
    
    // ~ Spouse isWorking 
    // ~ Spouse isDisabled 
    DependantManager dm;
    Employee_Dependant* empDependant = dm.searchDependants(employee->id);
    while(empDependant!=NULL)
    {
        //if spouse found
        if(empDependant->relationship=="Spouse")
        {
            //get spouse information
            Dependant* dependant = dm.searchDependant(empDependant->dependantID);
            if(dependant->isDisabled) //if disabled
                Su += 5000;
            if(!(dependant->isWorking)) //if no working
                S += 4000;
            delete dependant;
        }
        empDependant = empDependant->next; //next dependant
    }
    P = ((Y-K)+(Y1-K1)+ ((Y2-K2)*(12-targetMonth)) + (Yt - Kt)) - (D+S+2000*C+(LP+LP1));
    return P;
}

double DeductionManager::calculatePforAdditionalRemuneration(Employee* employee, int targetYear, int targetMonth) //complete
{
    /*
        P : total chargeable income for a year
        Y : accumulated gross normal remuneration + gross additional remuneration for current year, including amount paid by previous employment
        K : total EPF of Y

        Y1 : gross normal remuneration for current month
        K1 : total EPF of Y1

        Y2 : Estimated remuneration as Y1 for subsequent months
        K2 : total EPF of Y2 (if K1 < K2, K2=K1)

        LP : Total allowableDeduction for current year
        LP1 : allowableDeduction for current month

        D : deduction for individual
        S : deduction for spouse
        Du : deduction for disabled person
        Su : deduction for disabled spouse
        C : Number of qualifying children
    */
    double Q = 0, Y = 0, K = 0, Y1 = 0, K1 = 0,Y2 = 0, K2 = 0, Kt = 0, Yt = 0, LP = 0, LP1 = 0, P = 0;
    // ~ get Y:  accumulated gross normal and additional remuneration from current year //getAccumulatedNormalRemuneration(int employeeID,int targetYear, int targetMonth) (BasicSalary + VOLA + BIK)+ //getAccumulatedAdditionalRemuneration();
    // ~ get K: accumulated EPF //getAccumulatedDeduction (int employeeID, int deductionID , int targetYear, int targetMonth)
    // ~ get Y1: gross normal remuneration for current month , including VOLA& BIK //getCurrentRemuneration(int employeeID,int targetYear, int targetMonth) (BasicSalary + VOLA + BIK)
    // ~ get K1: EPF for normal remuneration for current month //searchEmpDeduction(int employeeID, int deductionID , int targetYear, int targetMonth)
    // ~ get Y2 = Y1,  estimated remuneration for subsequent months 
    // ~ get K2: 4000 - (K+K1) 
    //     if K1<K2 , K2 = K1
    Y = getAccumulatedNormalRemuneration(employee->id,targetYear,targetMonth) + getAccumulatedAdditionalRemuneration(employee->id,targetYear,targetMonth);
    K = getAccumulatedDeduction(employee->id,400002,targetYear,targetMonth);

    Y1 = employee->basicSalary;
    K1 = searchEmpDeduction(employee->id,400002,targetYear,targetMonth);


    //if has additional remuneration , calculate 2 P 
    // first call this function with Yt&Kt = 0
    // second call this function with value of Yt&Kt
    //if no additional remuneration, just let  Yt&Kt = 0
    // ~ get Kt = additional remuneration for current month if any //getCurrentAddtionalRemuneration()
    // ~ get Kt = EPF of addtional remuneration for current month if any //getEmployeeEPF(additionalRemuneration)

    //if(Kt != 0)
    //use another way to calculate 
    Yt = getCurrentAdditionalRemuneration(employee->id,targetYear,targetMonth);
    Kt = searchEmpDeduction(employee->id,400012,targetYear,targetMonth);
    // ~ get LP = accumulated allowable Deduction for current year excluding current month //getAccumulatedDeduction (int employeeID, int deductionID , int targetYear, int targetMonth)
    // ~ get LP1 = allowable deduction for current month //searchEmpDeduction(int employeeID, int deductionID , int targetYear, int targetMonth)
    LP = getAccumulatedDeduction(employee->id,400010,targetYear,targetMonth);
    LP1 = searchEmpDeduction(employee->id,400010,targetYear,targetMonth);

    Y2 = Y1;
    //calculate k2
    K2 = (4000- ( K + K1 + Kt))/(12-targetMonth);

    if(K1<K2)
        K2 = K1;
    double C = 0,D = 9000 ,S=0, Du = 0, Su = 0;

    // ~ Determine number of qualifying children //getNoOfQualifyingChildren 
    C =  getNoOfQualifyingChildren(employee);

    // ~ isDisabled 
    if(employee->isDisabled)
        Du = 6000;
    
    // ~ Spouse isWorking 
    // ~ Spouse isDisabled 
    DependantManager dm;
    Employee_Dependant* empDependant = dm.searchDependants(employee->id);
    while(empDependant!=NULL)
    {
        //if spouse found
        if(empDependant->relationship=="Spouse")
        {
            //get spouse information
            Dependant* dependant = dm.searchDependant(empDependant->dependantID);
            if(dependant->isDisabled) //if disabled
                Su += 5000;
            if(!(dependant->isWorking)) //if no working
                S += 4000;
            delete dependant;
        }
        empDependant = empDependant->next; //next dependant
    }
    P = ((Y-K)+(Y1-K1)+ ((Y2-K2)*(12-targetMonth)) + (Yt - Kt)) - (D+S+2000*C+(LP+LP1));

    return P;
}

double DeductionManager::calculateTotalTaxForAYear(double p, Employee* employee,int targetYear, int targetMonth)
{
    //this function is used when there is additional remuneration
    //get employee category
    EmployeeManager em;
    int category = em.getEmployeeCategory(employee->id);
    double totalTax = 0;
    if(employee->WorkerType=="Normal")
    {
        double m = 0, b1 = 0, b2=0,threshold;
        double r = 0;
        ifstream file("NormalPCB.txt");
        if(!file)
        {
            std::cout << "The file is not found. \n";
        }
        while(file >> threshold >> m >> r >> b1 >> b2)
        {
            if(p <= threshold)
            {
                // p = taxable income
                // z = accumulated zakat paid in current year (excluded current month)
                // x = accumulated pcb paid in current year (excluded current month)
                if(category ==1 ||category==3)
                    totalTax = (p-m) * r + b1;
                else
                    totalTax = (p-m) * r + b2;
                return totalTax;
            }
        }
        totalTax = (p-2000000) * 0.3 + 528400;
        file.close();
    }
    else
    {
        double R = 0.15;
        //Individual or husband or wife rebate
        double T = 0;
        if(p<=35000)
        {
            if(category==1 || category == 3)
                T = 400;
            else
                T = 800;
        }
        totalTax = (p * R - T);
    }
    return totalTax;
}

double DeductionManager::calculateTotalMTDForAYear(double MTD, int employeeID, int targetYear, int targetMonth)
{
    //only applicable when there is additional remuneration
    double accumulatedMTD = getAccumulatedDeduction(employeeID,400008,targetYear,targetMonth);
    double annualMTD = accumulatedMTD + (MTD*(12-targetMonth+1));
    return annualMTD;
}

double DeductionManager::calculateNormalMTD(double p, int employeeID,int targetYear, int targetMonth)
{
    //get employee category
    EmployeeManager em;
    int category = em.getEmployeeCategory(employeeID);

    //get accumulated zakat until previous month
    double accumulatedZakat = getAccumulatedDeduction(employeeID,400009,targetYear,targetMonth);

    
    //get accumulated MTD until previous month
    double accumulatedMTD = getAccumulatedDeduction(employeeID,400008,targetYear,targetMonth);

    double m = 0, b1 = 0, b2=0,MTD = 0,threshold;
    double r = 0;
    ifstream file("NormalPCB.txt");
    if(!file)
    {
        std::cout << "The file is not found. \n";
    }
    while(file >> threshold >> m >> r >> b1 >> b2)
    {
        if(p <= threshold)
        {
            // p = taxable income
            // z = accumulated zakat paid in current year (excluded current month)
            // x = accumulated pcb paid in current year (excluded current month)
            if(category ==1 ||category==3)
                MTD = (((p-m) * r + b1) - (accumulatedZakat + accumulatedMTD) ) /((12-targetMonth)+1);
            else
                MTD = (((p-m) * r + b2) - (accumulatedZakat + accumulatedMTD) ) /((12-targetMonth)+1);
            return MTD;
        }
    }
    MTD = (((p-2000000) * 0.3 + 528400) - (accumulatedZakat + accumulatedMTD) ) /((12-targetMonth)+1);
    file.close();
    return MTD;
}

double DeductionManager::calculateREP_KWASR_C_SUITE_MTD(double P, int employeeID,int targetYear, int targetMonth)
{
    //get employee category
    EmployeeManager em;
    int category = em.getEmployeeCategory(employeeID);

    //get accumulated zakat until previous month
    double accumulatedZakat = getAccumulatedDeduction(employeeID,400009,targetYear,targetMonth);
    
    //get accumulated MTD until previous month
    double accumulatedMTD = getAccumulatedDeduction(employeeID,400008,targetYear,targetMonth);

    //Percentage of tax rate
    double R = 0.15;

    //Individual or husband or wife rebate
    double T = 0;
    if(P<=35000)
    {
        if(category==1 || category == 3)
            T = 400;
        else
            T = 800;
    }

    double MTD = 0;
    MTD = ((P * R - T)- (accumulatedZakat + accumulatedMTD) ) /((12-targetMonth)+1);
    return MTD;
}

double DeductionManager::calculateNetMTD(Employee* employee,int targetYear, int targetMonth) 
{
    double MTD = 0;

    if(!employee->isResident)
    {
        double totalRemuneration = 0;
        totalRemuneration =  getCurrentNormalRemuneration(employee->id, targetYear,targetMonth) + getCurrentAdditionalRemuneration(employee->id, targetYear,targetMonth);
        MTD = totalRemuneration * 0.3;
        return MTD;
    }

    double P = 0, currentZakat = 0 ,netMTD = 0;    
    //calculate P
    P = calculatePforNormalRemuneration(employee,targetYear,targetMonth);
    if(employee->WorkerType == "Normal")
        MTD = calculateNormalMTD(P,employee->id,targetYear, targetMonth);
    else
        MTD = calculateREP_KWASR_C_SUITE_MTD(P,employee->id,targetYear, targetMonth);

    //get zakat paid for current month
    currentZakat = searchEmpDeduction(employee->id,400009,targetYear,targetMonth);
    netMTD = MTD - currentZakat;

    //if MTD before zakat deduction < 10, employer is not required to make the MTD
    if(MTD <10)
        netMTD = 0;

    //if there is additional remuneration//900010,2023,4
    if(getCurrentAdditionalRemuneration(employee->id,targetYear,targetMonth)!=0)
    {
        double P2 = calculatePforAdditionalRemuneration(employee,targetYear,targetMonth);

        double totalTax = calculateTotalTaxForAYear(P2,employee,targetYear,targetMonth);
        double totalMTD = calculateTotalMTDForAYear(MTD,employee->id,targetYear, targetMonth);
        double accumulatedZakat = getAccumulatedDeduction(employee->id,400009,targetYear,targetMonth);
        double addtionalMTD = totalTax - (totalMTD + accumulatedZakat);
        if(addtionalMTD<=10)
            addtionalMTD = 0;
        netMTD += addtionalMTD;
    }
    roundingUpToNearest5Cents(netMTD);
    return netMTD;
}

void DeductionManager::assignDeduction_MTD() 
{
    Menu menu;
    DateManager dateManager;
    int targetYear,targetMonth;
    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Year                  : ";
        std::cin >> targetYear;
        if(targetYear<1900)
            std::cout << "\n"<< std::setw(90) << "Invalid year. Please enter a valid year." << std::endl;
    } while (targetYear<1900);
    
    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Month                 : ";
        std::cin >> targetMonth;
        if(targetMonth<1||targetMonth>12)
            std::cout << "\n"<< std::setw(91) << "Invalid month. Please enter a valid month." << std::endl;
    } while (targetMonth<1||targetMonth>12);


    double netMTD = 0;
    // ~ get employee pointer
    Employee* head = NULL;
    head = getDeductionEmployees(400008,targetYear,targetMonth);

    if(head==NULL)
    {
        std::cout<< std::setw(83) << "No deduction is needed. " << std::endl; 
        return;
    }
    
    Employee* employee = head;
    
    struct Employee_MTD
    {
        int employeeID;
        double amount;
    };

    std::vector<Employee_MTD> empMTDs;

    //if only one employee, head->next = NULL
    menu.displayLogo();
    assignDeductionHeader();
    DepartmentManager dm;
    std::cout << std::setw(10) << "+" << std::setfill('-') <<"-" << std::setw(138) << "+" << std::setfill(' ') << std::endl
        << std::setw(24) << "| Employee Name" << std::setw(50) <<"| Department"  << std::setw(35) <<"| Position"   << std::setw(40) <<"| Deduction Amount (RM)|" << std::endl
        << std::setw(10) << "|" << std::setfill('-') <<"-" << std::setw(138) << "|" << std::setfill(' ') << std::endl;   

    while(employee!=NULL) 
    {
        //calculate net MTD for each employee
        std::cout << std::fixed << std::setprecision(2); 
        netMTD = calculateNetMTD(employee,targetYear,targetMonth);

        //get department name and position name
        Department* department = dm.searchDepartment(employee->departmentID);
        Position* position = dm.searchPosition(employee->positionID);

        if(netMTD!=0)
        {
            //store each element into vector
            Employee_MTD empMTD;
            empMTD.employeeID = employee->id;
            empMTD.amount = netMTD;
            empMTDs.push_back(empMTD);

            //display each element to user's screen
            std::cout << std::left << std::setw(9) << " " << "|  " << std::setw(50) << employee->name << "| "  << std::setw(35) << department->departmentName << "| "  << std::setw(24) << position->positionName << "| "  << std::setw(20) << netMTD << " " << "|" << std::endl;
        }
        //proceed to next element
        employee = employee->next;
    }
    std::cout << std::right << std::setw(10) << "+" << std::setfill('-') <<"-" << std::setw(138) << "+" << std::setfill(' ') << std::endl;

    char confirm;
    std::cout << "\n\n" <<std::setw(104) << "Are you sure to assign deduction to this/these employee(s)? Enter Y/y to confirm: ";
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        std::string date = dateManager.getCurrentDate();
        //loop for each element in the vector to assign each element's deduction
        for(const Employee_MTD& empMTD : empMTDs)
        {
            //assign deduction for current element of vector
            assignDeduction(empMTD.employeeID, 400008 ,empMTD.amount,date);
        }

        std::cout << "\n" <<std::setw(89) << "[ Deduction is assigned successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" <<std::setw(103) << "[ Deduction Assignment has been cancelled. No changes have been made ]" << std::endl;
    }   
}

void DeductionManager::roundingUpToNearest5Cents(double &amount) //rounding up to nearest 5 cents
{
    //Multiply by 100 (to get wanted value without decimals),
    // Divide by 5 (because that's the precision you want),
    // Round this number. Now reverse the procedure with rounded number:
    // Multiply by 5 and
    // Divide by 100 (to get value with two decimal places).

    //  Multiply by 20 (previous steps 1 and 2 combined),
    // Round the number,
    // Multiply by 0.05. (combine step 4 and 5)

    amount *= 20;
    amount = std::ceil(amount);
    amount *= 0.05;
}

void DeductionManager::assignDeduction_EPF()
{
    Menu menu;
    int targetYear, targetMonth;
    double employeeEPF = 0 ,employerEPF = 0; 
    double additionalRemuneration = 0, additionalEmployeeEPF=0,additionalEmployerEPF=0;
    double totalAllowance = 0, travellingAllowance = 0, totalBonus = 0;
    menu.displayLogo();
    assignDeductionHeader();

    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Year                  : ";
        std::cin >> targetYear;
        if(targetYear<1900)
            std::cout << "\n"<< std::setw(90) << "Invalid year. Please enter a valid year." << std::endl;
    } while (targetYear<1900);
    
    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Month                 : ";
        std::cin >> targetMonth;
        if(targetMonth<1||targetMonth>12)
            std::cout << "\n"<< std::setw(91) << "Invalid month. Please enter a valid month." << std::endl;
    } while (targetMonth<1||targetMonth>12);
    menu.displayLogo();
    assignDeductionHeader();
    Employee* head = getDeductionEmployees(400002,targetYear,targetMonth);
    menu.displayLogo();
    assignDeductionHeader();
    if(head==NULL)
    {
        std::cout << std::setw(83) << "No deduction is needed. " << std::endl;        
        return;
    }
    else
    {
        Employee* employee = head;
        struct Employee_EPF
        {
            int employeeID;
            double employeeEPF;
            double employerEPF;
        };
        struct Employee_AddtionalEPF
        {
            int employeeID;
            double addtionalEmployeeEPF;
            double addtionalEmployerEPF;
        };

        std::vector<Employee_EPF> empEPFs;

        std::vector<Employee_AddtionalEPF> empAddtionalEPFs;

        SalaryManager sm;
        DepartmentManager dm;
        DateManager dateManager;
        int age;
        std::cout << std::setw(2) << "+" << std::setfill('-') <<"-" << std::setw(153) << "+" << std::setfill(' ') << std::endl
                    << std::setw(16) << "| Employee Name"   << std::setw(50) <<"| Department"  << std::setw(35) <<"| Position"   << std::setw(36) <<"| Employee EPF(RM)"<<"| Employer EPF(RM)|" << std::endl
                    << std::setw(2) << "|" << std::setfill('-') <<"-" << std::setw(153) << "|" << std::setfill(' ') << std::endl;   
        Department* department = NULL;
        Position* position = NULL;
        while(employee!=NULL)
        {
            //only applicable to those who havent be assigned
            totalAllowance = sm.getTotalAllowance(employee->id);
            totalBonus = sm.getTotalBonus(employee->id,targetYear,targetMonth);
            travellingAllowance = sm.getTravellingAllowance(employee->id);
            age = dateManager.calculateAge(employee->dateofBirth);

            additionalRemuneration = getCurrentAdditionalRemuneration(employee->id, targetYear,targetMonth);
            if(additionalRemuneration!=0)
            {
                additionalEmployeeEPF = getEmployeeEPF(additionalRemuneration,age);
                additionalEmployerEPF = getEmployerEPF(additionalRemuneration,age);

                Employee_AddtionalEPF empAddtionalEPF;
                empAddtionalEPF.employeeID = employee->id;
                empAddtionalEPF.addtionalEmployeeEPF = additionalEmployeeEPF;
                empAddtionalEPF.addtionalEmployerEPF = additionalEmployerEPF;
                empAddtionalEPFs.push_back(empAddtionalEPF);
            }

            employeeEPF = getEmployeeEPF(employee->basicSalary,age);
            employerEPF =  getEmployerEPF(employee->basicSalary,age); 

            //get department name and position name
            department = dm.searchDepartment(employee->departmentID);
            position = dm.searchPosition(employee->positionID);

            //store each element into vector
            Employee_EPF empEPF;
            empEPF.employeeID = employee->id;
            empEPF.employeeEPF = employeeEPF;
            empEPF.employerEPF = employerEPF;
            empEPFs.push_back(empEPF);

            //display each element to user's screen
            std::cout << std::left << std::setw(1) << " " << "| " << std::setw(51) << employee->name << "| "  << std::setw(35) << department->departmentName << "| "  << std::setw(26) << position->positionName << "| "  << std::setw(16) << employeeEPF+additionalEmployeeEPF << "| "  << std::setw(16) << employerEPF+additionalEmployerEPF  << "|" << std::endl;
            employee = employee->next;
        }
        std::cout << std::right << std::setw(2) << "+" << std::setfill('-') <<"-" << std::setw(153) << "+" << std::setfill(' ') << std::endl;

        char confirm;
        std::cout << "\n\n" <<std::setw(104) << "Are you sure to assign deduction to this/these employee(s)? Enter Y/y to confirm: ";
        std::cin >> confirm;
        if(confirm == 'Y'|| confirm=='y')
        {
            std::string date = dateManager.getCurrentDate();

            //loop for each element in the vector to assign each element's deduction
            for(const Employee_EPF& empEPF : empEPFs)
            {
                //assign deduction for current element of vector
                assignDeduction(empEPF.employeeID, 400002 ,empEPF.employeeEPF,date);
                assignDeduction(empEPF.employeeID, 400001 ,empEPF.employerEPF,date);                
            }

            for(const Employee_AddtionalEPF& empAddtionalEPF : empAddtionalEPFs)
            {
                //assign deduction for current element of vector
                assignDeduction(empAddtionalEPF.employeeID, 400012 ,empAddtionalEPF.addtionalEmployeeEPF,date);
                assignDeduction(empAddtionalEPF.employeeID, 400011 ,empAddtionalEPF.addtionalEmployerEPF,date);                
            }


            std::cout << "\n" <<std::setw(89) << "[ Deduction is conducted successfully ]" << std::endl;
        }
        else
        {
            std::cout << "\n" <<std::setw(103) << "[ Deduction Conduction has been cancelled. No changes have been made ]" << std::endl;
        }   
    }
}

void DeductionManager::assignDeduction_Socso()
{
    Menu menu;
    int targetYear, targetMonth;
    double employeeSocso = 0 ,employerSocso = 0;

    menu.displayLogo();
    assignDeductionHeader();

    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Year                  : ";
        std::cin >> targetYear;
        if(targetYear<1900)
            std::cout << "\n"<< std::setw(90) << "Invalid year. Please enter a valid year." << std::endl;
    } while (targetYear<1900);
    
    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Month                 : ";
        std::cin >> targetMonth;
        if(targetMonth<1||targetMonth>12)
            std::cout << "\n"<< std::setw(91) << "Invalid month. Please enter a valid month." << std::endl;
    } while (targetMonth<1||targetMonth>12);

    menu.displayLogo();
    assignDeductionHeader();

    Employee* head = getDeductionEmployees(400005,targetYear,targetMonth);

    menu.displayLogo();
    assignDeductionHeader();

    if(head==NULL)
    {
        std::cout<< std::setw(83) << "No deduction is needed. " << std::endl;        
        return;
    }
    else
    {
        Employee* employee = head;
        struct Employee_Socso
        {
            int employeeID;
            double employeeSocso;
            double employerSocso;
        };

        std::vector<Employee_Socso> empSocsos;

        SalaryManager sm;
        DateManager dateManager;
        DepartmentManager dm;
        Department* department = NULL;
        Position* position = NULL;

        int age;
        std::cout << std::setw(2) << "+" << std::setfill('-') <<"-" << std::setw(153) << "+" << std::setfill(' ') << std::endl
                    << std::setw(16) << "| Employee Name"   << std::setw(48) <<"| Department"  << std::setw(35) <<"| Position"   << std::setw(36) <<"| Employee Socso(RM)"<<"| Employer Socso(RM)|" << std::endl
                    << std::setw(2) << "|" << std::setfill('-') <<"-" << std::setw(153) << "|" << std::setfill(' ') << std::endl;   
        while(employee!=NULL)
        {
            employeeSocso = getEmployeeSosco(employee->basicSalary);
            employerSocso = getEmployerSosco(employee->basicSalary);
            //get department name and position name
            department = dm.searchDepartment(employee->departmentID);
            position = dm.searchPosition(employee->positionID);

            //store each element into vector
            Employee_Socso empSocso;
            empSocso.employeeID = employee->id;
            empSocso.employeeSocso = employeeSocso;
            empSocso.employerSocso = employerSocso;
            empSocsos.push_back(empSocso);

            //display each element to user's screen
            std::cout << std::left << std::setw(1) << " " << "| " << std::setw(49) << employee->name << "| "  << std::setw(35) << department->departmentName << "| "  << std::setw(24) << position->positionName << "| "  << std::setw(18) << employeeSocso << "| "  << std::setw(18) << employerSocso  << "|" << std::endl;
            employee = employee->next;
        }
        std::cout << std::right << std::setw(2) << "+" << std::setfill('-') <<"-" << std::setw(153) << "+" << std::setfill(' ') << std::endl;

        char confirm;
        std::cout << "\n\n" <<std::setw(104) << "Are you sure to assign deduction to this/these employee(s)? Enter Y/y to confirm: ";
        std::cin >> confirm;
        if(confirm == 'Y'|| confirm=='y')
        {
            std::string date = dateManager.getCurrentDate();
            //loop for each element in the vector to assign each element's deduction
            for(const Employee_Socso& empSocso : empSocsos)
            {
                //assign deduction for current element of vector
                assignDeduction(empSocso.employeeID, 400005 ,empSocso.employeeSocso,date);
                assignDeduction(empSocso.employeeID, 400004 ,empSocso.employerSocso,date);
            }

            std::cout << "\n" <<std::setw(89) << "[ Deduction is conducted successfully ]" << std::endl;
        }
        else
        {
            std::cout << "\n" <<std::setw(103) << "[ Deduction Conduction has been cancelled. No changes have been made ]" << std::endl;
        }   
    }
}

void DeductionManager::assignDeduction_EIS()
{
    Menu menu;
    int targetYear, targetMonth;
    double employeeEIS = 0 ,employerEIS = 0;

    menu.displayLogo();
    assignDeductionHeader();

    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Year                  : ";
        std::cin >> targetYear;
        if(targetYear<1900)
            std::cout << "\n"<< std::setw(90) << "Invalid year. Please enter a valid year." << std::endl;
    } while (targetYear<1900);
    
    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Month                 : ";
        std::cin >> targetMonth;
        if(targetMonth<1||targetMonth>12)
            std::cout << "\n"<< std::setw(91) << "Invalid month. Please enter a valid month." << std::endl;
    } while (targetMonth<1||targetMonth>12);

    menu.displayLogo();
    assignDeductionHeader();

    Employee* head = getDeductionEmployees(400007,targetYear,targetMonth);

    menu.displayLogo();
    assignDeductionHeader();

    if(head==NULL)
    {
        std::cout << std::setw(83) << "No deduction is needed. " << std::endl;
        return;
    }
    else
    {
        Employee* employee = head;

        struct Employee_EIS
        {
            int employeeID;
            double employeeEIS;
            double employerEIS;
        };

        std::vector<Employee_EIS> Employee_EISes;

        SalaryManager sm;
        DateManager dateManager;
        DepartmentManager dm;
        Department* department = NULL;
        Position* position = NULL;

        std::cout << std::setw(2) << "+" << std::setfill('-') <<"-" << std::setw(153) << "+" << std::setfill(' ') << std::endl
                    << std::setw(16) << "| Employee Name"   << std::setw(50) <<"| Department"  << std::setw(35) <<"| Position"   << std::setw(36) <<"| Employee EIS(RM)"<<"| Employer EIS(RM)|" << std::endl
                    << std::setw(2) << "|" << std::setfill('-') <<"-" << std::setw(153) << "|" << std::setfill(' ') << std::endl;   
        while(employee!=NULL)
        {
            employeeEIS = getEIS(employee->basicSalary);
            employerEIS =  getEIS(employee->basicSalary); 

            //get department name and position name
            department = dm.searchDepartment(employee->departmentID);
            position = dm.searchPosition(employee->positionID);

            //store each element into vector
            Employee_EIS empEIS;
            empEIS.employeeID = employee->id;
            empEIS.employeeEIS = employeeEIS;
            empEIS.employerEIS = employerEIS;
            Employee_EISes.push_back(empEIS);

            //display each element to user's screen
            std::cout << std::left << std::setw(1) << " " << "| " << std::setw(51) << employee->name << "| "  << std::setw(35) << department->departmentName << "| "  << std::setw(26) << position->positionName << "| "  << std::setw(16) << employeeEIS << "| "  << std::setw(16) << employerEIS  << "|" << std::endl;
            employee = employee->next;
        }
        std::cout << std::right << std::setw(2) << "+" << std::setfill('-') <<"-" << std::setw(153) << "+" << std::setfill(' ') << std::endl;

        char confirm;
        std::cout << "\n\n" <<std::setw(104) << "Are you sure to assign deduction to this/these employee(s)? Enter Y/y to confirm: ";
        std::cin >> confirm;
        if(confirm == 'Y'|| confirm=='y')
        {
            std::string date = dateManager.getCurrentDate();
            //loop for each element in the vector to assign each element's deduction
            for(const Employee_EIS& empEIS : Employee_EISes)
            {
                //assign deduction for current element of vector
                assignDeduction(empEIS.employeeID, 400007 ,empEIS.employeeEIS,date);
                assignDeduction(empEIS.employeeID, 400006 ,empEIS.employerEIS,date);
            }

            std::cout << "\n" <<std::setw(89) << "[ Deduction is conducted successfully ]" << std::endl;
        }
        else
        {
            std::cout << "\n" <<std::setw(103) << "[ Deduction Conduction has been cancelled. No changes have been made ]" << std::endl;
        }   
    }
}

void DeductionManager::assignNewZakat()
{

    int employeeID;
    char response;
    double amount = 0;
    Menu menu;
    EmployeeManager em;
    DateManager dateManager;
    Employee* employee = NULL;
    menu.displayLogo();
    assignDeductionHeader();

    do
    {
        response = 'Z';
        menu.displayLogo();
        assignDeductionHeader();
        std::cout  << "\n\n"<< std::setw(72) << "Enter Employee ID        : ";
        std::cin >> employeeID;
        employee = em.searchEmployee(employeeID);
        if(employee==NULL)
        {
            std::cout << std::endl << std::setw(90) << "The employee is not found. Enter Y/y to retry: ";
            std::cin >> response;
            if(response != 'y'&& response!='Y')
                menu.conductDeductionMenu();
        }
    } while (response == 'y'||response=='Y');

    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Zakat Amount (RM)  : ";
        std::cin >> amount;
        if(amount<0||amount>999999.99)
            std::cout  << "\n\n" << std::setw(87)<< "Invalid amount. Please try again." << std::endl;
    } while (amount<0||amount>999999.99);

    std::string date = dateManager.getCurrentDate();

    menu.displayLogo();
    assignDeductionHeader();
     std::cout << "\n" << std::setw(78) <<  "Zakat Preview\n\n"
                << std::setw(41) << " " << std::setw(56) << std::setfill('*') << "*"  << std::setfill(' ') 
                << "\n\n"<< std::setw(72) << "Employee ID              : "   << employeeID << std::endl
                << "\n"<< std::setw(72) << "Total Amount(RM)         : " << amount << std::endl
                << "\n"<< std::setw(72) << "Date (YYYY/MM/DD))       : " << date << std::endl;

    char confirm;
    std::cout << "\n\n" <<std::setw(100) << "Are you sure to allocate zakat for this employee? Enter 'Y' to confirm : " ;
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm =='y')
    {
        assignDeduction(employeeID,400009,amount,date);
        std::cout << "\n" << std::setw(96) << "[ Zakat is assigned to the employee successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" << std::setw(105) << "[ Zakat Assignment has been cancelled. No changes have been made ]" << std::endl;
    }

    std::cout << "\n\n" << std::setw(96) << "Enter 'Y' to allocate zakat for another employee: " ;
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm =='y')
    {
        assignNewZakat();
    }
    else
    {
        menu.conductDeductionMenu();
    }

}

void DeductionManager::assignDeduction_Zakat()
{
    std::cout << std::fixed << std::setprecision(2); 

    Menu menu;
    menu.displayLogo();
    assignDeductionHeader();
    struct Employee_Zakat
    {
        int employeeID;
        std::string employeeName,departmentName,PositionName;
        double amount;
    };
    
    char delimiter;
    int year, month, day;
    DateManager dateManager;
    std::string currentDate = dateManager.getCurrentDate();
    std::istringstream dateStream(currentDate);
    dateStream >> year >> delimiter >> month >> delimiter >> day && delimiter == '-';

    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT b.EmployeeID, e.Name, b.Amount, d.DepartmentName, p.PositionName FROM ( SELECT ed.EmployeeID, ed.Amount, ed.`Date` FROM EMPLOYEE_DEDUCTION ed JOIN ( SELECT EmployeeID, MAX(`Date`) AS LatestDate FROM EMPLOYEE_DEDUCTION WHERE DeductionID = 400009 GROUP BY EmployeeID) a ON ed.EmployeeID = a.EmployeeID AND ed.`Date` = a.LatestDate WHERE ed.DeductionID = 400009) b JOIN EMPLOYEE e ON b.EmployeeID = e.EmployeeID JOIN DEPARTMENT d ON e.DepartmentID = d.DepartmentID JOIN POSITION p ON e.PositionID = p.PositionID ORDER BY b.EmployeeID");
    sql::ResultSet* rs = ps->executeQuery();

    vector<Employee_Zakat> empZakats;

    menu.displayLogo();
    assignDeductionHeader();
    bool exist;
    if(rs->next())
    {
        Employee_Zakat empZakat;
        exist = checkRepeatEmpDeduction(rs->getInt("EmployeeID"),400009,year,month);
        if(!exist)
        {
            std::cout << std::setw(18) << "Deduction : Zakat" << std::endl;
            std::cout << "+" << std::setfill('-') <<"-" << std::setw(152) << "+" << std::setfill(' ') << std::endl
                        << "| Employee ID | Employee Name" << std::setw(50) << "| Department"  << std::setw(35) <<"| Position"   << std::setw(40) <<"| Deduction Amount (RM)|" << std::endl
                        << "|" << std::setfill('-') << "-" << std::setw(152) << "|" << std::setfill(' ') << std::endl;  

            //display
            std::cout << std::left << "| " << std::setw(12) << rs->getInt("EmployeeID") << "| " << std::setw(51) << rs->getString("Name") << "| "  << std::setw(35) << rs->getString("DepartmentName") << "| "  << std::setw(24) << rs->getString("PositionName") << "| "  << std::right << std::setw(20) << rs->getString("Amount") << " " << "|" << std::endl;
            //insert into vector
            empZakat.employeeID = rs->getInt("EmployeeID");
            empZakat.employeeName = rs->getString("Name");
            empZakat.departmentName = rs->getString("DepartmentName");
            empZakat.PositionName = rs->getString("PositionName");
            empZakat.amount = rs->getDouble("Amount");
            empZakats.push_back(empZakat);
        }
        else
        {
            char response;
            std::cout << "\n" << std::setw(83) << "No deduction is needed. Or Enter 'Y' to add new Zakat record : " ;
            std::cin >> response;
            if(response=='Y'||response=='y')
            {
                assignNewZakat();
            }
            else
                menu.conductDeductionMenu();
        }
        while(rs->next())
        {
            Employee_Zakat empZakat;
            exist = checkRepeatEmpDeduction(rs->getInt("EmployeeID"),400009,year,month);
            if(!exist)
            {
                //display
                std::cout << std::left << "| " << std::setw(12) << rs->getInt("EmployeeID") << "| " << std::setw(51) << rs->getString("Name") << "| "  << std::setw(35) << rs->getString("DepartmentName") << "| "  << std::setw(24) << rs->getString("PositionName") << "| "  << std::right << std::setw(20) << rs->getString("Amount") << " " << "|" << std::endl;
 
                //insert into vector
                empZakat.employeeID = rs->getInt("EmployeeID");
                empZakat.employeeName = rs->getString("Name");
                empZakat.departmentName = rs->getString("DepartmentName");
                empZakat.PositionName = rs->getString("PositionName");
                empZakat.amount = rs->getDouble("Amount");
                empZakats.push_back(empZakat);
            }
        }
        //end display 
        std::cout << std::right << "+" << std::setfill('-') << "-" << std::setw(152) << "+" << std::setfill(' ') << std::endl;

        char choice = 'o'; // initialize char
        while(choice!='Z'&&choice!='z'&&choice!='Y'&&choice!='y' && !empZakats.empty())
        {
            std::cout << "\n\n" << std::right << std::setw(43) << "+" << std::setw(53) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl
                << std::right << std::setw(43) << "|" << std::left << std::setw(1) << " " << std::setw(51) <<  "Enter 'Y' to assign zakat to all of these employees" << std::setw(7) << "|"<< std::endl
                << std::right << std::setw(43) << "|" << std::left << std::setw(1) << " " << std::setw(51) <<  "Enter 'A' to assign new zakat to employee" << std::setw(7) << "|"<< std::endl
                << std::right << std::setw(43) << "|" << std::left << std::setw(1) << " " << std::setw(51) <<  "Enter 'U' to update zakat amount of employee" << std::setw(15) << "|"<< std::endl
                << std::right << std::setw(43) << "|" << std::left << std::setw(1) << " " << std::setw(51) <<  "Enter 'R' to remove employee from the list" << std::setw(20) << "|"<< std::endl
                << std::right << std::setw(43) << "|" << std::left << std::setw(1) << " " << std::setw(51) <<  "Enter 'Z' to exit" << std::setw(30) << "|"<< std::endl
                << std::right << std::setw(43) << "+" << std::setw(53) << std::setfill('-') << "+" << std::setfill(' ')  << std::endl ;  

            do
            {
                std::cout << "\n" << std::setw(72) << "Choice: " ;
                std::cin >> choice;
                if(choice!='Y'&&choice!='y'&&choice!='U'&&choice!='u'&&choice!='R'&&choice!='r'&&choice!='Z'&&choice!='z'&&choice!='a'&&choice!='A')
                    std::cout << "\n" << std::setw(76) << "Please enter a valid choice." << std::endl;
            } while (choice!='Y'&&choice!='y'&&choice!='U'&&choice!='u'&&choice!='R'&&choice!='r'&&choice!='Z'&&choice!='z'&&choice!='a'&&choice!='A');

            if(choice == 'Z'|| choice =='z')
                menu.conductDeductionMenu();

            else if(choice == 'Y'|| choice =='y')
            {
                for(const Employee_Zakat& empZakat : empZakats)
                    assignDeduction(empZakat.employeeID, 400009 ,empZakat.amount,currentDate);
                
                std::cout << "\n" << std::setw(96) << "[ Zakat is assigned to the employee successfully ]" << std::endl;
            }
            else
            {

                if(choice == 'A'|| choice =='a')
                {
                    int employeeID;
                    double amount = 0;
                    std::vector<Employee_Zakat>::iterator it;
                    EmployeeManager em;
                    DepartmentManager dm;
                    Employee* employee = NULL;
                    Department* department = NULL;
                    Position* position = NULL;
                    menu.displayLogo();
                        assignDeductionHeader();
                    do
                    {
                        
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee ID        : ";
                        std::cin >> employeeID;
                        employee = em.searchEmployee(employeeID);
                        if(employee!=NULL)
                        {
                            it = std::find_if(empZakats.begin(), empZakats.end(), [employeeID](const Employee_Zakat& empZakat) {
                                return empZakat.employeeID == employeeID;
                            });
                            if(it != empZakats.end())
                                std::cout << "\n" << std::setw(89) << "The employee is already in the list. " << std::endl;
                        }
                        else
                        {
                            std::cout << std::endl << std::setw(87) << "Please enter a valid employee ID." << std::endl;
                        }
                    } while (employee==NULL || it != empZakats.end());
                                        
                    department = dm.searchDepartment(employee->departmentID);
                    position = dm.searchPosition(employee->positionID);
                    do
                    {
                        std::cout << "\n\n" << std::setw(72) << "Enter Zakat Amount (RM)  : ";
                        std::cin >> amount;
                        if(amount<0||amount>999999.99)
                            std::cout  << "\n\n" << std::setw(87)<< "Invalid amount. Please try again." << std::endl;
                    } while (amount<0||amount>999999.99);

                    empZakat.employeeID = employee->id;
                    empZakat.employeeName = employee->name;
                    empZakat.departmentName = department->departmentName;
                    empZakat.PositionName = position->positionName;
                    empZakat.amount = amount;
                    empZakats.push_back(empZakat);
                }            
                else
                {
                    int employeeID;
                    std::vector<Employee_Zakat>::iterator it;

                    do
                    {
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee ID        : ";
                        std::cin >> employeeID;
                        it = std::find_if(empZakats.begin(), empZakats.end(), [employeeID](const Employee_Zakat& empZakat) {
                            return empZakat.employeeID == employeeID;
                        });

                        if(it == empZakats.end())
                            std::cout << "\n" << std::setw(88) << "Please enter a valid employee ID in the list. " << std::endl;
                    } while (it == empZakats.end());
                
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
                            empZakats.erase(it); // Remove the element
                    }

                }
                menu.displayLogo();
                assignDeductionHeader();

                if(empZakats.empty())
                {
                    char response;
                    std::cout << "\n" << std::setw(83) << "No deduction is needed. Or Enter 'Y' to add new Zakat record:  " ;
                    std::cin >> response;
                    if(response=='Y'||response=='y')
                        assignNewZakat();
                    else
                        menu.conductDeductionMenu();
                }

                //display updated list
                std::cout << std::setw(18) << "Deduction : Zakat" << std::endl;
                std::cout << "+" << std::setfill('-') <<"-" << std::setw(152) << "+" << std::setfill(' ') << std::endl
                        << "| Employee ID | Employee Name" << std::setw(50) <<"| Department"  << std::setw(35) <<"| Position"   << std::setw(40) <<"| Deduction Amount (RM)|" << std::endl
                        << "|" << std::setfill('-') << "-" << std::setw(152) << "|" << std::setfill(' ') << std::endl;  

                for(const Employee_Zakat& empZakat : empZakats)
                        std::cout << std::left << "| " << std::setw(12) << empZakat.employeeID << "| " << std::setw(51) << empZakat.employeeName << "| "  << std::setw(35) << empZakat.departmentName << "| "  << std::setw(24) << empZakat.PositionName << "| "  << std::right << std::setw(20) << empZakat.amount << " " << "|" << std::endl;
                        
                std::cout << std::right << "+" << std::setfill('-') << "-" << std::setw(152) << "+" << std::setfill(' ') << std::endl;
            }
        }
    }
    else
    {
        menu.displayLogo();
        assignDeductionHeader();

        char confirm;
        std::cout << "\n\n" << std::setw(104) << "No previous record is found. Enter 'Y' to add new Zakat record : " << std::endl;
        std::cin >> confirm;
        if(confirm=='Y'||confirm=='y')
        {
            assignNewZakat();
        }
        else
        {
            menu.conductDeductionMenu();
        }
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    
}

void DeductionManager::assignDeduction_TaxRelief()
{
    int employeeID;
    char response;
    double amount = 0;
    Menu menu;
    EmployeeManager em;
    DateManager dateManager;
    Employee* employee = NULL;
    do
    {
        response = 'Z';
        menu.displayLogo();
        assignDeductionHeader();
        std::cout  << "\n\n"<< std::setw(72) << "Enter Employee ID             : ";
        std::cin >> employeeID;
        employee = em.searchEmployee(employeeID);
        if(employee==NULL)
        {
            std::cout << std::endl << std::setw(90) << "The employee is not found. Enter Y/y to retry: ";
            std::cin >> response;
            if(response != 'y'&& response!='Y')
                menu.conductDeductionMenu();
        }
    } while (response == 'y'||response=='Y');

    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Tax Relief Amount (RM)  : ";
        std::cin >> amount;
        if(amount<0)
            std::cout  << "\n\n" << std::setw(87)<< "Invalid amount. Please try again." << std::endl;
    } while (amount<0);

    std::string date = dateManager.getCurrentDate();

    menu.displayLogo();
    assignDeductionHeader();
     std::cout << "\n" << std::setw(80) <<  "Tax Relief Preview\n\n"
                << std::setw(41) << " " << std::setw(56) << std::setfill('*') << "*"  << std::setfill(' ') 
                << "\n\n"<< std::setw(72) << "Employee ID              : "   << employeeID << std::endl
                << "\n"<< std::setw(72) << "Total Amount(RM)         : " << amount << std::endl
                << "\n"<< std::setw(72) << "Date (YYYY/MM/DD))       : " << date << std::endl;

    char confirm;
    std::cout << "\n\n" <<std::setw(96) << "Are you sure to allocate tax relief for this employee? Enter Y/y to confirm: " ;
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        assignDeduction(employeeID,400010,amount,date);
        std::cout << "\n" <<std::setw(96) << "[ Tax Relief is allocated to the employee successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" <<std::setw(105) << "[ Tax Relief Allocation has been cancelled. No changes have been made ]" << std::endl;
    }
}