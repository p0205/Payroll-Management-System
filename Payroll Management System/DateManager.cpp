#include "DateManager.h"

int DateManager::calculateAge(const std::string& dateOfBirth) 
{
    // Get the current time
    std::time_t currentTime = std::time(nullptr);

    // Convert the date of birth string to a tm structure
    std::tm dob = {};
    std::istringstream dateStream(dateOfBirth);
    dateStream >> dob.tm_year;  // Years since 1900
    dateStream.ignore();        // Ignore the '/'
    dateStream >> dob.tm_mon;   // Month (0-based)
    dateStream.ignore();        // Ignore the '/'
    dateStream >> dob.tm_mday;  // Day

    // Adjust the year and month to be 0-based and 0-11 respectively
    dob.tm_year -= 1900;
    dob.tm_mon--;

    // Convert the tm structure to a time_t object
    std::time_t dobTime = std::mktime(&dob);

    // Calculate the age in years
    std::tm* localTime = std::localtime(&currentTime);
    int age = localTime->tm_year - dob.tm_year;

    // Adjust the age if the birthday hasn't occurred yet this year
    if (localTime->tm_mon < dob.tm_mon || (localTime->tm_mon == dob.tm_mon && localTime->tm_mday < dob.tm_mday)) {
        age--;
    }

    return age;
}

bool DateManager::isValidDate(std::string dateStr)
{
    int year, month, day;
    std::istringstream iss(dateStr);
    char delimiter;

    if (iss >> year >> delimiter >> month >> delimiter >> day && delimiter == '/')
    {
    std::tm timeInfo = {0};
    timeInfo.tm_year = year - 1900;
    timeInfo.tm_mon = month - 1;
    timeInfo.tm_mday = day;

    std::time_t time = std::mktime(&timeInfo);

    return timeInfo.tm_year == year - 1900 &&
           timeInfo.tm_mon == month - 1 &&
           timeInfo.tm_mday == day &&
           time != -1;
    }
    else
    {
        return false;
    }
}

bool DateManager::isAfterHireDate(std::string hireDate,int year, int month)
{
    char delimiter;
    bool afterHireDate;
    int hireYear, hireMonth, hireDay;
    std::istringstream hireDateStream(hireDate);
    if (hireDateStream >> hireYear >> delimiter >> hireMonth >> delimiter >> hireDay && delimiter == '-')
    {
        if(hireYear > year || (hireYear == year && hireMonth > month))
            afterHireDate = false;
        else
            afterHireDate = true;
    }
    return afterHireDate;
}

std::string DateManager::getMonthName(int month)
{
    std::string monthName; 
    switch (month)
    {
    case 1:
        monthName =  "Jan";
        break;
    case 2:
        monthName =  "Feb";
        break;
    case 3:
        monthName = "Mar";
        break;
    case 4:
        monthName = "Apr";
        break;
    case 5:
        monthName = "May";
        break;
    case 6:
        monthName = "Jun";
        break;
    case 7:
        monthName = "Jul";
        break;
    case 8:
        monthName = "Aug";
        break;
    case 9:
        monthName = "Sep";
        break;
    case 10:
        monthName = "Oct";
        break;
    case 11:
        monthName = "Nov";
        break;
    case 12:
        monthName = "Dec";
        break;
    default:
        break;
    }
    return monthName;
}

std::string DateManager::getCurrentDate() 
{
    // Get the current time
    std::time_t currentTime = std::time(nullptr);

    // Convert the current time to a string
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y/%m/%d", std::localtime(&currentTime));

    // Return the formatted date string
    return std::string(buffer);
}

int DateManager::extractYear(const std::string& currentDate) 
{
   // Parse the date string
    std::tm tm = {};
    std::istringstream ss(currentDate);
    char discard; // To discard separators

    // Extract year, month, and day using formatted input
    ss >> tm.tm_year >> discard >> tm.tm_mon >> discard >> tm.tm_mday;

    // Check for parsing failure
    if (ss.fail()) {
        std::cerr << "Failed to parse date: " << currentDate << std::endl;
        return -1; // Indicate an error (you can choose a suitable error code)
    }

    // Adjust year and month (since tm_year is years since 1900, and tm_mon is 0-based)
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;

    // Extract the year
    int year = tm.tm_year + 1900;
    return year;
}

int DateManager::calculateYearDifference(const std::string& currentDate, const std::string& hireDate) {
    // Parse date strings
    std::tm timeinfo1 = {};
    std::tm timeinfo2 = {};

    strptime(hireDate.c_str(), "%Y-%m-%d", &timeinfo1);
    strptime(currentDate.c_str(), "%Y-%m-%d", &timeinfo2);

    // Calculate difference in years
    int yearDiff = timeinfo2.tm_year - timeinfo1.tm_year;

    // Adjust for months and days
    if (timeinfo2.tm_mon < timeinfo1.tm_mon || (timeinfo2.tm_mon == timeinfo1.tm_mon && timeinfo2.tm_mday < timeinfo1.tm_mday)) {
        yearDiff--;
    }

    return yearDiff;
}

bool DateManager::isValidEndDate(const std::string& startDate, const std::string& endDate) {
    // Convert string dates to tm structures
    std::tm startTm = {};
    std::tm endTm = {};

    if (strptime(startDate.c_str(), "%Y/%m/%d", &startTm) == nullptr ||
        strptime(endDate.c_str(), "%Y/%m/%d", &endTm) == nullptr) {
        // Invalid date format
        return false;
    }

    // Compare dates
    if (std::mktime(&endTm) > std::mktime(&startTm)) {
        return true; // endDate is after startDate
    } else {
        return false; // endDate is not after startDate
    }
}