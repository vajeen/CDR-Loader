#include <cppconn/connection.h>
#include <cppconn/driver.h>

#include "loadsummary.h"

loadsummary::loadsummary(Mutex& loadsum_mutex, Mutex& mocall_mutex, Mutex& mtcall_mutex, Mutex& mosms_mutex, Mutex& mtsms_mutex) :
mutex_loadsum(loadsum_mutex),
mutex_mocall(mocall_mutex),
mutex_mtcall(mtcall_mutex),
mutex_mosms(mosms_mutex),
mutex_mtsms(mtsms_mutex) {
    this->mtcall = 0;
    this->mocall = 0;
    this->mtsms = 0;
    this->mosms = 0;
    this->mcfcall = 0;
    this->moecall = 0;
    this->fwdcall = 0;
    this->total = 0;

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

void loadsummary::addMOCALL() {
    //cout<<"p1"<<endl;
    mutex_mocall.lock();
    this->mocall = this->mocall + 1;
    //cout<<this->mocall<<endl;
    mutex_mocall.unlock();
}

void loadsummary::addMTCALL() {
    mutex_mtcall.lock();
    this->mtcall = this->mtcall + 1;
    mutex_mtcall.unlock();
}

void loadsummary::addMOSMS() {
    mutex_mosms.lock();
    this->mosms = this->mosms + 1;
    mutex_mosms.unlock();
}

void loadsummary::addMTSMS() {
    mutex_mtsms.lock();
    this->mtsms = this->mtsms + 1;
    mutex_mtsms.unlock();
}

void loadsummary::addMCFCALL() {
    mutex_loadsum.lock();
    this->mcfcall = this->mcfcall + 1;
    mutex_loadsum.unlock();
}

void loadsummary::addMOECALL() {
    mutex_loadsum.lock();
    this->moecall = this->moecall + 1;
    mutex_loadsum.unlock();
}

void loadsummary::addFWDCALL() {
    mutex_loadsum.lock();
    this->fwdcall = this->fwdcall + 1;
    mutex_loadsum.unlock();
}

void* loadsummary::run() {
    cout<<"LOAD SUMMERY INIT"<<endl;
    while (true) {
        //cout<<"l sum top"<<endl;
        //cout<<"mocall=="<<this->mocall<<endl;
        mutex_loadsum.lock();
        mutex_mocall.lock();
        mutex_mtcall.lock();
        mutex_mosms.lock();
        mutex_mtsms.lock();
        this->total = this->mosms + this->mtsms + this->mocall + this->mtcall + this->mcfcall + this->moecall + this->fwdcall;
        cout << "MO_CALL=" << this->mocall << "|MT_SMS=" << this->mtcall << "|MO_SMS=" << this->mosms << "|MT_SMS=" << this->mtsms << "|MCF_CALL=" << this->mcfcall << "|MOE_CALL=" << this->moecall << "|FWD_CALL=" << this->fwdcall << "|TOTAL=" << this->total << endl;
        try {
            con->setSchema("SUMMARY");
            sql::Statement *stmt;
            //sql::ResultSet *res;
            stmt = con->createStatement();
            stmt->execute("INSERT INTO `SUMMARY`.`load_summary` (`MO_CALL`, `MO_SMS`, `MT_CALL`, `MT_SMS`, `MOE_CALL`, `MCF_CALL`, `FWD_CALL`, `TOTAL`, `MSC`, `added_time`) VALUES ("+to_string(this->mocall)+", "+to_string(this->mosms)+", "+to_string(this->mtcall)+", "+to_string(this->mtsms)+", "+to_string(this->moecall)+", "+to_string(this->mcfcall)+", "+to_string(this->fwdcall)+", "+to_string(this->total)+", 'ZTE', now());");
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
        this->mtcall = 0;
        this->mocall = 0;
        this->mtsms = 0;
        this->mosms = 0;
        this->mcfcall = 0;
        this->moecall = 0;
        this->fwdcall = 0;
        this->total = 0;
        mutex_loadsum.unlock();
        mutex_mocall.unlock();
        mutex_mtcall.unlock();
        mutex_mosms.unlock();
        mutex_mtsms.unlock();
        //flush to db
        sleep(60);
    }
}

loadsummary::~loadsummary() {
}

