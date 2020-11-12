#ifndef READFILE_H
#define	READFILE_H

#include <fstream>
#include <unistd.h>
#include <string.h>
#include <boost/tokenizer.hpp>
#include <boost/foreach.hpp>
#include <boost/iostreams/stream.hpp> 
#include <iostream>
#include <queue>
#include <vector>
#include "dataQueue.h"
#include "Thread.h"
#include "structs.h"
#include <algorithm>
#include <cstring>
#include <dirent.h>

class readFile : public Thread {
    dataQueue& data;

public:
    readFile(dataQueue&);
    void Checkpoint(int);
    void* run();

private:
    string process_state;
    int proc;
    string configfile;
};

#endif	/* READFILE_H */

