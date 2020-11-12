/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   loadsummary.h
 * Author: vajeenk
 *
 * Created on March 1, 2019, 9:28 AM
 */

#ifndef LOADSUMMARY_H
#define LOADSUMMARY_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctime>
#include <unistd.h>

#include "Thread.h"
#include "Mutex.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "instances.h"

using namespace std;

class loadsummary : public Thread {
    Mutex &mutex_loadsum;
    Mutex &mutex_mocall;
    Mutex &mutex_mtcall;
    Mutex &mutex_mosms;
    Mutex &mutex_mtsms;
public:
    loadsummary(Mutex& loadsum_mutex,Mutex& mocall_mutex,Mutex& mtcall_mutex,Mutex& mosms_mutex,Mutex& mtsms_mutex);
    void addMOCALL();
    void addMTCALL();
    void addMOSMS();
    void addMTSMS();
    void addMCFCALL();
    void addMOECALL();
    void addFWDCALL();
    void* run();
    virtual ~loadsummary();
private:
    sql::Connection *con;
    int mtcall;
    int mocall;
    int mtsms,mosms,mcfcall,moecall,fwdcall,total;
    string msc;
};

#endif /* LOADSUMMARY_H */

