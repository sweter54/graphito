//
// Created by 21927 on 12.12.2019.
//

#ifndef GRAPITO_GRAPH_H
#define GRAPITO_GRAPH_H

#include "edge.h"
#include "vertex.h"
#include <vector>
//#include <unordered_map> TODO implement hash struct for vertex type
#include <exception>
#include <string>
#include <iterator>
#include <utility>
#include <vector>
#include <initializer_list>
#include <functional>
#include <unordered_map>
#include <initializer_list>
#include "utils.h"
#include "vertex.h"


template <typename V_Type>
class Graph {
protected:
    typedef std::reference_wrapper<V_Type> VertexRefWrap;
    typedef typename V_Type::VertexHash VertexHasher;
    typedef std::unordered_map<VertexRefWrap, std::size_t, VertexHasher> VerticesMap;
    typedef std::vector<V_Type> VerticesVec;
    VerticesVec vertices;
    VerticesMap index_of_vertex;

    void _map_vertices_to_index() {
        std::size_t size = 0;

        for (V_Type& vertex: this->vertices)
        {
            this->index_of_vertex[std::ref(this->vertices[size])] = size;
            size = size + 1;
        }
    }
public:
    V_Type& get_vertex(int index) {
        return this->vertices.at(index);
    }
    std::size_t get_index(const V_Type& vertex) const {
        return this->index_of_vertex[vertex];
    }
    template <class V_Value>
    void set_vertex(V_Type vertex, V_Value value) {
        std::size_t index = this->index_of_vertex[vertex];
        this->vertices[index] = value;
    }
    template <class V_Value>
    void set_vertex(std::size_t index, V_Value value) {
        this->index_of_vertex[index] = value;
        V_Type& in_vertices = this->index_of_vertex.find();
    }
    virtual void append_vertex(V_Type vertex) {
        this->vertices.emplace_back(vertex);
        this->_map_vertices_to_index();
    }
    virtual V_Type pop_vertex() {
        V_Type& last = this->vertices.back();
        this->vertices.pop_back();
        this->index_of_vertex.erase(std::ref(last));

        return last;
    }


    Graph() {
        this->vertices = VerticesVec();
        this->index_of_vertex = VerticesMap();
    }

    Graph(const Graph& rhs){
        this->vertices = VerticesVec(rhs.vertices);
        this->_map_vertices_to_index();
    }
    Graph(Graph&& rhs) noexcept : _vertices_count_(rhs._vertices_count_) {
        this->vertices = std::move(rhs.vertices);
        this->_map_vertices_to_index();
    }
    Graph(const std::initializer_list<V_Type>& vertices) {
        this->vertices = VerticesVec(vertices);
        this->_map_vertices_to_index();
    }
    virtual ~Graph(){}

    Graph& operator=(const Graph& rhs) {
        if(this != &rhs) {
            this->vertices = std::move(rhs.vertices);
            this->index_of_vertex = std::move(rhs.index_of_vertex);
            return *this;
        }
        return *this;
    }
};

#endif //GRAPITO_GRAPH_H
