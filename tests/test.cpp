#include "../graph/graph.h"
#include "../catch/catch.hpp"

TEST_CASE("The graph is able to load data from a tsv") {
    Graph g(true, true);
    g.loadData("tests/data/sample.tsv");
    REQUIRE( g.getVertices().size() != 0);
}

TEST_CASE("Djikstra algorithm returns the shortest path") {
    Graph g(true, true);
    g.loadData("tests/data/sample.tsv");
    list<Vertex> correctPath;
    correctPath.push_back("first");
    correctPath.push_back("third");

    REQUIRE(g.DjikstraPath("first", "third") == correctPath);
}
TEST_CASE("Another shortest path test with a diffrence sample") {
    Graph g(true, true);
    g.loadData("tests/data/sample2.tsv");
    list<Vertex> correctPath;
    correctPath.push_back("first");
    correctPath.push_back("second");
    correctPath.push_back("third");
    
    REQUIRE(g.DjikstraPath("first", "third") == correctPath);
}
TEST_CASE("Djikstra algorithm returns the shortest path - Second Check") {
    Graph g(true, true);
    g.loadData("tests/data/testcase2.tsv");
    list<Vertex> correctPath;
    correctPath.push_back("first");
    correctPath.push_back("third");

    REQUIRE(g.DjikstraPath("first", "third") == correctPath);
}
TEST_CASE("The landmark algorithm returns the shortest path while traveling through a landmark") {
    Graph g(true, true);
    g.loadData("tests/data/sample.tsv");
    list<Vertex> correctPath;
    correctPath.push_back("first");
    correctPath.push_back("second");
    correctPath.push_back("third");

    REQUIRE(g.LandmarkPath("first", "second" ,"third") == correctPath);
}

