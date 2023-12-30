#include "DependantManager.h"
#include <iomanip>


void addDependantHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(21) << "Add Dependant" << setw(9) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

void updateDependantHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(23) << "Update Dependant" << setw(7) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

void deleteDependantHeader()
{
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;                            
    cout << setw(55) << "|" << setw(23) << "Delete Dependant" << setw(7) << "|" << endl;
    cout << setw(55) << "|" << setfill(' ') << ' ' << setw(29) << " |" << endl;
    cout << setw(55) << "+" <<setfill('-') << "-" << setw(29) << "+" << setfill(' ') << endl<< endl; 
}

void DependantManager::addDependant() 
{
    Menu menu;
    EmployeeManager em;
    DateManager dateManager;
    menu.displayLogo();
    addDependantHeader();
    string name,relationship,dateOfBirth,maritalStatus;
    int strlength,employeeID, isWorking, isDisabled, isStudyDiplomaOrHigher;
    bool valid;
    char response;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO DEPENDANT (Name, DateOfBirth,IsDisabled,IsWorking,MaritalStatus,IsStudyDiplomaOrHigher) VALUES (?,?,?,?,?,?)");
    cout << "\n\n"<< setw(72) << "Enter Employee ID               : ";
    cin >> employeeID;
    Employee* employee = em.searchEmployee(employeeID);
    if(employee!= NULL)
    {    
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        do
        {
            
            cout  << "\n\n"<< setw(72)  <<"Enter Dependant Name            : ";
            getline(cin,name);
            strlength = name.length();

            if(strlength>50)
            {
                cout << "\n\n"<<setw(85) << "The name is too long. Please use a shorter name." << endl;
            }
        }while(strlength>50);

        do{
        cout<< "\n\n"<< setw(72)  << "Enter Date of Birth (YYYY/MM/DD)  : ";
        cin >> dateOfBirth;
        valid = dateManager.isValidDate(dateOfBirth);
        if(!valid)
            cout << "\n" << setw(78) << "Invalid date or format. Please try again." << endl;
        } while (!valid);

        do
        {
            cout  << "\n\n"<< setw(72)  <<"Enter Relationship ('S' for Spouse and 'C' for children)  : ";
            cin >> relationship;
            if(relationship!="S"&&relationship!="s"&&relationship!="C"&&relationship!="c")
                cout << "\n" << setw(93) << "Please enter 'S' for spouse OR 'C' for child. " << endl;
        } while (relationship!="S"&&relationship!="s"&&relationship!="C"&&relationship!="c");

        if(relationship=="S"||relationship=="s")
            relationship = "Spouse";
        else
            relationship = "Child";

        cout << "\n\n" << right << setw(84) <<  "------ Marital Status -------" << endl;
        cout << "\n" << left << setw(63) << " " << "S : Single" << endl;
        cout << left << setw(63) << " " << "M : Married" << endl;
        cout << left << setw(63) << " " << "D : Divorced" << endl;
        cout << left << setw(63) << " " << "W : Widowed" << endl << right;

        do{
            cout  << "\n"<< setw(72)  <<"Enter Marital Status (S/M/D/W)  : ";
            cin >> maritalStatus;
            if(maritalStatus!="S"&&maritalStatus!="s"&&maritalStatus!="M"&&maritalStatus!="m"&&maritalStatus!="D"&&maritalStatus!="d"&&maritalStatus!="W"&&maritalStatus!="w")
                cout << "\n" << setw(93) << "Invalid input. Please enter (S/M/D/W). " << endl;
        } while(maritalStatus!="S"&&maritalStatus!="s"&&maritalStatus!="M"&&maritalStatus!="m"&&maritalStatus!="D"&&maritalStatus!="d"&&maritalStatus!="W"&&maritalStatus!="w");
        
        if(maritalStatus=="S"||maritalStatus=="s")
            maritalStatus = "Single";
        else if(maritalStatus=="M"||maritalStatus=="m")
            maritalStatus = "Married";
        else if(maritalStatus=="D"||maritalStatus=="d")
            maritalStatus = "Divorced";
        else
            maritalStatus = "Widowed";

        do
        {
            cout  << "\n\n"<< setw(72)  <<"Is Disabled ? (Y/N)  : ";
            cin >> response;
            if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
                cout << "\n" << setw(97) << "Please enter 'Y' if disabled OR 'N' if not disabled. " << endl;
        } while (response!='Y'&&response!='y'&&response!='N'&&response!='n');

        if(response=='Y'||response=='y')
            isDisabled = 1;
        else
            isDisabled = 0;

        do
        {
        cout  << "\n\n"<< setw(72)  <<"Is Working ? (Y/N)  : ";
        cin >> response;            
            if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
                cout << "\n" << setw(96) << "Please enter 'Y' if working OR 'N' if not working. " << endl;
        } while (response!='Y'&&response!='y'&&response!='N'&&response!='n');

        if(response=='Y'||response=='y')
            isWorking = 1;
        else
           isWorking = 0;

        do
        {
        cout  << "\n\n"<< setw(72)  <<"Is Studying Diploma or Higher ? (Y/N)  : ";
        cin >> response;
            if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
                cout << "\n\n" << setw(100) << "Please enter 'Y' if studying diploma or higher OR 'N' if not. " << endl;
        } while (response!='Y'&&response!='y'&&response!='N'&&response!='n');
        if(response=='Y'||response=='y')
            isStudyDiplomaOrHigher = 1;
        else
            isStudyDiplomaOrHigher = 0;

        menu.displayLogo();
        addDependantHeader();
        cout << "\n\n" << setw(83) <<  "NEW Dependant Preview\n\n" ;
        cout << setw(42) << " " << setw(56) << setfill('*') << "*"  << setfill(' ') ;
        cout  << "\n\n"<< setw(72) << "Name                          : " << name << endl;
        cout  << "\n\n"<< setw(72) << "Date Of Birth                 : " << dateOfBirth << endl; 
        cout  << "\n\n"<< setw(72) << "Relationship                  : " << relationship << endl;  
        cout  << "\n\n"<< setw(72) << "Marital Status                : " << maritalStatus << endl;  
        cout  << "\n\n"<< setw(72) << "Is Disabled                   : " ;
            if(isDisabled == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;

        cout  << "\n\n"<< setw(72) << "Is Working                    : ";
            if(isWorking == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;  

        cout  << "\n\n"<< setw(72) << "Is Studying Diploma Or Higher : " ;
            if(isStudyDiplomaOrHigher == 1)
                    cout << "Yes" << endl;
            else
                cout << "No" << endl; 

        char confirm;
        cout << "\n\n" << setw(97) << "Are you sure to add this dependant? Enter Y/y to confirm: ";
        cin >> confirm;
        if(confirm == 'Y'|| confirm=='y')
        {
            ps->setString(1,name);
            ps->setString(2,dateOfBirth);
            ps->setInt(3,isDisabled);
            ps->setInt(4,isWorking);
            ps->setString(5,maritalStatus);
            ps->setInt(6,isStudyDiplomaOrHigher);
            ps->executeUpdate();
            cout << "\n" << setw(90) << "[ New dependant is added successfully ]" << endl;
            ps->close();
            delete ps;
            sql::PreparedStatement* getDependantID = dbConn.prepareStatement("SELECT DependantID FROM DEPENDANT WHERE Name = ?");
            getDependantID->setString(1,name);
            sql::ResultSet* rs = getDependantID->executeQuery(); 
            if(rs->next())
            {
                int dependantID = rs->getInt("DependantID");
                getDependantID->close();
                delete getDependantID;
                addEmpDependant(employeeID,dependantID,relationship);
            } 
            rs->close();
            delete rs;        
        }
        else
        {
            cout << "\n" << setw(103) << "[ Addition process has been cancelled. No changes have been made ]" << endl;
        }
    }
    else
    {
        char again;
        cout << endl << setw(89) << "The employee is not found. Enter Y/y to retry: ";
        cin >> again;
        if(again == 'Y'|| again== 'y')
            addDependant();
        else
            menu.employeeMenu();
    }
    
}

void DependantManager::deleteDependant()
{
    Menu menu;
    int id;
    Dependant* dependant = NULL;
    menu.displayLogo();
    deleteDependantHeader();
    cout  << "\n\n"<< setw(72)  <<"Enter Dependant ID     : ";
    cin >> id;
    dependant = searchDependant(id);
    if(dependant!=NULL)
    {
        menu.displayLogo();
        deleteDependantHeader();
        char choice;
        DatabaseConnection dbConn;
        sql::PreparedStatement* ps = dbConn.prepareStatement("DELETE FROM DEPENDANT WHERE DependantID = ?");
        ps->setInt(1,dependant->dependantID);
        viewDependant(dependant);
        cout << endl << setw(99) <<  "Are you sure to delete this dependant? Enter Y/y to delete: ";
        cin >> choice;
        if(choice=='Y'||choice=='y')
        {
            ps->executeUpdate();
            cout << endl << setw(89) << "[ The dependant is deleted successfully ]" << endl;
        }
        else
        {
            cout << endl << setw(104) << "[ Deletion process has been cancelled. No changes have been made ]";        
        }
        ps->close();
        delete ps;  
    }
    else
    {
        char again;
        cout << endl << setw(89) << "The dependant is not found. Enter Y/y to retry: ";
        cin >> again;
        if(again == 'Y'|| again== 'y')
            deleteDependant();  
        else
            menu.employeeMenu();      
    }
}

int DependantManager::updateDependantMenu()
{
    int choice;
    cout << setw(90) << "Which information you want to update?\n\n";
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(42) <<  "------ Type of Information -------" << setw(8) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(18) << "1. Name" << setw(32)<< "|" << endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(27) << "2. Date Of Birth" << setw(23) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(26) << "3. Relationship" << setw(24) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(28) << "4. Marital Status" << setw(22) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(26) << "5. Is Disabled " << setw(24) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(24) << "6. Is Working" << setw(26) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "|" << setw(43) << "7. Is Studying Diploma Or Higher" << setw(7) << "|"<< endl;
    cout << setw(45) << "|" << setw(50) << "|"<< endl;
    cout << setw(45) << "+" << setw(50) << setfill('-') << "+" << setfill(' ')  << endl;
    do
    {
        cout << endl << setw(70) << "Choice: ";
        cin >> choice;
        if(choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7)
        {
            cout << endl << setw(80) << "Please enter a valid choice." << endl;
        }
    } while (choice!=1&&choice!=2&&choice!=3&&choice!=4&&choice!=5&&choice!=6&&choice!=7);
    return choice;
}

void DependantManager::updateDependant(string column, int data, int dependantID)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE DEPENDANT SET "+ column + "= ? WHERE DependantID = ?");
    char confirm;
    cout << "\n\n" << setw(93) << "Are you sure to update? Enter Y/y to confirm: " ;
    cin >> confirm;
    ps->setInt(1,data);
    ps->setInt(2,dependantID);
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->executeUpdate();
        cout << "\n" << setw(94) << "[ Dependant Information is updated successfully ]" << endl;
    }  
    else
    {
        cout << "\n" << setw(102) << "[ Update process has been cancelled. No changes have been made ]" << endl;
    }      
    ps->close();
    delete ps;
}

void DependantManager::updateDependant(string column, string data, int dependantID)
{
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE DEPENDANT SET "+ column + "= ? WHERE DependantID = ?");
    char confirm;
    cout << "\n\n" << setw(93) << "Are you sure to update? Enter Y/y to confirm: " ;
    cin >> confirm;
    ps->setString(1,data);
    ps->setInt(2,dependantID);
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->executeUpdate();
        cout << "\n" << setw(94) << "[ Dependant Information is updated successfully ]" << endl;
    }  
    else
    {
        cout << "\n" << setw(102) << "[ Update process has been cancelled. No changes have been made ]" << endl;
    }      
    ps->close();
    delete ps;
}

void DependantManager::updateEmpDependant(int employeeID,int dependantID,string relationship)
{
    char confirm;
    cout << "\n\n" << setw(93) << "Are you sure to update? Enter Y/y to confirm: " ;
    cin >> confirm;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("UPDATE EMPLOYEE_DEPENDANT SET Relationship = ? WHERE EmployeeID = ? AND DependantID = ?");
    ps->setInt(2,employeeID);
    ps->setInt(3,dependantID);
    ps->setString(1,relationship);
    if(confirm == 'Y'|| confirm=='y')
    {
        ps->executeUpdate();
        cout << "\n" << setw(94) << "[ Dependant Information is updated successfully ]" << endl;
    }  
    else
    {
        cout << "\n" << setw(102) << "[ Update process has been cancelled. No changes have been made ]" << endl;
    }      
    ps->close();
    delete ps;
}

void DependantManager::updateDependant(int employeeID,int dependantID)
{
    Menu menu;
    EmployeeManager em;
    DatabaseConnection dbConn;
    DateManager dateManager;
    string name,relationship,dateOfBirth;
    menu.displayLogo();
    updateDependantHeader();
    int strlength;
    char response;
    bool valid; 
    int choice = updateDependantMenu();
    menu.displayLogo();
    updateDependantHeader();
    switch (choice)
    {
    case 1: //name
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        do
        {
            cout  << "\n\n"<< setw(72)  <<"Enter Dependant Name : ";
            getline(cin,name);
            strlength = name.length();

            if(strlength>50)
            {
                cout << "\n"<<setw(85) << "The name is too long. Please use a shorter name." << endl;
            }
        }while(strlength>50);
        updateDependant("Name",name,dependantID);
        break;

    case 2://dob
        do{
        cout<< "\n\n"<< setw(72)  << "Enter Date of Birth (YYYY/MM/DD)  : ";
        cin >> dateOfBirth;
        valid = dateManager.isValidDate(dateOfBirth);
        if(!valid)
            cout << "\n" << setw(78) << "Invalid date or format. Please try again." << endl;
        } while (!valid);
        updateDependant("DateOfBirth",dateOfBirth,dependantID);
        break;

    case 3://relationship
        do
        {
            cout  << "\n\n"<< setw(72)  <<"Enter Relationship ('S' for Spouse and 'C' for children)  : ";
            cin >> relationship;
            if(relationship!="S"&&relationship!="s"&&relationship!="C"&&relationship!="c")
                cout << "\n" << setw(93) << "Please enter 'S' for spouse OR 'C' for child. " << endl;
        } while (relationship!="S"&&relationship!="s"&&relationship!="C"&&relationship!="c");
        if(relationship=="S"||relationship=="s")
            relationship = "Spouse";
        else
            relationship = "Child";
        updateEmpDependant(employeeID,dependantID,relationship);
        break;

    case 4://marital status
        do
        {
            cout << "\n\n" << right << setw(84) <<  "------ Marital Status -------" << endl;
            cout << "\n" << left << setw(63) << " " << "S : Single" << endl;
            cout << left << setw(63) << " " << "M : Married" << endl;
            cout << left << setw(63) << " " << "D : Divorced" << endl;
            cout << left << setw(63) << " " << "W : Widowed" << endl << right;
            cout  << "\n"<< setw(72)  <<"Enter Marital Status (S/M/D/W)  : ";
            cin >> response;
            if(response!='S'&&response!='s'&&response!='M'&&response!='m'&&response!='D'&&response!='d'&&response!='W'&&response!='w')
                cout << "\n" << setw(93) << "Please enter 'S' for spouse OR 'C' for child. " << endl;
        } while (response!='S'&&response!='s'&&response!='M'&&response!='m'&&response!='D'&&response!='d'&&response!='W'&&response!='w');
        
        if(response=='S'||response=='s')
            updateDependant("MaritalStatus","Single",dependantID);
        else if(response=='M'||response=='m')
            updateDependant("MaritalStatus","Married",dependantID);
        else if(response=='D'||response=='d')
            updateDependant("MaritalStatus","Divorced",dependantID);
        else
            updateDependant("MaritalStatus","Widowed",dependantID);
        break;

    case 5://is disabled
        do
        {
            cout  << "\n"<< setw(72)  <<"Is Disabled ? (Y/N)  : ";
            cin >> response;
            if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
                cout << "\n" << setw(97) << "Please enter 'Y' if disabled OR 'N' if not disabled. " << endl;
        } while (response!='Y'&&response!='y'&&response!='N'&&response!='n');

        if(response=='Y'||response=='y')
            updateDependant("IsDisabled",1,dependantID);
        else
            updateDependant("IsDisabled",0,dependantID);
        break;

    case 6://is working
        do
        {
        cout  << "\n"<< setw(72)  <<"Is Working ? (Y/N)  : ";
        cin >> response;            
            if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
                cout << "\n" << setw(96) << "Please enter 'Y' if working OR 'N' if not working. " << endl;
        } while (response!='Y'&&response!='y'&&response!='N'&&response!='n');

        if(response=='Y'||response=='y')
            updateDependant("IsWorking",1,dependantID);
        else
            updateDependant("IsWorking",0,dependantID);

        break;

    case 7://is studying diploma or higher
        do
        {
        cout  << "\n"<< setw(72)  <<"Is Studying Diploma or Higher ? (Y/N)  : ";
        cin >> response;
            if(response!='Y'&&response!='y'&&response!='N'&&response!='n')
                cout << "\n" << setw(100) << "Please enter 'Y' if studying diploma or higher OR 'N' if not. " << endl;
        } while (response!='Y'&&response!='y'&&response!='N'&&response!='n');
        if(response=='Y'||response=='y')
            updateDependant("IsStudyDiplomaOrHigher",1,dependantID);
        else
            updateDependant("IsStudyDiplomaOrHigher",0,dependantID);
        break;
    default:
        break;
    }

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
        updateDependant(employeeID,dependantID);
    else if(response == 'P'||response =='p')
        menu.employeeMenu();
    else
        menu.managerMainMenu(); 
}

void DependantManager::updateDependant()
{
    Menu menu;
    EmployeeManager em;
    DatabaseConnection dbConn;
    int employeeID,dependantID;
    menu.displayLogo();
    updateDependantHeader();
  
    cout << "\n\n"<< setw(72) << "Enter Employee ID  : ";
    cin >> employeeID;
    Employee *employee = em.searchEmployee(employeeID); 
    if(employee!= NULL)
    {   
        menu.displayLogo();
        updateDependantHeader();
        Employee_Dependant* employeeDependant = searchDependants(employeeID);
        if(employeeDependant!=NULL)
        {
            Employee_Dependant* head = employeeDependant;
            viewDependants(employeeDependant);
            bool valid = true;
            do
            {
                employeeDependant = head;
                cout << "\n\n" << setw(82)<< "Enter dependant ID to be updated: ";
                cin >> dependantID;
                while(employeeDependant!=NULL)
                {
                    if(dependantID==employeeDependant->dependantID)
                    {
                        valid = true;
                        break;
                    }              
                    else
                        valid = false;
                    employeeDependant = employeeDependant->next;
                }
                if(!valid)
                    cout << "\n" << setw(86)<< "Please enter correct dependant ID." << endl;
            }while(!valid);
            updateDependant(employeeID,dependantID);
        }
        else
        {
            cout  << "\n\n" << setw(85) << "The employee has no dependant.\n";
        }
    }
    else
    {
        char again;
        cout << endl << setw(89) << "The employee is not found. Enter Y/y to retry: ";
        cin >> again;
        if(again == 'Y'|| again== 'y')
            updateDependant();
        else
            menu.employeeMenu();
    }
}

Employee_Dependant* DependantManager::searchDependants(int employeeID)
{
    Employee_Dependant* employeeDepedant = NULL;
    Employee_Dependant* head = NULL;
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM Employee_Dependant WHERE EmployeeID = ?");
    ps->setInt(1,employeeID);
    sql::ResultSet* rs = ps->executeQuery();
    while(rs->next())
    {
        if(head == NULL)
        {
            employeeDepedant = new Employee_Dependant();
            head = employeeDepedant;
        }
        else
        {
            employeeDepedant->next = new Employee_Dependant();
            employeeDepedant = employeeDepedant->next;
        }
        employeeDepedant->employeeID = rs->getInt("EmployeeID");
        employeeDepedant->dependantID = rs->getInt("DependantID");
        employeeDepedant->relationship = rs->getString("Relationship");
    }
    rs->close();
    delete rs;
    ps->close();
    delete ps;
    return head;
}

void DependantManager::addEmpDependant(int employeeID,int dependantID,string relationship)
{
    
    DatabaseConnection dbConn;
    sql::PreparedStatement* ps = dbConn.prepareStatement("INSERT INTO EMPLOYEE_DEPENDANT (EmployeeID, DependantID, Relationship) VALUES (?,?,?)");
    ps->setInt(1,employeeID);
    ps->setInt(2,dependantID);
    ps->setString(3,relationship);
    ps->executeQuery();
    ps->close();
    delete ps;
}

void DependantManager::viewDependants(Employee_Dependant* employeeDepedant)
{
    int i = 1;
    Dependant* dependant;
    while(employeeDepedant!=NULL)
    {
        dependant = searchDependant(employeeDepedant->dependantID);
        cout  << "\n\n\n"<< setw(75)<< "Dependant "  << i << ": " << endl;    
        cout  << "\n\n"<< setw(72)<< "Dependant ID      : " <<  employeeDepedant->dependantID  << endl;
        cout  << "\n\n"<< setw(72)<< "Dependant Name    : " <<  dependant->name  << endl;
        cout << "\n\n"<< setw(72) << "Relationship      : " <<  employeeDepedant->relationship << endl;
        employeeDepedant = employeeDepedant->next;
        i++;
    }
}

void DependantManager::viewDependant(Dependant* dependant)
{
    cout << "\n\n" << setw(83) <<  "Dependant Information\n\n" ;
    cout << setw(42) << " " << setw(56) << setfill('*') << "*"  << setfill(' ') ; 
    cout  << "\n\n"<< setw(72) << "Dependant ID                  : " <<  dependant->dependantID  << endl
          << "\n\n"<< setw(72) << "Dependant Name                : " <<  dependant->name  << endl
          << "\n\n"<< setw(72) << "DOB                           : " <<  dependant->dateOfBirth  << endl
          << "\n\n"<< setw(72) << "Marital Status                : " <<  dependant->maritalStatus  << endl;
    cout  << "\n\n"<< setw(72) << "Is Disabled                   : " ;
            if(dependant->isDisabled == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;

        cout  << "\n\n"<< setw(72) << "Is Working                    : ";
            if(dependant->isWorking == 1)
                cout << "Yes" << endl;
            else
                cout << "No" << endl;  

        cout  << "\n\n"<< setw(72) << "Is Studying Diploma Or Higher : " ;
            if(dependant->isStudyingDiplomaOrHigher == 1)
                    cout << "Yes" << endl;
            else
                cout << "No" << endl; 


}

Dependant* DependantManager::searchDependant(int dependentID)
{
    DatabaseConnection dbConn;
    Dependant* dependant = new Dependant();
    sql::PreparedStatement* ps = dbConn.prepareStatement("SELECT * FROM DEPENDANT WHERE DependantID = ?");
    ps->setInt(1,dependentID);
    sql::ResultSet* rs = ps->executeQuery();
    if(rs->next())
    {
        dependant->name = rs->getString("Name");
        dependant->dateOfBirth = rs->getString("DateOfBirth");
        dependant->dependantID = rs->getInt("DependantID");
        dependant->maritalStatus = rs->getString("MaritalStatus");
        dependant->isDisabled = rs->getBoolean("IsDisabled");
        dependant->isWorking = rs->getBoolean("IsWorking");
        dependant->isStudyingDiplomaOrHigher = rs->getBoolean("IsStudyDiplomaOrHigher");
    }
    else
    {
        dependant = nullptr;
    }
    rs->close();
    ps->close();
    delete rs;
    delete ps;
    return dependant;
}

