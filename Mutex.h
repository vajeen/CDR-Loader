#ifndef MUTEX_H
#define	MUTEX_H

#include <pthread.h>
class Mutex
{
    pthread_mutex_t  m_mutex;
    pthread_cond_t cond;
 
  public:
    // just initialize to defaults
    Mutex();
    virtual ~Mutex();
 
    int lock();
    int trylock();
    int unlock();
    int wait();
    int signal_all();
};

#endif	/* MUTEX_H */

