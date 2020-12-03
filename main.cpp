#include <iostream>
#include <fstream>
#include <string>
#include "data.h"

using namespace std;

int main() {
    

    ifstream body;
    body.open("soc-redditHyperlinks-body.tsv");
    body.close();

    DataSet titles = DataSet("soc-redditHyperlinks-title.tsv");
    titles.print();
    return 0;
}