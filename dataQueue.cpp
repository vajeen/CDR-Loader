#include <unistd.h>

#include "dataQueue.h"

dataQueue::dataQueue(Mutex& q1_mutex, Mutex& q2_mutex, Mutex& add_mutex) :
mutex_q1(q1_mutex),
mutex_q2(q2_mutex),
mutex_add(add_mutex),
q1_num(0),
q2_num(0),
fin(1),
cur_queue(1),
chunk_count(0) {
}

dataQueue::~dataQueue() {
}

void dataQueue::addItem(struct holder *item) {
    mutex_add.lock();
    if (chunk_count == 0) {
        //cout << "new chunk" << endl;
        chunk = new vector<holder*>;
        //chunk->resize(500);
        chunk->push_back(item);
        chunk_count++;
        //cout << "new chunk done"<<endl;
    } else if (chunk_count < (100 - 1)) {
        chunk->push_back(item);
        chunk_count++;
    } else {
        chunk->push_back(item);
        chunk_count++;

        if ((q1_num == 0)&&(cur_queue == 1)) {
            q1_num++;
            cout << "Q1=" << q1_num << "+ | Q2=" << q2_num << " | CURQ=" << cur_queue << " | CHUNK=" << chunk_count << endl;
        } else if ((q2_num == 0)&&(cur_queue == 2)) {
            q2_num++;
            cout << "Q1=" << q1_num << " | Q2=" << q2_num << "+ | CURQ=" << cur_queue << " | CHUNK=" << chunk_count << endl;
        } else if ((cur_queue == 1)&&(q1_num < q_lim)) {
            q1_num++;
            cout << "Q1=" << q1_num << "+ | Q2=" << q2_num << " | CURQ=" << cur_queue << " | CHUNK=" << chunk_count << endl;
        } else if ((cur_queue == 2)&&(q2_num < q_lim)) {
            q2_num++;
            cout << "Q1=" << q1_num << " | Q2=" << q2_num << "+ | CURQ=" << cur_queue << " | CHUNK=" << chunk_count << endl;
        } else if ((cur_queue == 1)&&(q1_num == q_lim)) {
            while (!q2.empty()) {
                //cout << "waiting for Q2" << endl;
                usleep(50000);
            }
            cout << "switched to Q2" << endl;
            q2_num = 0;
            cur_queue = 2;
            cout << "Q1=" << q1_num << " | Q2=" << q2_num << " | CURQ=" << cur_queue << " | CHUNK=" << chunk_count << endl;
        } else if ((cur_queue == 2)&&(q2_num == q_lim)) {
            while (!q1.empty()) {
                //cout << "waiting for Q1" << endl;
                usleep(50000);
            }
            cout << "switched to Q1" << endl;
            q1_num = 0;
            cur_queue = 1;
            cout << "Q1=" << q1_num << " | Q2=" << q2_num << " | CURQ=" << cur_queue << " | CHUNK=" << chunk_count << endl;
        }

        if (cur_queue == 1) {
            //write to q1
            this->mutex_q1.lock();
            this->q1.push(chunk);
            this->mutex_q1.unlock();
        } else {
            //write to q2
            this->mutex_q2.lock();
            this->q2.push(chunk);
            this->mutex_q2.unlock();
        }
        chunk_count = 0;
    }
    mutex_add.unlock();
    //usleep(5000);
}

int dataQueue::getItem(vector<holder*>*& ret_p) {
    while (true) {
        if (this->fin == 1) {
            //cout <<"p11111"<<endl;
            if ((cur_queue == 1)&&(!this->q2.empty())) {
                //cout << "get from q2" << endl;
                this->mutex_q2.lock();
                ret_p = this->q2.front();
                this->q2.pop();
                this->mutex_q2.unlock();
                return (2);
            } else if ((cur_queue == 2)&&(!this->q1.empty())) {
                //cout << "get from q1" << endl;
                this->mutex_q1.lock();
                //cout<<"pp1"<<endl;
                ret_p = this->q1.front();
                //cout<<"pp2"<<endl;
                this->q1.pop();
                //cout<<"pp3"<<endl;
                this->mutex_q1.unlock();
                //cout<<"pp4"<<endl;
                return (1);
                //cout<<"pp5"<<endl;
            }
        } else {
            this->mutex_q1.lock();
            this->mutex_q2.lock();
            if (!this->q1.empty()) {
                //cout << "get from q1 fin" << endl;
                ret_p = this->q1.front();
                this->q1.pop();
                this->mutex_q1.unlock();
                this->mutex_q2.unlock();
                return (1);
            } else if (!this->q2.empty()) {
                //cout << "get from q2 fin" << endl;
                ret_p = this->q2.front();
                this->q2.pop();
                this->mutex_q1.unlock();
                this->mutex_q2.unlock();
                return (2);
            } else {
                if (this->fin == 0) {
                    cout << "Reset Queues" << endl;
                    this->mutex_add.unlock();
                    cout << "Reset Queues Q1=" << q1_num << " | Q2=" << q2_num << " | CURQ=" << cur_queue << " | CHUNK=" << chunk_count << endl;
                    this->q1_num = 0;
                    this->q2_num = 0;
                    this->fin = 1;
                    this->mutex_q1.unlock();
                    this->mutex_q2.unlock();
                    return (0);
                } else {
                    this->mutex_q1.unlock();
                    this->mutex_q2.unlock();
                }
            }
        }
        sleep(1);
    }
}

void dataQueue::setFin() {
    cout << "Flushing queues" << endl;
    this->mutex_add.lock();
    if (chunk_count != 0) {
        cout << chunk_count << "Pushing remaining chunk " << endl;
        //cout<<chunk->size()<<endl;
        if (cur_queue == 1) {
            //write to q1
            this->mutex_q1.lock();
            cout << "Pushing Q1" << endl;
            this->q1.push(this->chunk);
            this->mutex_q1.unlock();
        } else {
            //write to q2
            this->mutex_q2.lock();
            cout << "Pushing Q2" << endl;
            this->q2.push(this->chunk);
            this->mutex_q2.unlock();
        }
        chunk_count = 0;
    }
    //sleep(1);
    this->fin = 0;
}

int dataQueue::getFin() {
    return this->fin;
}
