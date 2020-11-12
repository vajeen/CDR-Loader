#ifndef MYSQL_H
#define MYSQL_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "instances.h"

using namespace std;

class mysql_loader {
public:
    mysql_loader();
    void query(string, string&);
    int has_table(string&);
    int getCelldata(map<string, struct cellElement>&,map<string, struct cellElement>&);
    virtual ~mysql_loader();
private:
    //sql::Driver& driver;
    sql::Connection *con;
    //sql::Statement *stmt;
    //sql::ResultSet *res;
    string query_str;
    string count_str;
    int stat;
};

#endif /* MYSQL_H */

