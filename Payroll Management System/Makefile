CXX = g++
CXXFLAGS = -std=c++11 -I/usr/local/mysql-connector-c++-8.2.0/include
LDFLAGS = -L/usr/local/mysql-connector-c++-8.2.0/lib64 -lmysqlcppconn

all: main

main: main.cpp AccountManager.cpp DatabaseConnection.cpp EmployeeManager.cpp DepartmentManager.cpp Menu.cpp DependantManager.cpp AllowanceManager.cpp SalaryManager.cpp BonusManager.cpp OvertimeManager.cpp DeductionManager.cpp LeaveManager.cpp DateManager.cpp 
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f main