#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream titles;
    titles.open("soc-redditHyperlinks-title.tsv");
    titles.close();

    ifstream body;
    body.open("soc-redditHyperlinks-title.tsv");
    body.close();

    return 0;
}