#include <iostream>
#include <iomanip>
#include "Menu.h"
#include <string>
using namespace std;

 void start();

int main() 
{ 
    start();
    return 0;
}

void start()
{
    Menu menu;
    AccountManager am;
    std::string role = am.login();
    if(!role.empty())
    {
        //get role
        //direct to different menu
        if(role=="Admin")
            menu.adminMainMenu();
        else if(role=="Manager")
            menu.managerMainMenu();
        else if(role == "Employee") //dummy page
        {
            Menu menu;
            menu.displayLogo();
            LeaveManager lm;
            lm.sendLeaveRequest();
        }
    }
    else
    {
        char again;
        cout << "\n\n" << setw(95) << "Invalid username or password. Enter Y/y to retry: ";
        cin >> again;
        if(again == 'Y'||again== 'y')
        {
            start();
        }
        else
        {
            menu.exitPage();
        }
    }   

}




