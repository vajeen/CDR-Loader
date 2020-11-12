#include "readFile.h"
#include "lineProcess.h"

readFile::readFile(dataQueue& queue) : data(queue), configfile("/CDR/state") {

}

void* readFile::run() {
    //HU
    string DIRECTORY = "/CDR/HU/";
    string PREFIX = "HW";
    
    //ZTE
    //string DIRECTORY = "/CDR/ZTE/";
    //string PREFIX = "ZTE";
    
    
    int line_threads = 20;
    int thread_exists = 0;
    int was_inside=0;
    vector<string> file_list;
    string filename;
    string filename_bkp;
    string fname;

    string line;
    Mutex line_queue_mutex;
    queue<string*> *lineq = new queue<string*>;

    //initialize line process threads
    lineProcess * t_lineProcess[line_threads];

    int upper_lim = 1000000;
    int lower_lim = 300000;
    int lim_flag = 0;

    DIR *dir;
    struct dirent *ent;

    while (true) {
        Checkpoint(0);
        if ((dir = opendir(DIRECTORY.c_str())) != NULL) {
            Checkpoint(0);
            /* print all the files and directories within directory */
            while ((ent = readdir(dir)) != NULL) {
                if (string(ent->d_name).find(PREFIX) != string::npos) {
                    cout << "added file" << ent->d_name << endl;
                    file_list.push_back(ent->d_name);
                }
            }
            closedir(dir);
            while (file_list.size() != 0) {
                was_inside=1;
                //create reader threads if not exists
                fname = file_list.back();
                filename = DIRECTORY + fname;
                file_list.pop_back();
                if (thread_exists == 0) {
                    for (int i = 0; i < line_threads; i++) {
                        t_lineProcess[i] = new lineProcess(data, *lineq, line_queue_mutex, i);
                        t_lineProcess[i]->start();
                    }
                    thread_exists = 1;
                }

                cout << filename << endl;
                ifstream infile(filename, std::ifstream::in);
                //infile.rdbuf()->pubsetbuf(_buffer, BufferSize);
                while (std::getline(infile, line)) {
                    //cout<<"q size "<<lineq->size()<<endl;
                    string* line_p = new string(line);
                    //cout << *line_p << endl;
                    if ((lineq->size() < upper_lim) || (lim_flag == 1)) {
                        //cout<<"line"<<endl;
                        line_queue_mutex.lock();
                        lineq->push(line_p);
                        line_queue_mutex.unlock();
                    } else {
                        while (true) {
                            lim_flag = 1;
                            if (lineq->size() > lower_lim) {
                                usleep(10000);
                            } else {
                                lim_flag = 0;
                                break;
                            }
                        }
                        line_queue_mutex.lock();
                        lineq->push(line_p);
                        line_queue_mutex.unlock();
                    }
                }
                infile.close();
                cout << "Backup " << fname << endl;
                filename_bkp = "/CDR/BACKUP/" + fname;
                if (rename(filename.c_str(), filename_bkp.c_str())) {
                    while (1) {
                        cout << "Error backup " << fname << " " << filename << " " << filename_bkp << endl;
                        sleep(5);
                    }
                    if (errno == EXDEV) {
                        // copy data and meta data 
                    } else {
                        perror("rename");
                        exit(EXIT_FAILURE);
                    };
                }
                if (file_list.size() == 0) {
                    Checkpoint(1);
                    cout << "file list empty, recheck" << endl;
                    if ((dir = opendir(DIRECTORY.c_str())) != NULL) {
                        while ((ent = readdir(dir)) != NULL) {
                            if (string(ent->d_name).find(PREFIX) != string::npos) {
                                cout << "added file2 " << ent->d_name << endl;
                                file_list.push_back(ent->d_name);
                            }
                        }
                    } else {
                        /* could not open directory */
                        perror("");
                        cout << "reader sleeping" << endl;
                        sleep(10);
                        cout << "reader wakeup" << endl;
                    }
                    closedir(dir);
                }
            }
            Checkpoint(1);
            if (was_inside==1){
                cout << "file set done" << endl;
                was_inside=0;
            }
            file_list.shrink_to_fit();
            //closedir(dir);

            if (thread_exists == 1) {
                line_queue_mutex.lock();
                for (int i = 0; i < line_threads; i++) {
                    string* line_p = new string("fin");
                    lineq->push(line_p);
                }
                line_queue_mutex.unlock();

                cout << "joining line threads" << endl;
                for (int i = 0; i < line_threads; i++) {
                    cout<<i<<endl;
                    t_lineProcess[i]->join();
                }
                cout<<"done"<<endl;
                queue<string*>().swap(*lineq);

                data.setFin();

            }

            Checkpoint(0);
            thread_exists = 0;
            sleep(2);

        } else {
            /* could not open directory */
            perror("");
            cout << "reader sleeping" << endl;
            sleep(10);
            cout << "reader wakeup" << endl;
        }
    }

    delete lineq;

    data.setFin();
    return NULL;
}

void readFile::Checkpoint(int setFinflag) {
    ifstream infile(this->configfile, std::ifstream::in);
    while (true) {
        ifstream infile(this->configfile, std::ifstream::in);
        while (std::getline(infile, this->process_state)) {
            this->proc = atoi(this->process_state.c_str());
        }
        infile.close();
        if (this->proc == 1) {
            if (setFinflag == 1) {
                data.setFin();
                setFinflag = 0;
            }
            cout << "file read stopped" << endl;
            sleep(5);
        } else {
            break;
        }
    }
}

