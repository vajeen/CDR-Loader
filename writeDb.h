#ifndef WRITEDB_H
#define	WRITEDB_H

#include "dataQueue.h"
#include "Thread.h"
#include "structs.h"
#include <unistd.h>
#include "Mutex.h"
#include "getCell.h"
#include "loadsummary.h"

#include <bsoncxx/types.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/instance.hpp>

#include <cppconn/driver.h>

class writeDb : public Thread
{
    getCell& cellmap;
    dataQueue& data;
    holder *hold;
    loadsummary& l_sum;
    int tid;
    Mutex &mutex_insert;
 
  public:
    //writeDb(dataQueue&,int,Mutex&,sql::Driver&);
      writeDb(dataQueue&,int,Mutex&,getCell&,loadsummary&);
    //writeDb(dataQueue&,int,Mutex&);
    void* run();
  private:
    //sql::Driver& driver;
};

#endif	/* WRITEDB_H */

