#include "mongo.h"
#include "Thread.h"
#include "dataQueue.h"
#include "getCell.h"
#include <string>
#include <sstream>
#include <ctime>
#include <bits/basic_string.h>
#include <chrono>

mongo::mongo(Mutex& insert_mutex, getCell& cell,loadsummary& lsum) : mutex_insert(insert_mutex), celldata(cell), l_sum(lsum) {
}

int mongo::error_log(string error) {
    outfile.open("/apps/cdr_loader/HU/error.log", std::ios_base::app);
    //outfile.open("/apps/cdr_loader/ZTE/error.log", std::ios_base::app);
    outfile << error;
    return (0);
}

int mongo::insert(struct holder *hold) {
    //LAC
    string LAC = string(5 - hold->LAC.length(), '0') + hold->LAC;

    //CELLID
    //cout<<hold->CellID<<endl;
    string CELLID;
    if (hold->CellID.length() < 5){
        CELLID = string(5 - hold->CellID.length(), '0') + hold->CellID;
    }else if ((hold->CellID.length()>5)&&(hold->CellID.length()<7)){
        CELLID = string(7 - hold->CellID.length(), '0') + hold->CellID;
    }else{
        CELLID=hold->CellID;
    }

    //LC
    string LC = LAC + CELLID;

    //CGI
    string CGI = "41301" + LC;

    //COLLECTION
    //string LAC_COLLECTION = "L" + LAC;
    //string MSISDN_COLLECTION = "MSISDN";

    //EVENT_DATE
    struct tm tdo;
    strptime(hold->Date.c_str(), "%Y%m%d", &tdo);
    char date_buf[15];
    char ym[10];
    char day[5];
    char md[5];
    strftime(date_buf, sizeof (date_buf), "%Y-%m-%d", &tdo);
    strftime(day, sizeof (day), "D%d", &tdo);
    strftime(ym, sizeof (ym), "%Y%m", &tdo);
    strftime(md, sizeof (md), "%m%d", &tdo);

    //EVENT_TIME
    struct tm tto;
    strptime(hold->Time.c_str(), "%H%M%S", &tto);
    char time_buf[15];
    strftime(time_buf, sizeof (time_buf), "%H:%M:%S", &tto);
    char hour_buf[5];
    strftime(hour_buf, sizeof (hour_buf), "%H", &tto);

    //DATETIME
    string datetime = string(date_buf) + " " + string(time_buf);
    boost::posix_time::ptime t(boost::posix_time::time_from_string(datetime));
    boost::posix_time::ptime start(boost::gregorian::date(1970, 1, 1));
    boost::posix_time::time_duration dur = t - start;
    time_t epoch = dur.total_seconds();
    auto DATETIME = bsoncxx::types::b_date{std::chrono::system_clock::time_point
        {std::chrono::seconds
            { epoch}}};

    //HOUR
    string hour = string(hour_buf);

    //MSISDN TABLE
    string M_TBL_NUM;
    if (!hold->MSISDN.empty()) {
        M_TBL_NUM = hold->MSISDN.substr(hold->MSISDN.length() - 2);
    }
    string M_TBL = "M" + M_TBL_NUM;

    //CELL DATA
    struct cellElement cell_element;
    int loc_ret = celldata.getData(LC, cell_element);
    
    //std::chrono::steady_clock::time_point begin_mysql = std::chrono::steady_clock::now();
    if ((loc_ret == -1)&&(CELLID != "00000")) {
        //string missing_cell = "insert into MISSING_CELLID (CGI,VLR,TYPE,DATE,TIME) values('" + CGI + "','" + hold->MSCID + "','" + to_string(hold->CallType) + "','" + date_buf + "','" + time_buf + "') on duplicate key update TYPE='" + to_string(hold->CallType) + "', VLR='" + hold->MSCID + "', DATE='" + date_buf + "',TIME='" + time_buf + "',FLAG='N', `COUNT`=`COUNT`+1;"
        string missing_cell = "insert into MISSING_CELLID (CGI,VLR,TYPE,DATE,TIME) values('" + CGI + "','" + hold->MSCID + "','" + to_string(hold->CallType) + "','" + date_buf + "','" + time_buf + "') on duplicate key update TYPE='" + to_string(hold->CallType) + "', VLR='" + hold->MSCID + "', DATE='" + date_buf + "',TIME='" + time_buf + "',FLAG='N';";
        //cout<<missing_cell<<endl;
        M.query("CELLID", missing_cell);
    } else if (CELLID != "00000") {
        //string unique_cgi_query = "insert into UNIQUE_CGI (CGI,VLR,TYPE,DATE,TIME) values('" + CGI + "','" + hold->MSCID + "','" + to_string(hold->CallType) + "','" + date_buf + "','" + time_buf + "') on duplicate key update TYPE='" + to_string(hold->CallType) + "', VLR='" + hold->MSCID + "', DATE='" + date_buf + "',TIME='" + time_buf + "', `COUNT`=`COUNT`+1;";
        string unique_cgi_query = "insert into UNIQUE_CGI (CGI,VLR,TYPE,DATE,TIME) values('" + CGI + "','" + hold->MSCID + "','" + to_string(hold->CallType) + "','" + date_buf + "','" + time_buf + "') on duplicate key update TYPE='" + to_string(hold->CallType) + "', VLR='" + hold->MSCID + "', DATE='" + date_buf + "',TIME='" + time_buf + "';";
        //cout<<unique_cgi_query<<endl;
        M.query("CELLID", unique_cgi_query);
    }
    //std::chrono::steady_clock::time_point end_mysql = std::chrono::steady_clock::now();
    //std::cout << "Time difference mysql = " << std::chrono::duration_cast<std::chrono::microseconds>(end_mysql - begin_mysql).count()/1000 << "[ms]" << std::endl;

    bsoncxx::builder::stream::document document_builder, filter_builder, update_builder, index_builder;
    mongocxx::options::update update_options;
    update_options.upsert(true);

    //RAW CDR
    string hour_table;
    string hour_msisdn;
    string month_collection;
    bool has_t;

    document_builder.clear();
    document_builder
            << "CALL_TYPE" << hold->CallType
            << "MSISDN" << hold->MSISDN
            << "A_NUMBER" << hold->ANumber
            << "B_NUMBER" << hold->BNumber
            << "C_NUMBER" << hold->CNumber
            << "EVENT_DATE" << date_buf
            << "EVENT_TIME" << time_buf
            << "DATETIME" << DATETIME
            << "DURATION" << hold->Duration
            << "SERVICE_CENTER" << hold->ServiceCenter
            << "MSC" << hold->MSCID
            << "LAC" << LAC
            << "CELLID" << CELLID
            << "LONGITUDE" << cell_element.LON
            << "LATITUDE" << cell_element.LAT
            << "BORE" << cell_element.BORE
            << "IMEI" << hold->IMEI
            << "IMSI" << hold->IMSI
            << "EVENT_TYPE" << hold->EventType;

    //HOURLY MSISDN
    filter_builder.clear();
    update_builder.clear();

    auto dbc = conn["CDR"];
    //auto dbhr = conn["HOURLY"];
    auto dbhour = conn["HOURLY_"+string(md)];
    auto dbday = conn["DAILY"];
    int insert_retry = 0;

       //std::chrono::steady_clock::time_point begin_mongo = std::chrono::steady_clock::now();
    switch (hold->CallType) {
        case 0:
            l_sum.addMOCALL();
            hour_table = "MO_CALL_" + hour;
            hour_msisdn = "M" + hour;
            month_collection = string(ym) + "_MO_CALL";
            has_t = dbc.has_collection(month_collection);
            if (has_t == 0) {
                mutex_insert.lock();
                if (has_t = dbc.has_collection(month_collection) == 0) {
                    cout << "creating collection" << endl;
                    document_builder.clear();
                    index_builder.clear();
                    index_builder << "MSISDN" << 1;
                    dbc.create_collection(month_collection);
                    dbc[month_collection].create_index(index_builder.view());
                    index_builder.clear();
                    mutex_insert.unlock();
                } else {
                    mutex_insert.unlock();
                }
            }

            try {
                dbc[month_collection].insert_one(document_builder.view());
            } catch (const mongocxx::bulk_write_exception& e) {
                insert_retry = 1;
                error_log("CDR insert error, retrying {bulk_write_exception}");
                sleep(.5);
                while (insert_retry == 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::bulk_write_exception& e) {
                        cout<<"bulk_write_exception"<<endl;
                        sleep(.5);
                    }
                }
            } catch (const mongocxx::v_noabi::operation_exception& e) {
                insert_retry = 3;
                error_log("CDR insert error, retrying {operation_exception}");
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR"<<endl;
                sleep(.5);
                while (insert_retry != 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::v_noabi::operation_exception& e) {
                        cout<<"operation_exception"<<endl;
                        insert_retry--;
                        sleep(.5);
                    }
                }
            }
            filter_builder
                    << "MSISDN"
                    << hold->MSISDN;
            update_builder
                    << "$set"
                    << open_document
                    << "MSISDN"
                    << hold->MSISDN
                    << "IMSI"
                    << hold->IMSI
                    << "DATETIME"
                    << DATETIME
                    << close_document
                    << "$push" << open_document << "MO_CALL_B_NUMBER" << hold->BNumber << close_document
                    << "$addToSet" << open_document << "MO_CALL_B_NUMBER_UNIQUE" << hold->BNumber << close_document
                    << "$addToSet" << open_document << "MO_CALL_LC_UNIQUE" << LC << close_document
                    << "$addToSet" << open_document << "MO_CALL_IMEI_UNIQUE" << hold->IMEI << close_document
                    << "$push" << open_document << "MO_CALL_DURATION" << hold->Duration << close_document;
//            dbhr[hour_table].insert_one(document_builder.view());
            try {
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
            } catch (const mongocxx::bulk_write_exception& e) {
                cout<<"bulk_write_exception"<<endl;
                mutex_insert.lock();
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
                mutex_insert.unlock();
            } catch (const mongocxx::operation_exception& e) {
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR2"<<endl;
                mutex_insert.lock();
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
                mutex_insert.unlock();
            }
            break;
        case 1:
            l_sum.addMTCALL();
            hour_table = "MT_CALL_" + hour;
            hour_msisdn = "M" + hour;
            month_collection = string(ym) + "_MT_CALL";
            has_t = dbc.has_collection(month_collection);
            if (has_t == 0) {
                mutex_insert.lock();
                if (has_t = dbc.has_collection(month_collection) == 0) {
                    cout << "creating collection" << endl;
                    document_builder.clear();
                    index_builder.clear();
                    index_builder << "MSISDN" << 1;
                    dbc.create_collection(month_collection);
                    dbc[month_collection].create_index(index_builder.view());
                    index_builder.clear();
                    mutex_insert.unlock();
                } else {
                    mutex_insert.unlock();
                }
            }
            try {
                dbc[month_collection].insert_one(document_builder.view());
            } catch (const mongocxx::bulk_write_exception& e) {
                insert_retry = 1;
                cout << "CDR insert error, retrying" << endl;
                sleep(.5);
                while (insert_retry == 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::bulk_write_exception& e) {
                        cout<<"bulk_write_exception"<<endl;
                        sleep(.5);
                    }
                }
            } catch (const mongocxx::v_noabi::operation_exception& e) {
                insert_retry = 3;
                error_log("CDR insert error, retrying {operation_exception}");
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR"<<endl;
                sleep(.5);
                while (insert_retry != 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::v_noabi::operation_exception& e) {
                        insert_retry--;
                        sleep(.5);
                    }
                }
            }

//            dbhr[hour_table].insert_one(document_builder.view());

            filter_builder
                    << "MSISDN"
                    << hold->MSISDN;
            update_builder
                    << "$set"
                    << open_document
                    << "MSISDN"
                    << hold->MSISDN
                    << "IMSI"
                    << hold->IMSI
                    << "DATETIME"
                    << DATETIME
                    << close_document
                    << "$push" << open_document << "MT_CALL_A_NUMBER" << hold->ANumber << close_document
                    << "$addToSet" << open_document << "MT_CALL_A_NUMBER_UNIQUE" << hold->ANumber << close_document
                    << "$addToSet" << open_document << "MT_CALL_LC_UNIQUE" << LC << close_document
                    //<< "$addToSet" << open_document<< "IMEI_UNIQUE"<< hold->IMEI << close_document
                    << "$push" << open_document << "MT_CALL_DURATION" << hold->Duration << close_document;

            try {
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
            } catch (const mongocxx::bulk_write_exception& e) {
                cout<<"bulk_write_exception"<<endl;
                mutex_insert.lock();
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
                mutex_insert.unlock();
            }catch (const mongocxx::operation_exception& e) {
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR2"<<endl;
                mutex_insert.lock();
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
                mutex_insert.unlock();
            }

            break;
        case 6:
            l_sum.addMOSMS();
            hour_table = "MO_SMS_" + hour;
            hour_msisdn = "M" + hour;
            month_collection = string(ym) + "_MO_SMS";
            has_t = dbc.has_collection(month_collection);
            if (has_t == 0) {
                mutex_insert.lock();
                if (has_t = dbc.has_collection(month_collection) == 0) {
                    cout << "creating collection" << endl;
                    document_builder.clear();
                    index_builder.clear();
                    index_builder << "MSISDN" << 1;
                    dbc.create_collection(month_collection);
                    dbc[month_collection].create_index(index_builder.view());
                    index_builder.clear();
                    mutex_insert.unlock();
                } else {
                    mutex_insert.unlock();
                }
            }

            try {
                dbc[month_collection].insert_one(document_builder.view());
            } catch (const mongocxx::bulk_write_exception& e) {
                insert_retry = 1;
                cout << "CDR insert error, retrying" << endl;
                sleep(.5);
                while (insert_retry == 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::bulk_write_exception& e) {
                        cout<<"bulk_write_exception"<<endl;
                        sleep(.5);
                    }
                }
            } catch (const mongocxx::v_noabi::operation_exception& e) {
                insert_retry = 3;
                error_log("CDR insert error, retrying {operation_exception}");
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR"<<endl;
                sleep(.5);
                while (insert_retry != 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::v_noabi::operation_exception& e) {
                        cout<<"operation_exception"<<endl;
                        insert_retry--;
                        sleep(.5);
                    }
                }
            }
//            dbhr[hour_table].insert_one(document_builder.view());
            filter_builder
                    << "MSISDN"
                    << hold->MSISDN;
            update_builder
                    << "$set"
                    << open_document
                    << "MSISDN"
                    << hold->MSISDN
                    << "IMSI"
                    << hold->IMSI
                    << "DATETIME"
                    << DATETIME
                    << close_document
                    << "$push" << open_document << "MO_SMS_B_NUMBER" << hold->BNumber << close_document
                    << "$addToSet" << open_document << "MO_SMS_B_NUMBER_UNIQUE" << hold->BNumber << close_document
                    << "$addToSet" << open_document << "MO_SMS_LC_UNIQUE" << LC << close_document
                    << "$addToSet" << open_document << "MO_SMS_IMEI_UNIQUE" << hold->IMEI << close_document;
            try {
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
            } catch (const mongocxx::bulk_write_exception& e) {
                mutex_insert.lock();
                cout<<"bulk_write_exception"<<endl;
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
                mutex_insert.unlock();
            }catch (const mongocxx::operation_exception& e) {
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR2"<<endl;
                mutex_insert.lock();
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
                mutex_insert.unlock();
            }

            break;
        case 7:
            l_sum.addMTSMS();
            hour_table = "MT_SMS_" + hour;
            hour_msisdn = "M" + hour;
            month_collection = string(ym) + "_MT_SMS";
            has_t = dbc.has_collection(month_collection);
            if (has_t == 0) {
                mutex_insert.lock();
                if (has_t = dbc.has_collection(month_collection) == 0) {
                    cout << "creating collection" << endl;
                    document_builder.clear();
                    index_builder.clear();
                    index_builder << "MSISDN" << 1;
                    dbc.create_collection(month_collection);
                    dbc[month_collection].create_index(index_builder.view());
                    index_builder.clear();
                    mutex_insert.unlock();
                } else {
                    mutex_insert.unlock();
                }
            }

            try {
                dbc[month_collection].insert_one(document_builder.view());
            } catch (const mongocxx::bulk_write_exception& e) {
                insert_retry = 1;
                cout << "CDR insert error, retrying" << endl;
                sleep(.5);
                while (insert_retry == 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::bulk_write_exception& e) {
                        cout<<"bulk_write_exception"<<endl;
                        sleep(.5);
                    }
                }
            } catch (const mongocxx::v_noabi::operation_exception& e) {
                insert_retry = 3;
                error_log("CDR insert error, retrying {operation_exception}");
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR"<<endl;
                sleep(.5);
                while (insert_retry != 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::v_noabi::operation_exception& e) {
                        cout<<"operation_exception"<<endl;
                        insert_retry--;
                        sleep(.5);
                    }
                }
            }
//            dbhr[hour_table].insert_one(document_builder.view());
            filter_builder
                    << "MSISDN"
                    << hold->MSISDN;
            update_builder
                    << "$set"
                    << open_document
                    << "MSISDN"
                    << hold->MSISDN
                    << "IMSI"
                    << hold->IMSI
                    << "DATETIME"
                    << DATETIME
                    << close_document
                    << "$push" << open_document << "MT_SMS_A_NUMBER" << hold->ANumber << close_document
                    << "$addToSet" << open_document << "MT_SMS_A_NUMBER_UNIQUE" << hold->ANumber << close_document
                    << "$addToSet" << open_document << "MT_SMS_LC_UNIQUE" << LC << close_document;
            //<< "$addToSet" << open_document<< "IMEI_UNIQUE"<< hold->IMEI << close_document;
            try {
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
            } catch (const mongocxx::bulk_write_exception& e) {
                mutex_insert.lock();
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
                mutex_insert.unlock();
            }catch (const mongocxx::operation_exception& e) {
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR2"<<endl;
                mutex_insert.lock();
                dbhour[hour_msisdn].update_one(filter_builder.view(), update_builder.view(), update_options);
                mutex_insert.unlock();
            }

            break;
        case 12:
            l_sum.addMOECALL();
            month_collection = string(ym) + "_MOE_CALL";
            has_t = dbc.has_collection(month_collection);
            if (has_t == 0) {
                mutex_insert.lock();
                if (has_t = dbc.has_collection(month_collection) == 0) {
                    cout << "creating collection" << endl;
                    document_builder.clear();
                    index_builder.clear();
                    index_builder << "MSISDN" << 1;
                    dbc.create_collection(month_collection);
                    dbc[month_collection].create_index(index_builder.view());
                    index_builder.clear();
                    mutex_insert.unlock();
                } else {
                    mutex_insert.unlock();
                }
            }

            try {
                dbc[month_collection].insert_one(document_builder.view());
            } catch (const mongocxx::bulk_write_exception& e) {
                insert_retry = 1;
                cout << "CDR insert error, retrying" << endl;
                sleep(.5);
                while (insert_retry == 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::bulk_write_exception& e) {
                        sleep(.5);
                    }
                }
            } catch (const mongocxx::v_noabi::operation_exception& e) {
                insert_retry = 3;
                error_log("CDR insert error, retrying {operation_exception}");
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR"<<endl;
                sleep(.5);
                while (insert_retry != 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::v_noabi::operation_exception& e) {
                        insert_retry--;
                        sleep(.5);
                    }
                }
            }
//            hour_table = "MOE_CALL_" + hour;
//            dbhr[hour_table].insert_one(document_builder.view());
            break;
        case 13:
            l_sum.addMCFCALL();
            month_collection = string(ym) + "_MCF_CALL";
            has_t = dbc.has_collection(month_collection);
            if (has_t == 0) {
                mutex_insert.lock();
                if (has_t = dbc.has_collection(month_collection) == 0) {
                    cout << "creating collection" << endl;
                    document_builder.clear();
                    index_builder.clear();
                    index_builder << "MSISDN" << 1;
                    dbc.create_collection(month_collection);
                    dbc[month_collection].create_index(index_builder.view());
                    index_builder.clear();
                    mutex_insert.unlock();
                } else {
                    mutex_insert.unlock();
                }
            }

            try {
                dbc[month_collection].insert_one(document_builder.view());
            } catch (const mongocxx::bulk_write_exception& e) {
                insert_retry = 1;
                cout << "CDR insert error, retrying" << endl;
                sleep(.5);
                while (insert_retry == 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::bulk_write_exception& e) {
                        sleep(.5);
                    }
                }
            } catch (const mongocxx::v_noabi::operation_exception& e) {
                insert_retry = 3;
                error_log("CDR insert error, retrying {operation_exception}");
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR"<<endl;
                sleep(.5);
                while (insert_retry != 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::v_noabi::operation_exception& e) {
                        insert_retry--;
                        sleep(.5);
                    }
                }
            }
//            hour_table = "MCF_CALL_" + hour;
//            dbhr[hour_table].insert_one(document_builder.view());
            break;
        case 100:
            l_sum.addFWDCALL();
            month_collection = string(ym) + "_FWD_CALL";
            has_t = dbc.has_collection(month_collection);
            if (has_t == 0) {
                mutex_insert.lock();
                if (has_t = dbc.has_collection(month_collection) == 0) {
                    cout << "creating collection" << endl;
                    document_builder.clear();
                    index_builder.clear();
                    index_builder << "MSISDN" << 1;
                    dbc.create_collection(month_collection);
                    dbc[month_collection].create_index(index_builder.view());
                    index_builder.clear();
                    mutex_insert.unlock();
                } else {
                    mutex_insert.unlock();
                }
            }

            try {
                dbc[month_collection].insert_one(document_builder.view());
            } catch (const mongocxx::bulk_write_exception& e) {
                insert_retry = 1;
                cout << "CDR insert error, retrying" << endl;
                sleep(.5);
                while (insert_retry == 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::bulk_write_exception& e) {
                        sleep(.5);
                    }
                }
            } catch (const mongocxx::v_noabi::operation_exception& e) {
                insert_retry = 3;
                error_log("CDR insert error, retrying {operation_exception}");
                cout<<"ERRORRRRRRRRRRRRRRRRRRRRRRRRR"<<endl;
                sleep(.5);
                while (insert_retry != 1) {
                    try {
                        dbc[month_collection].insert_one(document_builder.view());
                        insert_retry = 0;
                    } catch (const mongocxx::v_noabi::operation_exception& e) {
                        insert_retry--;
                        sleep(.5);
                    }
                }
            }
//            hour_table = "FWD_CALL_" + hour;
//            dbhr[hour_table].insert_one(document_builder.view());
            break;
        default:
            month_collection = string(ym) + "_DEFAULT";
            has_t = dbc.has_collection(month_collection);
            if (has_t == 0) {
                mutex_insert.lock();
                if (has_t = dbc.has_collection(month_collection) == 0) {
                    cout << "creating collection" << endl;
                    document_builder.clear();
                    index_builder.clear();
                    index_builder << "MSISDN" << 1;
                    dbc.create_collection(month_collection);
                    dbc[month_collection].create_index(index_builder.view());
                    index_builder.clear();
                    mutex_insert.unlock();
                } else {
                    mutex_insert.unlock();
                }
            }
            try {
                dbc[month_collection].insert_one(document_builder.view());
            } catch (const mongocxx::bulk_write_exception& e) {
                insert_retry = 1;
                cout << "CDR insert error, retrying" << endl;
            }
    }
    
    //std::chrono::steady_clock::time_point end_mongo = std::chrono::steady_clock::now();
    //std::cout << "Time difference mongo = " << std::chrono::duration_cast<std::chrono::microseconds>(end_mongo - begin_mongo).count()/1000 << "[ms]" << std::endl;
    //##########################################LAC insert##################################################
    //mongo LAC
    //    int update_flag = 0;
    //    if (lac_length == 5) {
    //        //      auto dbl = conn["LAC"];
    //        //     auto cursor = dbl.has_collection(LAC_COLLECTION);
    //        //       if (cursor == 0) {
    //        //            mutex_insert.lock();
    //        //            if (cursor = dbl.has_collection(LAC_COLLECTION) == 0) {
    //        //                cout << "creating collection" << endl;
    //        //               document_builder.clear();
    //        //               index_builder.clear();
    //        //               index_builder << "MSISDN" << 1;
    //        //               mongocxx::options::index index_options{};
    //        //               index_options.unique(true);
    //        //               document_builder << "MSISDN" << hold->MSISDN << "CELLID" << CELLID << "DATETIME" << DATETIME;
    //        //               dbl.create_collection(LAC_COLLECTION);
    //        //              dbl[LAC_COLLECTION].insert_one(document_builder.view());
    //        //              dbl[LAC_COLLECTION].create_index(index_builder.view(), index_options);
    //        //               index_builder.clear();
    //        //               index_builder << "CELLID" << 1;
    //        //               dbl[LAC_COLLECTION].create_index(index_builder.view());
    //        //              mutex_insert.unlock();
    //        //          } else {
    //        //              mutex_insert.unlock();
    //        //             update_flag = 1;
    //        //         }
    //        //      } else {
    //        //          update_flag = 1;
    //        //      }
    //        //
    //        //    if (update_flag == 1) {
    //        //           filter_builder.clear();
    //        //          update_builder.clear();
    //        //          filter_builder
    //        //                   << "MSISDN"
    //        //                   << hold->MSISDN
    //        //                  << "DATETIME"
    //        //                  << open_document
    //        //                  << "$lt"
    //        //                  << DATETIME
    //        //                  << close_document;
    //        //          update_builder
    //        //                  << "$set"
    //        //                  << open_document
    //        //                  << "MSISDN"
    //        //                  << hold->MSISDN
    //        //                 << "CELLID"
    //        //                 << CELLID
    //        //                 << "LONGITUDE" << cell_element.LON
    //        //                 << "LATITUDE" << cell_element.LAT
    //        //                << "BORE" << cell_element.BORE
    //        //                << "DATETIME"
    //        //               << DATETIME
    //        //              << close_document;
    //        //         try {
    //        //             dbl[LAC_COLLECTION].update_one(filter_builder.view(), update_builder.view(), update_options);
    //        //         } catch (const mongocxx::bulk_write_exception& e) {
    //        //         }
    //        //         //mutex_insert.unlock();
    //        //
    //        //      }
    //
    //        //commented for performance reasons
    //        //mysql LAC
    //        int my_insert_flag = 0;
    //        int tbl_stat;
    //        string tbl_chk = "SELECT count(*) FROM information_schema.TABLES WHERE (TABLE_SCHEMA = 'LAC') AND (TABLE_NAME = '" + LAC_COLLECTION + "')";
    //        tbl_stat = M.has_table(tbl_chk);
    //        if (tbl_stat == 1) {
    //            my_insert_flag = 1;
    //        } else if (tbl_stat == 0) {
    //            mutex_insert.lock();
    //            tbl_stat = M.has_table(tbl_chk);
    //            if (tbl_stat == 0) {
    //                string create_stmt = "create table " + LAC_COLLECTION + " like STRUCT;";
    //                M.query("LAC", create_stmt);
    //                my_insert_flag = 1;
    //                mutex_insert.unlock();
    //            } else {
    //                my_insert_flag = 1;
    //                mutex_insert.unlock();
    //            }
    //
    //        } else {
    //            cout << "ERROR AT MYSQL TABLE CHECK" << endl;
    //        }
    //
    //        if (my_insert_flag == 1) {
    //            string lac_query = "insert into " + LAC_COLLECTION + " (MSISDN,CELLID,LON,LAT,BORE,DATETIME) VALUES('" + hold->MSISDN + "','" + CELLID + "','" + cell_element.LON + "','" + cell_element.LAT + "','" + to_string(cell_element.BORE) + "','" + datetime + "') on duplicate key update MSISDN=IF('" + datetime + "'> VALUES(`DATETIME`),'" + hold->MSISDN + "',values(MSISDN)), CELLID=IF('" + datetime + "'> VALUES(`DATETIME`),'" + CELLID + "',values(CELLID)), LON=IF('" + datetime + "'> VALUES(`DATETIME`),'" + cell_element.LON + "',values(LON)), LAT=IF('" + datetime + "'> VALUES(`DATETIME`),'" + cell_element.LAT + "',values(LAT)), BORE=IF('" + datetime + "'> VALUES(`DATETIME`),'" + to_string(cell_element.BORE) + "',values(BORE)), DATETIME=IF('" + datetime + "'> VALUES(`DATETIME`),'" + datetime + "',values(DATETIME))";
    //            M.query("LAC", lac_query);
    //        } else {
    //            cout << "NOT INSERTED TO LAC TABLE" << endl;
    //        }
    //
    //    } else {
    //        cout << "LAC length mismatch: " << lac_length << " LAC: " << LAC << endl;
    //    }

    //##################################GEO insert##############################################
    //GEO mongo
//    auto dbgeo = conn["GEO"];
//    if ((!hold->MSISDN.empty())&&(loc_ret != -1)) {
//        //UNIQUE
//        filter_builder.clear();
//        update_builder.clear();
//        filter_builder
//                << "MSISDN"
//                << hold->MSISDN
//                << "DATETIME"
//                << open_document
//                << "$lt"
//                << DATETIME
//                << close_document;
//        update_builder
//                << "$set"
//                << open_document
//                << "MSISDN"
//                << hold->MSISDN
//                << "DATETIME"
//                << DATETIME
//                << "LOCATION" << open_array << atof(cell_element.LON.c_str()) << atof(cell_element.LAT.c_str()) << close_array
//                << "BORE" << cell_element.BORE
//                << close_document;
//        try {
//            dbgeo["MSISDN"].update_one(filter_builder.view(), update_builder.view(), update_options);
//        } catch (const mongocxx::bulk_write_exception& e) {
//            //cout<<e.what()<<endl;
//        }
//
//    } else {
//        //cout << "MSISDN EMPTY" << endl;
//    }

    //MSISDN mysql
    //std::chrono::steady_clock::time_point begin_mysql2 = std::chrono::steady_clock::now();
    //string msisdn_query = "insert into " + M_TBL + " (MSISDN,LAC,CELLID,LON,LAT,BORE,IMEI,`DATETIME`) values('" + hold->MSISDN + "','" + LAC + "','" + CELLID + "','" + cell_element.LON + "','" + cell_element.LAT + "','" + to_string(cell_element.BORE) + "','" + hold->IMEI + "','" + datetime + "') on duplicate key update LAC=IF('" + datetime + "'> VALUES(`DATETIME`),'" + LAC + "',values(LAC)),CELLID=IF('" + datetime + "'> VALUES(`DATETIME`),'" + CELLID + "',values(CELLID)), LON=IF('" + datetime + "'> VALUES(`DATETIME`),'" + cell_element.LON + "',values(LON)), LAT=IF('" + datetime + "'> VALUES(`DATETIME`),'" + cell_element.LAT + "',values(LAT)), BORE=IF('" + datetime + "'> VALUES(`DATETIME`),'" + to_string(cell_element.BORE) + "',values(BORE)),IMEI=IF('" + datetime + "'> VALUES(`DATETIME`),'" + hold->IMEI + "',values(IMEI)),`DATETIME`=IF('" + datetime + "'> VALUES(`DATETIME`),'" + datetime + "',values(`DATETIME`))";
    //M.query("MSISDN", msisdn_query);
    //std::chrono::steady_clock::time_point end_mysql2 = std::chrono::steady_clock::now();
    //std::cout << "Time difference mysql2 = " << std::chrono::duration_cast<std::chrono::microseconds>(end_mysql2 - begin_mysql2).count()/1000 << "[ms]" << std::endl;

    delete hold;
}

mongo::~mongo() {
}

