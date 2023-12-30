#ifndef LEAVEMANAGER_H
#define LEAVEMANAGER_H
#include "Leave.h"
#include "DatabaseConnection.h"
#include "Employee_Leave.h"
#include "LeaveRequest.h"
#include "EmployeeManager.h"
#include "Menu.h"

struct EmployeeLeave
{
    int employeeID;
    int leaveID;
    double deductionAmount;
};

class LeaveManager
{
    public:
    void deductLeaveBalanceHeader();
    void manageLeaveRequestHeader();
    void assignLeaveQuotaHeader();
    bool checkRepeatInt(int input,string table,string column);
    Leave* searchLeave(int leaveID);
    Leave* searchLeaves();
    void viewLeaves();
    int assignLeaveQuota(int employeeID,int leaveID,int quota, int year);
    Employee_Leave* searchEmpLeave(int employeeID,int leaveID,int year);
    bool checkRepeatEmpLeave(int employeeID,int leaveID,int year);
    Employee_Leave* searchEmpLeaves(int employeeID,std::string date);
    Employee* searchEmployees(int leaveID, int targetYear);
    Employee* searchEmployeesByDepartment(int departmentID,int leaveID,int targetYear);
    Employee* getLeaveEmployees(int leaveID, int targetYear);
    void assignLeaveQuota();
    LeaveRequest* searchLeaveRequest(int ID);
    int displayLeaveRequest();
    void rejectLeaveRequest(int ID);
    void approveLeaveRequest();
    void manageLeaveRequest();
    double calculateLeaveDeduction(Employee* employee, int deductionDays);    
    void addLeaveDeduction(int employeeID, double amount, std::string date);
    std::vector <EmployeeLeave> searchLeaveDeductionEmployees();
    void displayLeaveDeductionEmployees(const std::vector<EmployeeLeave>& empLeaves);
    int resetLeave(int employeeID, int leaveID, int year);

    void conductDeduction_Leave();

    void sendLeaveRequest();
    void insertData(int employeeID,int leaveID,std::string startDate,std::string endDate, std::string requestDate);

};


#endif