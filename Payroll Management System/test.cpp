#include <iostream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cmath>
using namespace std;
#include <fstream>
#include <iostream>


int main() 
{
    cout<< endl;
    cout<< endl;
    cout << setw(90) << "Please choose an operation from menu.\n\n";
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(41) <<  "--------- Manage Order ---------" << setw(9) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(29) << "1. Add Order" << setw(21)<< "|" << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(32) << "2. Delete Order" << setw(18) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(32) << "3. Update Order" << setw(18) << "|"<< endl;
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;

    return 0;
}
