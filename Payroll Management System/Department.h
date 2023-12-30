#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include <string>
using namespace std;

class Department
{
    public:
    int departmentID;
    string departmentName;
    string contactNo;
    Department* next;
};

#endif