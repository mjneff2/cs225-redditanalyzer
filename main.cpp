#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <unordered_set>
#include <queue>
#include "data.h"
#include "graph.h"

using namespace std;

int main(int argc, char *argv[]) {
    Graph g(true, true);
    if (argc == 2) {
        ifstream f(argv[1]);
        if (f.good()) {
            string header;
            getline(f, header);
            if (header.find("SOURCE_SUBREDDIT") == string::npos || header.find("TARGET_SUBREDDIT") == string::npos) {
                cout << "File is not a valid dataset." << endl;
                return -1;
            }
            cout << "Parsing dataset..." << endl;
            g.loadData(argv[1]);
        } else {
            cout << "File does not exist." << endl;
            return -1;
        }
    } else {
        cout << "Arguments should only be one filename." << endl;
        return -1;
    }
    while (true) {
        cout << "Select algorithm (\"bfs\", \"djikstra\", \"landmark\") or \"end\" to end: ";
        string choice;
        cin >> choice;
        if (choice == "bfs") {
            g.BFS();
        } else if (choice == "djikstra") {
            string start, end;
            cout << "Enter start: ";
            cin >> start;
            cout << "Enter end: ";
            cin >> end;
            g.Djikstra(start, end);
        } else if (choice == "landmark") {
            string start, end, landmark;
            cout << "Enter start: ";
            cin >> start;
            cout << "Enter end: ";
            cin >> end;
            cout << "Enter landmark: ";
            cin >> landmark;
            g.Landmark(start, landmark, end);
        } else if (choice == "end") {
            return 0;
        } else {
            cout << "Invalid choice." << endl;
        }
    }
}