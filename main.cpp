#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <unordered_set>
#include <queue>
#include "data.h"
#include "graph.h"

using namespace std;

void bfs(const Graph& g, const Vertex& start);

int main() {
    /*DataSet titles = DataSet("small_sample.tsv");
    titles.print();
    return 0;*/
    Graph g(false, true);
    Vertex start = "";
    std::ifstream infile("soc-redditHyperlinks-title.tsv");
    std::string line;
    std::getline(infile, line); // Get rid of first line
    while (std::getline(infile, line)) {
        std::istringstream buffer(line);
        std::vector<std::string> results((std::istream_iterator<std::string>(buffer)), // Parse string into vector separated by spaces
                                 std::istream_iterator<std::string>());
        if (start == "") {
            start = results[0];
        }
        if (!g.vertexExists(results[0])) {
            g.insertVertex(results[0]); // Insert source vertex if it doesn't exist
        }
        if (!g.vertexExists(results[1])) {
            g.insertVertex(results[1]); // Insert destination vertex if it doesn't exists
        }
        g.insertEdge(results[0], results[1]); // Insert edge from that line
    }
    bfs(g, start);
}

void bfs(const Graph& g, const Vertex& start) {
    std::unordered_set<std::string> traversed;
    std::queue<std::string> queue;
    queue.push(start);
    while (!queue.empty()) {
        std::string current = queue.front();
        std::cout << current << std::endl;
        traversed.insert(current);
        queue.pop();

        for (std::string neighbor : g.getAdjacent(current)) {
            if (traversed.find(neighbor) == traversed.end()) {
                queue.push(neighbor);
                traversed.insert(neighbor);
            }
        }
    }
}