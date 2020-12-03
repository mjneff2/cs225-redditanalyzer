#include "data.h"
#include <fstream>
#include <iostream>

DataSet::DataSet(string name) {
    ifstream file;
    file.open(name);
    while(file >> data) {
        cout << data << endl;
    }
}

void DataSet::print() {
    cout << data << endl;
}