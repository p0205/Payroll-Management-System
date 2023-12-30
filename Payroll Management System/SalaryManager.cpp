#include "SalaryManager.h"
#include <iomanip>
#include <sstream>
#include <ctime>
#include <fstream>
#include <filesystem>

void SalaryManager::updateBasicSalaryHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(24) << "Update Basic Salary" << setw(6) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

void SalaryManager::addSalaryScheduleHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(24) << "Add Salary Schedule" << setw(6) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

void SalaryManager::deleteSalaryScheduleHeader()
{
    std::cout << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << std::setfill(' ') << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl                           
                << std::setw(55) << "|" << std::setw(25) << "Delete Salary Schedule" << setw(5) << "|" << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl
                << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << setfill(' ') << std::endl << std::endl; 
}

void SalaryManager::printPaySlipHeader()
{
    std::cout << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << std::setfill(' ') << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl                           
                << std::setw(55) << "|" << std::setw(21) << "Print PaySlip" << setw(9) << "|" << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl
                << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << setfill(' ') << std::endl << std::endl; 
}

void SalaryManager::paySalaryHeader()
{
    std::cout << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << std::setfill(' ') << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl                           
                << std::setw(55) << "|" << std::setw(19) << "Pay Salary" << setw(11) << "|" << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl
                << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << setfill(' ') << std::endl << std::endl; 
}

void SalaryManager::producePayrollReportHeader()
{
    std::cout << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << std::setfill(' ') << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl                           
                << std::setw(55) << "|" << std::setw(26) << "Produce Payroll Report" << setw(4) << "|" << std::endl
                << std::setw(55) << "|" << std::setfill(' ') << ' ' << std::setw(29) << " |" << std::endl
                << std::setw(55) << "+" << std::setfill('-') << "-" << std::setw(29) << "+" << setfill(' ') << std::endl << std::endl; 
}

bool SalaryManager::checkRepeatInt(int input,string table,string column)
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

void SalaryManager::updateBasicSalary()
{
    Menu menu;
    DatabaseConnection dbConn;
    EmployeeManager em;
    Employee* employee = NULL;
    bool repeat;
    double basicSalary;
    int employeeID;
    char response;
    sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE EMPLOYEE SET BasicSalary = ? WHERE EmployeeID = ?");
    do
    {
        menu.displayLogo();
        updateBasicSalaryHeader();
        response = 'Z';
        std::cout  << "\n\n"<< std::setw(72) << "Enter Employee ID  : ";
        std::cin >> employeeID;
        employee = em.searchEmployee(employeeID);
        if(employee == NULL)
        {
            std::cout << std::endl << std::setw(90) << "The employee is not found. Enter Y/y to retry: ";
            std::cin >> response;
            if(response != 'y'&&response!='Y')
                menu.administerSalaryMenu();
        }
    } while (response == 'y'||response=='Y');    
    menu.displayLogo();
    updateBasicSalaryHeader();

    std::cout << "\n\n" << std::setw(82) <<  "Employee Information\n\n" 
            << std::setw(42) << " " << std::setw(56) << std::setfill('*') << "*"  <<std::setfill(' ') 
            << "\n\n"<< std::setw(72) << "Employee ID               : " << employee->id << std::endl
            << "\n\n"<< std::setw(72) << "Employee Name             : " << employee->name << std::endl
            << "\n\n"<< std::setw(72) << "Current Basic Salary (RM) : " << employee->basicSalary << std::endl;

    do
    {
        std::cout  << "\n\n"<< std::setw(72) << "Enter Updated Basic Salary (RM) : ";
        std::cin >> basicSalary;
        if(basicSalary<0 || basicSalary > 99999999.99)
        {
            std::cout << std::setw(87) <<  "Invalid amount. Please try again. " << std::endl;
        }
    } while (basicSalary<0 || basicSalary > 99999999.99);

    char confirm;
    std::cout << "\n\n" <<std::setw(103) << "Are you sure to update basic salary of this employee? Enter Y/y to confirm: ";
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->setDouble(1,basicSalary);
        ps->setInt(2,employeeID);
        ps->executeUpdate();
        std::cout << "\n" << std::setw(90) << "[ Basic Salary is updated successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" << std::setw(103) << "[ Update process has been cancelled. No changes have been made ]" << std::endl;
    }   
    ps->close();
    delete ps;
}

void SalaryManager::addSalarySchedule()
{
    Menu menu;
    DatabaseConnection dbConn;
    DateManager dateManager;
    bool valid;
    int year,month;
    std::string date;
    menu.displayLogo();
    addSalaryScheduleHeader();
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO SALARY_SCHEDULE(Year,Month,`Date`) VALUES (?,?,?)");

    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Year     : ";
        std::cin >> year;
        if(year<0)
            std::cout << "\n"<< std::setw(90) << "Invalid year. Please enter a valid year." << std::endl;
    } while (year<0);
    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter month    : " ;
        std::cin >> month;
        if(month<1||month>12)
            std::cout << "\n\n" << std::setw(92) << "Invalid month. Please enter a valid month. "  << std::endl;
    } while (month<1||month>12);

    Salary_Schedule* sc = NULL;
    sc = searchSalarySchedule(year,month);

    menu.displayLogo();
    addSalaryScheduleHeader();
    
    if(sc!=NULL)
    {
        std::cout << "\n\n" <<std::setw(88) << "[ The Salary Schedule already exists ]" << std::endl;
        return;
    }
    
    date = dateManager.getCurrentDate();

    std::cout << "\n\n" << std::setw(84) <<  "NEW Salary Schedule Preview\n\n" 
            << std::setw(42) << " " << std::setw(56) << std::setfill('*') << "*"  <<std::setfill(' ') 
            << "\n\n"<< std::setw(72) << "Year              : " << year << std::endl
            << "\n\n"<< std::setw(72) << "Month             : " << month << std::endl
            << "\n\n"<< std::setw(72) << "Date (YYYY/MM/DD) : " << date << std::endl;
    char confirm;
    std::cout << "\n\n" <<std::setw(103) << "Are you sure to add this salary schedule? Enter Y/y to confirm: ";
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->setInt(1,year);
        ps->setInt(2,month);
        ps->setString(3,date);
        ps->executeUpdate();
        std::cout << "\n" <<std::setw(90) << "[ Salary Schedule is added successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" <<std::setw(103) << "[ Addition process has been cancelled. No changes have been made ]" << std::endl;
    }   
    ps->close();
    delete ps;
    delete sc;
}

void SalaryManager::deleteSalarySchedule()
{
    Menu menu;
    DatabaseConnection dbConn;
    DateManager dateManager;
    bool valid;
    int year,month;
    menu.displayLogo();
    deleteSalaryScheduleHeader();
    sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM SALARY_SCHEDULE WHERE `Year` = ? AND Month = ?");

    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Year     : ";
        std::cin >> year;
        if(year<0)
            std::cout << "\n"<< std::setw(90) << "Invalid year. Please enter a valid year." << std::endl;
    } while (year<0);
    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter month    : " ;
        std::cin >> month;
        if(month<1||month>12)
            std::cout << "\n\n" << std::setw(92) << "Invalid month. Please enter a valid month. "  << std::endl;
    } while (month<1||month>12);

    Salary_Schedule* sc = NULL;
    sc = searchSalarySchedule(year,month);

    menu.displayLogo();
    deleteSalaryScheduleHeader();
    
    if(sc==NULL)
    {
        std::cout << "\n\n" <<std::setw(88) << "[ The Salary Schedule does not exists ]" << std::endl;
        return;
    }
    std::cout << "\n\n" << std::setw(82) <<  "Salary Schedule Preview\n\n" 
            << std::setw(42) << " " << std::setw(56) << std::setfill('*') << "*"  <<std::setfill(' ') 
            << "\n\n"<< std::setw(72) << "Year              : " << sc->year << std::endl
            << "\n\n"<< std::setw(72) << "Month             : " << sc->month << std::endl
            << "\n\n"<< std::setw(72) << "Date (YYYY/MM/DD) : " << sc->date << std::endl;
    char confirm;
    std::cout << "\n\n" <<std::setw(106) << "Are you sure to delete this salary schedule? Enter Y/y to confirm: ";
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->setInt(1,year);
        ps->setInt(2,month);
        ps->executeUpdate();
        std::cout << "\n" <<std::setw(90) << "[ Salary Schedule is deleted successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" <<std::setw(103) << "[ Deletion process has been cancelled. No changes have been made ]" << std::endl;
    }   
    ps->close();
    delete ps;
    delete sc;
}

void SalaryManager::producePayrollReport()
{
    Menu menu;
    DepartmentManager dm;
    DateManager dateManager;
    EmployeeManager em;
    Department* department = NULL;
    menu.displayLogo();
    producePayrollReportHeader();
    int year,month,departmentID;
    char filterMonth, filterDepartment;
    std::string startDate, endDate;
    bool valid = true;
    std::cout  << "\n\n" << std::setw(84) << "Select Time Range for Report" << std::endl 
                << std::setw(43) << " " << std::setw(56) << std::setfill('*') << "*"  << std::setfill(' ') << std::endl;
    do
    {
        std::cout << "\n\n" << std::setw(72) << "Start Date (YYYY/MM/DD)    : " ;
        std::cin >> startDate;
        valid = dateManager.isValidDate(startDate);
        if(!valid)
             std::cout << "\n" << std::setw(90) << "Invalid date or format. Please try again." << std::endl;
    } while (!valid);

    bool validEndDate = true;
    do
    {
        std::cout << "\n\n" << std::setw(72) << "End Date (YYYY/MM/DD)      : " ;
        std::cin >> endDate;
        valid = dateManager.isValidDate(endDate);
        validEndDate = dateManager.isValidEndDate(startDate,endDate);
        if(!valid ||!validEndDate)
            std::cout  << "\n\n" << std::setw(90)<< "Invalid date or format. Please try again." << std::endl;        
    } while (!valid||!validEndDate);


    do
    {
        std::cout  << "\n\n" <<  std::setw(72) << "Filter By Department (Y/N) : "  ;
        std::cin >> filterDepartment;
        if(filterDepartment!='Y'&&filterDepartment!='y'&&filterDepartment!='N'&&filterDepartment!='n')
            std::cout << "\n"  <<  std::setw(88) << "Invalid response. Please enter Y/N. "  << std::endl;
    } while (filterDepartment!='Y'&&filterDepartment!='y'&&filterDepartment!='N'&&filterDepartment!='n');
    
    if(filterDepartment=='Y'||filterDepartment=='y')
    {
        PayrollReportByEmployee(startDate,endDate);
    }
    else
    {
        PayrollReportByDepartment(startDate,endDate);
    }
    delete department;
}

void SalaryManager::PayrollReportByDepartment(std::string startDate, std::string endDate) //new
{
    std::cout << std::fixed << std::setprecision(2);
    EmployeeManager em;
    DateManager dateManager;
    double netSalary = 0, allowance = 0, bonus = 0, overtime = 0,deduction = 0,basicSalary = 0;
    double totalnetSalary = 0, totalAllowance = 0, totalBonus = 0, totalOvertime = 0, totalDeduction = 0, totalBasicSalary=0;
    double grandTotalNetSalary = 0, grandTotalAllowance = 0, grandTotalBonus = 0, grandTotalOvertime = 0, grandTotalDeduction = 0,grandBasicSalary=0;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT SUM(s.`BasicSalary`) AS `TotalBasicSalary`,SUM(s.TotalAllowance) AS `TotalAllowance`,SUM(s.TotalBonus) AS `TotalBonus`,SUM(s.TotalOvertime) AS `TotalOvertime`,SUM(s.TotalDeduction) AS `TotalDeduction`, SUM(s.NetSalary) AS `TotalSalary` ,d.DepartmentName, YEAR(sc.`Date`) AS `Year` ,MONTH(sc.`Date`) AS `Month` FROM SALARY s JOIN SALARY_SCHEDULE sc ON s.SalaryID = sc.SalaryID JOIN EMPLOYEE e ON s.EmployeeID = e.EmployeeID JOIN DEPARTMENT d ON e.DepartmentID = d.DepartmentID WHERE sc.`Date` BETWEEN ?  AND ? GROUP BY d.DepartmentName, YEAR(sc.`Date`),MONTH(sc.`Date`) ORDER BY d.DepartmentName,`Year`,`Month`");
    ps->setString(1,startDate);
    ps->setString(2,endDate);
    sql::ResultSet* rs = ps->executeQuery();
    Menu menu;
    menu.displayLogo();
    producePayrollReportHeader();

    if(!rs->next())
    {
        std::cout << "\n" << std::setw(81) << "No result is found. " << std::endl;
        return;
    }

    std::string filename = "SummaryByDepartment";
    filename = filename + "_" + startDate + "_" + endDate + "_" + ".txt"; 
    std::replace(filename.begin(), filename.end(), '/', '-');
    std::ofstream outputFile;
    outputFile.open("/Users/phoebekiew/Desktop/Payroll Management System /PayrollSummaryByDepartment/" + filename, std::ios::out);
    if(!outputFile.is_open())
    {
        cout << "Fail to print Payroll Summary By Department! " << std::endl;
        std::perror("Error details:");
        return;
    }

    outputFile << std::fixed << std::setprecision(2); 


    std::cout  << std::right << std::setw(1) << "+" << std::setfill('-') << "-" << std::setw(174) << "+" << std::setfill(' ') << std::endl
            << std::right << std::setw(1) << "| " << std::setw(99) <<  " Payroll Summary By Department"  << setw(75)  << "|" << std::endl
            << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl
            << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(174) << " |" << std::endl             

            << std::left
            << "| Period               : " << std::setw(10) << startDate << " - " << std::setw(137) << endDate << "| "  << std::endl
            << std::right << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(174) << " |" << std::endl                           
            << std::right << std::setw(1) << "|" << std::setfill('=') << "=" << std::setw(174) << "|" << std::setfill(' ') << std::endl
            << std::left << std::setw(53) << "| Department" << std::setw(21) << "|  Basic Salary (RM)" << "|   Allowance (RM)   " << "|     Bonus (RM)    " << "|   Overtime (RM)   " << "|   Deduction (RM)  " << "|  Net Salary (RM)  |" << std::endl; 
    outputFile  << std::right << std::setw(1) << "+" << std::setfill('-') << "-" << std::setw(174) << "+" << std::setfill(' ') << std::endl
            << std::right << std::setw(1) << "| " << std::setw(99) <<  " Payroll Summary By Department"  << setw(75)  << "|" << std::endl
            << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl
            << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(174) << " |" << std::endl             

            << std::left
            << "| Period               : " << std::setw(10) << startDate << " - " << std::setw(137) << endDate << "| "  << std::endl
            << std::right << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(174) << " |" << std::endl                           
            << std::right << std::setw(1) << "|" << std::setfill('=') << "=" << std::setw(174) << "|" << std::setfill(' ') << std::endl
            << std::left << std::setw(53) << "| Department" << std::setw(21) << "|  Basic Salary (RM)" << "|   Allowance (RM)   " << "|     Bonus (RM)    " << "|   Overtime (RM)   " << "|   Deduction (RM)  " << "|  Net Salary (RM)  |" << std::endl; 
        std::cout << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl;
        outputFile << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl;

    std::string previousDepartment ;
    std::string currentDepartment ;
    currentDepartment = rs->getString("DepartmentName");
    std::cout << std::left << "| " << std::setw(51) << rs->getString("DepartmentName") << "| " << std::setw(19) << " " << "| " << std::setw(19) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " "<< "| " << std::setw(18) << " " << "| " << std::setw(18) << " " << "| "  << std::endl;
    outputFile << std::left << "| " << std::setw(51) << rs->getString("DepartmentName") << "| " << std::setw(19) << " " << "| " << std::setw(19) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " "<< "| " << std::setw(18) << " " << "| " << std::setw(18) << " " << "| "  << std::endl;
    std::cout << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month")) << " " << std::setw(41) << rs->getInt("Year")<< "|" << std::right << std::setw(19) << rs->getDouble("TotalBasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance")<< " " << "|" << std::setw(18) << rs->getDouble("TotalBonus")  << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime") << " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
    outputFile << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month")) << " " << std::setw(41) << rs->getInt("Year")<< "|" << std::right << std::setw(19) << rs->getDouble("TotalBasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance")<< " " << "|" << std::setw(18) << rs->getDouble("TotalBonus")  << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime") << " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
    
    basicSalary = rs->getDouble("TotalBasicSalary");
    allowance = rs->getDouble("TotalAllowance");
    bonus = rs->getDouble("TotalBonus");
    overtime = rs->getDouble("TotalOvertime");
    deduction = rs->getDouble("TotalDeduction");
    netSalary = rs->getDouble("TotalSalary");

    totalBasicSalary += basicSalary;
    totalAllowance += allowance;
    totalBonus += bonus;
    totalOvertime += overtime;
    totalDeduction += deduction;
    totalnetSalary += netSalary;

    grandBasicSalary += basicSalary;
    grandTotalAllowance += allowance;
    grandTotalBonus += bonus;
    grandTotalOvertime += overtime;
    grandTotalDeduction += deduction;
    grandTotalNetSalary += netSalary;

    previousDepartment = currentDepartment;
      
    while(rs->next())
    {
        currentDepartment = rs->getString("DepartmentName");
        if(currentDepartment==previousDepartment)//if still in the round of same department, print the month and amount
        {
            std::cout << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month")) << " " << std::setw(41) << rs->getInt("Year")<< "|" << std::right << std::setw(19) << rs->getDouble("TotalBasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance")<< " " << "|" << std::setw(18) << rs->getDouble("TotalBonus")  << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime") << " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
            outputFile << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month")) << " " << std::setw(41) << rs->getInt("Year")<< "|" << std::right << std::setw(19) << rs->getDouble("TotalBasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance")<< " " << "|" << std::setw(18) << rs->getDouble("TotalBonus")  << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime") << " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
            basicSalary = rs->getDouble("TotalBasicSalary");
            allowance = rs->getDouble("TotalAllowance");
            bonus = rs->getDouble("TotalBonus");
            overtime = rs->getDouble("TotalOvertime");
            deduction = rs->getDouble("TotalDeduction");
            netSalary = rs->getDouble("TotalSalary");
            
            totalBasicSalary += basicSalary;
            totalAllowance += allowance;
            totalBonus += bonus;
            totalOvertime += overtime;
            totalDeduction += deduction;
            totalnetSalary += netSalary;

        }
        else
        {
            std::cout << std::left << "|       " << std::setw(45) << "Total"  << "|" << std::right << std::setw(19) << totalBasicSalary << " " << "|" << std::setw(19) << totalAllowance << " " << "|" << std::setw(18) << totalBonus << " " << "|" << std::setw(18) << totalOvertime << " " << "|" << std::setw(18) << totalDeduction << " " << "|" << std::setw(18) << totalnetSalary << " " << "|" << std::endl;
            outputFile << std::left << "|       " << std::setw(45) << "Total"  << "|" << std::right << std::setw(19) << totalBasicSalary << " " << "|" << std::setw(19) << totalAllowance << " " << "|" << std::setw(18) << totalBonus << " " << "|" << std::setw(18) << totalOvertime << " " << "|" << std::setw(18) << totalDeduction << " " << "|" << std::setw(18) << totalnetSalary << " " << "|" << std::endl;
            std::cout << std::right << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(52) << "|" << std::setw(21) << "|" << std::setw(21) << "|" << std::setw(20)  << "|" << std::setw(20)  << "|" << std::setw(20) << "|" << std::setw(20) << "|"  << std::endl;
            outputFile << std::right << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(52) << "|" << std::setw(21) << "|" << std::setw(21) << "|" << std::setw(20)  << "|" << std::setw(20)  << "|" << std::setw(20) << "|" << std::setw(20) << "|"  << std::endl;
            std::cout << std::left << "| " << std::setw(51) << currentDepartment  << "| " << std::setw(19) << " " << "| " << std::setw(19) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " "<< "| " << std::setw(18) << " " << "| " << std::endl;
            outputFile << std::left << "| " << std::setw(51) << currentDepartment  << "| " << std::setw(19) << " " << "| " << std::setw(19) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " "<< "| " << std::setw(18) << " " << "| " << std::endl;
            
            totalnetSalary = 0; //initialize amount for new department
            totalAllowance = 0;
            totalBonus = 0;
            totalOvertime = 0;
            totalDeduction = 0;
            totalBasicSalary = 0;
            std::cout << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month")) << " " << std::setw(41) << rs->getInt("Year")<< "|" << std::right << std::setw(19) << rs->getDouble("TotalBasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance")<< " " << "|" << std::setw(18) << rs->getDouble("TotalBonus")  << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime") << " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
            outputFile << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month")) << " " << std::setw(41) << rs->getInt("Year")<< "|" << std::right << std::setw(19) << rs->getDouble("TotalBasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance")<< " " << "|" << std::setw(18) << rs->getDouble("TotalBonus")  << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime") << " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
            basicSalary = rs->getDouble("TotalBasicSalary");
            allowance = rs->getDouble("TotalAllowance");
            bonus = rs->getDouble("TotalBonus");
            overtime = rs->getDouble("TotalOvertime");
            deduction = rs->getDouble("TotalDeduction");
            netSalary = rs->getDouble("TotalSalary");

            
            totalBasicSalary += basicSalary;
            totalAllowance += allowance;
            totalBonus += bonus;
            totalOvertime += overtime;
            totalDeduction += deduction;
            totalnetSalary += netSalary;

        }
        grandBasicSalary += basicSalary;
        grandTotalAllowance += allowance;
        grandTotalBonus += bonus;
        grandTotalOvertime += overtime;
        grandTotalDeduction += deduction;
        grandTotalNetSalary += netSalary;
        previousDepartment = currentDepartment;
    }
    std::cout << std::left << "|       " << std::setw(45) << "Total"  << "|" << std::right << std::setw(19) << totalBasicSalary << " " << "|" << std::setw(19) << totalAllowance << " " << "|" << std::setw(18) << totalBonus << " " << "|" << std::setw(18) << totalOvertime << " " << "|" << std::setw(18) << totalDeduction << " " << "|" << std::setw(18) << totalnetSalary << " " << "|" << std::endl;
    outputFile << std::left << "|       " << std::setw(45) << "Total"  << "|" << std::right << std::setw(19) << totalBasicSalary << " " << "|" << std::setw(19) << totalAllowance << " " << "|" << std::setw(18) << totalBonus << " " << "|" << std::setw(18) << totalOvertime << " " << "|" << std::setw(18) << totalDeduction << " " << "|" << std::setw(18) << totalnetSalary << " " << "|" << std::endl;

    std::cout << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl
                << std::left << "| " << std::setw(51) << "Grand Total" << "|" << std::right << std::setw(19) << grandBasicSalary << " " << "|" << std::setw(19) << grandTotalAllowance << " " << "|" << std::setw(18) << grandTotalBonus << " " << "|" << std::setw(18) << grandTotalOvertime << " " << "|" << std::setw(18) << grandTotalDeduction << " " << "|" << std::setw(18) << grandTotalNetSalary << " " << "|" << std::endl
                << std::right << "+" << std::setfill('-') << "-" << std::setw(174) << "+" << std::setfill(' ') << std::endl;
    outputFile << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl
                << std::left << "| " << std::setw(51) << "Grand Total" << "|" << std::right << std::setw(19) << grandBasicSalary << " " << "|" << std::setw(19) << grandTotalAllowance << " " << "|" << std::setw(18) << grandTotalBonus << " " << "|" << std::setw(18) << grandTotalOvertime << " " << "|" << std::setw(18) << grandTotalDeduction << " " << "|" << std::setw(18) << grandTotalNetSalary << " " << "|" << std::endl
                << std::right << "+" << std::setfill('-') << "-" << std::setw(174) << "+" << std::setfill(' ') << std::endl;

    outputFile.close();
    rs->close();
    ps->close();
    delete rs;
    delete ps;
}

void SalaryManager::PayrollReportByEmployee(std::string startDate, std::string endDate) //new
{
    DepartmentManager dm;
    Department* department =NULL;
    int departmentID;
    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Department ID        : ";
        std::cin >> departmentID;
        department = dm.searchDepartment(departmentID);
        if(department==NULL)
            std::cout << std::endl << std::setw(93) << "The department is not found. Please try again." ;
    } while (department==NULL);

    std::cout << std::fixed << std::setprecision(2);
    EmployeeManager em;
    DateManager dateManager;
    double netSalary = 0, allowance = 0, bonus = 0, overtime = 0,deduction = 0,basicSalary = 0;
    double totalnetSalary = 0, totalAllowance = 0, totalBonus = 0, totalOvertime = 0, totalDeduction = 0, totalBasicSalary=0;
    double grandTotalNetSalary = 0, grandTotalAllowance = 0, grandTotalBonus = 0, grandTotalOvertime = 0, grandTotalDeduction = 0,grandBasicSalary=0;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT e.EmployeeID, e.Name, p.PositionName, e.BasicSalary,SUM(s.TotalAllowance) AS `TotalAllowance`,SUM(s.TotalBonus) AS `TotalBonus`,SUM(s.TotalOvertime) AS `TotalOvertime`,SUM(s.TotalDeduction) AS `TotalDeduction`, SUM(s.NetSalary) AS `TotalSalary`, YEAR(sc.`Date`) AS `Year` ,MONTH(sc.`Date`) AS `Month` FROM SALARY s JOIN SALARY_SCHEDULE sc ON s.SalaryID = sc.SalaryID JOIN EMPLOYEE e ON s.EmployeeID = e.EmployeeID JOIN POSITION p ON e.PositionID = p.PositionID WHERE sc.`Date` BETWEEN ? AND ? AND e.DepartmentID = ? GROUP BY e.EmployeeID,e.BasicSalary, e.Name,`Year`,`Month`");
    ps->setString(1,startDate);
    ps->setString(2,endDate);
    ps->setInt(3,department->departmentID);
    sql::ResultSet* rs = ps->executeQuery();
    Menu menu;
    menu.displayLogo();
    producePayrollReportHeader();

    if(!rs->next())
    {
        std::cout << "\n" << std::setw(81) << "No result is found. " << std::endl;
        return;
    }

    int central = 176/2;
    std::string departmentName = department->departmentName;
    departmentName += " Department";
    int position = central - (departmentName.length()/2) ;

    std::string filename = "SummaryByEmployee";
    filename = filename + "_" + departmentName + "_" + startDate + "_" + endDate + ".txt"; 
    std::replace(filename.begin(), filename.end(), '/', '-');
    std::ofstream outputFile;
    outputFile.open("/Users/phoebekiew/Desktop/Payroll Management System /PayrollSummaryByEmployee/" + filename, std::ios::out);
    if(!outputFile.is_open())
    {
        cout << "Fail to print Payroll Summary By Employee! " << std::endl;
        std::perror("Error details:");
        return;
    }
    outputFile << std::fixed << std::setprecision(2); 
    std::cout  << "\n\n";
    std::cout  << std::right << std::setw(1) << "+" << std::setfill('-') << "-" << std::setw(174) << "+" << std::setfill(' ') << std::endl
            << std::right << std::setw(1) << "| " << std::setw(99) <<  " Payroll Summary By Employee"  << setw(75)  << "|" << std::endl
            << std::left << std::setw(1) << "| " << std::setw(position-3) << " " << "< " <<  departmentName  << setw(176-position-departmentName.length()-2) << " >" << "|" << std::endl
            << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl
            << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(174) << " |" << std::endl             

            << std::left
            << "| Period               : " << std::setw(10) << startDate << " - " << std::setw(137) << endDate << "| "  << std::endl
            << std::right << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(174) << " |" << std::endl                           
            << std::right << std::setw(1) << "|" << std::setfill('=') << "=" << std::setw(174) << "|" << std::setfill(' ') << std::endl
            << std::left << std::setw(53) << "| Employee Name" << std::setw(21) << "|  Basic Salary (RM)" << "|   Allowance (RM)   " << "|     Bonus (RM)    " << "|   Overtime (RM)   " << "|   Deduction (RM)  " << "|  Net Salary (RM)  |" << std::endl; //this 
    std::cout << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl;
    
    outputFile  << "\n\n";
    outputFile  << std::right << std::setw(1) << "+" << std::setfill('-') << "-" << std::setw(174) << "+" << std::setfill(' ') << std::endl
            << std::right << std::setw(1) << "| " << std::setw(99) <<  " Payroll Summary By Employee"  << setw(75)  << "|" << std::endl
            << std::left << std::setw(1) << "| " << std::setw(position-3) << " " << "< " <<  departmentName  << setw(176-position-departmentName.length()-2) << " >" << "|" << std::endl
            << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl
            << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(174) << " |" << std::endl             

            << std::left
            << "| Period               : " << std::setw(10) << startDate << " - " << std::setw(137) << endDate << "| "  << std::endl
            << std::right << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(174) << " |" << std::endl                           
            << std::right << std::setw(1) << "|" << std::setfill('=') << "=" << std::setw(174) << "|" << std::setfill(' ') << std::endl
            << std::left << std::setw(53) << "| Employee Name" << std::setw(21) << "|  Basic Salary (RM)" << "|   Allowance (RM)   " << "|     Bonus (RM)    " << "|   Overtime (RM)   " << "|   Deduction (RM)  " << "|  Net Salary (RM)  |" << std::endl; //this 
    outputFile << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl;
    int previousEmployee ;
    int currentEmployee ;

    currentEmployee = rs->getInt("EmployeeID");
    std::cout << std::left << "| " << std::setw(51) << rs->getString("Name") << "| " << std::setw(19) << " " << "| " << std::setw(19) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " "<< "| " << std::setw(18) << " "<< "| " << std::setw(18) << " " << "| " << std::endl;
    outputFile << std::left << "| " << std::setw(51) << rs->getString("Name") << "| " << std::setw(19) << " " << "| " << std::setw(19) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " "<< "| " << std::setw(18) << " "<< "| " << std::setw(18) << " " << "| " << std::endl;
    std::cout << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month"))  << " " << std::setw(41) << rs->getInt("Year") << "|" << std::right << std::setw(19) << rs->getDouble("BasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance") << " " << "|" << std::setw(18) << rs->getDouble("TotalBonus") << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime")<< " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
    outputFile << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month"))  << " " << std::setw(41) << rs->getInt("Year") << "|" << std::right << std::setw(19) << rs->getDouble("BasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance") << " " << "|" << std::setw(18) << rs->getDouble("TotalBonus") << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime")<< " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;

    basicSalary = rs->getDouble("BasicSalary");
    allowance = rs->getDouble("TotalAllowance");
    bonus = rs->getDouble("TotalBonus");
    overtime = rs->getDouble("TotalOvertime");
    deduction = rs->getDouble("TotalDeduction");
    netSalary = rs->getDouble("TotalSalary");

    totalBasicSalary += basicSalary;
    totalAllowance += allowance;
    totalBonus += bonus;
    totalOvertime += overtime;
    totalDeduction += deduction;
    totalnetSalary += netSalary;

    grandBasicSalary += basicSalary;
    grandTotalAllowance += allowance;
    grandTotalBonus += bonus;
    grandTotalOvertime += overtime;
    grandTotalDeduction += deduction;
    grandTotalNetSalary += netSalary;

    previousEmployee = currentEmployee;
      
    while(rs->next())
    {
        currentEmployee = rs->getInt("EmployeeID");
        if(currentEmployee==previousEmployee)//if still in the round of same employee, print the month and amount
        {
        std::cout << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month"))  << " " << std::setw(41) << rs->getInt("Year") << "|" << std::right << std::setw(19) << rs->getDouble("BasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance") << " " << "|" << std::setw(18) << rs->getDouble("TotalBonus") << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime")<< " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
        outputFile << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month"))  << " " << std::setw(41) << rs->getInt("Year") << "|" << std::right << std::setw(19) << rs->getDouble("BasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance") << " " << "|" << std::setw(18) << rs->getDouble("TotalBonus") << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime")<< " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
            basicSalary = rs->getDouble("BasicSalary");            
            allowance = rs->getDouble("TotalAllowance");
            bonus = rs->getDouble("TotalBonus");
            overtime = rs->getDouble("TotalOvertime");
            deduction = rs->getDouble("TotalDeduction");
            netSalary = rs->getDouble("TotalSalary");
            totalBasicSalary += basicSalary;
            totalAllowance += allowance;
            totalBonus += bonus;
            totalOvertime += overtime;
            totalDeduction += deduction;
            totalnetSalary += netSalary;
        }
        else
        {
            std::cout << std::left << "|       " << std::setw(45) << "Total"  << "|" << std::right << std::setw(19) << totalBasicSalary << " " << "|" << std::setw(19) << totalAllowance << " " << "|" << std::setw(18) << totalBonus << " " << "|" << std::setw(18) << totalOvertime << " " << "|" << std::setw(18) << totalDeduction << " " << "|" << std::setw(18) << totalnetSalary << " " << "|" << std::endl;
            outputFile<< std::left << "|       " << std::setw(45) << "Total"  << "|" << std::right << std::setw(19) << totalBasicSalary << " " << "|" << std::setw(19) << totalAllowance << " " << "|" << std::setw(18) << totalBonus << " " << "|" << std::setw(18) << totalOvertime << " " << "|" << std::setw(18) << totalDeduction << " " << "|" << std::setw(18) << totalnetSalary << " " << "|" << std::endl;
            std::cout << std::right << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(52) << "|" << std::setw(21) << "|" << std::setw(21) << "|" << std::setw(20)  << "|" << std::setw(20)  << "|" << std::setw(20) << "|" << std::setw(20) << "|"  << std::endl;
            outputFile << std::right << std::setw(1) << "|" << std::setfill(' ') << ' ' << std::setw(52) << "|" << std::setw(21) << "|" << std::setw(21) << "|" << std::setw(20)  << "|" << std::setw(20)  << "|" << std::setw(20) << "|" << std::setw(20) << "|"  << std::endl;
            std::cout << std::left << "| " << std::setw(51) << rs->getString("Name") << "| " << std::setw(19) << " " << "| " << std::setw(19) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " "<< "| " << std::setw(18) << " " << "| " << std::endl;
            outputFile << std::left << "| " << std::setw(51) << rs->getString("Name") << "| " << std::setw(19) << " " << "| " << std::setw(19) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " " << "| " << std::setw(18) << " "<< "| " << std::setw(18) << " " << "| " << std::endl;
            
            totalnetSalary = 0; //initialize amount for new department
            totalAllowance = 0;
            totalBonus = 0;
            totalOvertime = 0;
            totalDeduction = 0;
            totalBasicSalary = 0;

            std::cout << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month"))  << " " << std::setw(41) << rs->getInt("Year") << "|" << std::right << std::setw(19) << rs->getDouble("BasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance") << " " << "|" << std::setw(18) << rs->getDouble("TotalBonus") << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime")<< " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
            outputFile << std::left << "|       " << std::setw(3) << dateManager.getMonthName(rs->getInt("Month"))  << " " << std::setw(41) << rs->getInt("Year") << "|" << std::right << std::setw(19) << rs->getDouble("BasicSalary") << " " << "|" << std::setw(19) << rs->getDouble("TotalAllowance") << " " << "|" << std::setw(18) << rs->getDouble("TotalBonus") << " " << "|" << std::setw(18) << rs->getDouble("TotalOvertime")<< " " << "|" << std::setw(18) << rs->getDouble("TotalDeduction") << " " << "|" << std::setw(18) << rs->getDouble("TotalSalary") << " " << "|" << std::endl;
            basicSalary = rs->getDouble("BasicSalary");            
            allowance = rs->getDouble("TotalAllowance");
            bonus = rs->getDouble("TotalBonus");
            overtime = rs->getDouble("TotalOvertime");
            deduction = rs->getDouble("TotalDeduction");
            netSalary = rs->getDouble("TotalSalary");

            totalBasicSalary += basicSalary;
            totalAllowance += allowance;
            totalBonus += bonus;
            totalOvertime += overtime;
            totalDeduction += deduction;
            totalnetSalary += netSalary;

        }
            grandBasicSalary += basicSalary;
            grandTotalAllowance += allowance;
            grandTotalBonus += bonus;
            grandTotalOvertime += overtime;
            grandTotalDeduction += deduction;
            grandTotalNetSalary += netSalary;

        previousEmployee = currentEmployee;
    }
    std::cout << std::left << "|       " << std::setw(45) << "Total"  << "|" << std::right << std::setw(19) << totalBasicSalary << " " << "|" << std::setw(19) << totalAllowance << " " << "|" << std::setw(18) << totalBonus << " " << "|" << std::setw(18) << totalOvertime << " " << "|" << std::setw(18) << totalDeduction << " " << "|" << std::setw(18) << totalnetSalary << " " << "|" << std::endl;
    outputFile << std::left << "|       " << std::setw(45) << "Total"  << "|" << std::right << std::setw(19) << totalBasicSalary << " " << "|" << std::setw(19) << totalAllowance << " " << "|" << std::setw(18) << totalBonus << " " << "|" << std::setw(18) << totalOvertime << " " << "|" << std::setw(18) << totalDeduction << " " << "|" << std::setw(18) << totalnetSalary << " " << "|" << std::endl;

    std::cout << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl
                << std::left << "| " << std::setw(51) << "Grand Total" << "|" << std::right << std::setw(19) << grandBasicSalary << " " << "|" << std::setw(19) << grandTotalAllowance << " " << "|" << std::setw(18) << grandTotalBonus << " " << "|" << std::setw(18) << grandTotalOvertime << " " << "|" << std::setw(18) << grandTotalDeduction << " " << "|" << std::setw(18) << grandTotalNetSalary << " " << "|" << std::endl
                << std::right << "+" << std::setfill('-') << "-" << std::setw(174) << "+" << std::setfill(' ') << std::endl;
    outputFile << std::right << std::setw(1) << "|" << std::setfill('-') << "-" << std::setw(174) << "|" << std::setfill(' ') << std::endl
                << std::left << "| " << std::setw(51) << "Grand Total" << "|" << std::right << std::setw(19) << grandBasicSalary << " " << "|" << std::setw(19) << grandTotalAllowance << " " << "|" << std::setw(18) << grandTotalBonus << " " << "|" << std::setw(18) << grandTotalOvertime << " " << "|" << std::setw(18) << grandTotalDeduction << " " << "|" << std::setw(18) << grandTotalNetSalary << " " << "|" << std::endl
                << std::right << "+" << std::setfill('-') << "-" << std::setw(174) << "+" << std::setfill(' ') << std::endl;

    outputFile.close();

    rs->close();
    ps->close();
    delete rs;
    delete ps;
}

void SalaryManager::printPaySlip(std::string role)
{
    Menu menu;
    DateManager dateManager;
    EmployeeManager em;
    AllowanceManager am;
    BonusManager bm;
    OvertimeManager om;
    DeductionManager dm;
    DepartmentManager departmentManager;

    menu.displayLogo();
    printPaySlipHeader();
    std::cout << std::fixed << std::setprecision(2); 
    int employeeID, year, month ,salaryID;
    double basicSalary=0, totalAllowance=0, travellingAllowance = 0,totalBonus=0,totalOvertime=0,grossPay=0, totalDeduction=0, netSalary=0, employerEPF=0,employeeEPF=0,employerSOSCO=0, employeeSOSCO=0, employeeEIS=0, employerEIS=0;
    char response;

    Employee* employee = NULL;
    do
    {
        response = 'Z';
        menu.displayLogo();
        printPaySlipHeader();

        std::cout  << "\n\n" << std::setw(72) << "Enter Employee ID     : ";
        std::cin >> employeeID;
        employee = em.searchEmployee(employeeID);
            if(employee==NULL)
            {
                cout << endl << setw(90) << "The employee is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.generateReportMenu(role);
            }
        } while (response == 'y'||response=='Y');    

    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Year            : ";
        std::cin >> year;
        if(year<0)
            std::cout << "\n"<< std::setw(90) << "Invalid year. Please enter a valid year." << std::endl;
    } while (year<0);
    
    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Month           : ";
        std::cin >> month;
        if(month<1||month>12)
            std::cout << "\n"<< std::setw(91) << "Invalid month. Please enter a valid month." << std::endl;
    } while (month<1||month>12);

    menu.displayLogo();
    printPaySlipHeader();    

    Department* department = NULL;
    department = departmentManager.searchDepartment(employee->departmentID);
    std::string departmentName = department->departmentName;
    Position* position = NULL;
    position = departmentManager.searchPosition(employee->positionID);
    std::string positionName = position->positionName;
    std::string monthname = dateManager.getMonthName(month);

    Salary_Schedule* sc = NULL;
    sc = searchSalarySchedule(year,month);
    if(sc==NULL)
    {
        std::cout << "\n" << std::setw(81) << "No result is found. " << std::endl;
        return;
    }
    salaryID = sc->salaryID;

    Salary* salary = NULL;  
    salary = searchSalary(employeeID,salaryID);
    if(salary == NULL)
    {
        std::cout << "\n" << std::setw(81) << "No result is found. " << std::endl;
        return;
    }

    basicSalary = salary->basicSalary;
    totalAllowance = salary->totalAllowance;
    totalBonus = salary->totalBonus;
    totalOvertime = salary->totalOvertime;
    grossPay = salary->grossSalary;
    totalDeduction = salary->totalDeduction;
    netSalary = salary->netSalary;
    Allowance* allowance = NULL;
    Bonus* bonus = NULL;
    Overtime* overtime = NULL;
    Deduction* deduction = NULL;
    Employee_Allowance* empAllowances = NULL;
    Employee_Bonus* empBonuses = NULL;
    Employee_Overtime* empOvertimes = NULL;
    Employee_Deduction* empDeductions = NULL;
    empAllowances = am.getEmployeeAllowances(employee->id);
    empBonuses = bm.getEmployeeBonuses(employee->id,year,month);
    empOvertimes = om.getEmployeeOvertimes(employee->id,year,month);
    empDeductions = dm.getEmployeeDeductions(employee->id,year,month);


    std::string currentDate = dateManager.getCurrentDate();
    std::string filename = "PaySlip";
    filename = filename + "_" + std::to_string(employee->id) + "_" + monthname + "_" + std::to_string(year) + ".txt"; 
    // std::string directoryPath = "/Users/phoebekiew/Desktop/Payroll Management System/PayrollReport";
    std::ofstream outputFile;
    outputFile.open("/Users/phoebekiew/Desktop/Payroll Management System /PaySlip/" + filename, std::ios::out);
    if(!outputFile.is_open())
    {
        cout << "Fail to print paySlip! " << std::endl;
        std::perror("Error details:");
        return;
    }

    outputFile << std::fixed << std::setprecision(2); 

    // std::streambuf *coutbuf = std::cout.rdbuf(); // Save the console cout buffer
    // std::cout.rdbuf(outputFile.rdbuf()); // Redirect cout to the file


    //display in terminal
    std::cout << std::right << std::setw(3) << "+" << std::setfill('-') << "-" << std::setw(144) << "+" << std::setfill(' ') << std::endl
                << std::setw(3) << "|" << std::setw(70) << "Payslip for " << std::left << std::setw(3) << monthname << " "  << std::setw(70) << year << "|" << std::endl
                << std::right << std::setw(3) << "|" << std::setfill('-') << "-" << std::setw(144) << "|" << std::setfill(' ') << std::endl

                << std::left
                << std::setw(2) << " " << std::setw(20) << "| Employee ID       : " << std::setw(123) << employee->id << "| " << std::endl
                << std::setw(2) << " " << std::setw(20) << "| Employee Name     : " << std::setw(123) << employee->name << "| " << std::endl
                << std::setw(2) << " " << std::setw(20) << "| Department        : " << std::setw(123) << departmentName << "| " << std::endl
                << std::setw(2) << " " << std::setw(20) << "| Position          : " << std::setw(123) << positionName << "| " << std::endl
                << std::right << std::setw(3) << "|" << std::setfill('=') << "=" << std::setw(144) << "|" << std::setfill(' ') << std::endl
                << std::left << std::setw(2) << " " << std::setw(25) << "| Basic Salary      : RM " << std::setw(48) << basicSalary << "| Total Deduction   : RM " << std::setw(47) << totalDeduction << "|" << std::endl;
            //write to output file
    outputFile << std::right << std::setw(3) << "+" << std::setfill('-') << "-" << std::setw(144) << "+" << std::setfill(' ') << std::endl
                << std::setw(3) << "|" << std::setw(70) << "Payslip for " << std::left << std::setw(3) << monthname << " "  << std::setw(70) << year << "|" << std::endl
                << std::right << std::setw(3) << "|" << std::setfill('-') << "-" << std::setw(144) << "|" << std::setfill(' ') << std::endl

                << std::left
                << std::setw(2) << " " << std::setw(20) << "| Employee ID       : " << std::setw(123) << employee->id << "| " << std::endl
                << std::setw(2) << " " << std::setw(20) << "| Employee Name     : " << std::setw(123) << employee->name << "| " << std::endl
                << std::setw(2) << " " << std::setw(20) << "| Department        : " << std::setw(123) << departmentName << "| " << std::endl
                << std::setw(2) << " " << std::setw(20) << "| Position          : " << std::setw(123) << positionName << "| " << std::endl
                << std::right << std::setw(3) << "|" << std::setfill('=') << "=" << std::setw(144) << "|" << std::setfill(' ') << std::endl
                << std::left << std::setw(2) << " " << std::setw(25) << "| Basic Salary      : RM " << std::setw(48) << basicSalary << "| Total Deduction   : RM " << std::setw(47) << totalDeduction << "|" << std::endl;

                if(empDeductions!=NULL)
                {
                    deduction = dm.searchDeduction(empDeductions->deductionID);
                    std::cout << std::left << std::setw(2) << " " << "| " << std::setw(71) << " " << "|" << setw(5) << " " << std::setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    outputFile << std::left << std::setw(2) << " " << "| " << std::setw(71) << " " << "|" << setw(5) << " " << std::setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    empDeductions = empDeductions->next;
                }
                else
                {
                    std::cout << std::right << std::setw(3) << "|" << std::setfill(' ') << " " << std::setw(72) << "|" << std::setw(72) << "|" << std::setfill(' ') << std::endl;
                    outputFile << std::right << std::setw(3) << "|" << std::setfill(' ') << " " << std::setw(72) << "|" << std::setw(72) << "|" << std::setfill(' ') << std::endl;
                }

                std::cout << std::left << std::setw(2) << " " << std::setw(25) << "| Total Allowance   : RM " << std::setw(48) << totalAllowance << "|";
                outputFile << std::left << std::setw(2) << " " << std::setw(25) << "| Total Allowance   : RM " << std::setw(48) << totalAllowance << "|";
                    if(empDeductions!=NULL)
                    {
                        deduction = dm.searchDeduction(empDeductions->deductionID);
                        std::cout << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                        outputFile << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                        empDeductions = empDeductions->next;
                    }
                    else
                    {
                        std::cout << std::left << std::setw(71) << " " << "| " << std::endl;
                        outputFile << std::left << std::setw(71) << " " << "| " << std::endl;
                    }

                while(empAllowances!=NULL) 
                {
                    allowance = am.searchAllowance(empAllowances->allowanceID);
                    std::cout << std::left << std::setw(2) << " " << "|" << setw(6) << " " << setw(50) << allowance->name << " - RM " << std::right << std::setw(9) << empAllowances->amount << " |";
                    outputFile << std::left << std::setw(2) << " " << "|" << setw(6) << " " << setw(50) << allowance->name << " - RM " << std::right << std::setw(9) << empAllowances->amount << " |";
                    empAllowances = empAllowances->next;
                    if(empDeductions!=NULL)
                    {
                        deduction = dm.searchDeduction(empDeductions->deductionID);
                        std::cout << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                        outputFile << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                        empDeductions = empDeductions->next;
                    }
                    else
                    {
                        std::cout << std::left << std::setw(71) << " " << "| " << std::endl;
                        outputFile << std::left << std::setw(71) << " " << "| " << std::endl;
                    }
                }

                if(empDeductions!=NULL)
                {
                    deduction = dm.searchDeduction(empDeductions->deductionID);
                    std::cout << std::left << std::setw(2) << " " << "| " << std::setw(71) << " " << "|" << setw(5) << " " << std::setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    outputFile << std::left << std::setw(2) << " " << "| " << std::setw(71) << " " << "|" << setw(5) << " " << std::setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    empDeductions = empDeductions->next;
                }
                else
                {
                    std::cout << std::right << std::setw(3) << "|" << std::setfill(' ') << " " << std::setw(72) << "|" << std::setw(72) << "|" << std::setfill(' ') << std::endl;
                    outputFile << std::right << std::setw(3) << "|" << std::setfill(' ') << " " << std::setw(72) << "|" << std::setw(72) << "|" << std::setfill(' ') << std::endl;
                }

                std::cout << std::left << std::setw(2) << " " << std::setw(25) << "| Total Bonus       : RM " << std::setw(48) << totalBonus << "|";
                outputFile << std::left << std::setw(2) << " " << std::setw(25) << "| Total Bonus       : RM " << std::setw(48) << totalBonus << "|";
                if(empDeductions!=NULL)
                {
                    deduction = dm.searchDeduction(empDeductions->deductionID);
                    std::cout << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    outputFile << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    empDeductions = empDeductions->next;
                }
                else
                {
                    std::cout << std::left << std::setw(71) << " " << "| " << std::endl;
                    outputFile << std::left << std::setw(71) << " " << "| " << std::endl;
                }


                while(empBonuses!=NULL)
                {
                    bonus = bm.searchBonus(empBonuses->bonusID);
                    std::cout << std::left << std::setw(2) << " " << "|" << setw(6) << " " << setw(50) << bonus->name << " - RM " << std::right << std::setw(9) << empBonuses->amount << " |";
                    outputFile << std::left << std::setw(2) << " " << "|" << setw(6) << " " << setw(50) << bonus->name << " - RM " << std::right << std::setw(9) << empBonuses->amount << " |";
                    empBonuses = empBonuses->next;

                    if(empDeductions!=NULL)
                    {
                        deduction = dm.searchDeduction(empDeductions->deductionID);
                        std::cout << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM "  << std::right << std::setw(9) << empDeductions->amount << " |"  << std::endl;
                        outputFile << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM "  << std::right << std::setw(9) << empDeductions->amount << " |"  << std::endl;
                        empDeductions = empDeductions->next;
                    }
                    else
                    {
                        std::cout << std::left << std::setw(71) << " " << "| " << std::endl;
                        outputFile << std::left << std::setw(71) << " " << "| " << std::endl;
                    }
                }


                if(empDeductions!=NULL)
                {
                    deduction = dm.searchDeduction(empDeductions->deductionID);
                    std::cout << std::left << std::setw(2) << " " << "| " << std::setw(71) << " " << "|" << setw(5) << " " << std::setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    outputFile << std::left << std::setw(2) << " " << "| " << std::setw(71) << " " << "|" << setw(5) << " " << std::setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    empDeductions = empDeductions->next;
                }
                else
                {
                    std::cout << std::right << std::setw(3) << "|" << std::setfill(' ') << " " << std::setw(72) << "|" << std::setw(72) << "|" << std::setfill(' ') << std::endl;
                    outputFile << std::right << std::setw(3) << "|" << std::setfill(' ') << " " << std::setw(72) << "|" << std::setw(72) << "|" << std::setfill(' ') << std::endl;
                }

                std::cout << std::left << std::setw(2) << " " << std::setw(25) << "| Total Overtime    : RM " << std::setw(48) << totalOvertime << "|";
                outputFile << std::left << std::setw(2) << " " << std::setw(25) << "| Total Overtime    : RM " << std::setw(48) << totalOvertime << "|";

                if(empDeductions!=NULL)
                {
                    deduction = dm.searchDeduction(empDeductions->deductionID);
                    std::cout << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM "  << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    outputFile << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM "  << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    empDeductions = empDeductions->next;
                }
                else
                {
                    std::cout << std::left << std::setw(71) << " " << "| " << std::endl;
                    outputFile << std::left << std::setw(71) << " " << "| " << std::endl;
                }

                while(empOvertimes!=NULL) 
                {
                    std::cout << std::left << std::setw(2) << " " << "|" << setw(6) << " " << setw(50) << empOvertimes->date << " - RM " << std::right << std::setw(9) << empOvertimes->amount << " |";
                    outputFile << std::left << std::setw(2) << " " << "|" << setw(6) << " " << setw(50) << empOvertimes->date << " - RM " << std::right << std::setw(9) << empOvertimes->amount << " |";
                    empOvertimes = empOvertimes->next;
                    if(empDeductions!=NULL)
                    {
                        deduction = dm.searchDeduction(empDeductions->deductionID);
                        std::cout << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                        outputFile << std::left << setw(5) << " " << setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                        empDeductions = empDeductions->next;
                    }
                    else
                    {
                        std::cout << std::left << std::setw(71) << " " << "| " << std::endl;
                        outputFile << std::left << std::setw(71) << " " << "| " << std::endl;
                    }
                }

                while(empDeductions!=NULL)
                {
                    deduction = dm.searchDeduction(empDeductions->deductionID);
                    std::cout << std::left << std::setw(2) << " " << "| " << std::setw(71) << " " << "|" << setw(5) << " " << std::setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    outputFile << std::left << std::setw(2) << " " << "| " << std::setw(71) << " " << "|" << setw(5) << " " << std::setw(50) << deduction->name << " - RM " << std::right << std::setw(9) << empDeductions->amount << " |" << std::endl;
                    empDeductions = empDeductions->next;
                }

                std::cout << std::right << std::setw(3) << "|" << std::setfill('-') << "-" << std::setw(72) << "+" << std::setfill('-') << "-" << std::setw(71) << "|" << std::setfill(' ') << std::endl;
                outputFile << std::right << std::setw(3) << "|" << std::setfill('-') << "-" << std::setw(72) << "+" << std::setfill('-') << "-" << std::setw(71) << "|" << std::setfill(' ') << std::endl;
                std::cout << std::left << std::setw(2) << " " << "| Gross Salary      : RM " << std::setw(48)  << grossPay << "| Net Salary        : RM " << std::setw(47) << netSalary << "| " << std::endl
                        << std::right << std::setw(3) << "+" << std::setfill('-') << "-" << std::setw(144) << "+" << std::setfill(' ') << std::endl;
                outputFile << std::left << std::setw(2) << " " << "| Gross Salary      : RM " << std::setw(48)  << grossPay << "| Net Salary        : RM " << std::setw(47) << netSalary << "| " << std::endl
                        << std::right << std::setw(3) << "+" << std::setfill('-') << "-" << std::setw(144) << "+" << std::setfill(' ') << std::endl;

    outputFile.close();
    // std::cout.rdbuf(coutbuf);
    delete position;
    delete department;
    delete employee;
    delete salary;
}

Salary_Schedule* SalaryManager::searchSalarySchedule(int year, int month)
{
    Salary_Schedule* sc = NULL;
    std::string date;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM SALARY_SCHEDULE WHERE `Year` = ? AND Month = ? ");
    ps->setInt(1,year);
    ps->setInt(2,month);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        sc = new Salary_Schedule();
        sc->salaryID = rs->getInt("SalaryID");
        sc->year = rs->getInt("Year");
        sc->month = rs->getInt("Month");
        sc->date = rs->getString("Date");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return sc;
}

double SalaryManager::getTotalAllowance(int employeeID)
{
    double totalAllowance = 0;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT Amount FROM EMPLOYEE_ALLOWANCE WHERE EmployeeID = ?");
    ps->setInt(1,employeeID);
    sql::ResultSet* rs = ps->executeQuery();

    while(rs->next())
    {
        totalAllowance+=rs->getDouble("Amount");
    }

    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return totalAllowance;
}

double SalaryManager::getTravellingAllowance(int employeeID)
{
    double travellingAllowance = 0;
    std::string date;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT Amount FROM EMPLOYEE_ALLOWANCE WHERE EmployeeID = ? AND AllowanceID = 100002");
    ps->setInt(1,employeeID);
    sql::ResultSet* rs = ps->executeQuery();

    if(rs->next())
    {
        travellingAllowance+= rs->getDouble("Amount");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return travellingAllowance;
}

double SalaryManager::getTotalBonus(int employeeID, int targetYear, int targetMonth)
{
    double totalBonus = 0;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT Amount  FROM EMPLOYEE_BONUS WHERE EmployeeID = ? AND YEAR(Date) = ? AND MONTH(Date)= ? ");
    ps->setInt(1,employeeID);
    ps->setInt(2,targetYear);
    ps->setInt(3,targetMonth);
    sql::ResultSet* rs = ps->executeQuery();
    while (rs->next()) 
    {
        totalBonus+= rs->getDouble("Amount");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return totalBonus;
}

double SalaryManager::getTotalOvertime(int employeeID, int targetYear, int targetMonth)
{
    double totalOverTime = 0;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT Amount FROM EMPLOYEE_OVERTIME WHERE EmployeeID = ? AND YEAR(Date) = ? AND MONTH(Date)= ? ");
    ps->setInt(1,employeeID);
    ps->setInt(2,targetYear);
    ps->setInt(3,targetMonth);
    sql::ResultSet* rs = ps->executeQuery();

    while (rs->next()) 
    {
        totalOverTime+= rs->getDouble("Amount");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return totalOverTime;
}

double SalaryManager::getTotalDeduction(int employeeID, int targetYear, int targetMonth)
{
    double totalDeduction = 0;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT Amount FROM EMPLOYEE_DEDUCTION  WHERE EmployeeID = ? AND YEAR(Date) = ? AND MONTH(Date)= ? AND DeductionID <> 400001 AND DeductionID <> 400004 AND DeductionID <> 400006 AND  DeductionID <> 400010 AND DeductionID <> 400011" );
    ps->setInt(1,employeeID);
    ps->setInt(2,targetYear);
    ps->setInt(3,targetMonth);
    sql::ResultSet* rs = ps->executeQuery();

    while (rs->next()) 
    {
        totalDeduction += rs->getDouble("Amount");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return totalDeduction;
}

bool SalaryManager::checkExistEmpSalary(int employeeID,int salaryID)
{
    DatabaseConnection dbConn;
    Salary* salary = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM SALARY WHERE EmployeeID = ? AND SalaryID = ?" );
    ps->setInt(1,employeeID);
    ps->setInt(2,salaryID);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        // salary = new Salary();
        // salary->employeeID = rs->getInt("EmployeeID");
        // salary->salaryID = rs->getInt("SalaryID");
        // salary->basicSalary = rs->getInt("BasicSalary");
        // salary->totalAllowance = rs->getInt("TotalAllowance");
        // salary->totalBonus = rs->getInt("TotalBonus");
        // salary->totalOvertime = rs->getInt("TotalOvertime");
        // salary->grossSalary = rs->getInt("GrossPay");
        // salary->totalDeduction = rs->getInt("TotalDeduction");
        // salary->netSalary = rs->getInt("NetSalary");
        // salary->paymentStatus = rs->getInt("PaymentStatus");
        return true;
    } 
    return false;
}

Employee* SalaryManager::searchEmployees(int salaryID)//return employee list who have no salary data
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
        if(!checkExistEmpSalary(rs->getInt("EmployeeID"),salaryID))
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

Employee* SalaryManager::searchEmployeesByDepartment(int departmentID,int salaryID)//return employee list who have no salary data
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
        if(!checkExistEmpSalary(rs->getInt("EmployeeID"),salaryID))
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

Employee* SalaryManager::getSalaryEmployees(int salaryID)//return employee list chosen
{
    Menu menu;
    DateManager dateManager;
    menu.displayLogo();
    paySalaryHeader();
    std::cout << std::setw(81) << "Process Salary of : " << std::endl
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
    AllowanceManager am; //to use function "EmployeeInList"
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
        employee = searchEmployees(salaryID);
        break;
    case 2:
        head = dm.searchDepartments();
        do
        {
            response = 'Z';
            department = head;
            if(department!=NULL)
            {
                menu.displayLogo();
                paySalaryHeader();
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
                    std::cout << endl << setw(94) << "The department is not found. Enter Y/y to retry: ";
                    std::cin >> response;
                    if(response != 'y'&& response!='Y')
                    {
                        menu.managerMainMenu();
                        return 0;
                    }
                }
            }
        } while (response == 'y' || response =='Y');
        //pass the found department ID to get all employees in that department
        employee = searchEmployeesByDepartment(departmentID,salaryID);
        break;
    case 3:
        menu.displayLogo();
        paySalaryHeader();
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
                    paySalaryHeader();
                    response = 'Z';
                    do 
                    {
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee ID              : ";
                        std::cin >> employeeID;
                        // Check if the user input already exists in the list
                        repeat = am.isEmployeeInList(employeeHead, employeeID);
                        if (repeat) {
                            std::cout << std::right << std::setw(90) << "The employee already exists in the list. " << std::endl;
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
                                    menu.managerMainMenu();
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
                                    menu.managerMainMenu();
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
                paySalaryHeader();
                response = 'Z';
                do
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    do {
                        std::cout << "\n\n" << std::setw(72) << "Enter Employee Name            : ";
                        getline(cin, name);
                        // Check if the user input already exists in the list
                        repeat = am.isEmployeeInList(employeeHead, name);
                        if (repeat) {
                            std::cout << "\n" << std::right << std::setw(90) << "The employee already exists in the list. " << std::endl;
                        }
                    } while (repeat);
                    if(employeeHead == NULL) 
                    {
                        employee = em.searchEmployee(name);
                        if(employee==NULL)
                        {
                            std::cout << "\n" << std::setw(90) << "The employee is not found. Enter Y/y to retry: ";
                            std::cin >> response;
                            if (response != 'y' && response != 'Y') 
                            {
                                if (employeeHead == NULL)
                                    menu.managerMainMenu();
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
                                    menu.managerMainMenu();
                                else
                                    break;
                            }
                        }
                    }
                }while(response == 'y' || response == 'Y');
            }
            if (checkExistEmpSalary(employee->id, salaryID))
            {
                employee = nullptr;
                std::cout << "\n" << std::setw(95) << "The salary for this employee had been processed." << std::endl;
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

void SalaryManager::addSalary(Salary * salary)
{
    //int employeeID, int salaryID, double basicSalary, double totalAllowance,double totalBonus, double totalOvertime, double grossPay, double totalDeduction, double netSalary)
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO SALARY(EmployeeID, SalaryID,BasicSalary,TotalAllowance,TotalBonus,TotalOvertime,GrossPay,TotalDeduction,NetSalary) VALUES (?,?,?,?,?,?,?,?,?)");
    ps->setInt(1,salary->employeeID);
    ps->setInt(2,salary->salaryID);
    ps->setDouble(3,salary->basicSalary);
    ps->setDouble(4,salary->totalAllowance);
    ps->setDouble(5,salary->totalBonus);
    ps->setDouble(6,salary->totalOvertime);
    ps->setDouble(7,salary->grossSalary);
    ps->setDouble(8,salary->totalDeduction);
    ps->setDouble(9,salary->netSalary);
    ps->executeUpdate();
    ps->close();
    delete ps;
}

Salary* SalaryManager::searchSalary(int employeeID, int salaryID)
{
    Salary* payslip = NULL;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM SALARY WHERE EmployeeID = ? AND SalaryID = ?");
    ps->setInt(1,employeeID);
    ps->setInt(2,salaryID);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        payslip = new Salary();
        payslip->employeeID = rs->getInt("EmployeeID");
        payslip->salaryID = rs->getInt("SalaryID");
        payslip->basicSalary = rs->getDouble("BasicSalary");
        payslip->totalAllowance = rs->getDouble("TotalAllowance");
        payslip->totalBonus = rs->getDouble("TotalBonus");
        payslip->totalOvertime = rs->getDouble("TotalOvertime");
        payslip->grossSalary = rs->getDouble("GrossPay");
        payslip->totalDeduction = rs->getDouble("TotalDeduction");
        payslip->netSalary = rs->getDouble("NetSalary");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return payslip;
}

void SalaryManager::paySalary()
{
    std::cout << std::fixed << std::setprecision(2); 

    Menu menu;
    DateManager dateManager;
    menu.displayLogo();
    paySalaryHeader();
    int year, month ,salaryID;
    double basicSalary=0, totalAllowance=0, travellingAllowance = 0,totalBonus=0,totalOvertime=0,grossPay=0, totalDeduction=0, netSalary=0;

    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Year            : ";
        std::cin >> year;
        if(year<0)
            std::cout << "\n"<< std::setw(90) << "Invalid year. Please enter a valid year." << std::endl;
    } while (year<0);
    
    do
    {
        std::cout  << "\n\n" << std::setw(72) << "Enter Month           : ";
        std::cin >> month;
        if(month<1||month>12)
            std::cout << "\n"<< std::setw(91) << "Invalid month. Please enter a valid month." << std::endl;
    } while (month<1||month>12);

    menu.displayLogo();
    paySalaryHeader();
    //get salary ID
    Salary_Schedule* sc = NULL;
    sc = searchSalarySchedule(year,month);
    salaryID = sc->salaryID;

    EmployeeManager em;
    DepartmentManager dm;
    Employee* head = NULL;
    //get employee after filtering
    head = getSalaryEmployees(salaryID);
    Employee* employee = head;

    Department* department = NULL;
    Position* position = NULL;

    menu.displayLogo();
    paySalaryHeader();

    if(employee==NULL)
    {
        std::cout << "\n\n" << std::setw(82) << "There is no unpaid salary." << std::endl;
        return;
    }

    //display salary for employee
    std::cout << std::right << " Year   : " << year << std::endl;
    std::cout << std::right << " Month  : " << dateManager.getMonthName(month) << std::endl;
    std::cout << std::right << " Salaries that are yet to be paid : " << std::endl;
    std::cout << std::right << "+" << std::setfill('-') << "-" << std::setw(256) << "+" << std::setfill(' ') << std::endl 
                            << "| Employee ID | Employee Name" << std::setw(50) << "| Department"  << std::setw(40) << "| Position" << std::setw(139) << "| Total Allowance(RM)| Total Bonus(RM) | Total Overtime(RM) | Total Deduction(RM) | Total Net Salary (RM) |" << std::endl
                            << "|" << std::setfill('-') << "-" << std::setw(256) << "|" << std::setfill(' ') << std::endl;
    Salary* salaryHead = NULL;
    Salary* salary = NULL;  
    while(employee!=NULL)
    {
        department = dm.searchDepartment(employee->departmentID);
        position = dm.searchPosition(employee->positionID);
        //insert data into salary linked list
        if(salaryHead == NULL)
        {
            salary = new Salary();
            salaryHead = salary;
        }
        else
        {
            salary->next = new Salary();
            salary = salary->next;
        }
        salary->employeeID = employee->id;
        salary->salaryID = salaryID;
        salary->basicSalary = employee->basicSalary;
        salary->totalAllowance = getTotalAllowance(employee->id);
        salary->totalBonus = getTotalBonus(employee->id,year,month);
        salary->totalOvertime = getTotalOvertime(employee->id,year,month);
        salary->grossSalary = salary->basicSalary + salary->totalAllowance + salary->totalBonus + salary->totalOvertime;
        salary->totalDeduction = getTotalDeduction(employee->id,year,month);
        salary->netSalary = salary->grossSalary - salary->totalDeduction;
        //display data to user
        std::cout << std::left << "| "  << std::setw(12) << employee->id  << "| " << std::setw(51) << employee->name << "| "  << std::setw(40) << department->departmentName << "| "  << std::setw(40) << position->positionName << "| " << std::setw(19) << salary->totalAllowance << "| " << std::setw(16) << salary->totalBonus << "| "  << std::setw(19) << salary->totalOvertime << "| "  << std::setw(20) << salary->totalDeduction << "| "  << std::setw(22) << salary->netSalary << "|"  << std::endl;
        employee = employee->next;
    }
    std::cout << std::right << "+" << std::setfill('-') << "-" << std::setw(256) << "+" << std::setfill(' ') << std::endl;


    char response;
    int excludedID;
    std::cout << "\n\n" << std::right << setw(100) << "Enter 'Y' if any employee is excluded from salary payment : " ;
    std::cin >> response;

    if(response=='Y'||response=='y')
    {
        std::vector <int> excludedIDs;
        do
        {
            do
            {
                std::cout << "\n\n" << std::right << std::setw(80) << "Enter the excluded employee ID or '-1' to terminate : ";
                std::cin >> excludedID;
                //assign salary pointer to head
                salary = salaryHead;

                while (salary != NULL) 
                {
                    if (excludedID == salary->employeeID) 
                        break;  // Found a matching employee ID, exit the loop
                    else 
                        salary = salary->next;
                }

                if (excludedID != -1 && salary == NULL) 
                    std::cout << "\n" << std::setw(88) << "Please enter a valid employee ID in the list. " << std::endl;
            }while (excludedID!=-1 && salary==NULL);

            if(excludedID!=-1)
                excludedIDs.push_back(excludedID);
        }while(excludedID!=-1);

        //delete excluded employee from linked list
        Salary* temp = NULL;
        Salary* prev = NULL;

        for(const int& excludedID : excludedIDs)
        {
            temp = salaryHead;
            while(temp!=NULL && temp->employeeID != excludedID)
            {
                prev = temp;
                temp = temp->next;
            }
            if(temp != NULL && temp->employeeID == excludedID)
            {
                if(temp == salaryHead)
                {
                    salaryHead = salaryHead->next;
                    delete temp;
                }
                else
                {
                    prev->next = temp->next;
                    delete temp;
                }
            }
        }
    }
    menu.displayLogo();
    paySalaryHeader();

    if(salaryHead == NULL)
    {
        std::cout << "\n\n" << std::setw(85) << "There is no salary to be paid." << std::endl;
        return;
    }

    //display paid salary for employee
    std::cout << std::right << " Year   : " << year << std::endl;
    std::cout << std::right << " Month  : " << dateManager.getMonthName(month) << std::endl;
    std::cout << std::right << " Salaries that are paid : " << std::endl;
    std::cout << std::right << "+" << std::setfill('-') << "-" << std::setw(168) << "+" << std::setfill(' ') << std::endl
                            << "| Employee ID | Employee Name" << std::setw(50) << "| Department"  << std::setw(40) << "| Position"  << std::setw(51) << "| Net Salary (RM) |" << std::endl
                            << "|" << std::setfill('-') << "-" << std::setw(168) << "|" << std::setfill(' ') << std::endl;
    salary = salaryHead;
    while(salary!=NULL)
    {
        employee = em.searchEmployee(salary->employeeID);
        department = dm.searchDepartment(employee->departmentID);
        position = dm.searchPosition(employee->positionID);
        std::cout << std::left << "| "  << std::setw(12) << employee->id  << "| " << std::setw(51) << employee->name << "| "  << std::setw(40) << department->departmentName << "| "  << std::setw(40) << position->positionName << "| " << std::setw(16) << salary->netSalary << "|" << std::endl;
        addSalary(salary);
        salary= salary->next;
    }
    std::cout << std::right << "+" << std::setfill('-') << "-" << std::setw(168) << "+" << std::setfill(' ') << std::endl;

    std::cout << std::right << "\n\n" << std::setw(87) << "[ Salaries are paid successfully ]" << std::endl ;
}

