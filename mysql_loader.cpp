#include <cppconn/connection.h>
#include <cppconn/driver.h>

#include "mysql_loader.h"
#include "structs.h"

mysql_loader::mysql_loader() {
    try {
        con = driver->connect("tcp://127.0.0.1:3306", "root", "icbt123");
    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}

void mysql_loader::query(string db, string& query) {
    try {
        con->setSchema(db);
        sql::Statement *stmt;
        //sql::ResultSet *res;
        stmt = con->createStatement();
        stmt->execute(query);
        //while (res->next()) {
        //  cout << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
        //res->getString("count");
        // cout << "\t... MySQL says it again: ";
        /* Access column fata by numeric offset, 1 is the first column */
        // cout << res->getString(1) << endl;
        //}
        //res->close();
        stmt->close();
        //delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        if (!e.getErrorCode() == 0) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
    }
}

int mysql_loader::has_table(string& query_str) {
    this->stat = 1;
    try {
        sql::Statement *stmt;
        sql::ResultSet *res;
        stmt = con->createStatement();
        res = stmt->executeQuery(query_str);
        while (res->next()) {
            this->count_str = res->getString("count(*)");
            this->stat = atoi(this->count_str.c_str());
        }
        res->close();
        stmt->close();
        delete res;
        delete stmt;
    } catch (sql::SQLException &e) {
        if (!e.getErrorCode() == 0) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
        //delete con;	
    }
    return (this->stat);
}

int mysql_loader::getCelldata(map<string, struct cellElement>& m,map<string, struct cellElement>& m4g) {
    int ret = -1;
    try {
        sql::Statement *stmt;
        sql::ResultSet *res;
        con->setSchema("CELLID");
        struct cellElement cell;
        struct cellElement cell4g;
        string count_query = "select count(*) from cell_id;";
        string cell_query = "select substr(CGI,6) as CI,`long` as lon ,lat,angle,sitename from cell_id where type!='4G' order by CGI;";
        string cell_query4g = "select substr(CGI,6) as CI,`long` as lon ,lat,angle,sitename from cell_id where type='4G' order by CGI;";
        while (true) {
            stmt = con->createStatement();
            res = stmt->executeQuery(count_query);
            while (res->next()) {
                this->count_str = res->getString("count(*)");
                this->stat = atoi(this->count_str.c_str());
            }

            if (this->stat == 0) {
                cout << "Cell data 0" << cout;
                res->close();
                stmt->close();
                ret = -1;
                sleep(3);
            } else {
                res->close();
                stmt->close();
                stmt = con->createStatement();
                res = stmt->executeQuery(cell_query);
                while (res->next()) {
                    cell.CL = res->getString("CI");
                    cell.LON = res->getString("lon");
                    cell.LAT = res->getString("lat");
                    cell.BORE = atoi(res->getString("angle").c_str());
                    m[cell.CL] = cell;
                    ret = 0;
                }
                res->close();
                stmt->close();
                
                stmt = con->createStatement();
                res = stmt->executeQuery(cell_query4g);
                while (res->next()) {
                    cell4g.CL = res->getString("CI");
                    cell4g.LON = res->getString("lon");
                    cell4g.LAT = res->getString("lat");
                    cell4g.BORE = atoi(res->getString("angle").c_str());
                    m4g[cell4g.CL] = cell;
                    ret = 0;
                }
                res->close();
                stmt->close();
                
                break;
            }
        }
        delete res;
        delete stmt;
        //delete con;
    } catch (sql::SQLException &e) {
        if (!e.getErrorCode() == 0) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
        //delete con;	
    }
    return (ret);
}

mysql_loader::~mysql_loader() {
    con->close();
    //delete res;
    //delete stmt;
    delete con;
    //delete this->query_str;
}

