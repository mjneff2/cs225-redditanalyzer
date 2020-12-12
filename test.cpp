#include "graph.h"
#include "catch/catch.hpp"

TEST_CASE("The graph is able to load data from a tsv") {
    Graph g(true, true);
    g.loadData("sample.tsv");
    REQUIRE( g.getVertices().size() != 0);
}

TEST_CASE("Djikstra algorithm returns the shortest path") {
    Graph g(true, true);
    g.loadData("sample.tsv");
    list<Vertex> correctPath;
    correctPath.push_back("first");
    correctPath.push_back("third");

    REQUIRE(g.DjikstraPath("first", "third") == correctPath);
}