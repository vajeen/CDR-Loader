#include "getCell.h"

getCell::getCell() : current_map(1), status(-1) {
}

void* getCell::run() {
    cout << "Loading cell data into memory(1)" << endl;
    mysql_loader *M = new mysql_loader();
    M->getCelldata(map1,map14g);
    cout << "Cell data loaded into memory(1)" << endl;
    delete M;
    setStatus(0);
    sleep(refresh_rate);

    while (true) {
        if (getCurrent() == 1) {
            cout << "Loading cell data into memory(2)" << endl;
            map2.clear();
            map24g.clear();
            mysql_loader *M = new mysql_loader();
            M->getCelldata(map2,map24g);
            delete M;
            cout << "Cell data loaded into memory(2)" << endl;
            setCurrent(2);
            cout << "Cell data memory swapped" << endl;
        } else if (getCurrent() == 2) {
            cout << "Loading cell data into memory(1)" << endl;
            map1.clear();
            map14g.clear();
            mysql_loader *M = new mysql_loader();
            M->getCelldata(map1,map14g);
            delete M;
            cout << "Cell data loaded into memory(1)" << endl;
            setCurrent(1);
            cout << "Cell data memory swapped" << endl;
        }
        sleep(refresh_rate);
    }
}

int getCell::getData(string ci, struct cellElement& element) {
    if (ci != "0000000000") {
        if (getCurrent() == 1) {
            if (map1.find(ci) == map1.end()) {
                //cout << "Cell data not found CI=" << ci << endl;
                element.BORE = 0;
                element.LAT = "0";
                element.LON = "0";
                return (-1);
            } else {
                element = map1[ci];
                return (0);
            }
        } else {
            if (map2.find(ci) == map2.end()) {
                //cout << "Cell data not found CI=" << ci << endl;
                element.BORE = 0;
                element.LAT = "0";
                element.LON = "0";
                return (-1);
            } else {
                element = map2[ci];
                return (0);
            }
        }
    } else {
        return -1;
    }
}

void getCell::setStatus(int s) {
    this->status = s;
}

int getCell::getStatus() {
    return this->status;
}

void getCell::setCurrent(int s) {
    this->current_map = s;
}

int getCell::getCurrent() {
    return this->current_map;
}

getCell::~getCell() {
}

