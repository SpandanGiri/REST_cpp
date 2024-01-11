#include "crow.h"
#include "string.h"


//mysql headers
#include "mysql_connection.h"

/*

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

*/

#include "Dbtools.h"

using namespace std;

int main()
{
    crow::SimpleApp app; //define your crow application

    //define your endpoint at the root directory
    CROW_ROUTE(app, "/")([](){
        auto page = crow::mustache::load_text("test.html");
	return page;
    });

    CROW_ROUTE(app,"/help")([](){
	return "SOS";		    
    });

    CROW_ROUTE(app,"/register")([](){
        auto userRegisterPage = crow::mustache::load_text("register.html");
        return userRegisterPage;
    });


    CROW_ROUTE(app, "/user/<string>")([](std::string name){  
        auto page = crow::mustache::load("person.html"); 
        int isAuthorized; 


	cout<<name<< " is requesting access"<<endl;	
	//login to test db and check for if there is an entry or not

	isAuthorized = Dbtools::userAuth(name);
        cout<<"main.cpp:isauth:"<<isAuthorized<<endl;  
	
	if(isAuthorized > 0){
		crow::mustache::context ctx ;
        	ctx["person"]=name;	
        	return page.render(ctx);
	}	

	auto invalidPage = crow::mustache::load_text("invalid.html");
        return invalidPage;


    });

    CROW_ROUTE(app, "/addUser/<string>")([](std::string username){
    
	try{	
    	   Dbtools::userAdd(username,"vobadmin");
           return ("Successfully Added");
        }
	catch(char* e){
	   return ("Failed");
	}


    });


    //set the port, set the app to run on multiple threads, and run the app
    app.bindaddr("127.0.0.1").port(18080).multithreaded().run();
}
