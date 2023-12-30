#include "EmployeeManager.h"
#include <iostream>
#include <cstdlib> 
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>
using namespace std;

void addEmployeeHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(21) << "Add Employee" << setw(9) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl << endl; 
}

void deleteEmployeeHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(23) << "Delete Employee" << setw(7) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

void searchEmployeeHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(23) << "Search Employee" << setw(7) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

void viewEmployeeHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(21) << "View Employee" << setw(9) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

void updateEmployeeHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(23) << "Update Employee" << setw(7) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

int EmployeeManager::IDorName()
{
    bool valid = false;
    int choice;
        cout << setw(48) << "+" << setfill('-') << "-" <<setw(43) << "+" << setfill(' ') << endl;
        cout << setw(48) << "|" << left << setw(8) << " " <<setw(35) <<  "    Choose how to search :  "  <<  "|"<< endl;
        cout << right << setw(48) << "|" << setfill('-') << "-" <<setw(43) << "|" << setfill(' ') << endl;
        cout << right << setw(48) << "|" << setw(44) << "|" << endl;
        cout << right << setw(48) << "|" << left << setw(11) << " " <<setw(32) <<  "   1.   By ID "  <<  "|"<< endl;
        cout << right << setw(48) << "|" << setw(44) << "|" << endl;
        cout << right << setw(48) << "|" << left << setw(11) << " " <<setw(32) <<  "   2.   By Name"    <<  "|"<< endl;
        cout << right << setw(48) << "|" << setw(44) << "|" << endl;
        cout << right << setw(48) << "+" << setfill('-') << "-" <<setw(43) << "+" << setfill(' ') << endl;
        do
        {
            cout << endl << setw (70) <<  "Choice: ";
            cin >> choice;
            if(choice==1 || choice==2)
            {
                valid = true;
            }
            else
            {   
                valid = false;
                cout << endl << setw(87) << "Invalid choice. Please try again." << endl;
            }
        } while (!valid);
    return choice; 
}

void EmployeeManager::EmployeeTransform(sql::ResultSet* rs,Employee * employee)
{
    employee->id = rs->getInt("EmployeeID");
    employee->name = rs->getString("Name");
    employee->gender  = rs->getString("Gender")[0];
    employee->contactNo = rs->getString("ContactNo");
    employee->address = rs->getString("Address");
    employee->dateOfHire = rs->getString("DateOfHire");
    employee->departmentID = rs->getInt("DepartmentID");
    employee->positionID = rs -> getInt("PositionID");
    employee->email = rs->getString("Email");
    employee->basicSalary = rs->getDouble("BasicSalary");
    employee->dateofBirth = rs->getString("DateOfBirth");
    employee->isDisabled = rs->getBoolean("IsDisabled");
    employee->isResident = rs->getBoolean("IsResident");
    employee->maritalStatus = rs->getString("MaritalStatus");
    employee->WorkerType = rs->getString("WorkerType");
}

bool EmployeeManager::isEmployeeInList(Employee* head, int targetID) 
{
    while (head != nullptr) {
        if (head->id == targetID) {
            return true; // Employee ID already exists in the list
        }
        head = head->next;
    }
    return false; // Employee ID not found in the list
}

bool EmployeeManager::isEmployeeInList(Employee* head, const std::string& targetName) 
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

bool EmployeeManager::checkRepeatString(string input,string table,string column)
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

bool EmployeeManager::checkRepeatInt(int input,string table,string column)
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

void EmployeeManager::addEmployee()
{
    Menu menu;
    DateManager dateManager;
    menu.displayLogo();
    addEmployeeHeader();
    bool repeat = false;
    bool valid = true;
    int strlength;
    char response;
    Employee* employee = new Employee();

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    do
    {
        cout  << "\n\n"<< setw(72) << "Enter Name                       : ";
        getline(cin,employee->name);
        strlength = employee->name.length();
        if(strlength>50)
        {
            cout << "\n\n"<<setw(85) << "The name is too long. Please use a shorter name." << endl;
        }
    }while(strlength>50);

    do{
        cout << "\n\n"<< setw(72) << "Enter Gender (F/M)               : ";
        cin >> employee->gender;
        if(employee->gender!='F'&& employee->gender!='M'&& employee->gender!='f'&& employee->gender!='m')
            cout << "\n\n"<<setw(96) << "Invalid input. Please enter 'F' for female OR 'M' for male." << endl;
        if(employee->gender=='f'|| employee->gender=='m')
            employee->gender = toupper(employee->gender);
    }while(employee->gender!='F'&& employee->gender!='M'&& employee->gender!='f'&& employee->gender!='m' );

    do
    {
    cout<< "\n\n"<< setw(72)  << "Enter Date of Birth (YYYY/MM/DD) : ";
    cin >> employee->dateofBirth;
    valid = dateManager.isValidDate(employee->dateofBirth);
    if(!valid)
        cout << "\n\n" << setw(78) << "Invalid date or format. Please try again." << endl;
    } while (!valid);

    
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    do
    {
        cout << "\n\n"<< setw(72) << "Enter Address                    : ";
        getline(cin,employee->address);
        strlength = employee->address.length();
        if(strlength>150)
        {
            cout << "\n\n"<<setw(88) << "The address is too long. Please use a shorter name." << endl;
        }
    }while(strlength>150);

    do
    {
        cout << "\n\n"<< setw(72) << "Enter Contact Number             : " ;
        cin >> employee->contactNo;
        repeat = checkRepeatString(employee->contactNo,"EMPLOYEE","ContactNo");
        strlength = employee->contactNo.length();
        if(repeat)
        {
            cout << "\n\n" <<setw(108) << "This contact number already exists. Please use another contact number. " << endl;
        }
        if(strlength>15)
        {
            cout << "\n\n" << setw(99) << "The contact number is too long. Please enter a shorter number." << endl;
        }
    }while(repeat || strlength>15);

    do
    {
        cout << "\n\n"<< setw(72) << "Enter Email                      : " ;
        cin >> employee->email;
        repeat = checkRepeatString(employee->email,"EMPLOYEE","Email");
        strlength = employee->email.length();
        if(repeat)
        {
            cout << "\n\n" <<setw(99) << "This email already exists. Please use another contact number. " << endl;
        }
        if(strlength>50)
        {
            cout << "\n\n" << setw(90) << "The email is too long. Please enter a shorter number." << endl;
        }
    }while(repeat || strlength>50);



    cout << "\n\n" << right << setw(84) <<  "------ Marital Status -------" << endl;
    cout << "\n" << left << setw(63) << " " << "S : Single" << endl;
    cout << left << setw(63) << " " << "M : Married" << endl;
    cout << left << setw(63) << " " << "D : Divorced" << endl;
    cout << left << setw(63) << " " << "W : Widowed" << endl << right;

    do{
        cout  << "\n"<< setw(72)  <<"Enter Marital Status (S/M/D/W)   : ";
        cin >> employee->maritalStatus;
        if(employee->maritalStatus!="S"&&employee->maritalStatus!="s"&&employee->maritalStatus!="M"&&employee->maritalStatus!="m"&&employee->maritalStatus!="D"&&employee->maritalStatus!="d"&&employee->maritalStatus!="W"&&employee->maritalStatus!="w")
            cout << "\n" << setw(93) << "Invalid input. Please enter (S/M/D/W). " << endl;
    } while(employee->maritalStatus!="S"&&employee->maritalStatus!="s"&&employee->maritalStatus!="M"&&employee->maritalStatus!="m"&&employee->maritalStatus!="D"&&employee->maritalStatus!="d"&&employee->maritalStatus!="W"&&employee->maritalStatus!="w");
    
    if(employee->maritalStatus=="S"||employee->maritalStatus=="s")
        employee->maritalStatus = "Single";
    else if(employee->maritalStatus=="M"||employee->maritalStatus=="m")
        employee->maritalStatus = "Married";
    else if(employee->maritalStatus=="D"||employee->maritalStatus=="d")
        employee->maritalStatus = "Divorced";
    else
        employee->maritalStatus = "Widowed";

    do
    {
        cout  << "\n\n"<< setw(72) << "Is Disabled ? (Y/N)              : ";
        cin >> response;
        if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
            cout << "\n" << setw(97) << "Please enter 'Y' if disabled OR 'N' if not disabled. " << endl;
    } while (response!='Y'&&response!='y'&&response!='N'&&response!='n');

    if(response=='Y'||response=='y')
        employee->isDisabled = 1;
    else
        employee->isDisabled = 0;

    do
    {
        cout  << "\n\n"<< setw(72) << "Is Resident ? (Y/N)              : ";
        cin >> response;
        if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
            cout << "\n" << setw(97) << "Please enter 'Y' for resident OR 'N' for non resident. " << endl;
    } while (response!='Y'&&response!='y'&&response!='N'&&response!='n');

    if(response=='Y'||response=='y')
        employee->isResident = 1;
    else
        employee->isResident = 0;
    
    cout << "\n\n" << right << setw(84) <<  "------ Worker Type -------" << endl;
    cout << "\n" << left << setw(52) << " " << "N : Normal" << endl;
    cout << left << setw(52) << " " << "R : Returning Expert Program" << endl;
    cout << left << setw(52) << " " << "K : Knowledge Worker At Specific Region" << endl;
    cout << left << setw(52) << " " << "C : Hold position of C-Suite" << endl << right;
    do{
        cout  << "\n"<< setw(72) << "Enter Worker Type (N/R/K/C)      : ";
        cin >> employee->WorkerType;
        if(employee->WorkerType!="N"&&employee->WorkerType!="n"&&employee->WorkerType!="K"&&employee->WorkerType!="k"&&employee->WorkerType!="R"&&employee->WorkerType!="r"&&employee->WorkerType!="C"&&employee->WorkerType!="c")
            cout << "\n" << setw(93) << "Invalid input. Please enter (N/R/K/C). " << endl;
    } while(employee->WorkerType!="N"&&employee->WorkerType!="n"&&employee->WorkerType!="K"&&employee->WorkerType!="k"&&employee->WorkerType!="R"&&employee->WorkerType!="r"&&employee->WorkerType!="C"&&employee->WorkerType!="c");
    
    if(employee->WorkerType=="N"||employee->WorkerType=="n")
        employee->WorkerType = "Normal";
    else if(employee->WorkerType=="R"||employee->WorkerType=="r")
        employee->WorkerType = "REP";
    else if(employee->WorkerType=="K"||employee->WorkerType=="k")
        employee->WorkerType = "KWASR";
    else
        employee->WorkerType = "C-Suite";


    do
    {
    cout<< "\n\n"<< setw(72) << "Enter Date of Hire (YYYY/MM/DD)  : ";
    cin >> employee->dateOfHire;
    valid = dateManager.isValidDate(employee->dateOfHire);
    if(!valid)
        cout << "\n\n" << setw(78) << "Invalid date or format. Please try again." << endl;
    } while (!valid);

    do
    {
        cout << "\n\n"<< setw(72) << "Enter Department ID              : ";
        cin >> employee->departmentID;
        repeat = checkRepeatInt(employee->departmentID,"DEPT_POSITION","DepartmentID");
        if(!repeat)
        {
            cout << "\n\n" <<setw(96) << "Invalid Department ID. Please re-enter a valid Department ID." << endl;
        }

    }while(!repeat);
    
    do
    {
    cout << "\n\n"<< setw(72) << "Enter Position ID                : ";
    cin >> employee->positionID;
        repeat = checkRepeatInt(employee->positionID,"DEPT_POSITION","PositionID");
        if(!repeat)
        {
            cout << "\n\n" <<setw(94) << "Invalid Position ID. Please re-enter a valid Position ID." << endl;
        }

    }while(!repeat);  

    do
    {
    cout << "\n\n"<< setw(72) << "Enter Basic Salary               : ";
    cin >> employee->basicSalary;
    if(employee->basicSalary<0)
    {
        cout << "\n\n" <<setw(99) << "Invalid amount. Please re-enter a valid amount." << endl;
    }

    }while(employee->basicSalary<0);  

    menu.displayLogo();
    addEmployeeHeader();
    
    cout << "\n" << setw(82) <<  "NEW Employee Preview\n\n" ;
    cout << setw(40) << " " << setw(56) << setfill('*') << "*"  << setfill(' ') ;
    cout  << "\n\n"<< setw(72) << "Name                    : " << employee->name << endl;
    cout  << "\n"<< setw(72) << "Gender                  : " << employee->gender << endl;
    cout  << "\n"<< setw(72) << "Date of Birth (YY/MM/DD): " << employee->dateofBirth << endl;
    cout  << "\n"<< setw(72) << "Address                 : " << employee->address << endl;
    cout  << "\n"<< setw(72) << "Contact Number          : " << employee->contactNo << endl;   
    cout  << "\n"<< setw(72) << "Is Resident             : " ;
            if(employee->isResident == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;  

    cout  << "\n"<< setw(72) << "Is Disabled             : ";  
            if(employee->isDisabled == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;  

    cout  << "\n" << setw(72) << "Marital Status          : " << employee->maritalStatus << endl;   
    cout  << "\n" << setw(72) << "Worker Type             : " << employee->WorkerType << endl;   
    cout  << "\n" << setw(72) << "Date of Hire (YY/MM/DD) : " << employee->dateOfHire << endl;
    cout  << "\n" << setw(72) << "Department ID           : " << employee->departmentID << endl;
    cout  << "\n" << setw(72) << "Position ID             : " << employee->positionID << endl;
    cout  << "\n" << setw(72) << "Basic Salary            : " << employee->basicSalary << endl;

    char confirm;
    cout << "\n\n" << setw(96) << "Are you sure to add this employee? Enter Y/y to confirm: " ;
    cin >> confirm;

    if(confirm != 'Y'&& confirm !='y')
    {
        cout << "\n" << setw(100) << "[ Addition process has been cancelled. No changes have been made ]" << endl;
        delete employee;
        return;
    }

    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO EMPLOYEE (Name,Gender,Address,ContactNo,Email,DateOfHire,DepartmentID,PositionID,DateOfBirth,isResident,isDisabled,MaritalStatus,WorkerType,BasicSalary) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
    ps->setString(1,employee->name);
    string genderString(1, employee->gender);
    ps->setString(2, genderString);
    ps->setString(3, employee->address);
    ps->setString(4, employee->contactNo);
    ps->setString(5, employee->email);
    ps->setString(6, employee->dateOfHire);
    ps->setInt(7, employee->departmentID);
    ps->setInt(8, employee->positionID);
    ps->setString(9,employee->dateofBirth);
    ps->setBoolean(10,employee->isResident);
    ps->setBoolean(11,employee->isDisabled);
    ps->setString(12,employee->maritalStatus);
    ps->setString(13,employee->WorkerType);
    ps->setDouble(14,employee->basicSalary);
    ps->executeUpdate();
    std::cout << "\n" << std::setw(88) << "[ New Employee is added successfully ]" << std::endl;
    //get lastest inserted row id
    int ID;
    sql::ResultSet* rs = (dbConn.prepareStatement("SELECT LAST_INSERT_ID()"))->executeQuery();
    if(rs->next())
        ID = rs->getInt(1);
    rs->close();
    ps->close();
    delete rs;
    delete ps;

    //add allowance
    AllowanceManager am;
    char choice;
    std::cout << "\n\n" << std::setw(94) << "Enter 'Y' to allocate allowance to this employee: " ;
    std::cin >> choice;
    if(choice=='Y'||choice=='y')
    {
        Employee* newEmployee = searchEmployee(ID);
        am.allocateAllowanceToNewEmp(newEmployee);
    }
    delete employee;
}

void EmployeeManager::deleteEmployee(Employee * employee)
{
    char choice;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM EMPLOYEE WHERE EmployeeID = ?");
    ps->setInt(1,employee->id);
    cout << endl << setw(96) <<  "Are you sure to delete this employee? Enter Y/y to delete: ";
    cin >> choice;
    if(choice=='Y'||choice=='y')
    {
        ps->executeUpdate();
        cout << endl << setw(90) << "[ The employee is deleted successfully ]" << endl;
    }
    else
    {
        cout << endl << setw(104) << "[ Deletion process has been cancelled. No changes have been made ]";        
    }
    ps->close();
    delete ps;
}

void EmployeeManager::deleteEmployee()
{
    DatabaseConnection dbConn;
    Menu menu;
    menu.displayLogo();
    deleteEmployeeHeader();
    int choice = IDorName();
    char response;
    menu.displayLogo();
    deleteEmployeeHeader();
    Employee* employee = nullptr;
    if(choice==1)
    {
        int employeeID;
        do
        {
            response = 'Z';
            menu.displayLogo();
            deleteEmployeeHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Employee ID              : ";
            cin >> employeeID;
            employee = searchEmployee(employeeID);
            if(employee==NULL)
            {
                cout << endl << setw(90) << "The employee is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.employeeMenu();
            }
        } while (response == 'y'||response=='Y');    
    }

    if(choice==2)
    {      
        string name;
        do
        { 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');   
            response = 'Z';
            menu.displayLogo();
            deleteEmployeeHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Employee Name            : ";
            getline(cin,name);
            employee = searchEmployee(name);
            if(employee==NULL)
            {
                cout << endl << setw(90) << "The employee is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.employeeMenu();
            }
        } while (response == 'y'||response=='Y');
    }

    if(employee!=nullptr)
    {
        menu.displayLogo();
        deleteEmployeeHeader();
        viewEmployee(employee);
        deleteEmployee(employee);
    }
}

Employee* EmployeeManager::searchEmployee(int id)
{
    DatabaseConnection dbConn;
    Employee* employee = nullptr;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE WHERE EmployeeID = ?");
    ps->setInt(1,id);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        employee = new Employee();
        EmployeeTransform(rs,employee);
    } 
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return employee;
}

Employee* EmployeeManager::searchEmployee(string name)
{
    DatabaseConnection dbConn;
    Employee* employee = nullptr;
    Employee* head = nullptr;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE WHERE Name = ?");
    ps->setString(1,name);
    sql::ResultSet* rs = ps->executeQuery();

    while(rs->next())
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
        EmployeeTransform(rs,employee);
    }

    Employee* curr = head;

    if(curr!= nullptr && curr->next!=nullptr)
    {   
        Department* department = nullptr;
        Position* position = nullptr;
        int i = 1;
        while(curr!=NULL)
        {
            DepartmentManager dm;
            department = dm.searchDepartment(curr->departmentID);
            position = dm.searchPosition(curr->positionID);
            cout << "\n\n"<< setw(73) <<  "Employee "<< i << endl;  
            cout << setw(42) << " " << setw(56) << setfill('*') << "*"  << setfill(' ') << endl << endl;
            cout << setw(72) << "Id                  : " << curr->id << endl;
            cout << "\n" << setw(72) << "Name                : " << curr->name << endl;
            cout << "\n" << setw(72) << "Department          : " << department->departmentName <<endl;
            cout << "\n" << setw(72) << "Position            : " << position->positionName << endl; 
            curr = curr->next;
            i++;
        }
        do
        {
            curr = head;
            int employeeID;
            cout << "\n\n"<< setw(72)<< "Enter Employee ID you want to choose  : ";
            cin >> employeeID;
            i = 1;
            while(curr!=nullptr)
            {
                if(curr->id!=employeeID)
                    curr = curr->next;
                else
                    break;
            }
            if(curr==nullptr)
                cout << endl << setw(93) << "Please enter the employee ID in the list.";
        }while(curr==nullptr);
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return curr;
}

Employee* EmployeeManager::searchEmployees()
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE");
    sql::ResultSet* rs = ps->executeQuery();
    Employee* employee = NULL;
    Employee* head = NULL;
    while(rs->next())
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
        EmployeeTransform(rs,employee);
    } 
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

void EmployeeManager::viewEmployee(Employee * employee )
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT d.DepartmentName , p.PositionName FROM EMPLOYEE e JOIN DEPARTMENT d USING(DepartmentID) JOIN POSITION p USING(PositionID) WHERE EmployeeID = ?");
    ps->setInt(1,employee->id);
    sql::ResultSet* rs = ps->executeQuery();
    string departmentName,positionName;
    if(rs->next())
    {
        departmentName = rs->getString("DepartmentName");
        positionName = rs->getString("PositionName");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;

    cout << setw(81) <<  "Employee Information\n" ;
    cout << setw(42) << " " << setw(56) << setfill('*') << "*"  << setfill(' ') << endl << endl;
    cout << setw(72) << "Id                  : " << employee->id << endl;
    cout << "\n" << setw(72) << "Name                : " << employee->name << endl;
    cout << "\n" << setw(72) << "Gender              : " << employee->gender << endl;
    cout << "\n" << setw(72) << "Date Of Birth       : " << employee->dateofBirth << endl;
    cout << "\n" << setw(72) << "Contact Number      : " << employee->contactNo << endl;
    cout << "\n" << setw(72) << "Address             : " << employee->address << endl;
    cout << "\n" << setw(72) << "Email               : " << employee->email << endl;
    cout  << "\n"<< setw(72) << "Is Resident         : " ;
            if(employee->isResident == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;  

    cout  << "\n"<< setw(72) << "Is Disabled         : ";  
            if(employee->isDisabled == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;  

    cout  << "\n"<< setw(72) << "Marital Status      : " << employee->maritalStatus << endl;   
    cout  << "\n"<< setw(72) << "Worker Type         : " << employee->WorkerType << endl;   
    cout << "\n" << setw(72) << "Date Of Hire        : " << employee->dateOfHire << endl;
    cout << "\n" << setw(72) << "Department          : " << departmentName <<endl;
    cout << "\n" << setw(72) << "Position            : " << positionName << endl; 
}

void EmployeeManager::viewEmployee()
{
    Menu menu;
    menu.displayLogo();
    searchEmployeeHeader();
    Employee * employee = NULL;
    cout << "\n\n";
    int choice = IDorName();
    char response;
    if(choice==1)
    {
        int employeeID;
        do
        {
            response = 'Z';
            menu.displayLogo();
            searchEmployeeHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Employee ID              : ";
            cin >> employeeID;
            employee = searchEmployee(employeeID);
            if(employee==NULL)
            {
                cout << endl << setw(90) << "The employee is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.employeeMenu();
            }
        } while (response == 'y'||response=='Y');    
    }

    if(choice==2)
    {      
        string name;
        do
        { 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');   
            response = 'Z';
            menu.displayLogo();
            searchEmployeeHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Employee Name            : ";
            getline(cin,name);
            employee = searchEmployee(name);
            if(employee==NULL)
            {
                cout << endl << setw(90) << "The employee is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.employeeMenu();
            }
        } while (response == 'y'||response=='Y');
    }

    if(employee!=NULL)
    {
        menu.displayLogo();
        searchEmployeeHeader();
        viewEmployee(employee);
    }
}

int EmployeeManager::updateEmployeeMenu()
{
    int choice;
    cout << setw(90) << "Which information you want to update?\n\n";
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "------ Type of Information -------" << setw(8) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(24) << "1. Name" << setw(26)<< "|" << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(26) << "2. Gender" << setw(24) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(27) << "3. Address" << setw(23) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) << "4. Date Of Birth" << setw(17) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(34) << "5. Contact Number" << setw(16) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(25) << "6. Email" << setw(25) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(31) << "7. Is Resident" << setw(19) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(34) << "8. Marital Status" << setw(16) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(31) << "9. Is Disabled" << setw(19) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(31) << "10. Worker Type" << setw(19) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(32) << "11. Date Of Hire" << setw(18)<< "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) << "12. Department ID" << setw(17)<< "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(31) << "13. Position ID" << setw(19)<< "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7&&choice!=8&&choice!=9&&choice!=10&&choice!=11&&choice!=12&&choice!=13)
        {
            cout << endl << setw(76) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7&&choice!=8&&choice!=9&&choice!=10&&choice!=11&&choice!=12&&choice!=13);
    return choice;
}

void EmployeeManager::updateEmployee(string column, int data, int employeeID)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE EMPLOYEE SET "+ column + "= ? WHERE EmployeeID = ?");
    char confirm;
    cout << "\n\n" << setw(94) << "Are you sure to update? Enter Y/y to confirm: " ;
    cin >> confirm;
    ps->setInt(1,data);
    ps->setInt(2,employeeID);
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->executeUpdate();
        cout << "\n" << setw(93) << "[ Employee Information is updated successfully ]" << endl;
    }  
    else
    {
        cout << "\n" << setw(102) << "[ Update process has been cancelled. No changes have been made ]" << endl;
    }      
    ps->close();
    delete ps;
}

void EmployeeManager::updateEmployee(string column, string data, int employeeID)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE EMPLOYEE SET "+ column + "= ? WHERE EmployeeID = ?");
    char confirm;
    cout << "\n\n" << setw(94) << "Are you sure to update? Enter Y/y to confirm: " ;
    cin >> confirm;
    ps->setString(1,data);
    ps->setInt(2,employeeID);
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->executeUpdate();
        cout << "\n" << setw(93) << "[ Employee Information is updated successfully ]" << endl;
    }  
    else
    {
        cout << "\n" << setw(102) << "[ Update process has been cancelled. No changes have been made ]" << endl;
    }      
    ps->close();
    delete ps;
}

void EmployeeManager::updateEmployee(string column, char data, int employeeID)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE EMPLOYEE SET "+ column + "= ? WHERE EmployeeID = ?");
    char confirm;
    cout << "\n\n" << setw(94) << "Are you sure to update? Enter 'Y' to confirm : " ;
    cin >> confirm;
    std::string charAsString(1,data);
    ps->setString(1,charAsString);
    ps->setInt(2,employeeID);
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->executeUpdate();
        cout << "\n" << setw(93) << "[ Employee Information is updated successfully ]" << endl;
    }  
    else
    {
        cout << "\n" << setw(102) << "[ Update process has been cancelled. No changes have been made ]" << endl;
    }      
    ps->close();
    delete ps;
}

void EmployeeManager::updateEmployee(Employee* employee)
{
    Menu menu;
    DateManager dateManager;
    bool repeat = false, valid = false;
    int strlength,positionID,departmentID;
    menu.displayLogo();
    updateEmployeeHeader();
    int choice = updateEmployeeMenu();
    menu.displayLogo();
    updateEmployeeHeader();
    string name,genderString,address, email, dateOfBirth,contactNo,dateOfHire,maritalStatus,workerType;
    char gender,response;
    int isDisabled,isResident;
    switch (choice)
    {
        case 1://name
            do
            {

                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout  << "\n\n"<< setw(72)  <<"Enter Name                       : ";
                getline(cin,name);
                strlength = name.length();
                if(strlength>50)
                {
                    cout << "\n\n"<<setw(85) << "The name is too long. Please use a shorter name." << endl;
                }
            }while(strlength>50);
            updateEmployee("Name",name,employee->id);
            break;

        case 2://gender
            do{
                cout << "\n\n"<< setw(72) << "Enter Gender (F/M)               : ";
                cin >> employee->gender;
                if(employee->gender!='F'&& employee->gender!='M'&& employee->gender!='f'&& employee->gender!='m')
                    cout << "\n\n"<<setw(96) << "Invalid input. Please enter 'F' for female OR 'M' for male." << endl;
                if(employee->gender=='f'|| employee->gender=='m')
                    employee->gender = toupper(employee->gender);
            }while(employee->gender!='F'&& employee->gender!='M'&& employee->gender!='f'&& employee->gender!='m' );
            updateEmployee("Gender",gender,employee->id);
            break;

        case 3://address
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            do
            {
                cout << "\n\n"<< setw(72) << "Enter Address                    : ";
                getline(cin,address);
                strlength = address.length();
                if(strlength>150)
                {
                    cout << "\n\n"<<setw(88) << "The address is too long. Please use a shorter name." << endl;
                }
            }while(strlength>150);
            updateEmployee("Address",address,employee->id);
            break;
        
        case 4://DoB
            do
            {
            cout<< "\n\n"<< setw(72)  << "Enter Date of Birth (YYYY/MM/DD)  : ";
            cin >> dateOfBirth;
            valid = dateManager.isValidDate(dateOfBirth);
            if(!valid)
                cout << "\n\n" << setw(78) << "Invalid date or format. Please try again." << endl;
            } while (!valid);
            updateEmployee("DateOfBirth",dateOfBirth,employee->id);
            break;

        case 5://contactNo
            do
            {
                cout << "\n\n"<< setw(72) << "Enter Contact Number             : " ;
                cin >> contactNo;
                repeat = checkRepeatString(contactNo,"EMPLOYEE","ContactNo");
                strlength = contactNo.length();
                if(repeat)
                {
                    cout << "\n\n" <<setw(108) << "This contact number already exists. Please use another contact number. " << endl;
                }
                if(strlength>15)
                {
                    cout << "\n\n" << setw(99) << "The contact number is too long. Please enter a shorter number." << endl;
                }
            }while(repeat || strlength>15);
            updateEmployee("ContactNo",contactNo,employee->id);
            break;

        case 6://email
            do
            {
                cout << "\n\n"<< setw(72) << "Enter Email                      : " ;
                cin >> email;
                repeat = checkRepeatString(email,"EMPLOYEE","Email");
                strlength = email.length();
                if(repeat)
                {
                    cout << "\n\n" <<setw(99) << "This email already exists. Please use another contact number. " << endl;
                }
                if(strlength>50)
                {
                    cout << "\n\n" << setw(90) << "The email is too long. Please enter a shorter number." << endl;
                }
            }while(repeat || strlength>50);
            updateEmployee("Email",email,employee->id);
            break;

        case 7: //isResident
            do
            {
                cout  << "\n\n"<< setw(72)  <<"Is Resident ? (Y/N)  : ";
                cin >> response;
                if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
                    cout << "\n" << setw(97) << "Please enter 'Y' for resident OR 'N' for non resident. " << endl;
            } while (response!='Y'&&response!='y'&&response!='N'&&response!='n');

            if(response=='Y'||response=='y')
                isResident = 1;
            else
                isResident = 0;
            updateEmployee("IsResident",isResident,employee->id);
            break;

        case 8: //maritalStatus
            cout << "\n\n" << right << setw(84) <<  "------ Marital Status -------" << endl;
            cout << "\n" << left << setw(63) << " " << "S : Single" << endl;
            cout << left << setw(63) << " " << "M : Married" << endl;
            cout << left << setw(63) << " " << "D : Divorced" << endl;
            cout << left << setw(63) << " " << "W : Widowed" << endl << right;
            do{
                cout  << "\n"<< setw(72)  <<"Enter Marital Status (S/M/D/W)  : ";
                cin >> maritalStatus;
                if(maritalStatus!="S"&&maritalStatus!="s"&&maritalStatus!="M"&&maritalStatus!="m"&&maritalStatus!="D"&&maritalStatus!="d"&&maritalStatus!="W"&&maritalStatus!="w")
                    cout << "\n" << setw(93) << "Invalid input. Please enter (S/M/D/W). " << endl;
            } while(maritalStatus!="S"&&maritalStatus!="s"&&maritalStatus!="M"&&maritalStatus!="m"&&maritalStatus!="D"&&maritalStatus!="d"&&maritalStatus!="W"&&maritalStatus!="w");
            
            if(maritalStatus=="S"||maritalStatus=="s")
                maritalStatus = "Single";
            else if(maritalStatus=="M"||maritalStatus=="m")
                maritalStatus = "Married";
            else if(maritalStatus=="D"||maritalStatus=="d")
                maritalStatus = "Divorced";
            else
                maritalStatus = "Widowed";
            updateEmployee("MaritalStatus",maritalStatus,employee->id);
            break;

        case 9: //isDisabled
            do
            {

                cout  << "\n\n"<< setw(72)  <<"Is Disabled ? (Y/N)  : ";
                cin >> response;
                if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
                    cout << "\n" << setw(97) << "Please enter 'Y' if disabled OR 'N' if not disabled. " << endl;
            } while (response!='Y'&&response!='y'&&response!='N'&&response!='n');

            if(response=='Y'||response=='y')
                isDisabled = 1;
            else
                isDisabled = 0;
            updateEmployee("IsDisabled",isDisabled,employee->id);
            break;

        case 10: //workerType
            cout << "\n\n" << right << setw(84) <<  "------ Worker Type -------" << endl;
            cout << "\n" << left << setw(52) << " " << "N : Normal" << endl;
            cout << left << setw(52) << " " << "R : Returning Expert Program" << endl;
            cout << left << setw(52) << " " << "K : Knowledge Worker At Specific Region" << endl;
            cout << left << setw(52) << " " << "C : Hold position of C-Suite" << endl << right;
            do{
                cout  << "\n"<< setw(72)  <<"Enter Worker Type (N/R/K/C) : ";
                cin >> workerType;
                if(workerType!="N"&&workerType!="n"&&workerType!="K"&&workerType!="k"&&workerType!="R"&&workerType!="r"&&workerType!="C"&&workerType!="c")
                    cout << "\n" << setw(93) << "Invalid input. Please enter (N/R/K/C). " << endl;
            } while(workerType!="N"&&workerType!="n"&&workerType!="K"&&workerType!="k"&&workerType!="R"&&workerType!="r"&&workerType!="C"&&workerType!="c");
            
            if(workerType=="N"||workerType=="n")
                workerType = "Normal";
            else if(workerType=="R"||workerType=="r")
                workerType = "REP";
            else if(workerType=="K"||workerType=="k")
                workerType = "KWASR";
            else
                workerType = "C-Suite";
            updateEmployee("WorkerType",workerType,employee->id);
            break;

        case 11://dateOfHire
            break;
            do
            {
            cout<< "\n\n"<< setw(72)  << "Enter Date of Hire (YYYY/MM/DD)  : ";
            cin >> dateOfHire;
            valid = dateManager.isValidDate(dateOfHire);
            if(!valid)
                cout << "\n\n" << setw(78) << "Invalid date or format. Please try again." << endl;
            } while (!valid);
            updateEmployee("DateOfHire",dateOfHire,employee->id);
            break;

        case 12://departmentID
            do
            {
                cout << "\n\n"<< setw(72) << "Enter Department ID              : ";
                cin >> departmentID;
                repeat = checkRepeatInt(departmentID,"DEPT_POSITION","DepartmentID");
                if(!repeat)
                {
                    cout << "\n\n" <<setw(96) << "Invalid Department ID. Please re-enter a valid Department ID." << endl;
                }
            }while(!repeat);
            updateEmployee("DepartmentID",departmentID,employee->id);
            break;

        case 13://positionID
            do
            {
            cout << "\n\n"<< setw(72) << "Enter Position ID                : ";
            cin >>positionID;
                repeat = checkRepeatInt(positionID,"DEPT_POSITION","PositionID");
                if(!repeat)
                {
                    cout << "\n\n" <<setw(94) << "Invalid Position ID. Please re-enter a valid Position ID." << endl;
                }
            }while(!repeat);    
            updateEmployee("PositionID",positionID,employee->id);
            break;
        default:
            break;
    }


    //ask user decision for other update
    cout << "\n\n\n" << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" <<setw(37) << "Enter 'Y' for any other update" <<setw(13) << "|"<< endl;
    cout << setw(45) << "|" <<setw(43) <<  "Press 'P' to return to Previous menu" <<setw(7) << "|"<< endl;
    cout << setw(45) << "|" <<setw(39) <<  "Press 'M' to return to Main Menu" <<setw(11) << "|"<< endl;
    cout  << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl << endl;  
    do
    {
        cout << setw(69) << "Choice: ";
        cin >> response;
        if(response!='P'&& response!='p'&& response!='M'&& response!='m'&&response != 'Y'&& response !='y')
        cout << setw(90) << "Invalid choice. Please enter a valid choice.\n" << endl;
    } while (response!='P'&& response!='p'&& response!='M'&& response!='m'&&response != 'Y'&& response !='y');

    if(response == 'Y'||response =='y')
        updateEmployee(employee);
    else if(response == 'P'||response =='p')
    {
        delete employee;
        menu.employeeMenu();
    }        
    else
    {
        delete employee;
         menu.managerMainMenu(); 
    }
}

void EmployeeManager::updateEmployee()
{
    Menu menu;
    menu.displayLogo();
    updateEmployeeHeader();
    Employee *employee = nullptr;
    DatabaseConnection dbConn;
    char response;
    bool repeat = false, valid = false;
    int strlength;
    int choice = IDorName(); 
    if(choice==1)
    {
        int employeeID;
        do
        {
            response = 'Z';
            menu.displayLogo();
            updateEmployeeHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Employee ID              : ";
            cin >> employeeID;
            employee = searchEmployee(employeeID);
            if(employee==NULL)
            {
                cout << endl << setw(90) << "The employee is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.employeeMenu();
            }
        } while (response == 'y'||response=='Y');    
    }

    if(choice==2)
    {      
        string name;
        do
        { 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');   
            response = 'Z';
            menu.displayLogo();
            updateEmployeeHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Employee Name            : ";
            getline(cin,name);
            employee = searchEmployee(name);
            if(employee==NULL)
            {
                cout << endl << setw(90) << "The employee is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.employeeMenu();
            }
        } while (response == 'y'||response=='Y');
    }
    if(employee!=nullptr)
        updateEmployee(employee);
}

int EmployeeManager::filterEmpMenu()
{
    bool valid = false;
    int choice;
    cout << setw(48) << "+" << setfill('-') << "-" <<setw(43) << "+" << setfill(' ') << endl;
    cout << setw(48) << "|" << left << setw(11) << " " <<setw(32) <<  "Choose a filter option: "  <<  "|"<< endl;
    cout << right << setw(48) << "|" << setfill('-') << "-" <<setw(43) << "|" << setfill(' ') << endl;
    cout << right << setw(48) << "|" << setw(44) << "|" << endl;
    cout << right << setw(48) << "|" << left << setw(11) << " " <<setw(32) <<  "1.   Filter By Position  "  <<  "|"<< endl;
    cout << right << setw(48) << "|" << setw(44) << "|" << endl;
    cout << right << setw(48) << "|" << left << setw(11) << " " <<setw(32) <<  "2.   Filter By Department"    <<  "|"<< endl;
    cout << right << setw(48) << "|" << setw(44) << "|" << endl;
    cout << right << setw(48) << "|" << left << setw(11) << " " <<setw(32) <<  "3.   Filter By Salary"    <<  "|"<< endl;
    cout << right << setw(48) << "|" << setw(44) << "|" << endl;
    cout << right << setw(48) << "|" << left << setw(11) << " " <<setw(32) <<  "4.   No Filter"    <<  "|"<< endl;
    cout << right << setw(48) << "|" << setw(44) << "|" << endl;
    cout << right << setw(48) << "+" << setfill('-') << "-" <<setw(43) << "+" << setfill(' ') << endl;
    do
    {
        cout << endl << setw (70) <<  "Choice: ";
        cin >> choice;
        if(choice==1 || choice==2 || choice ==3 || choice ==4)
        {
            valid = true;
        }
        else
        {   
            valid = false;
            cout << endl << setw(87) << "Invalid choice. Please try again." << endl;
        }
    } while (!valid);
    return choice; 
}

void EmployeeManager::viewEmployeeList()
{
    Menu menu;
    int choice;
    menu.displayLogo();
    viewEmployeeHeader();
    choice = filterEmpMenu(); 
    switch (choice)
    {
        case 1:
            filterPosition();
            menu.empBackToMenu();
            break;
        case 2:
            filterDepartment();
            menu.empBackToMenu();
            break;
        case 3:
            filterSalary();
            break;
        case 4:
            viewAllEmployees();
            menu.empBackToMenu();
            break;
        default:
            break;
    }
}

void EmployeeManager::filterPosition()
{   
    Menu menu;
    DatabaseConnection dbConn;
    char response;
    DepartmentManager dm;
    Position* head = dm.searchPositions();
    Position* position = NULL;
    do
    {
        menu.displayLogo();
        viewEmployeeHeader();
        response = 'Z';
        position = head;
        int positionID;
        if(position!=NULL)
        {
            cout << setw(38) << "+" << setfill('-') <<"-" << setw(64) << "+" << setfill(' ') << endl;
            cout << setw(50) << "| Position ID" << setw(19) <<"| Position Name"  << setw(34) << "|" << endl;
            cout << setw(38) << "|" << setfill('-') <<"-" <<setw(64) << "|" << setfill(' ') << endl;
            while(position!=NULL)
            {
                cout << left;
                cout << left << setw(37) << " " << "| " << setw(15) << position->positionID << "| "  << setw(45) <<position->positionName << " " << "|" << endl;
                position = position->next;
            }
            cout << right;
            cout << setw(38) << "+" << setfill('-') <<"-" << setw(64) << "+" << setfill(' ') << endl;

            cout  << "\n\n"<< setw(72)  <<"Enter Position ID       : ";
            cin >> positionID;

            position = head;
            while(position!=NULL)
            {
                if(positionID == position->positionID)
                    break;
                else
                    position = position->next;
            }
            if(position == NULL)
            {
                cout << endl << setw(92) << "The position is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                {
                    menu.employeeMenu();
                    return;
                }
            }
        }
        else
        {
            cout << setw(58) << "No position available." << endl;
            return;
        }
    }while (response == 'y'||response=='Y');      


    menu.displayLogo();
    viewEmployeeHeader();
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT e.EmployeeID,e.Name, p.PositionName,d.DepartmentName FROM EMPLOYEE e JOIN POSITION p ON e.PositionID = p.PositionID JOIN DEPARTMENT d ON e.DepartmentID = d.DepartmentID WHERE e.PositionID = ?");
    ps->setInt(1,position->positionID);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        cout  << setw(30) << "Filter By: Position" << endl;
        cout  << setw(11)<< "+" << setfill('-') <<"-" <<setw(133) << "+" << setfill(' ') << endl;
        cout  << setw(24) << "| Employee ID " << "| Name" << setw(58) <<"| Position"  << setw(35) <<"| Department" << setw(22) << "|" << endl;
        cout << setw(11) << "|" << setfill('-') <<"-" <<setw(133) << "|" << setfill(' ') << endl;
        cout << left;
        cout  << setw(10) << " " << "| " << setw(12) << rs->getInt(1)<< "| " << setw(51)<< rs->getString(2) << " | " << setw(31) << rs->getString(3)  << "| "  << setw(30) << rs->getString(4) << " " << "|" << endl;
        while(rs->next())
        {
            cout  << setw(10) << " " << "| " << setw(12) << rs->getInt(1)<< "| " << setw(51)<< rs->getString(2) << " | " << setw(31) << rs->getString(3)  << "| "  << setw(30) << rs->getString(4) << " " << "|" << endl;
        }
        cout << right;
        cout  << setw(11)<< "+" << setfill('-') <<"-" <<setw(133) << "+" << setfill(' ') << endl;
    }
    else
    {
        cout << setw(79) << "No result is found." << endl;
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
}

void EmployeeManager::filterDepartment()
{
    Menu menu;
    DatabaseConnection dbConn;
    int departmentID;
    char response;
    DepartmentManager dm;
    Department* department = NULL;
    Department* head = dm.searchDepartments();
    do
    {
        menu.displayLogo();
        viewEmployeeHeader();
        department = head;
        response = 'Z';
        if(department!=NULL)
        {
            cout << setw(38) << "+" << setfill('-') <<"-" << setw(64) << "+" << setfill(' ') << endl;
            cout << setw(52) << "| Department ID" << setw(19) <<"| Department Name"  << setw(32) << "|" << endl;
            cout << setw(38) << "|" << setfill('-') <<"-" <<setw(64) << "|" << setfill(' ') << endl;
            while(department!=NULL)
            {
                cout << left;
                cout << left << setw(37) << " " << "| " << setw(15) << department->departmentID << "| "  << setw(45) <<department->departmentName << " " << "|" << endl;
                department = department->next;
            }
            cout << right;
            cout << setw(38) << "+" << setfill('-') <<"-" << setw(64) << "+" << setfill(' ') << endl;

            cout  << "\n\n"<< setw(72)  <<"Enter Department ID     : ";
            cin >> departmentID;

            department = head;
            while(department!=NULL)
            {
                if(departmentID == department->departmentID)
                    break;
                else
                    department = department->next;
            }
            if(department == NULL)
            {
                cout << endl << setw(94) << "The department is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                {
                    menu.employeeMenu();
                    return;
                }
            }
        }
        else
        {
            cout << setw(58) << "No department available." << endl;
            return;
        }
    }while (response == 'y'||response=='Y');      

    menu.displayLogo();
    viewEmployeeHeader();
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT e.EmployeeID,e.Name, p.PositionName,d.DepartmentName FROM EMPLOYEE e JOIN POSITION p ON e.PositionID = p.PositionID JOIN DEPARTMENT d ON e.DepartmentID = d.DepartmentID WHERE d.DepartmentID = ?");
    ps->setInt(1,department->departmentID);
    sql::ResultSet* rs = ps->executeQuery();

    if(rs->next())
    {
        cout  << setw(32) << "Filter By: Department" << endl;
        cout  << setw(11)<< "+" << setfill('-') <<"-" <<setw(133) << "+" << setfill(' ') << endl;
        cout  << setw(24) << "| Employee ID " << "| Name" << setw(60)<<"| Department"   << setw(31)<<"| Position"  << setw(24) << "|" << endl;
        cout << setw(11) << "|" << setfill('-') <<"-" <<setw(133) << "|" << setfill(' ') << endl;
        cout << left;
        cout  << setw(10) << " " << "| " << setw(12) << rs->getInt(1) << "| " << setw(51)<< rs->getString(2) << " | " << setw(31) << rs->getString(4)  << "| "  << setw(30) << rs->getString(3) << " " << "|" << endl;
        while(rs->next())
        {
            cout << left;
            cout  << setw(10) << " " << "| " << setw(12) << rs->getInt(1) << "| " << setw(51)<< rs->getString(2) << " | " << setw(31) << rs->getString(4)  << "| "  << setw(30) << rs->getString(3) << " " << "|" << endl;
        }
        cout << right;
        cout  << setw(11)<< "+" << setfill('-') <<"-" <<setw(133) << "+" << setfill(' ') << endl;
    }
    else
    {
        cout << setw(79) << "No result is found." << endl;
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
}

void EmployeeManager::filterSalary() 
{
    Menu menu;
    menu.displayLogo();
    viewEmployeeHeader();
    DatabaseConnection dbConn;
    double maxSalary,minSalary;
    std::string order;
    cout << "\n\n" << setw(84) << "Please enter Salary Range  " ;
    do
    {
        cout << "\n\n" << setw(73) << "Enter Minimum Salary(RM)    : " ;
        cin >> minSalary;
        if(minSalary<0||minSalary>99999999.99)
            cout << "\n" << setw(70) << "Invalid amount. Please try again. " ;
    } while (minSalary<0||minSalary>99999999.99);
    
    do
    {
        cout << "\n\n" << setw(73) << "Enter Maximum Salary(RM)    : " ;
        cin >> maxSalary;
        if(maxSalary<0||maxSalary>99999999.99)
            cout << "\n" << setw(70) << "Invalid amount. Please try again. " ;
    } while (maxSalary<0||maxSalary>99999999.99);

    do
    {
        cout << "\n\n" << setw(73) << "Sort the data in (ASC/DESC) : " ;
        cin >> order;
        if(order!="ASC"&&order!="DESC"&&order!="asc"&&order!="desc")
            cout << "\n" << setw(70) << "Invalid input. Please try again. " ;
        if(order=="asc"||order=="desc")
        {
            //convert lower case string to uppercase
            //transform() function from algorithm library
            //transform(beginning of the string, end of the string, toupperfunction taht convert each character to uppercase, ::toupper)
            std::transform(order.begin(),order.end(),order.begin(),::toupper);
        }
    } while (order!="ASC"&&order!="DESC"&&order!="asc"&&order!="desc");
    filterSalary(minSalary,maxSalary,order);
}

void EmployeeManager::filterSalary(double minSalary, double maxSalary, string order) //asc ,desc
{
    DatabaseConnection dbConn;
    Menu menu;
    menu.displayLogo();
    viewEmployeeHeader();
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT EmployeeID,Name,BasicSalary FROM EMPLOYEE WHERE BasicSalary >= ? AND BasicSalary <= ? ORDER BY BasicSalary "+ order);
    ps->setDouble(1,minSalary);
    ps->setDouble(2,maxSalary);
    sql::ResultSet* rs = ps->executeQuery();

    if(rs->next())
    {
        cout << right << setw(48) << "Filter By: Basic Salary ( " << left << setw(4) << order +" )" << endl;
        cout << right << setw(22)<< "+" << setfill('-') <<"-" <<setw(99) << "+" << setfill(' ') << endl;
        cout << setw(35) << "| Employee ID " << "| Name" << setw(66)<<"| Basic Salary (RM)"    << setw(15) << "|" << endl;
        cout << setw(22) << "|" << setfill('-') <<"-" <<setw(99) << "|" << setfill(' ') << endl;
        cout << left;
        cout  << setw(21) << " " << "| " << setw(12) << rs->getInt(1) << "| " << setw(51)<< rs->getString(2)  << "| "  << setw(30) << rs->getDouble(3) << " " << "|" << endl;
        while(rs->next())
        {
            cout  << setw(21) << " " << "| " << setw(12) << rs->getInt(1) << "| " << setw(51)<< rs->getString(2)  << "| "  << setw(30) << rs->getDouble(3) << " " << "|" << endl;
        }
        cout << right;
        cout  << setw(22)<< "+" << setfill('-') <<"-" <<setw(99) << "+" << setfill(' ') << endl;
    }
    else
    {
        cout << setw(79) << "No result is found." << endl;
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    cout << "\n\n\n" << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" <<setw(45) <<  "Press 'A' to sort data in ascending order" <<setw(5) << "|"<< endl;
    cout << setw(45) << "|" <<setw(46) <<  "Press 'D' to sort data in descending order" <<setw(4) << "|"<< endl;
    cout << setw(45) << "|" <<setw(40) <<  "Press 'P' to return to Previous menu" <<setw(10) << "|"<< endl;
    cout << setw(45) << "|" <<setw(36) <<  "Press 'M' to return to Main Menu" <<setw(14) << "|"<< endl;
    cout  << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl << endl;  
    char choice;
    do
    {
      cout << setw(69) << "Choice: ";
      cin >> choice;
      if(choice!='P'&& choice!='p'&& choice!='M'&& choice!='m'&&choice == 'A'&&choice =='a'&&choice == 'D'&&choice =='d')
        cout << setw(90) << "Invalid choice. Please enter a valid choice.\n" << endl;
    } while (choice!='P'&& choice!='p'&& choice!='M'&& choice!='m'&&choice == 'A'&&choice =='a'&&choice == 'D'&&choice =='d');

    if(choice == 'A'||choice =='a')
        filterSalary(minSalary,maxSalary,"ASC");
    else if(choice == 'D'||choice =='d')
        filterSalary(minSalary,maxSalary,"DESC");
    else if(choice == 'P'||choice =='p')
        menu.employeeMenu();
    else
        menu.adminMainMenu(); 
}

void EmployeeManager::viewAllEmployees()
{
    Menu menu;
    menu.displayLogo();
    viewEmployeeHeader();
    Employee* head = searchEmployees();
    Employee* employee = nullptr;
    employee = head; 
    int totalEmployee = 0;
    Department* department = nullptr;
    Position* position = nullptr;
    while (employee!=NULL)
    {
        totalEmployee++;
        employee = employee->next;
    }

    if (totalEmployee > 0)
    {
        employee = head;
        cout << setw(27) << "Total Employee: " << totalEmployee << endl; // Display total at the top
        cout << setw(11) << "+" << setfill('-') << "-" << setw(133) << "+" << setfill(' ') << endl;
        cout << setw(24) << "| Employee ID " << "| Name" << setw(60) << "| Department" << setw(31) << "| Position" << setw(24) << "|" << endl;
        cout << setw(11) << "|" << setfill('-') << "-" << setw(133) << "|" << setfill(' ') << endl;
        cout << left;
        DepartmentManager dm;
        while (employee!=NULL)
        {
            department = dm.searchDepartment(employee->departmentID);
            position =dm.searchPosition(employee->positionID);
            cout << setw(10) << " " << "| " << setw(12) << employee->id << "| " << setw(51) << employee->name << " | " << setw(31) << department->departmentName << "| " << setw(30) << position->positionName << " " << "|" << endl;
            employee = employee->next;
        }

        cout << right;
        cout << setw(11) << "+" << setfill('-') << "-" << setw(133) << "+" << setfill(' ') << endl;
    }
    else
    {
        cout << setw(79) << "No result is found." << endl;
    }
}

int EmployeeManager::getEmployeeCategory(int employeeID)
{
    DependantManager dm;
    Employee_Dependant* emp_dependant = nullptr;
    DatabaseConnection dbConn;
    Employee* employee = nullptr;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT MaritalStatus FROM EMPLOYEE WHERE EmployeeID = ?");
    ps->setInt(1,employeeID);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        emp_dependant = dm.searchDependants(employeeID);
        if(rs->getString("MaritalStatus")=="Divorced"||rs->getString("MaritalStatus")=="Widowed")//divorced
            return 3;

        else if(rs->getString("MaritalStatus")=="Single" ) //single 
        {
            if(emp_dependant == nullptr)
                return 1;
            else
            {
                while(emp_dependant!= NULL)
                {
                    if(emp_dependant->relationship == "Child")
                        return 3;
                    emp_dependant = emp_dependant->next;
                }
            }
        }
        else //married
        {
            if(emp_dependant != nullptr)
            {
                while(emp_dependant!=NULL)
                {
                    if(emp_dependant->relationship == "Spouse")
                    {
                        Dependant* dependant = dm.searchDependant(emp_dependant->dependantID);
                        if(dependant->isWorking)
                            return 3;
                        else
                            return 2;
                        break;
                    }
                    emp_dependant = emp_dependant->next;
                }

            }
    
        }

    }
    //if employee not found
    return 0;
}

int EmployeeManager::getTotalEmployees()
{
    int total = 0;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT COUNT(EmployeeID) AS `TotalEmployee` FROM EMPLOYEE");
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
        total =  rs->getInt("TotalEmployee");
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return total;   
}

int EmployeeManager::getTotalEmployeesByDepartment(int departmentID)
{
    int total = 0;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT COUNT(EmployeeID) AS `TotalEmployee` FROM EMPLOYEE WHERE DepartmentID = ?");
    ps->setInt(1,departmentID);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
        total =  rs->getInt("TotalEmployee");
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return total;   
}