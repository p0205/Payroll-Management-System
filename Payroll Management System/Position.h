#ifndef POSITION_H
#define POSITION_H
#include <string>
using namespace std;

class Position
{
    public:
    int positionID;
    string positionName,description;
    Position *next;
};

#endif