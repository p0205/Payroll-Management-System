#ifndef ALLOWANCE_H
#define ALLOWANCE_H
#include <string>

class Allowance
{
    public:
    int allowanceID;
    std::string name, frequency;
    Allowance* next;
};

#endif