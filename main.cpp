#include <iostream>
#include "readFile.h"
#include "dataQueue.h"
#include "writeDb.h"
#include <pthread.h>
#include <stdlib.h>
#include "Mutex.h"
#include "structs.h"
#include "getCell.h"
#include "loadsummary.h"
#include <cppconn/driver.h>
#include "mongo.h"

#include <mongocxx/v_noabi/mongocxx/pool.hpp>

using namespace std;

int main() {
    setbuf(stdout, 0);
    Mutex q1_mutex;
    Mutex q2_mutex;
    Mutex add_mutex;
    Mutex insert_mutex;
    Mutex loadsummary_mutex;
    Mutex mocall_mutex,mtcall_mutex,mosms_mutex,mtsms_mutex;
    mongocxx::instance inst{};
    
    //HU
    int writer_threads=250;
    //int writer_threads=1;
    
    //ZTE
    //int writer_threads=50;
    
    dataQueue *q = new dataQueue(q1_mutex,q2_mutex,add_mutex);
    
    //initialize loadsummary thread
    loadsummary *loadsum = new loadsummary(loadsummary_mutex,mocall_mutex,mtcall_mutex,mosms_mutex,mtsms_mutex);
    loadsum->start();
    //initialize getCell thread
    cout<<"Initializing getCell threads"<<endl;
    getCell* t_getcell = new getCell();
    t_getcell->start();
    sleep(1);
    while(t_getcell->getStatus()!=0){
        sleep(1);
    }
    struct cellElement ce;
    t_getcell->getData("6250017236",ce);
    
    //initialize read thread
    cout<<"Initializing reader thread"<<endl;
    readFile* t_read = new readFile(*q);
    t_read->start();
    
    //initialize write threads
    cout<<"Initializing writer threads"<<endl;
    writeDb* t_write[writer_threads];
    
    for (int i=0;i<writer_threads;i++){
        t_write[i] = new writeDb(*q,i,insert_mutex,*t_getcell,*loadsum);
        t_write[i]->start();
    }
    
    t_read->join();
    
    for (int i=0;i<writer_threads;i++){
        t_write[i]->join();
    }
    
    delete q;
    return 0;
}
