#ifndef LEAVE_REQUEST_H
#define LEAVE_REQUEST_H
#include <string>

class LeaveRequest
{
    public:
    int ID, employeeID,leaveID,year;
    std::string startDate,endDate,requestDate,status;
    LeaveRequest* next;
};

#endif