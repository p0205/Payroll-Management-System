#ifndef DATE_MANAGER_H
#define DATE_MANAGER_H
#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>

class DateManager
{
    public:
    int calculateAge(const std::string& dateOfBirth);
    bool isValidDate(std::string dateStr);
    bool isAfterHireDate(std::string hireDate,int year, int month);
    std::string getMonthName(int month);
    std::string getCurrentDate();
    int extractYear(const std::string& currentDate);
    int calculateYearDifference(const std::string& date1, const std::string& date2);
    bool isValidEndDate(const std::string& startDate, const std::string& endDate);
};

#endif