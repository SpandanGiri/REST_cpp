#include <stdlib.h>
#include <iostream>
#include <iostream>
#include <string>
/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/connection.h>

using namespace std;

class Dbtools{


public:
	static int isAuthorized;
	static int isDuplicateENtry;
public:
	Dbtools();

	static sql::Connection *dbConnect(string dbuser, string dbpassword);

	static int getRowCount(string db_name);

	static int  userAuth(string username);
	
	static void  userAdd(string username, string permissions);


};


