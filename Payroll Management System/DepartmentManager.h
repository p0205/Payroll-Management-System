#ifndef DEPARTMENTMANAGER_H
#define DEPARTMENTMANAGER_H
#include "DatabaseConnection.h"
#include "Department.h"
#include "Position.h"
#include "Dept_Position.h"
#include "Menu.h"



class DepartmentManager
{
    public:
    void DepartmentTransform(sql::ResultSet* rs, Department * department);
    void addDepartmentHeader();
    void deleteDepartmentHeader();
    void updateDepartmentHeader();
    void searchDepartmentHeader();
    void viewDepartmentHeader();
    void addPositionHeader();
    void deletePositionHeader();
    void viewPositionHeader();
    void addDepartmentPositionHeader();

    Department* searchDepartments();
    Department* searchDepartment(int id);
    Department* searchDepartment(string name);
    int IDorName();
    bool checkRepeatString(string name,string table,string column);
    void addDepartment();
    void deleteDepartment(int departmentID);
    void deleteDepartment();
    int updateDepartmentMenu();
    void updateDepartment(string column, string data, int departmentID);
    void updateDepartment(int departmentID);
    void updateDepartment();

    void viewDepartmentList();
    void viewDepartment(Department* department);
    void viewDepartment();

    Position* searchPosition(int id);
    Position* searchPosition(string name);
    Position* searchPositions();
    void viewPosition(Position* position);
    void viewPosition();
    void viewPositionList();
    void PositionTransform(sql::ResultSet* rs, Position* position);
    void addPosition();
    void deletePosition(int id);
    void deletePosition();
    void addDept_Position(int departmentID,int positionID,string description);
    void addDept_Position(int departmentID,int positionID);
    void addDept_Position();
    bool searchDept_Position(int departmentID,int positionID);
};

#endif