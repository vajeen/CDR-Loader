#ifndef READQUEUE_H
#define	READQUEUE_H

#include <iostream>
#include <string.h>
#include <queue>
#include "structs.h"
#include "Mutex.h"

using namespace std;

class readQueue {
    Mutex &mutex_read;
public:
    void addItem(string *);
    void getItem();
    readQueue(Mutex& read_mutex);
    virtual ~readQueue();
private:
    queue <string*> lineq;
};

#endif	/* READQUEUE_H */

