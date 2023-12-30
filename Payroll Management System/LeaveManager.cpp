#include "LeaveManager.h"
#include <iomanip>
#include <cmath>

void LeaveManager::deductLeaveBalanceHeader()
{
    std::cout <<std::setw(55) << "+" << std::setfill('-') << "-" <<std::setw(29) << "+" <<  std::setfill(' ') <<std::endl
                <<std::setw(55) << "|" <<  std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl                         
                <<std::setw(55) << "|" <<std::setw(21) << "Deduct Leave" <<std::setw(9) << "|" <<std::endl
                <<std::setw(55) << "|" <<std::setw(17) << "Balance" <<std::setw(13) << "|" <<std::endl
                <<std::setw(55) << "|" <<  std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl
                <<std::setw(55) << "+" << std::setfill('-') << "-" <<std::setw(29) << "+" <<  std::setfill(' ') <<std::endl <<std::endl;
}

void LeaveManager::manageLeaveRequestHeader()
{
    std::cout <<std::setw(55) << "+" <<std::setfill('-') << "-" <<std::setw(29) << "+" << std::setfill(' ') <<std::endl
                <<std::setw(55) << "|" << std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl                           
                <<std::setw(55) << "|" <<std::setw(21) << "Manage Leave" <<std::setw(9) << "|" <<std::endl
                <<std::setw(55) << "|" <<std::setw(18) << "Request" <<std::setw(12) << "|" <<std::endl
                <<std::setw(55) << "|" << std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl
                <<std::setw(55) << "+" <<std::setfill('-') << "-" <<std::setw(29) << "+" << std::setfill(' ') <<std::endl <<std::endl; 
}

void LeaveManager::assignLeaveQuotaHeader()
{
    std::cout <<std::setw(55) << "+" << std::setfill('-') << "-" <<std::setw(29) << "+" <<  std::setfill(' ') <<std::endl
                <<std::setw(55) << "|" <<  std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl                         
                <<std::setw(55) << "|" <<std::setw(21) << "Assign Leave" <<std::setw(9) << "|" <<std::endl
                <<std::setw(55) << "|" <<std::setw(18) << "Quota" <<std::setw(12) << "|" <<std::endl
                <<std::setw(55) << "|" <<  std::setfill(' ') << ' ' <<std::setw(29) << " |" <<std::endl
                <<std::setw(55) << "+" << std::setfill('-') << "-" <<std::setw(29) << "+" <<  std::setfill(' ') <<std::endl <<std::endl;
}

bool LeaveManager::checkRepeatInt(int input,string table,string column)
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

Leave* LeaveManager::searchLeave(int leaveID)
{
    DatabaseConnection dbConn;
    Leave* leave = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM `LEAVE` WHERE LeaveID = ?");
    ps->setInt(1,leaveID);
    sql::ResultSet* rs = ps->executeQuery();

    if(rs->next())
    {
        leave = new Leave();
        leave->leaveID = rs->getInt("LeaveID");  
        leave->leaveName = rs->getString("Name");  
        leave->description = rs->getString("Description");  
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return leave;
}

Leave* LeaveManager::searchLeaves()
{
    DatabaseConnection dbConn;
    Leave* leave = NULL;
    Leave* head = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM `LEAVE`");
    sql::ResultSet* rs = ps->executeQuery();
    while(rs->next())
    {   
        if(head == NULL)
        {
            leave = new Leave();
            head = leave;
        }
        else
        {
            leave->next = new Leave();
            leave = leave->next; 
        }
        leave->leaveID = rs->getInt("LeaveID");      
        leave->leaveName = rs->getString("Name");      
        leave->description = rs->getString("Description");      
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

void LeaveManager::viewLeaves()
{
    Leave* leave = NULL;
    leave = searchLeaves();
    if(leave!=NULL)
    {
        std::cout << std::setw(4) << "+" << std::setfill('-') <<"-" << std::setw(141) << "+" << std::setfill(' ') << std::endl
                  << std::setw(8)  << "| ID " << std::setw(13) << "| Name" << std::setw(45) <<"| Description"  << std::setw(80) << "|" << std::endl
                  << std::setw(4) << "|" << std::setfill('-') <<"-" << std::setw(141) << "|" << std::setfill(' ') << std::endl;
        while(leave!=NULL)
        {
            std::cout << std::left
                      << std::setw(3) << " " << "| "<< std::setw(9) << leave->leaveID << " | " << std::setw(35) << leave->leaveName << " | "  << std::setw(90) << leave->description  << "|" << std::endl;
            leave = leave->next;
        }
        std::cout << std::right
                  << std::setw(4) << "+" << std::setfill('-') <<"-" << std::setw(141) << "+" << std::setfill(' ') << std::endl;
    }
    else
    {
        std::cout << std::setw(82) << "No leave available." << std::endl;
    }
    delete leave;
}

int LeaveManager::assignLeaveQuota(int employeeID,int leaveID,int quota, int year)
{
    DatabaseConnection dbConn;
    Employee_Leave* emp_leave = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO EMPLOYEE_LEAVE (EmployeeID, LeaveID, Leave_Total,Year) VALUES (?,?,?,?)");
    ps->setInt(1,employeeID);
    ps->setInt(2,leaveID);
    ps->setInt(3,quota);
    ps->setInt(4,year);
    int rowAffected = ps->executeUpdate();
    ps->close();
    delete ps;
    return rowAffected;
}

Employee_Leave* LeaveManager::searchEmpLeave(int employeeID,int leaveID,int year)
{
    DatabaseConnection dbConn;
    Employee_Leave* emp_leave = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE_LEAVE WHERE EmployeeID = ? AND LeaveID = ? AND Year = ?" );
    ps->setInt(1,employeeID);
    ps->setInt(2,leaveID);
    ps->setInt(3,year);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        emp_leave = new Employee_Leave();
        emp_leave->employeeID = rs->getInt("EmployeeID");
        emp_leave->leaveID = rs->getInt("LeaveID");
        emp_leave->leaveTotal = rs->getInt("Leave_Total");
        emp_leave->leaveTaken = rs->getInt("Leave_Taken");
        emp_leave->leaveBalance = rs->getInt("Leave_Balance");
        emp_leave->year = rs->getInt("Year");
    }
    return emp_leave;
}

bool LeaveManager::checkRepeatEmpLeave(int employeeID,int leaveID,int year)
{
    DatabaseConnection dbConn;
    Employee_Leave* emp_leave = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE_LEAVE WHERE EmployeeID = ? AND LeaveID = ? AND Year = ?" );
    ps->setInt(1,employeeID);
    ps->setInt(2,leaveID);
    ps->setInt(3,year);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        return true;
    }
    return false;
}

Employee_Leave* LeaveManager::searchEmpLeaves(int employeeID,std::string date)
{
    DatabaseConnection dbConn;
    Employee_Leave* emp_leave = NULL;
    Employee_Leave* head = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM EMPLOYEE_LEAVE WHERE EmployeeID = ? AND Year = YEAR(?)" );
    ps->setInt(1,employeeID);
    ps->setString(2,date);
    sql::ResultSet* rs = ps->executeQuery();
    while(rs->next())
    {
        if(head == NULL)
        {
            emp_leave = new Employee_Leave();
            head = emp_leave;
        }
        else
        {
            emp_leave->next = new Employee_Leave();
            emp_leave = emp_leave->next;
        }
        emp_leave->employeeID = rs->getInt("EmployeeID");
        emp_leave->leaveID = rs->getInt("LeaveID");
        emp_leave->leaveTotal = rs->getInt("Leave_Total");
        emp_leave->leaveTaken = rs->getInt("Leave_Taken");
        emp_leave->leaveBalance = rs->getInt("Leave_Balance");
        emp_leave->year = rs->getInt("Year");
    } 
    return head;
}

Employee* LeaveManager::searchEmployees(int leaveID, int targetYear)
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
        if(!checkRepeatEmpLeave(rs->getInt("EmployeeID"),leaveID,targetYear))
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

Employee* LeaveManager::searchEmployeesByDepartment(int departmentID,int leaveID,int targetYear)
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
        if(!checkRepeatEmpLeave(rs->getInt("EmployeeID"),leaveID,targetYear))
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

Employee* LeaveManager::getLeaveEmployees(int leaveID, int targetYear)
{
    Menu menu;
    DateManager dateManager;
    menu.displayLogo();
    assignLeaveQuotaHeader();
    std::cout << std::setw(81) << "Assign Leave Quota To: " << std::endl
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
        employee = searchEmployees(leaveID,targetYear);
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
                assignLeaveQuotaHeader();
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
                    if(response != 'y'&&response!='Y')
                    {
                        menu.LeaveMenu();
                        return 0;
                    }
                }
            }
        } while (response == 'y' || response =='Y');
        
        //pass the found department ID to get all employees in that department
        employee = searchEmployeesByDepartment(departmentID,leaveID,targetYear);
        break;

    case 3:
        menu.displayLogo();
        assignLeaveQuotaHeader();
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
                    assignLeaveQuotaHeader();
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
                                    menu.LeaveMenu();
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
                                    menu.LeaveMenu();
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
                assignLeaveQuotaHeader();
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
                                    menu.LeaveMenu();
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
                                    menu.LeaveMenu();
                                else
                                    break;
                            }
                        }
                    }
                }while(response == 'y' || response == 'Y');
            }

            if (checkRepeatEmpLeave(employee->id, leaveID, targetYear))
            {
                employee = nullptr;
                std::cout << "\n" << std::setw(95) << "The leave is already assigned to this employee." << std::endl;
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

void LeaveManager::assignLeaveQuota()
{
    Menu menu;
    menu.displayLogo();
    assignLeaveQuotaHeader();
    int employeeID, leaveID, quota,year;
    bool valid;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO EMPLOYEE_LEAVE(EmployeeID,LeaveID,Leave_Total,Year) VALUES (?,?,?,YEAR(?))");
    viewLeaves();
    Leave* leave = NULL;

    do
    {
        std::cout << "\n\n" << std::setw(70) << "Enter Leave ID              : ";
        std::cin >> leaveID;
        leave = searchLeave(leaveID);
        if(leave==NULL)
            std::cout  << "\n" << std::setw(89)  << "Invalid leave ID. Please try again." << std::endl;
    } while (leave==NULL);

    DateManager dateManager;
    std::string currentDate = dateManager.getCurrentDate();
    year = dateManager.extractYear(currentDate);

    menu.displayLogo();
    assignLeaveQuotaHeader();
    Employee* head = NULL;
    head = getLeaveEmployees(leaveID,year);

    Employee* employee = head;
    DepartmentManager dm;
    Department* department = NULL;
    Position* position = NULL;
    menu.displayLogo();
    assignLeaveQuotaHeader();
    if(employee==NULL)
    {
        std::cout << "\n" << std::setw(87) << "No leave assignment is needed." << std::endl;
        return;
    }

    struct empLeaveQuota
    {
        int employeeID;
        int quota;
    };

    vector<empLeaveQuota> empLeaveQuotas;

    //display quota for each employee
    std::cout << std::right << std::setw(17) << "Choice       : " << std::left << leave->leaveName << std::endl;
    std::cout << std::right << std::setw(17) << "Year         : " << year << std::endl;
    std::cout << std::right << std::setw(2) << "+" << std::setfill('-') << "-" << std::setw(151) << "+" << std::setfill(' ') << std::endl
              << std::setw(16) << "| Employee Name" << std::setw(50) << "| Department"  << std::setw(40) << "| Position" << std::setw(35) << std::setw(48) << "| Quota (days) |" << std::endl
              << std::setw(2) << "|" << std::setfill('-') << "-" << std::setw(151) << "|" << std::setfill(' ') << std::endl;   

    while(employee!=NULL) 
    {
        int years = dateManager.calculateYearDifference(currentDate,employee->dateOfHire);

        if(leaveID == 500000)
        {
            if (years < 2)
                quota = 8;
            else if(years >= 2 && years < 5 )
                quota = 12;
            else
                quota = 16;
        }
        else if(leaveID == 500001)
        {
            if (years < 2)
                quota = 14;
            else if(years >= 2 && years < 5 )
                quota = 18;
            else
                quota = 22;
        }
        else if(leaveID == 500002)
            quota = 60;
        else if(leaveID == 500003)
            quota = 7;

        //get department name and position name
        department = dm.searchDepartment(employee->departmentID);
        position = dm.searchPosition(employee->positionID);

        std::cout << std::left << std::setw(1) << " " << "| " << std::setw(51) << employee->name << "| "  << std::setw(40) << department->departmentName << "| "  << std::setw(40) << position->positionName  << "| " << std::setw(13) << quota << "| " << std::endl;

        empLeaveQuota empLeaveQuota;
        empLeaveQuota.employeeID = employee->id;
        empLeaveQuota.quota = quota;
        //add element into empLeaveQuotas vector
        empLeaveQuotas.push_back(empLeaveQuota);

        //proceed to next element
        employee = employee->next;
    }
    std::cout << std::right << std::setw(2) << "+" << std::setfill('-') << "-" << std::setw(151) << "+" << std::setfill(' ') << std::endl;

    char confirm;
    std::cout << "\n\n" <<std::setw(104) << "Are you sure to assign the leave quota to this/these employee(s)? Enter Y/y to confirm: ";
    std::cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        employee = head;
        int rowAffected = 0;
        for(const empLeaveQuota& empLeaveQuota : empLeaveQuotas)
        {
            rowAffected = assignLeaveQuota(empLeaveQuota.employeeID,leaveID,empLeaveQuota.quota,year);
            if(rowAffected==0)
                std::cout  << "\n\n" << std::setw(90) << "Fail to insert data." << std::endl;        
            employee = employee->next;
        }
        std::cout << "\n" <<std::setw(90) << "[ Leave quota is assigned successfully ]" << std::endl;
    }
    else
    {
        std::cout << "\n" <<std::setw(103) << "[ Assignment process has been cancelled. No changes have been made ]" << std::endl;
    }   
}

LeaveRequest* LeaveManager::searchLeaveRequest(int ID)//
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT EmployeeID,LeaveID,StartDate,EndDate,RequestDate, Year(StartDate) AS `Year` FROM LEAVE_REQUEST WHERE ID = ?");
    ps->setInt(1,ID);
    sql::ResultSet* rs = ps->executeQuery();
    LeaveRequest* leaveRequest = NULL;
    if(rs->next())
    {
        leaveRequest = new LeaveRequest();
        leaveRequest->employeeID = rs->getInt("EmployeeID");
        leaveRequest->leaveID = rs->getInt("LeaveID");
        leaveRequest->startDate = rs->getString("StartDate");
        leaveRequest->endDate = rs->getString("EndDate");
        leaveRequest->requestDate = rs->getString("RequestDate");
        leaveRequest->year = rs->getInt("Year");
    }
    return leaveRequest;
}

int LeaveManager::displayLeaveRequest()
{
    DatabaseConnection dbConn;
    EmployeeManager em;
    Employee* employee = NULL;
    DepartmentManager dm;
    Department* department = NULL;
    Position* position = NULL;
    Employee_Leave* empLeave = NULL;
    Leave* leave= NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT ID,EmployeeID,LeaveID,StartDate,EndDate,RequestDate,YEAR(StartDate) AS `Year` FROM LEAVE_REQUEST WHERE Status = 'Pending Approved'");
    sql::ResultSet* rs = ps->executeQuery();
    if(!rs->next())
    {
        std::cout << std::right << std::setw(87) << "No pending approved leave available." << std::endl;
        return 0;
    }

    else
    {
    std::cout << std::right << "+" << std::setfill('-') << "-" << std::setw(262) << "+" << std::setfill(' ') << std::endl
              << "| ID" << std::setw(26) << "| Employee Name" << std::setw(50) << "| Department"  << std::setw(40) << "| Position" << std::setw(46) << "| Leave Type"  << std::setw(30) << "| Start Date"  << std::setw(15) << "| End Date"  << std::setw(29) << "| Leave Balance (days)"  << std::setw(0) << "| Request Date"  << std::setw(10) << "|" << std::endl
              << "|" << std::setfill('-') << "-" << std::setw(262) << "|" << std::setfill(' ') << std::endl;   
        employee = em.searchEmployee(rs->getInt("EmployeeID"));
        department = dm.searchDepartment(employee->departmentID);
        position = dm.searchPosition(employee->positionID);
        empLeave = searchEmpLeave(employee->id,rs->getInt("LeaveID"),rs->getInt("Year"));
        leave = searchLeave(rs->getInt("LeaveID"));
        std::cout << std::left << "| " << std::setw(13) << rs->getInt("ID") << "| " << std::setw(51) << employee->name << "| "  << std::setw(40) << department->departmentName << "| "  << std::setw(42) << position->positionName << "| "  << std::setw(28) << leave->leaveName << "| "  << std::setw(15) << rs->getString("StartDate") << "| " << std::setw(15) << rs->getString("EndDate")  << "| " << std::setw(20) << empLeave->leaveBalance << "| " << std::setw(21) << rs->getString("RequestDate") << "| " << std::endl;

        while(rs->next())
        {
            employee = em.searchEmployee(rs->getInt("EmployeeID"));
            department = dm.searchDepartment(employee->departmentID);
            position = dm.searchPosition(employee->positionID);
            empLeave = searchEmpLeave(employee->id,rs->getInt("LeaveID"),rs->getInt("Year"));
            leave = searchLeave(rs->getInt("LeaveID"));
            std::cout << std::left << "| " << std::setw(13) << rs->getInt("ID") << "| " << std::setw(51) << employee->name << "| "  << std::setw(40) << department->departmentName << "| "  << std::setw(42) << position->positionName << "| "  << std::setw(28) << leave->leaveName << "| "  << std::setw(15) << rs->getString("StartDate") << "| " << std::setw(15) << rs->getString("EndDate")  << "| " << std::setw(20) << empLeave->leaveBalance << "| " << std::setw(21) << rs->getString("RequestDate") << "| " << std::endl;
        }
    std::cout << std::right << "+" << std::setfill('-') <<"-" << std::setw(262) << "+" << std::setfill(' ') << std::endl;
    }
    delete employee;
    delete department;
    delete position;
    delete empLeave;
    delete leave;
    return 1;
}

void LeaveManager::rejectLeaveRequest(int ID)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE LEAVE_REQUEST SET Status = 'Rejected' WHERE ID = ?");
    ps->setInt(1,ID);
    int rowAffected = ps->executeUpdate();
    ps->close();
    delete ps;
}

void LeaveManager::approveLeaveRequest()
{
    DatabaseConnection dbConn;
    int rowAffected;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT EmployeeID,LeaveID, Year(StartDate) AS `Year`,(DATEDIFF(EndDate, StartDate)+1) AS `LeaveTaken` FROM LEAVE_REQUEST WHERE Status = 'Pending Approved'");
    sql::ResultSet* rs = ps->executeQuery();
    while(rs->next())
    {
        Employee_Leave* empLeave = searchEmpLeave(rs->getInt("EmployeeID"),rs->getInt("LeaveID"),rs->getInt("Year"));
        sql::PreparedStatement* psUpdate = dbConn.prepareStatement("UPDATE EMPLOYEE_LEAVE SET Leave_Taken = ? WHERE EmployeeID = ? AND LeaveID = ? AND Year = ?");
        psUpdate->setInt(1,empLeave->leaveTaken + rs->getInt("LeaveTaken"));
        psUpdate->setInt(2,rs->getInt("EmployeeID"));
        psUpdate->setInt(3,rs->getInt("LeaveID"));
        psUpdate->setInt(4,rs->getInt("Year"));
        rowAffected = psUpdate->executeUpdate();
        psUpdate->close();
        delete psUpdate;
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    sql::PreparedStatement* psUpdateStatus = dbConn.prepareStatement("UPDATE LEAVE_REQUEST SET Status = 'Approved' WHERE Status = 'Pending Approved'");
    rowAffected = psUpdateStatus->executeUpdate();
    psUpdateStatus->close();
    delete psUpdateStatus;
}

void LeaveManager::manageLeaveRequest()
{
    Menu menu;
    menu.displayLogo();
    manageLeaveRequestHeader();
    int hasResult = displayLeaveRequest();
    if(hasResult == 0)
        return;
    LeaveRequest* leaveRequest;
    std::vector <int> rejectedRequests;
    int response;
    bool repeat;
    std::cout << std::right << std::setw(120) << "Enter Request ID to be rejected, other requests will be approved and Enter '-1' to terminate " << endl;
    std::cout << std::setw(26) << " " << std::setw(94) << std::setfill('*') << "*"  << std::setfill(' ')  << std::endl;
    while(response!=-1)
    {
        do
        {
            repeat = false;
            std::cout << std::right << std::setw(72) << "Request ID to be rejected : ";
            std::cin >> response;
            leaveRequest = searchLeaveRequest(response);
            if(leaveRequest==NULL && response!=-1)
            std::cout << std::right << std::setw(95) << "Invalid Request ID. Please enter a valid Request ID." << std::endl;
            for(const int& rejectedRequest:rejectedRequests )
            {
                if(rejectedRequest == response )
                repeat = true;
            }
        } while (leaveRequest==NULL&& response!=-1);
        if(response!=-1 && !repeat)
            rejectedRequests.push_back(response);
    }
    if(!rejectedRequests.empty())
    {
        menu.displayLogo();
        manageLeaveRequestHeader();
        hasResult = displayLeaveRequest();
        std::cout << "\n\n" << std::setw(82) << "Rejected Request ID" << std::endl;
        std::cout << std::setw(50) << " " << std::setw(46) << std::setfill('*') << "*"  << std::setfill(' ') << std::endl ;
        for(const int& rejectedRequest:rejectedRequests)
        {
            std::cout << "\n" << std::setw(75) << rejectedRequest << std::endl;
        }
        char confirm;
        std::cout << std::right << "\n\n" << std::setw(72) << "Are you sure to reject this/these request(s)? Enter Y to confirm : ";
        std::cin >> confirm;
        if(confirm=='Y'||confirm=='y')
        {
            for(const int& rejectedRequest:rejectedRequests)
            {
                    rejectLeaveRequest(rejectedRequest);
            }
            approveLeaveRequest();
            std::cout << std::right << "\n\n" << std::setw(110) << "[ The request(s) is/are rejected successfully. Other request(s) is/are approved ]" << std::endl;
        }
        else
        {
            std::cout << std::right << "\n\n" << std::setw(94) << "[ The operation is cancelled. No change is made ]" << std::endl;
        }
    }
    else
    {
        approveLeaveRequest();
        std::cout << std::right << "\n\n" << std::setw(93) << "[ The request(s) is/are approved successfully ]" << std::endl;
    }
}

void LeaveManager::addLeaveDeduction(int employeeID, double amount, std::string date)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO EMPLOYEE_DEDUCTION(EmployeeID, DeductionID, Amount, Date) VALUES (?,400003,?,?)");
    ps->setInt(1,employeeID);
    ps->setDouble(2,amount);
    ps->setString(3,date);
    ps->executeUpdate();
    ps->close();
    delete ps;
}

double LeaveManager::calculateLeaveDeduction(Employee* employee, int deductionDays)
{
    std::cout << std::fixed << std::setprecision(2); 
    double leaveDeduction = 0;
    leaveDeduction = (employee->basicSalary/26) * deductionDays;
    return leaveDeduction;
} 

//search EmployeeLeaveDeduction list
std::vector <EmployeeLeave> LeaveManager::searchLeaveDeductionEmployees()
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT EmployeeID, LeaveID, Leave_Balance FROM EMPLOYEE_LEAVE WHERE Leave_Balance < 0 ");
    sql::ResultSet* rs = ps->executeQuery();
    std::vector <EmployeeLeave> empLeaves;

    EmployeeManager em;
    Employee* employee = NULL;
    while(rs->next())
    {
        EmployeeLeave empLeave;
        empLeave.employeeID = rs->getInt("EmployeeID");
        employee = em.searchEmployee(rs->getInt("EmployeeID"));
        empLeave.leaveID = rs->getInt("LeaveID");
        empLeave.deductionAmount = calculateLeaveDeduction(employee,abs(rs->getInt("Leave_Balance")));
        empLeaves.push_back(empLeave);
    }
    delete employee;
    return empLeaves;
}

void LeaveManager::displayLeaveDeductionEmployees(const std::vector<EmployeeLeave>& empLeaves)
{
    EmployeeManager em;
    Employee* employee = NULL;
    DepartmentManager dm;
    Department* department = NULL;
    Position* position = NULL;
    Leave* leave = NULL;
    std::cout << std::right << "+" << std::setfill('-') << "-" << std::setw(184) << "+" << std::setfill(' ') << std::endl
              << "| Employee Name" << std::setw(50) << "| Department"  << std::setw(40) << "| Position"  << std::setw(40)  << "| Leave "  << std::setw(40)  << "| Deduction Amount(RM)" << "|" << std::endl
              << "|" << std::setfill('-') <<"-" << std::setw(184) << "|" << std::setfill(' ') << std::endl;   


    for(const EmployeeLeave& empLeave : empLeaves)
    {
        employee = em.searchEmployee(empLeave.employeeID);
        department = dm.searchDepartment(employee->departmentID);
        position = dm.searchPosition(employee->positionID);
        leave = searchLeave(empLeave.leaveID);
        std::cout << std::left << "| " << std::setw(51) << employee->name << "| "  << std::setw(40) << department->departmentName << "| "  << std::setw(40) << position->positionName << "| "   << std::setw(24) << leave->leaveName << "| " << std::setw(20) << empLeave.deductionAmount << "|" << std::endl;
    }
    std::cout << std::right << "+" << std::setfill('-') << "-" << std::setw(184) << "+" << std::setfill(' ') << std::endl;
    delete employee;
    delete department;
    delete position;
}

int LeaveManager::resetLeave(int employeeID, int leaveID, int year)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE EMPLOYEE_LEAVE SET Leave_Total = 0 , Leave_Taken = 0, Leave_Balance = 0 WHERE EmployeeID = ? AND LeaveID = ? AND Year = ?");
    ps->setInt(1,employeeID);
    ps->setInt(2,leaveID);
    ps->setInt(3,year);
    int affectedRow = ps->executeUpdate();
    return affectedRow;
}

void LeaveManager::conductDeduction_Leave()
{
    Menu menu;
    DeductionManager deductionManager;
    menu.displayLogo();
    deductionManager.assignDeductionHeader();
    int leaveID, year;
    cout << "Test " << endl;
    std::vector <EmployeeLeave> empLeaves = searchLeaveDeductionEmployees();

    menu.displayLogo();
    deductionManager.assignDeductionHeader();

    if(empLeaves.empty())
    {
        std::cout<< std::setw(83) << "No deduction is needed. " << std::endl; 
        return;       
    }
    else
    {
        displayLeaveDeductionEmployees(empLeaves);
        char confirm;
        std::cout << "\n\n" <<std::setw(104) << "Are you sure to assign deduction to this/these employee(s)? Enter Y/y to confirm: ";
        std::cin >> confirm;
        if(confirm == 'Y'|| confirm=='y')
        {
            DateManager dateManager;
            DeductionManager dm;
            std::string date = dateManager.getCurrentDate();

                //loop for each element in the vector to assign each element's deduction
            for(const EmployeeLeave& empLeave : empLeaves)
            {
                //assign deduction for current element of vector
                dm.assignDeduction(empLeave.employeeID, 400003 ,empLeave.deductionAmount,date);
                //reset leave to 0 if deduction is conducted to remove employee from deduction list
                resetLeave(empLeave.employeeID,leaveID,year);
            }
            std::cout << "\n" <<std::setw(89) << "[ Deduction is conducted successfully ]" << std::endl;
        }
        else
        {
            std::cout << "\n" <<std::setw(103) << "[ Deduction Conduction has been cancelled. No changes have been made ]" << std::endl;
        }   
    }
}

void LeaveManager::sendLeaveRequest()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(20) << "Send Leave" << setw(10) << "|" << endl;
    cout << setw(55) << "|" << setw(19) << "Request" << setw(11) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 

    int employeeID, leaveID;
    std::string startDate,endDate,reqeustDate;


    EmployeeManager em;
    Employee* employee = NULL;
    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Employee ID                  : " ;
        std::cin >> employeeID;
        employee = em.searchEmployee(employeeID);
        if(employee==NULL)
            std::cout << "\n" << std::setw(90) << "The employee is not found." ;
    } while (employee==NULL);
    
    LeaveManager lm;
    Leave* leave = NULL;
    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Leave ID                     : " ;
        std::cin >> leaveID;
        leave = lm.searchLeave(leaveID);
        if(leave==NULL)
            std::cout << "\n" << std::setw(89) << "The leave is not found. Enter Y/y to retry: ";
    } while (leave==NULL);
    

    DateManager dateManager;
    bool validDate,validEndDate;
    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Leave Start Date (YYYY/MM/DD): " ;
        std::cin >> startDate;
        validDate = dateManager.isValidDate(startDate);
        if(!validDate)
            std::cout  << "\n\n" << std::setw(90)<< "Invalid date or format. Please try again." << std::endl;        
    } while (!validDate);

    do
    {
        std::cout << "\n\n" << std::setw(72) << "Enter Leave End Date (YYYY/MM/DD)  : " ;
        std::cin >> endDate;
        validDate = dateManager.isValidDate(startDate);
        validEndDate = dateManager.isValidEndDate(startDate,endDate);
        if(!validDate||!validEndDate)
            std::cout  << "\n\n" << std::setw(90)<< "Invalid date or format. Please try again." << std::endl;        
    } while (!validDate||!validEndDate);

    reqeustDate = dateManager.getCurrentDate();

    char confirm;
    std::cout << "\n\n" << std::setw(72) << "Enter Y to send leave request      : ";
    std::cin >> confirm;
    if(confirm=='Y'||confirm=='y')
        insertData(employeeID,leaveID,startDate,endDate,reqeustDate);
    else
    std::cout << "\n\n" << std::setw(80) << "Request is cancelled." << std::endl;
}

void LeaveManager::insertData(int employeeID,int leaveID,std::string startDate,std::string endDate, std::string requestDate)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO LEAVE_REQUEST(EmployeeID,LeaveID,StartDate,EndDate,RequestDate) VALUES (?,?,?,?,?)");
    ps->setInt(1,employeeID);
    ps->setInt(2,leaveID);
    ps->setString(3,startDate);
    ps->setString(4,endDate);
    ps->setString(5,requestDate);
    int rowAffected = ps->executeUpdate();
    if(rowAffected==0)
        std::cout << "\n\n" << std::setw(81) << "Failed to insert data. " << std::endl;
    else
        std::cout << "\n\n" << std::setw(84) <<  "Reqeust is sent successfully." << std::endl;
}