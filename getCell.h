#ifndef GETCELL_H
#define GETCELL_H

#include "structs.h"
#include <string>
#include <map>
#include "Thread.h"
#include "mysql_loader.h"
#include <unistd.h>

using namespace std;

class getCell : public Thread {
public:
    getCell();
    void setStatus(int);
    int getStatus();
    void setCurrent(int);
    int getCurrent();
    int getData(string, struct cellElement&);
    void* run();
    virtual ~getCell();
private:
    map <string, struct cellElement> map1;
    map <string, struct cellElement> map2;
    map <string, struct cellElement> map14g;
    map <string, struct cellElement> map24g;
    int current_map;
    int status;
    int refresh_rate = 15 * 60; //in seconds

};

#endif /* GETCELL_H */

