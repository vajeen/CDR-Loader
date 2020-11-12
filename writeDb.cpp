#include "writeDb.h"
#include "dataQueue.h"
#include "loadsummary.h"
#include "mongo.h"
#include <chrono>
//#include "aero.h"

writeDb::writeDb(dataQueue& queue, int id, Mutex& insert_mutex, getCell& cell, loadsummary& loadsum) : 
data(queue), tid(id), mutex_insert(insert_mutex), cellmap(cell), l_sum(loadsum) {
}

void* writeDb::run() {
    cout << "writer thread" << tid << " start" << endl;
    int fin = 0;
    //aero a;
    //mongo M;
    vector<holder*> *chunk;
    int chunk_size = 0;
    int q_flag = 0;
    struct holder *item;
    //mysql_loader *MY = new mysql_loader(driver);
    //mongo *M = new mongo(tid,mutex_insert,*MY);

    while (true) {
        //cout<<"ppppppppqqqqqqqp1"<<endl;

        
        q_flag = data.getItem(chunk);
        //cout<<"blabla"<<endl;
        std::chrono::steady_clock::time_point begin_mongo = std::chrono::steady_clock::now();
        if (q_flag != 0) {
            //cout<<"xp2"<<endl;
            //cout<<"xp1"<<endl;
            //mysql_loader *MY = new mysql_loader(driver);
            mongo *M = new mongo(mutex_insert, cellmap, l_sum);
            //cout<<"xp2"<<endl;
            chunk_size = chunk->size();
            //cout << "thread " << tid << " processing chunk" << endl;
            //cout<<"thread "<<tid<<" chunk_size "<<chunk_size<<endl;
            for (int i = 0; i < chunk_size; i++) {
                item = chunk->at(i);
                //cout << "mob "<<item->MSISDN << "time "<<item->Time << "date "<<item->IMEI << endl;
                M->insert(item);
                //cout<<"inserted"<<endl;
            }
            //cout << "writer thread" << tid << " finished" << endl;
            //M->finish();
            std::chrono::steady_clock::time_point end_mongo = std::chrono::steady_clock::now();
            //std::cout << "Time difference mongo = " << std::chrono::duration_cast<std::chrono::microseconds>(end_mongo - begin_mongo).count()/1000 << "[ms]" << std::endl;
            cout<<"thread "<<tid<<" time: "<< std::chrono::duration_cast<std::chrono::microseconds>(end_mongo - begin_mongo).count()/1000000 << "[s]" <<endl;
            //cout<<"pp1"<<endl;
            delete chunk;
            //cout<<"pp2"<<endl;
            delete M;
            //cout<<"pp3"<<endl;
            //        delete MY;
            //cout<<"pp4"<<endl;
            //cout<<"thread "<<tid<<" deleted"<<endl;
        } else {
            sleep(1);
        }
    }
    //cout << "thread " << tid << " exit" << endl;
    //return NULL;
}

