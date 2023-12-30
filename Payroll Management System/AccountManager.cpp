#include "AccountManager.h"
#include "DatabaseConnection.h"
#include "Menu.h"
#include <iomanip>
#include <fstream>
#include <iostream>
#include <termios.h>
#include <unistd.h>

void disableEcho() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void enableEcho() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

std::string AccountManager::login()
{
    Menu menu;
    bool valid;
    char ch;
    std::string role = "";
    menu.displayLogo();
    std::cout << std::setw(111)<< "************** [ Streamline Your Payroll, Empower Your Business ] **************" << std::endl; 
    string username, password;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT Role FROM ACCOUNT WHERE Username = ? AND Password = ?");
    std::cout << "\n\n" << std::setw(73) << "Enter username: ";
    std::cin >> username;

    disableEcho();
    std::cout << "\n\n" <<std::setw(73) << "Enter password: ";
    std::cin >> password;
    enableEcho();

    ps->setString(1,username);
    ps->setString(2,password);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        role = rs->getString("Role");
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return role;
}
