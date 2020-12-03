
#pragma once
#include <fstream>
#include <string>

using namespace std;

class DataSet {
public:
    DataSet(string name);
    void print();
    
private:
    char data[100];
};