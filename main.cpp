#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <unordered_set>
#include <queue>
#include "data.h"
#include "graph.h"

using namespace std;

int main() {
    Graph g(false, true);
    g.loadData("soc-redditHyperlinks-title.tsv");
    g.BFS();
}