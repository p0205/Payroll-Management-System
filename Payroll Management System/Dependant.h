#ifndef DEPENDANT_H
#define DEPENDANT_H
#include <string>
using namespace std;

class Dependant
{
    public:
    int dependantID;
    string name,dateOfBirth, maritalStatus;
    bool isWorking, isStudyingDiplomaOrHigher,isDisabled;
    Dependant* next;
};

#endif