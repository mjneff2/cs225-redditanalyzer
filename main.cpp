#include <iostream>
#include <fstream>
#include <string>
#include "data.h"

using namespace std;

int main() {
    DataSet titles = DataSet("small_sample.tsv");
    titles.print();
    return 0;
}