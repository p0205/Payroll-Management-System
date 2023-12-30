#ifndef BONUS_H
#define BONUS_H
#include <string>

class Bonus
{
    public:
    int bonusID;
    std::string name, frequency;
    Bonus* next;
};

#endif