#ifndef EMPLOYEE_LEAVE_H
#define EMPLOYEE_LEAVE_H


class Employee_Leave
{
    public:
    int ID, employeeID, leaveID,year, leaveTotal, leaveTaken,leaveBalance;
    Employee_Leave* next;
};

#endif