#include "lineProcess.h"

lineProcess::lineProcess(dataQueue& q, queue<string*>& lineq_i, Mutex& line_mutex_i, int i) : data(q), lineq(lineq_i), line_mutex(line_mutex_i), t_id(i) {

}

void* lineProcess::run() {
    boost::char_separator<char> sep("|", "", boost::keep_empty_tokens);
    //cout << "line thread" << t_id << " start" << endl;
    while (true) {
        tokenCount = 0;
        mark = 0;
        line_mutex.lock();
        if (!lineq.empty()) {
            line = lineq.front();
            lineq.pop();
            line_mutex.unlock();

            if (*line == "fin") {
                //cout << "line thread" << t_id << " end" << endl;
		delete line;
                return (0);
            } else {
                struct holder *hold = new holder;
                boost::tokenizer< boost::char_separator<char> > tokens(*line, sep);

                BOOST_FOREACH(string tok, tokens) {
                    switch (tokenCount) {
                        case 0:
                            hold->CallType=atoi(tok.c_str());
                            break;
                        case 1:
                            hold->MSISDN = tok;
                            break;
                        case 2:
                            hold->ANumber = tok;
                            break;
                        case 3:
                            hold->BNumber = tok;
                            break;
                        case 4:
                            hold->CNumber = tok;
                            break;
                        case 5:
                            hold->Date = tok;
                            break;
                        case 6:
                            hold->Time = tok;
                            break;
                        case 7:
                            hold->Duration = tok;
                            break;
                        case 8:
                            hold->ServiceCenter = tok;
                            break;
                        case 9:
                            hold->MSCID = tok;
                            break;
                        case 10:
                            hold->LAC = tok;
                            break;
                        case 11:
                            hold->CellID = tok;
                            break;
                        case 12:
                            hold->IMEI = tok;
                            break;
                        case 13:
                            hold->IMSI = tok;
                            break;
                        case 22:
                            hold->EventType = tok;
                            break;
                        default:
                            break;
                    }
                    tokenCount++;
                    if (tokenCount>22){
                        break;
                    }
                }
                delete line;
                data.addItem(hold);
            }
        } else {
            line_mutex.unlock();
            sleep(1);
        }
    }
}

lineProcess::~lineProcess(){

}
