#include "../cs225/catch/catch.hpp"

#include "../graph.h"
#include "../edge.h"
#include "../NetworkFlow.h"

#include <iostream>
#include <ctime>

vector<unsigned> getRandomHelper(unsigned n, unsigned upper) {
    static bool flag = false; // only want to call srand once
    if (!flag) {
        srand(time(NULL));
        flag = true;
    }
    vector<unsigned> v;
    for (unsigned i = 0; i < n; i++) {
        v.push_back(rand() % upper);
    }
    return v;
}

void sanityCheckFlowGraph(Graph flow, unsigned capacity) {
    for (auto v1 : flow.getVertices()) {
        unsigned vertexOutflow = 0;
        for (auto v2 : flow.getAdjacent(v1)) {
            Edge e = flow.getEdge(v1, v2);
            vertexOutflow += e.getWeight();
        }
        REQUIRE( vertexOutflow <= capacity );
    }
} 

TEST_CASE("Graph a - 10 -> b  has flow of 10.", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",10);

  NetworkFlow n(g,"a","b");

  Graph f = n.calculateFlow();

  sanityCheckFlowGraph( n.getFlowGraph(), 10 );
  REQUIRE( n.getMaxFlow() == 10 );
}

TEST_CASE("Graph a - rand -> b  has flow of rand.", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  vector<unsigned> r = getRandomHelper(1,1000);
  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",r[0]);

  NetworkFlow n(g,"a","b");

  Graph f = n.calculateFlow();

  sanityCheckFlowGraph( n.getFlowGraph(), r[0] );
  REQUIRE( n.getMaxFlow() == r[0] );
}

TEST_CASE("Testing flow through two pipes", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",10);
  g.insertEdge("b","c");
  g.setEdgeWeight("b","c",5);
  g.insertEdge("a","c");
  g.setEdgeWeight("a","c",3);

  NetworkFlow n(g,"a","c");

  Graph f = n.calculateFlow();

  sanityCheckFlowGraph( n.getFlowGraph(), 8 );
  REQUIRE( n.getMaxFlow() == 8 );
}

TEST_CASE("Testing random flow through two pipes", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  vector<unsigned> r = getRandomHelper(3,1000);
  unsigned result = (r[0] < r[1]) ? r[0] + r[2] : r[1] + r[2];
  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",r[0]);
  g.insertEdge("b","c");
  g.setEdgeWeight("b","c",r[1]);
  g.insertEdge("a","c");
  g.setEdgeWeight("a","c",r[2]);

  NetworkFlow n(g,"a","c");

  Graph f = n.calculateFlow();

  sanityCheckFlowGraph( n.getFlowGraph(), result );
  REQUIRE( n.getMaxFlow() == result );
}

TEST_CASE("Testing simple backflow", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",10);
  g.insertEdge("a","c");
  g.setEdgeWeight("a","c",10);
  g.insertEdge("b","c");
  g.setEdgeWeight("b","c",5);
  g.insertEdge("b","d");
  g.setEdgeWeight("b","d",10);
  g.insertEdge("c","d");
  g.setEdgeWeight("c","d",10);

  NetworkFlow n(g,"a","d");

  Graph f = n.calculateFlow();

  sanityCheckFlowGraph( n.getFlowGraph(), 20 );
  REQUIRE( n.getMaxFlow() == 20 );
}

TEST_CASE("Testing random backflow", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  vector<unsigned> r = getRandomHelper(5, 1000);
  unsigned result = ((r[0] + r[1]) < (r[2] + r[3])) ? r[0] + r[1] : r[2] + r[3];

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",r[0]);
  g.insertEdge("a","c");
  g.setEdgeWeight("a","c",r[1]);
  g.insertEdge("b","c");
  g.setEdgeWeight("b","c",r[4]);
  g.insertEdge("b","d");
  g.setEdgeWeight("b","d",r[2]);
  g.insertEdge("c","d");
  g.setEdgeWeight("c","d",r[3]);

  NetworkFlow n(g,"a","d");

  Graph f = n.calculateFlow();

  sanityCheckFlowGraph( n.getFlowGraph(), result );
  REQUIRE( n.getMaxFlow() <= result );
}


TEST_CASE("Testing full pipe usage", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",9);
  g.insertEdge("a","d");
  g.setEdgeWeight("a","d",4);
  g.insertEdge("b","c");
  g.setEdgeWeight("b","c",8);
  g.insertEdge("c","d");
  g.setEdgeWeight("c","d",5);
  g.insertEdge("d","e");
  g.setEdgeWeight("d","e",7);
  g.insertEdge("c","f");
  g.setEdgeWeight("c","f",3);
  g.insertEdge("e","f");
  g.setEdgeWeight("e","f",8);

  NetworkFlow n(g,"a","f");

  Graph f = n.calculateFlow();

  sanityCheckFlowGraph( n.getFlowGraph(), 10 );
  REQUIRE( n.getMaxFlow() == 10 );
}

TEST_CASE("Testing 3 x 3 plumbing", "[valgrind][weight=1]") {
  Graph g = Graph(true,true);

  g.insertEdge("a","b");
  g.setEdgeWeight("a","b",4);
  g.insertEdge("b","c");
  g.setEdgeWeight("b","c",5);

  g.insertEdge("d","e");
  g.setEdgeWeight("d","e",3);
  g.insertEdge("e","f");
  g.setEdgeWeight("e","f",5);

  g.insertEdge("g","h");
  g.setEdgeWeight("g","h",1);
  g.insertEdge("h","i");
  g.setEdgeWeight("h","i",5);

  g.insertEdge("a","d");
  g.setEdgeWeight("a","d",8);
  g.insertEdge("b","e");
  g.setEdgeWeight("b","e",5);
  g.insertEdge("c","f");
  g.setEdgeWeight("c","f",3);

  g.insertEdge("d","g");
  g.setEdgeWeight("d","g",4);
  g.insertEdge("e","h");
  g.setEdgeWeight("e","h",11);
  g.insertEdge("f","i");
  g.setEdgeWeight("f","i",7);

  NetworkFlow n(g,"a","i");

  Graph f = n.calculateFlow();

  sanityCheckFlowGraph( n.getFlowGraph(), 8 );
  REQUIRE( n.getMaxFlow() == 8 );
}
