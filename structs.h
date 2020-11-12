#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>

struct holder {
    int CallType;
    std::string MSISDN;
    std::string ANumber;
    std::string BNumber;
    std::string CNumber;
    std::string Date;
    std::string Time;
    std::string Duration;
    std::string ServiceCenter;
    std::string MSCID;
    std::string LAC;
    std::string CellID;
    std::string IMEI;
    std::string IMSI;
    std::string EventType;
};

struct cellElement {
    std::string CL;
    std::string LON;
    std::string LAT;
    int BORE;
};

#endif /* STRUCTS_H */
