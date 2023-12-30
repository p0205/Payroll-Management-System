#include <string>
using namespace std;
#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee
{
    public:
    string name,address,email,dateOfHire,contactNo,dateofBirth,maritalStatus,WorkerType;
    char gender;
    int id,departmentID,positionID,isDisabled,isResident; 
    double basicSalary;
    Employee *next;
};

#endif