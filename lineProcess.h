#ifndef LINEPROCESS_H
#define	LINEPROCESS_H

#include <fstream>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>
#include <queue>
#include "dataQueue.h"
#include "Thread.h"
#include "structs.h"
#include <algorithm>
#include <cstring>

using namespace std;

class lineProcess : public Thread
{
    dataQueue& data;
    queue<string*>& lineq;
    Mutex& line_mutex;
    string *line;
    int tokenCount = 0;
    int mark = 0;
    int t_id;
 
  public:
    lineProcess(dataQueue&,queue<string*>&,Mutex&,int);
    void* run();
    virtual ~lineProcess();
};

#endif	/* LINEPROCESS_H */

