#ifndef LEAVE_H
#define LEAVE_H
#include <string>

class Leave
{
    public:
    int leaveID,year;
    std::string leaveName,description;
    Leave* next;
};

#endif