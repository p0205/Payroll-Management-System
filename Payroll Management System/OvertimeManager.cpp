#include "OvertimeManager.h"
#include <iostream>
#include <iomanip>

void computeOvertimeHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(23) << "Compute Overtime" << setw(7) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl << endl; 
}

bool checkRepeatInt(int input,std::string table,std::string column)
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

void OvertimeManager::viewOvertimeType()
{
    std::cout << std::fixed << std::setprecision(2); 
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM OVERTIME");
    sql::ResultSet* rs = ps->executeQuery();
    if (rs->next())
    {
        std::cout << std::setw(37) << "+" << std::setfill('-') << "-" << std::setw(63) << "+" << std::setfill(' ') << std::endl
                << std::setw(51) << "| Overtime ID  " << "| Overtime Type" << std::setw(25) << "| Rate" << std::setw(10) << "|" << std::endl
                << std::setw(37) << "+" << std::setfill('-') << "-" << std::setw(63) << "+" << std::setfill(' ') << std::endl
                << std::left
                << std::setw(36) << " " << "| " << std::setw(13) << rs->getInt("OvertimeID") << "| " << std::setw(31) << rs->getString("Type") << " | " << std::setw(13) << rs->getDouble("Rate") << "|" << std::endl;
        while (rs->next())
        {
            std::cout << std::setw(36) << " " << "| " << std::setw(13) << rs->getInt("OvertimeID") << "| " << std::setw(31) << rs->getString("Type") << " | " << std::setw(13) << rs->getDouble("Rate") << "|" << std::endl;
        }
        std::cout << std::right
                << std::setw(37) << "+" << std::setfill('-') << "-" << std::setw(63) << "+" << std::setfill(' ') << std::endl
                << std::endl;
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
}

double OvertimeManager::getEmpHourRate(int employeeID)
{
    double empHourRate;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT BasicSalary FROM EMPLOYEE WHERE EmployeeID = ?");
    ps->setInt(1,employeeID);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
          empHourRate = rs->getDouble("BasicSalary") / (26 * 8);
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return empHourRate;
}

Overtime* OvertimeManager::getOvertime(int overtimeID)
{
    int choice;
    bool valid;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM OVERTIME WHERE OvertimeID = ?");
    ps->setInt(1,overtimeID);
    sql::ResultSet* rs = ps->executeQuery();
    Overtime* overtime = NULL;
    if(rs->next())
    {
        overtime = new Overtime();
        overtime->overtimeID = rs->getInt("OvertimeID");
        overtime->type = rs->getString("Type");
        overtime->rate = rs->getDouble("Rate");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return overtime;
}

void OvertimeManager::computeOvertime()
{
    Menu menu;
    menu.displayLogo();
    computeOvertimeHeader();
    int employeeID, overtimeID, overtimeHours;
    double empHourRate, amount;
    std::string date;
    bool exist,valid;
    viewOvertimeType();

    std::cout << std::fixed << std::setprecision(2); 

    std::cout << "\n\n"<< std::setw(72) << "Enter Employee ID                 : ";
    std::cin >> employeeID; 
    exist = checkRepeatInt(employeeID,"EMPLOYEE","EmployeeID");
    if(!exist)
    { 
        char response;
        std::cout << std::endl << std::setw(93) << "The employee is not found. Enter Y/y to retry: ";
        std::cin >> response;
        if(response == 'Y'|| response == 'y')  
        {
            computeOvertime();
            return;
        }
        else
            menu.handleEmolumentMenu();
    }


    empHourRate = getEmpHourRate(employeeID);

    do
    {
        std::cout << "\n\n"<< std::setw(72) << "Enter Overtime ID                 : ";
        std::cin >> overtimeID; 
        exist = checkRepeatInt(overtimeID,"OVERTIME","OvertimeID");
        if(!exist)
            std::cout << std::endl << std::setw(96) << "Invalid Overtime ID. Please enter a valid OvertimeID.";
    } while (!exist);
    Overtime* overtime = getOvertime(overtimeID);
    DateManager dateManager;
    do
    {
        std::cout << "\n\n"<< std::setw(72)  << "Enter Overtime Date (YYYY/MM/DD)  : ";
        std::cin >> date;
        valid = dateManager.isValidDate(date);
        if(!valid)
            std::cout << "\n" <<std::setw(90) << "Invalid date or format. Please try again." << std::endl;
    } while (!valid);

    do
    {
        std::cout << "\n\n"<< std::setw(72) << "Enter Overtime Hours              : ";
        std::cin >> overtimeHours;
        if(overtimeHours<0)
            std::cout << "\n" <<std::setw(87) << "Invalid hours. Please try again." << std::endl;
    } while (overtimeHours<0);
    
    amount = empHourRate * overtimeHours * overtime->rate;

    menu.displayLogo();
    computeOvertimeHeader();
     std::cout << "\n" << std::setw(80) <<  "Overtime Preview\n\n"
            << std::setw(40) << " " << std::setw(56) << std::setfill('*') << "*"  << std::setfill(' ') 
            << "\n\n"<< std::setw(72)  << "Employee ID              : "   << employeeID << std::endl
            << "\n"<< std::setw(72)    << "Overtime Type            : "   << overtime->type << std::endl
            << "\n"<< std::setw(72)    << "Overtime Rate            : "   << overtime->rate << std::endl
            << "\n"<< std::setw(72)    << "Overtime Date (YY/MM/DD) : "  << date << std::endl
            << "\n"<< std::setw(72)    << "Employee Hour Rate       : " << empHourRate << std::endl
            << "\n"<< std::setw(72)    << "Overtime Hours           : " << overtimeHours << std::endl 
            << "\n"<< std::setw(72)    << "Total Amount(RM)         : " << amount << std::endl;

    char confirm;
    std::cout << "\n\n" <<std::setw(96) << "Are you sure to add overtime for this employee? Enter Y/y to confirm: " ;
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        assignOvertime(employeeID,overtimeID,empHourRate,overtimeHours,amount,date);
        std::cout << "\n" <<std::setw(96) << "[ Overtime is assigned to the employee successfully ]" << std::endl;

    }
    else
    {
        std::cout << "\n" <<std::setw(105) << "[ Overtime Assignment has been cancelled. No changes have been made ]" << std::endl;
    }
}

void OvertimeManager::assignOvertime(int employeeID,int overtimeID,double employeeHourRate,int overtimeHours,double amount,std::string date)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO EMPLOYEE_OVERTIME(EmployeeID,OvertimeID,EmployeeHourRate,OvertimeHours,Amount,Date) VALUES (?,?,?,?,?,?)");
    ps->setInt(1,employeeID);
    ps->setInt(2,overtimeID);
    ps->setDouble(3,employeeHourRate);
    ps->setInt(4,overtimeHours);
    ps->setDouble(5,amount);
    ps->setString(6,date);
    ps->executeUpdate();
    ps->close();
    delete ps;
}

Employee_Overtime* OvertimeManager::getEmployeeOvertimes(int employeeID,int year,int month)
{
    Employee_Overtime* head = NULL;
    Employee_Overtime* empOvertime = NULL;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT OvertimeID,Amount,`Date` FROM EMPLOYEE_OVERTIME WHERE EmployeeID = ? AND YEAR(Date) = ? AND MONTH(Date) = ?");

    ps->setInt(1,employeeID);
    ps->setInt(2,year);
    ps->setInt(3,month);
    
    sql::ResultSet* rs = ps->executeQuery();

    while(rs->next())
    {
        if(head == NULL)
        {
            empOvertime = new Employee_Overtime();
            head = empOvertime;
        }
        else
        {
            empOvertime->next = new Employee_Overtime();
            empOvertime = empOvertime->next;
        }
        empOvertime->overtimeID = rs->getInt("OvertimeID");
        empOvertime->amount = rs->getDouble("Amount");
        empOvertime->date = rs->getString("Date");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}
