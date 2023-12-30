#include "DepartmentManager.h"
#include <iomanip>

void DepartmentManager::addDepartmentHeader()
{
    cout << setw(85) << "+-----------------------------+" << endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "|        Add Department       |"<< endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "+-----------------------------+" << endl << endl;
}

void DepartmentManager::deleteDepartmentHeader()
{
    cout << setw(85) << "+-----------------------------+" << endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "|      Delete Department      |"<< endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "+-----------------------------+" << endl << endl;  
}

void DepartmentManager::updateDepartmentHeader()
{
    cout << setw(85) << "+-----------------------------+" << endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "|      Update Department      |"<< endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "+-----------------------------+" << endl << endl;
}

void DepartmentManager::searchDepartmentHeader()
{
    cout << setw(85) << "+-----------------------------+" << endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "|      Search Department      |"<< endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "+-----------------------------+" << endl << endl;
}

void DepartmentManager::viewDepartmentHeader()
{
    cout << setw(85) << "+-----------------------------+" << endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "|       View Department       |"<< endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "+-----------------------------+" << endl << endl;
}

void DepartmentManager::addPositionHeader()
{
    cout << setw(85) << "+-----------------------------+" << endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "|         Add Postion         |"<< endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "+-----------------------------+" << endl;
}

void DepartmentManager::deletePositionHeader()
{
    cout << setw(85) << "+-----------------------------+" << endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "|       Delete Position       |"<< endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "+-----------------------------+" << endl << endl;
}

void DepartmentManager::viewPositionHeader()
{
    cout << setw(85) << "+-----------------------------+" << endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "|        View Position        |"<< endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "+-----------------------------+" << endl << endl;
}

void DepartmentManager::addDepartmentPositionHeader()
{
    cout << setw(85) << "+-----------------------------+" << endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "|      Add Department's       |"<< endl;
    cout << setw(85) << "|          Position           |"<< endl;
    cout << setw(85) << "|                             |"<< endl;
    cout << setw(85) << "+-----------------------------+" << endl << endl;
}

void DepartmentManager::DepartmentTransform(sql::ResultSet* rs,Department * department)
{
    department->departmentID = rs->getInt(1);
    department->departmentName = rs->getString(2);
    department->contactNo = rs->getString(3);
}

void DepartmentManager::PositionTransform(sql::ResultSet* rs, Position* position)
{
    position->positionID = rs->getInt(1);
    position->positionName = rs->getString(2);
    position->description = rs->getString(3);
}

Department* DepartmentManager::searchDepartment(int id)
{
    DatabaseConnection dbConn;
    Department * department = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM DEPARTMENT WHERE DepartmentID = ? ");
    ps->setInt(1,id);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        department = new Department(); //if found, create a department variable, else it will remain null
        DepartmentTransform(rs,department);
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return department;
}

Department* DepartmentManager::searchDepartment(string name)
{
    DatabaseConnection dbConn ;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM DEPARTMENT WHERE DepartmentName = ? ");
    Department* department = NULL;
    ps->setString(1,name);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        department = new Department(); //if found, create a department variable, else it will remain null
        DepartmentTransform(rs,department);
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return department;
}

Department* DepartmentManager::searchDepartments()
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM DEPARTMENT");
    sql::ResultSet* rs = ps->executeQuery();
    Department* head = NULL;
    Department* department = NULL;
    while(rs->next())
    {
        if(head==NULL)
        {
            department = new Department();
            head = department;
        }
        else
        {
            department->next = new Department();
            department = department->next;
        }
        DepartmentTransform(rs,department);
    }        
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

bool DepartmentManager::checkRepeatString(string input,string table,string column)
{
    DatabaseConnection dbConn;
    bool repeat;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM " + table + " WHERE " + column + " = ?");
    ps->setString(1,input);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
        repeat = true;
    else
        repeat = false;
    
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return repeat;
}

int DepartmentManager::IDorName()
{
    bool valid = false;
    int choice;
        cout << setw(48) << "+" << setfill('-') << "-" <<setw(43) << "+" << setfill(' ') << endl;
        cout << setw(48) << "|" << left << setw(8) << " " <<setw(35) <<  "    Choose how to search :  "  <<  "|"<< endl;
        cout << right << setw(48) << "|" << setfill('-') << "-" <<setw(43) << "|" << setfill(' ') << endl;
        cout << right << setw(48) << "|" << setw(44) << "|" << endl;
        cout << right << setw(48) << "|" << left << setw(11) << " " <<setw(32) <<  "   1.   By ID "  <<  "|"<< endl;
        cout << right << setw(48) << "|" << setw(44) << "|" << endl;
        cout << right << setw(48) << "|" << left << setw(11) << " " <<setw(32) <<  "   2.   By Name"    <<  "|"<< endl;
        cout << right << setw(48) << "|" << setw(44) << "|" << endl;
        cout << right << setw(48) << "+" << setfill('-') << "-" <<setw(43) << "+" << setfill(' ') << endl;
        do
        {
            cout << endl << setw (70) <<  "Choice: " ;
            cin >> choice;
            if(choice==1 || choice==2)
            {
                valid = true;
            }
            else
            {   
                valid = false;
                cout << endl << setw(87) << "Invalid choice. Please try again." << endl;
            }
        } while (!valid);
    return choice; 
}

void DepartmentManager::addDepartment()
{
    Menu menu;
    bool repeat = false;
    int strlength;
    menu.displayLogo();
    addDepartmentHeader();

    Department* department = new Department();
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO DEPARTMENT (DepartmentName, ContactNo)VALUES(?,?)");
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    do
    {
        cout  << "\n\n"<< setw(72)  <<"Enter Department Name            : ";
        getline(cin,department->departmentName);
        repeat = checkRepeatString(department->departmentName,"DEPARTMENT","DepartmentName");
        strlength = department->departmentName.length();
        if(repeat)
        {
            cout << "\n\n" <<setw(98) << "This department name already exists. Please use another name. " << endl;
        } 
        if(strlength>30)
        {
            cout << "\n\n"<<setw(85) << "The name is too long. Please use a shorter name." << endl;
        }
    }while(repeat || strlength>30);

    do
    {
        cout << "\n\n"<< setw(72) << "Enter Department Contact Number  : " ;
        cin >> department->contactNo;
        repeat = checkRepeatString(department->contactNo,"DEPARTMENT","ContactNo");
        strlength = department->contactNo.length();
        if(repeat)
        {
            cout << "\n\n" <<setw(108) << "This department contact number already exists. Please use another contact number. " << endl;
        }
        if(strlength>15)
        {
            cout << "\n\n" <<setw(97) << "The contact number is too long. Please enter a shorter number." << endl;
        }
    }while(repeat || strlength>15);
  
    ps->setString(1,department->departmentName);
    ps->setString(2,department->contactNo);

    menu.displayLogo();
    addDepartmentHeader();
    
    cout << "\n\n" << setw(83) <<  "NEW Department Preview\n\n" ;
    cout << setw(42) << " " << setw(56) << setfill('*') << "*"  << setfill(' ') ;
    cout  << "\n\n"<< setw(72) << "Name                 : " << department->departmentName<< endl;
    cout  << "\n\n"<< setw(72) << "Contact Number       : " << department->contactNo << endl;    

    char confirm;
    cout << "\n\n" << setw(97) << "Are you sure to add this department? Enter Y/y to confirm: ";
    cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->executeUpdate();
        cout << "\n" << setw(90) << "[ New department is added successfully ]" << endl;
    }
    else
    {
        cout << "\n" << setw(103) << "[ Addition process has been cancelled. No changes have been made ]" << endl;
    }
    ps->close();
    delete ps;
}

void DepartmentManager::deleteDepartment(int departmentID)
{
    char choice;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM DEPARTMENT WHERE DepartmentID = ?");
    ps->setInt(1,departmentID);
    cout << endl << setw(100) << "Are you sure to delete this department? Enter Y/y to delete: " ;
    cin >> choice;
    if(choice=='Y'||choice=='y')
    {
        ps->executeUpdate();
        cout << endl << setw(90) << "[ The department is deleted successfully ]" << endl;
    }
    else
    {
        cout << endl << setw(104) << "[ Deletion process has been cancelled. No changes have been made ]" << endl;    
    }
    ps->close();
    delete ps;
}

void DepartmentManager::deleteDepartment()
{
    Menu menu;
    char response;
    bool valid  = false;
    Department * department = NULL;

    menu.displayLogo();
    deleteDepartmentHeader();
    cout << "\n\n";
    int choice = IDorName();
    menu.displayLogo();
    deleteDepartmentHeader();
    if(choice==1)
    {
        int departmentID;
        do
        {
            response = 'Z';
            menu.displayLogo();
            updateDepartmentHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Department ID      : ";
            cin >> departmentID;
            department = searchDepartment(departmentID);
            if(department==NULL)
            {
                cout << endl << setw(93) << "The department is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.departmentMenu();
            }
        } while (response == 'y'||response=='Y');    
    }

    if(choice==2)
    {      
        string name;
        do
        { 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');   
            response = 'Z';
            menu.displayLogo();
            updateDepartmentHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Department Name    : ";
            getline(cin,name);
            department = searchDepartment(name);
            if(department==NULL)
            {
                cout << endl << setw(93) << "The department is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.departmentMenu();
            }
        } while (response == 'y'||response=='Y');
    }

    if(department!=NULL)
    {
        menu.displayLogo();
        deleteDepartmentHeader();
        cout << "\n\n";
        viewDepartment(department);
        deleteDepartment(department->departmentID);
    }     
}

int DepartmentManager::updateDepartmentMenu()
{
    int choice;
    cout << "\n\n\n" << setw(90) << "Which information you want to update?\n\n";
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "------ Type of Information -------" << setw(8) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(34) << "1. Department Name" << setw(16)<< "|" << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(33) << "2. Contact Number" << setw(17) << "|"<< endl;
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2)
        {
            cout << endl << setw(76) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2);
    return choice;
}

void DepartmentManager::updateDepartment(string column, string data, int departmentID)
{
    Menu menu;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE DEPARTMENT SET "+column+" = ? WHERE DepartmentID = ?" );
    ps->setString(1,data);
    ps->setInt(2,departmentID);

    char confirm;
    cout << "\n\n" << setw(88) << "Are you sure to update? Enter Y/y to update: ";
    cin >> confirm;

    if(confirm=='Y'||confirm=='y')
    {
        ps->executeUpdate();
        cout << "\n" << setw(94) << "[ Department Information is updated successfully ]" << endl;
    }
    else
    {
        cout << endl << setw(102) << "[ Update process has been cancelled. No changes have been made ]" << endl;        
    }
    ps->close();
    delete ps;

    char response;
    cout << "\n\n\n" << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" <<setw(37) << "Enter 'Y' for any other update" <<setw(13) << "|"<< endl;
    cout << setw(45) << "|" <<setw(43) <<  "Press 'P' to return to Previous menu" <<setw(7) << "|"<< endl;
    cout << setw(45) << "|" <<setw(39) <<  "Press 'M' to return to Main Menu" <<setw(11) << "|"<< endl;
    cout  << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl << endl;  
    do
    {
        cout << setw(69) << "Choice: ";
        cin >> response;
        if(response!='P'&& response!='p'&& response!='M'&& response!='m'&&response != 'Y'&& response !='y')
        cout << setw(90) << "Invalid choice. Please enter a valid choice.\n" << endl;
    } while (response!='P'&& response!='p'&& response!='M'&& response!='m'&&response != 'Y'&& response !='y');

    if(response == 'Y'||response =='y')
    {
            menu.displayLogo();
            updateDepartmentHeader();
            updateDepartment(departmentID);
    }
    else if(response == 'P'||response =='p')
        menu.departmentMenu();
    else
        menu.managerMainMenu();
}

void DepartmentManager::updateDepartment(int departmentID)
{
    Menu menu;
    DatabaseConnection dbConn;
    string departmentName,contactNo;
    bool repeat = false;
    int strlength, choice;
    choice = updateDepartmentMenu();
    menu.displayLogo();
    updateDepartmentHeader();
    switch (choice)
    {
    case 1:
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        do
        {

            cout << "\n\n" << setw(80) << "Enter updated Department Name             : ";
            getline(cin,departmentName);
            repeat = checkRepeatString(departmentName,"DEPARTMENT","DepartmentName");
            strlength = departmentName.length();
            if(repeat)
            {
                cout << "\n\n" <<setw(98) << "This department name already exists. Please use another name. " << endl;
            } 
            if(strlength>30)
            {
                cout << "\n\n"<<setw(85) << "The name is too long. Please use a shorter name." << endl;
            }
        }while(repeat || strlength>30);
        updateDepartment("DepartmentName",departmentName,departmentID);
        break;

    case 2:
        do
        {
            cout << "\n\n" << setw(80) << "Enter updated Department Contact Number   : ";
            cin >> contactNo;
            repeat = checkRepeatString(contactNo,"DEPARTMENT","ContactNo");
            strlength = contactNo.length();
            if(repeat)
            {
                cout << "\n\n" <<setw(108) << "This department contact number already exists. Please use another contact number. " << endl;
            }
            if(strlength>15)
            {
                cout << "\n\n" <<setw(97) << "The contact number is too long. Please enter a shorter number." << endl;
            }
        }while(repeat || strlength>15);
        updateDepartment("ContactNo",contactNo,departmentID);
    default:
        break;
    }

}

void DepartmentManager::updateDepartment()
{
    Menu menu;
    menu.displayLogo();
    updateDepartmentHeader();
    Department * department = NULL;
    char response ;
    int choice = IDorName();


    if(choice==1)
    {
        int departmentID;
        do
        {
            response = 'Z';
            menu.displayLogo();
            updateDepartmentHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Department ID      : ";
            cin >> departmentID;
            department = searchDepartment(departmentID);
            if(department==NULL)
            {
                cout << endl << setw(93) << "The department is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.departmentMenu();
            }
        } while (response == 'y'||response=='Y');
    }

    if(choice==2)
    { 
        string name;
        do
        {   
            cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
            response = 'Z';
            menu.displayLogo();
            updateDepartmentHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Department Name    : ";
            getline(cin,name);
            department = searchDepartment(name);
            if(department==NULL)
            {
                cout << endl << setw(93) << "The department is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.departmentMenu();
            }
        } while (response == 'y'||response=='Y');
    }

    if(department!=NULL)
    {
        menu.displayLogo();
        updateDepartmentHeader();
        viewDepartment(department);
        updateDepartment(department->departmentID);
    }
}

void DepartmentManager::viewDepartmentList()
{
    Menu menu;
    menu.displayLogo();
    viewDepartmentHeader();
    Department* department = searchDepartments();
    if(department!=NULL)
    {
        cout << setw(31) << "+" << setfill('-') <<"-" <<setw(78) << "+" << setfill(' ') << endl;
        cout << setw(37) << "|  Name" << setw(62) <<"| Contact Number"  << setw(11) << "|" << endl;
        cout << setw(31) << "|" << setfill('-') <<"-" <<setw(78) << "|" << setfill(' ') << endl;
        while(department!=NULL)
        {
            cout << left << setw(30) << " " << "|  " << setw(50) << department->departmentName << "| "  << setw(23) << department->contactNo << " " << "|" << endl;
            department = department->next;
        }
        cout << right;
        cout << setw(31) << "+" << setfill('-') <<"-" <<setw(78) << "+" << setfill(' ') << endl;
    }
    else
    {
        cout << setw(81) << "No department available." << endl;
    }

}

void DepartmentManager::viewDepartment(Department* department)
{
    cout << "\n\n" << setw(82) <<  "Department Information\n" ;
    cout << setw(42) << " " << setw(56) << setfill('*') << "*"  << setfill(' ') << endl << endl;
    cout << setw(72)<< "Name                 : " << department->departmentName << endl<< endl;
    cout<< setw(72) << "Contact Number       : " << department->contactNo << endl<< endl;
}

void DepartmentManager::viewDepartment()
{
    Menu menu;
    char response;
    menu.displayLogo();
    searchDepartmentHeader();
    bool valid  = false;
    cout << "\n\n";
    int choice = IDorName();
    Department* department = NULL;
    if(choice==1)
    {
        int departmentID;
        do
        {
            response = 'Z';
            menu.displayLogo();
            searchDepartmentHeader();
            cout  << "\n\n"<< setw(72)  << "Enter Department ID      : ";
            cin >> departmentID;
            department = searchDepartment(departmentID);
            if(department==NULL)
            {
                cout << endl << setw(93) << "The department is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.departmentMenu();
            }
        } while (response == 'y'||response=='Y');    

    }
    if(choice==2)
    {
        string name;
        do
        { 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');   
            response = 'Z';
            menu.displayLogo();
            searchDepartmentHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Department Name    : ";
            getline(cin,name);
            department = searchDepartment(name);
            if(department==NULL)
            {
                cout << endl << setw(93) << "The department is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.departmentMenu();
            }
        } while (response == 'y'||response=='Y');
    }
    menu.displayLogo();
    searchDepartmentHeader();
    viewDepartment(department);
}

Position* DepartmentManager::searchPosition(int id)
{
    DatabaseConnection dbConn;
    Position* position = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM POSITION WHERE PositionID = ? ");
    ps->setInt(1,id);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        position = new Position(); //if found, create a department variable, else it will remain null
        PositionTransform(rs,position);
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return position;
}

Position* DepartmentManager::searchPosition(string name)
{
    DatabaseConnection dbConn ;
    Position* position = NULL;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM POSITION WHERE PositionName = ? ");
    ps->setString(1,name);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        position = new Position(); //if found, create a department variable, else it will remain null
        PositionTransform(rs,position);
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return position;
}

Position* DepartmentManager::searchPositions()
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM POSITION");
    sql::ResultSet* rs = ps->executeQuery();
    Position* head = NULL;
    Position* position = NULL;
    while(rs->next())
    {
        if(head==NULL)
        {
            position = new Position();
            head = position;
        }
        else
        {
            position->next = new Position();
            position = position->next;
        }
        PositionTransform(rs,position);
    }        
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return head;
}

void DepartmentManager::viewPosition(Position* position)
{
    cout << setw(80) <<  "Position Information\n" ;
    cout << setw(41) << " " << setw(56) << setfill('*') << "*"  << setfill(' ') << endl << endl;
    cout << setw(69)<< "ID                   : " << position->positionID<< endl<< endl;
    cout << setw(69)<< "Name                 : " << position->positionName << endl<< endl;
    cout << setw(69) << "Description          : " << position->description << endl<< endl;
}

void DepartmentManager::viewPosition()
{
    Menu menu;
    char response;
    bool valid  = false;
    Position *position = NULL;

    menu.displayLogo();
    viewPositionHeader();
    cout << "\n\n";
    int choice = IDorName();
    menu.displayLogo();
    viewPositionHeader();
    if(choice==1)
    {
        int positionID;
        do
        {
            response = 'Z';
            menu.displayLogo();
            viewPositionHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Position ID       : ";
            cin >> positionID;
            position = searchPosition(positionID);
            if(position==NULL)
            {
                cout << endl << setw(92) << "The position is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.departmentMenu();
            }
        } while (response == 'y'||response=='Y');      
    }
        if(choice==2)
    {
        string name;
        do
        { 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');   
            response = 'Z';
            menu.displayLogo();
            viewPositionHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Position Name     : ";
            getline(cin,name);
            position = searchPosition(name);
            if(position==NULL)
            {
                cout << endl << setw(92) << "The position is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.departmentMenu();
            }
        } while (response == 'y'||response=='Y');
    }

    if(position!=NULL)
    {
        menu.displayLogo();
        viewPositionHeader();
        cout << "\n\n";
        viewPosition(position);
    }
}

void DepartmentManager::viewPositionList()
{
    Menu menu;
    menu.displayLogo();
    viewPositionHeader();
    Position* position = searchPositions();
    if(position!=NULL)
    {
        cout << setw(24) << "+" << setfill('-') <<"-" << setw(100) << "+" << setfill(' ') << endl;
        cout << setw(30) << "|  Name" << setw(59) <<"| Description"  << setw(36) << "|" << endl;
        cout << setw(24) << "|" << setfill('-') <<"-" <<setw(100) << "|" << setfill(' ') << endl;
        while(position!=NULL)
        {
            cout << left;
            cout << left << setw(23) << " " << "|  " << setw(50) << position->positionName << "| "  << setw(45) << position->description << " " << "|" << endl;
            position = position->next;
        }
        cout << right;
        cout << setw(24) << "+" << setfill('-') <<"-" <<setw(100) << "+" << setfill(' ') << endl;
    }
    else
    {
        cout << setw(58) << "No position available." << endl;
    }

}

void DepartmentManager::addPosition()
{
    Menu menu;
    bool repeat = false;
    int strlength;
    char response;
    menu.displayLogo();
    addPositionHeader();

    Position* position = new Position();
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    do
    {
        cout  << "\n\n"<< setw(72) <<"Enter Position Name            : ";
        getline(cin,position->positionName);
        repeat = checkRepeatString(position->positionName,"POSITION","PositionName");
        strlength = position->positionName.length();
        if(repeat)
        {
            cout << "\n\n" <<setw(98) << "This position name already exists. Please use another name. " << endl;
        } 
        if(strlength>30)
        {
            cout << "\n\n"<<setw(87) << "The name is too long. Please use a shorter name." << endl;
        }
    }while(repeat || strlength>30);



        cout << "\n\n"<< setw(93) << "Any description? Enter Y/y to write description: " ;
        cin >> response;
        if(response=='Y'||response=='y')
        {
            do
            {
                cout << "\n\n"<< setw(72) << "Enter Description              : " ;
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                getline(cin,position->description);
                strlength = position->description.length();
                if(strlength>50)
                {
                    cout << "\n\n" <<setw(97) << "The description is too long. Please enter a shorter description." << endl;
                }
            }while(strlength>50);
            ps = dbConn.prepareStatement("INSERT INTO POSITION (PositionName, Description)VALUES(?,?)");
            ps->setString(2,position->description);
        }
        else
                ps = dbConn.prepareStatement("INSERT INTO POSITION (PositionName)VALUES(?)");
    ps->setString(1,position->positionName);

    menu.displayLogo();
    addPositionHeader();
   
    cout << "\n\n" << setw(81) <<  "NEW Position Preview\n\n" ;
    cout << setw(42) << " " << setw(56) << setfill('*') << "*"  << setfill(' ') ;
    cout  << "\n\n"<< setw(68) << "Name                 : " << position->positionName << endl;
    cout  << "\n\n"<< setw(68) << "Description          : " << position->description << endl; 

    char confirm;
    cout << "\n\n" << setw(97) << "Are you sure to add this position? Enter Y/y to confirm: " ;
    cin >> confirm;
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->executeUpdate();
        cout << "\n" << setw(90) << "[ New position is added successfully ]" << endl;
    }
    else
    {
        cout << "\n" << setw(103) << "[ Addition process has been cancelled. No changes have been made ]" << endl;
    }
    ps->close();
    delete ps;

}

void DepartmentManager::deletePosition(int positionID)
{
    char choice;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM POSITION WHERE PositionID = ?");
    ps->setInt(1,positionID);
    cout << endl << setw(96) <<  "Are you sure to delete this position? Enter Y/y to delete: ";
    cin >> choice;
    if(choice=='Y'||choice=='y')
    {
        ps->executeUpdate();
        cout << endl << setw(90) << "[ The position is deleted successfully ]" << endl;
    }
    else
    {
        cout << endl << setw(103) << "[ Deletion process has been cancelled. No changes have been made ]";        
    }
    ps->close();
    delete ps;     
}

void DepartmentManager::deletePosition()
{
    Menu menu;
    menu.displayLogo();
    deletePositionHeader();
    bool valid  = false;
    char response;
    Position* position = NULL;
    cout << "\n\n";
    int choice = IDorName();
    menu.displayLogo();
    deletePositionHeader();
    if(choice==1)
    { 
        int positionID;
        do
        {
            response = 'Z';
            menu.displayLogo();
            deletePositionHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Position ID       : ";
            cin >> positionID;
            position = searchPosition(positionID);
            if(position==NULL)
            {
                cout << endl << setw(92) << "The position is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.departmentMenu();
            }
        } while (response == 'y'||response=='Y');      
    }

    if(choice==2)
    {
        string name;
        do
        { 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');   
            response = 'Z';
            menu.displayLogo();
            deletePositionHeader();
            cout  << "\n\n"<< setw(72)  <<"Enter Position Name     : ";
            getline(cin,name);
            position = searchPosition(name);
            if(position==NULL)
            {
                cout << endl << setw(92) << "The position is not found. Enter Y/y to retry: ";
                cin >> response;
                if(response != 'y'&&response!='Y')
                    menu.departmentMenu();
            }
        } while (response == 'y'||response=='Y');
    }

    if(position!=NULL)
    {
        menu.displayLogo();
        deletePositionHeader();
        cout << "\n\n";
        viewPosition(position);
        deletePosition(position->positionID);
    }
}

void DepartmentManager::addDept_Position(int departmentID,int positionID,string description)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO DEPT_POSITION (DepartmentID, PositionID, Description) VALUES (?,?,?)");
    ps->setInt(1,departmentID);
    ps->setInt(2,positionID);
    ps->setString(3,description);
    ps->executeQuery();
    ps->close();
    delete ps;
}

void DepartmentManager::addDept_Position(int departmentID,int positionID)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO DEPT_POSITION (DepartmentID, PositionID) VALUES (?,?)");
    ps->setInt(1,departmentID);
    ps->setInt(2,positionID);
    ps->executeQuery();
    ps->close();
    delete ps;
}

void DepartmentManager::addDept_Position()
{
    Menu menu;
    int departmentID, positionID;
    string description;
    Department* department = NULL;
    Position* position = NULL;
    bool found ;     
    char response,confirm;
    menu.displayLogo();
    addDepartmentPositionHeader();

    department = searchDepartments();
    if(department!=NULL)
    {

        cout << setw(41) << "+" << setfill('-') << "-" << setw(64) << "+" << setfill(' ') << endl;
        cout << setw(45) << "|  ID" << setw(14) << "|  Name" << setw(47) << "|" << endl;
        cout << setw(41) << "|" << setfill('-') << "-" << setw(64) << "|" << setfill(' ') << endl;
        while(department!=NULL)
        {
            cout << left << setw(40) << " " << "|  " << setw(9) << department->departmentID << "| "  << setw(51) << department->departmentName << "| "  << endl;
            department = department->next;
        }
        cout << right << setw(41) << "+" << setfill('-') <<"-" <<setw(64) << "+" << setfill(' ') << endl;

    }
    else
    {
        cout << setw(81) << "No department available." << endl;
    }

    do
    {
        cout << "\n\n" << setw(70) << "Enter Department ID  : ";
        cin >> departmentID;
        department = searchDepartment(departmentID);
        if(department==NULL)
        cout << endl << setw(103) << "The department is not found. Please enter a valid department ID. " << endl;
    } while (department==NULL);

    menu.displayLogo();
    addDepartmentPositionHeader();


    position = searchPositions();
    if(position!=NULL)
    {

        cout << setw(41) << "+" << setfill('-') << "-" << setw(64) << "+" << setfill(' ') << endl;
        cout << setw(45) << "|  ID" << setw(14) << "|  Name" << setw(47) << "|" << endl;
        cout << setw(41) << "|" << setfill('-') << "-" << setw(64) << "|" << setfill(' ') << endl;
        while(position!=NULL)
        {
            cout << left << setw(40) << " " << "|  " << setw(9) << position->positionID << "| "  << setw(51) << position->positionName << "| "  << endl;
            position = position->next;
        }
        cout << right << setw(41) << "+" << setfill('-') <<"-" <<setw(64) << "+" << setfill(' ') << endl;

    }
    else
    {
        cout << setw(81) << "No position available." << endl;
    }

    do
    {
        cout << "\n\n" << setw(70) << "Enter Position ID    : ";
        cin >> positionID;
        position = searchPosition(positionID);
        if(position==NULL)
        cout << endl << setw(100) << "The position is not found. Please enter a valid position ID. " << endl;
    } while (position==NULL);
    found = searchDept_Position(departmentID,positionID);

    if(!found)
    {
        cout << "\n\n" << setw(94) << "Any description? Enter Y/y to write description: ";
        cin >> response;
        if(response=='Y'||response=='y')
        {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout << "\n\n" << setw(70)<< "Enter Description   : ";
            getline(cin,description);
        }
        cout << "\n\n" << setw(110) << "Are you sure to assign this position to this department? Enter Y/y to confirm: ";
        cin >> confirm;
        if(confirm == 'Y'|| confirm=='y')
        {
            if(response=='Y'||response=='y')
                addDept_Position(departmentID,positionID,description);
            else
                addDept_Position(departmentID,positionID);  
            cout << "\n\n" << setw(94) << "[ Position is added to department successfully ]" << endl;
        }
        else
        {
            cout << "\n" << setw(103) << "[ Assign process has been cancelled. No changes have been made ]" << endl;
        }
    }
    else
    {
        cout  << "\n\n" << setw(95) << "The position already added to the department." << endl    
                << "\n" << setw(73) << "Enter Y/y to retry: ";
        cin >> confirm;
        if(confirm=='Y'||confirm=='y')
            addDept_Position();
        else
            menu.departmentMenu();
    }
}

bool DepartmentManager::searchDept_Position(int departmentID,int positionID)
{
    bool found ;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM DEPT_POSITION WHERE DepartmentID = ? AND PositionID = ?");
    ps->setInt(1,departmentID);
    ps->setInt(2,positionID);
    sql::ResultSet*rs = ps->executeQuery();
    if(rs->next())
        found = true;
    else
        found = false;
    ps->close();
    delete ps;
    return found;
}