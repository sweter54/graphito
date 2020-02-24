//
// Created by 21927 on 12.01.2020.
//

#ifndef GRAPITO_LISTED_GRAPH_H
#define GRAPITO_LISTED_GRAPH_H

#include "graph.h"
#include <list>
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <tuple>
#include "utils.h"

template < class Weight>
using EdgeWeightToIndex = std::tuple<int, int, Weight>;


template <class EdgeType>
struct IsEdgeType{
    static_assert(
        is_base_of_template_t<Edge, EdgeType>::value,
        "Given Type must inherit from Edge type"
    );
    typedef typename EdgeType::type type;
    typedef typename EdgeType::WeightType WeightType;
};


template <class V_Type, class E_Type>
class ListedGraph: Where<E_Type, IsEdgeType>, Graph<V_Type> {
public:
    typedef typename E_Type::type type;
    typedef typename E_Type::WeightType WeightType;
    typedef EdgeWeightToIndex<WeightType> EdgeWTIITuple;    // TODO please change this names
protected:
    typedef std::list<E_Type> EdgesList;
    std::vector<EdgesList> vertices_edge_lists;

    std::vector<EdgesList> initialize_adjacency_lists(){
        return std::vector<EdgesList>(this->vertices.size());
    }
    bool insert_edge(std::size_t vertex_index, const E_Type& edge) {
        EdgesList& target = this->vertices_edge_lists[vertex_index];
        auto found = std::find(target.begin(), target.end(), edge);
        if(found != target.end()) {
            return false;
        }
        target.push_back(edge);
        return true;
    }
public:
    void add_edge_to_vertex(const WeightType& weight, std::size_t index_from, std::size_t index_to)
    {
        V_Type& first = this->get_vertex(index_from);
        V_Type second = this->get_vertex(index_to);
        E_Type edge = E_Type(weight, first, second);

        this->insert_edge(index_from, edge);
        this->insert_edge(index_to, edge);
    }

    E_Type& get_edge(int vertex_index, int edge_index) {
        EdgesList& vertices_edges = this->vertices_edge_lists[vertex_index];
        return vertices_edges[edge_index];
    }

    EdgesList const& get_edges_list(int vertex_index) {
        return this->vertices_edge_lists[vertex_index];
    }

    ListedGraph(
            const std::initializer_list<V_Type>& vertices,
            const std::initializer_list<EdgeWTIITuple>& edges
    ): Graph(std::move(vertices)) {
        this->vertices_edge_lists = std::vector<EdgesList>(this->vertices.size());
        for(const EdgeWTIITuple& edge: edges)
        {
            int first_vertex_index, second_vertex_index;
            WeightType weight;
            std::tie(first_vertex_index, second_vertex_index, weight) = edge;
            this->add_edge_to_vertex(weight, first_vertex_index, second_vertex_index);
            this->add_edge_to_vertex(weight, second_vertex_index, first_vertex_index);
        }
    }
};

#endif //GRAPITO_LISTED_GRAPH_H
