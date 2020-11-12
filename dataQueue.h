#ifndef DATAQUEUE_H
#define	DATAQUEUE_H

#include <iostream>
#include <queue>
#include <string.h>
#include <pthread.h>
#include "Mutex.h"
#include "structs.h"
#include <vector>
#include <ctime>

using namespace std;
    
class dataQueue {
    Mutex &mutex_q1;
    Mutex &mutex_q2;
    Mutex &mutex_add;
public:
    void addItem(struct holder*);
    int getItem(vector<holder*>*&);
    void setFin();
    int getFin();
    dataQueue(Mutex& q1_mutex,Mutex& q2_mutex,Mutex& add_mutex);
    ~dataQueue();
private:
    static const int q_lim = 500;
    int chunk_count;
    int fin;
    int q1_num;
    int q2_num;
    int cur_queue;
    queue< vector<holder*>* > q1;
    queue< vector<holder*>* > q2;
    vector<holder*> *chunk;
};

#endif	/* DATAQUEUE_H */

