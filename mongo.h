#ifndef MONGO_H
#define	MONGO_H

#include <iostream>
#include <iomanip>
#include <chrono>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <bsoncxx/types.hpp>
#include <bsoncxx/builder/stream/document.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/exception/bulk_write_exception.hpp>
#include <mongocxx/exception/error_code.hpp>
#include <mongocxx/exception/server_error_code.hpp>
#include <mongocxx/exception/logic_error.hpp>
#include <mongocxx/exception/operation_exception.hpp>
#include <mongocxx/instance.hpp>

#include "structs.h"
#include "Mutex.h"
#include "mysql_loader.h"
#include "getCell.h"
#include "loadsummary.h"
#include <unistd.h>
#include <fstream>

using namespace std;
using bsoncxx::builder::stream::open_document;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::close_array;

class mongo {
public:
    mongo(Mutex&,getCell&,loadsummary&);
    int insert(struct holder*);
    int error_log(string error);
    void finish();
    virtual ~mongo();
private:
    ofstream outfile;
    mysql_loader M = mysql_loader();
    //int update_flag;
    Mutex &mutex_insert;
    getCell &celldata;
    loadsummary &l_sum;
    string connection_string = "mongodb://root:1cbtm0ngo@172.19.151.56:27017/?socketTimeoutMS=360000&connectTimeoutMS=360000";
    mongocxx::client conn{mongocxx::uri{connection_string}};
   //mysql_loader &MY;
};

#endif	/* MONGO_H */

