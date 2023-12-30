#include <string>
using namespace std;
#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account
{
public:
    string username,password,name;
    Account* next;

};

#endif