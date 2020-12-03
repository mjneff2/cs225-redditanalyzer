#include "data.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

DataSet::DataSet(string name) {
    ifstream file;
    file.open(name);
    char data[100];
    while(file >> data) {
        lines.push_back(data);
    }
    file.close();
}

void DataSet::print() {
    for (unsigned int i = 0; i < lines.size(); i++) {
        cout << lines[i] << endl;
    }
}