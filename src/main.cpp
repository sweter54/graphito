#include <iostream>
#include "edge.h"
#include "vertex.h"
#include "graph.h"
#include "listed_graph.h"

using IntVertex = Vertex<int>;
using IntEdgeIntVertex = Edge<int, Vertex<int>>;
using ListedIntToIntG = ListedGraph<IntVertex, IntEdgeIntVertex>;
using IndexIndexWeight = typename ListedIntToIntG::EdgeWTIITuple;

int main() {
    Vertex<int> a = Vertex<int>(5);
    Vertex<int> b = Vertex<int>(5);
    Vertex<int> c = a;
    Edge<int, Vertex<int>> e = Edge<int, Vertex<int>>(5, a, b);
    std::cout << e << std::endl;
    std::vector<Vertex<int>> x = {Vertex<int>(1), Vertex<int>(12), Vertex<int>(55)};

    auto test_graph = Graph<Vertex<int>>({Vertex<int>(1), Vertex<int>(12), Vertex<int>(55)});
    Vertex<int>& second = test_graph.get_vertex(1);
    std::cout << "Second has: " << second.get_value() << std::endl;
    second.set_vertex(1200);
    std::cout << "SECOND VERTEX IN GRAPHS VECTOR IS: " << test_graph.get_vertex(1).get_value() << std::endl;

    ListedIntToIntG test_listed_from_init_list = ListedIntToIntG(
            {IntVertex(15), IntVertex(21), IntVertex(37), IntVertex(49), IntVertex(54)},
            {IndexIndexWeight()}
    );
    return 0;
}
