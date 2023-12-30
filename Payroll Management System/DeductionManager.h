#ifndef DEDUCTIONMANAGER_H
#define DEDUCTIONMANAGER_H
#include "Deduction.h"
#include "DatabaseConnection.h"
#include "Employee_Deduction.h"
#include "Menu.h"

class DeductionManager
{
    public:
    void assignDeductionHeader();
    bool checkRepeatString(string input,string table,string column);
    bool checkRepeatInt(int input,string table,string column);
    bool checkValidChar(char response);
    bool checkValidDouble(double input, double max);
    Deduction* searchDeduction(int deductionID);
    Deduction* searchDeductions();
    Employee_Deduction* getEmployeeDeductions(int employeeID, int year,int month);
    double searchEmpDeduction(int employeeID,int deductionID, int targetYear, int targetMonth);
    bool checkRepeatEmpDeduction(int employeeID,int deductionID, int targetYear, int targetMonth);
    Employee* searchEmployees(int deductionID,int targetYear, int targetMonth);
    Employee* searchEmployeesByDepartment(int departmentID,int deductionID,int targetYear, int targetMonth);
    Employee* getDeductionEmployees(int deductionID, int targetYear, int targetMonth);


    void viewDeductions();
    void addDeduction(std::string deductionName, std::string type, std::string description);
    void addDeduction(std::string deductionName, std::string type);
    void addDeduction();
    void assignDeduction(int employeeID,int deductionID, double amount, std::string date);
    void assignDeduction();
    // double calculateTaxableIncome();
    // double calculateMonthlyTax(double taxableIncome);
    // void calculateTax();
    
    double getEmployeeEPF(double amount,int age);
    double getEmployerEPF(double amount,int age);
    double getEmployeeSosco(double basicSalary);
    double getEmployerSosco(double basicSalary);
    double getEIS(double basicSalary);
    double getAccumulatedDeduction(int employeeID, int deductionID, int targetYear, int targetMonth);

    int getNoOfQualifyingChildren(Employee* employee);
    double getAccumulatedAdditionalRemuneration(int employeeID, int targetYear , int targetMonth);
    double getAccumulatedNormalRemuneration(int employeeID, int targetYear , int targetMonth);
    double getCurrentNormalRemuneration(int employeeID, int targetYear , int targetMonth);
    double getCurrentAdditionalRemuneration(int employeeID, int targetYear , int targetMonth);
 
    double calculatePforNormalRemuneration(Employee* employee, int targetYear, int targetMonth);
    double calculatePforAdditionalRemuneration(Employee* employee, int targetYear, int targetMonth);
    double calculateTotalTaxForAYear(double p, Employee* employee,int targetYear, int targetMonth);
    double calculateTotalMTDForAYear(double MTD, int employeeID, int targetYear, int targetMonth);

    double calculateNormalMTD(double p, int employeeID,int targetYear, int targetMonth);
    double calculateREP_KWASR_C_SUITE_MTD(double p, int employeeID,int targetYear, int targetMonth);
    double calculateNetMTD(Employee* employee,int targetYear, int targetMonth);
    void assignDeduction_MTD();
    void roundingUpToNearest5Cents(double &amount);
    void assignDeduction_EPF();
    void assignDeduction_Socso();
    void assignDeduction_EIS();
    void assignNewZakat();
    void assignDeduction_Zakat();
    void assignDeduction_TaxRelief(); 
};

#endif