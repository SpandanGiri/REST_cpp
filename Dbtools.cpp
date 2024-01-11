#include "Dbtools.h"


int Dbtools::isAuthorized = 0;


sql::Connection* Dbtools::dbConnect(string dbuser, string dbpassword){
	try{
            sql::Driver *driver;
            sql::Connection *con;
            
            driver = get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", dbuser, dbpassword);
            
	    cout<<"Connecting as "<<dbuser<<endl;
	    return con;

	}
	catch(sql::SQLException &e){
                  cout << "# ERR: SQLException in " << __FILE__;
                cout << "(" << __FUNCTION__ << ")"<< endl;
                 cout << "# ERR: " << e.what();
                 cout << " (MySQL error code: " << e.getErrorCode();
                 cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	    return nullptr;
	}
}

int Dbtools::getRowCount(string db_name){

	try{
            sql::Connection *con;
            sql::Statement *stmt;
	    sql::ResultSet *res;

	    con = Dbtools::dbConnect("root","mysqlroot");
	    cout<<"no:37"<<endl;

	    if(con == nullptr){
            
	        delete res;
                delete stmt;
                delete con;

	    	return -1;
	    }

	    con->setSchema(db_name);
            cout<<"Connection with table "<<endl;
	    stmt = con->createStatement();

            res = stmt->executeQuery("SELECT count(*) AS row_count from Users");
            res->next();    //move to the first row  
	    

	    auto row_count = res->getInt("row_count");

            delete res;
            delete stmt;
            delete con;


	    return row_count;



	}
        catch(sql::SQLException &e){
                  cout << "# ERR: SQLException in " << __FILE__;
                cout << "(" << __FUNCTION__ << ")"<< endl;
                 cout << "# ERR: " << e.what();
                 cout << " (MySQL error code: " << e.getErrorCode();
                 cout << ", SQLState: " << e.getSQLState() << " )" << endl;
		return -1;
        }

}

int Dbtools::userAuth(string username){


        try{
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
            sql::ResultSet *res;

            driver = get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "root", "mysqlroot");

            con->setSchema("test");

            stmt = con->createStatement();

            res = stmt->executeQuery("SELECT * from Users");

            while (res->next()) {
                if(res->getString("userName") == username){
			cout<<username<<" is authorized "<<endl;
			cout<<"Dbtools:isAuth:"<<Dbtools::isAuthorized<<endl;

                        return Dbtools::isAuthorized = 1;

                }

            }

            delete res;
            delete stmt;
            delete con;

	    cout<<"Dbtools:isAuth:"<<Dbtools::isAuthorized<<endl;	    
	    return Dbtools::isAuthorized = 0;

         }

         catch (sql::SQLException &e) {
                  cout << "# ERR: SQLException in " << __FILE__;
                cout << "(" << __FUNCTION__ << ")"<< endl;
                 cout << "# ERR: " << e.what();
                 cout << " (MySQL error code: " << e.getErrorCode();
                 cout << ", SQLState: " << e.getSQLState() << " )" << endl;

		 return Dbtools::isAuthorized = -1;
        }

}


void Dbtools::userAdd(string username, string permissions){

	try{
            sql::Driver *driver;
            sql::Connection *con;
            sql::Statement *stmt;
	    string dqts = (string)"\"";

            auto row_count = Dbtools::getRowCount("test");
	    cout<<"count"<<row_count<<endl;  
            
	    if(row_count<0){
                   cout<<"ERROR"<<endl;
                   return;
            }

            auto id = row_count + 1;


	    driver = get_driver_instance();
            con = driver->connect("tcp://127.0.0.1:3306", "root", "mysqlroot");

            con->setSchema("test");
                

            stmt = con->createStatement();
	    
	    string useradd_stmt = "INSERT INTO Users VALUES (" + to_string(id) + ","+ dqts + username + dqts + (string)"," + dqts + permissions + dqts + (string)");";
	    
	    cout<<useradd_stmt<<endl; 

            stmt->execute(useradd_stmt);

            delete stmt;
            delete con;
	   
	}
	
	catch(sql::SQLException &e){
                  cout << "# ERR: SQLException in " << __FILE__;
                cout << "(" << __FUNCTION__ << ")"<< endl;
                 cout << "# ERR: " << e.what();
                 cout << " (MySQL error code: " << e.getErrorCode();
                 cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	
	}       
}



