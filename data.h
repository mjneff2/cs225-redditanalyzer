
#pragma once
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class DataSet {
public:
    DataSet(string name);
    void print();
    
private:
    vector<string> lines;
};
