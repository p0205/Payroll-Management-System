#ifndef EMPLOYEE_DEPENDANT_H
#define EMPLOYEE_DEPENDANT_H
#include <string>
using namespace std;

class Employee_Dependant
{
    public:
    int dependantID, employeeID;
    string relationship;
    Employee_Dependant *next;
};

#endif