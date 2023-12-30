#ifndef DEDUCTION_H
#define DEDUCTION_H
#include <string>

class Deduction
{
    public:
    int deductionID;
    std::string name,type,description;
    Deduction* next;
};
#endif