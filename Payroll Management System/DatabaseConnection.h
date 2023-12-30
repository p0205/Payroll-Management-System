#include <mysql/jdbc.h>
#include <jdbc/mysql_connection.h>
#include <jdbc/mysql_driver.h>

#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

class DatabaseConnection
{
private:
	sql::Connection* connection;

public:
	DatabaseConnection();
	~DatabaseConnection();
	sql::PreparedStatement* prepareStatement(std::string query);
};

#endif