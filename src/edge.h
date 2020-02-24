//
// Created by Meitner on 12.12.2019.
//

#ifndef GRAPITO_EDGE_H
#define GRAPITO_EDGE_H

#include <exception>
#include <list>
#include <tuple>
#include "vertex.h"


template <typename WeightType, typename Vertex>
class Edge: Where<Vertex, IsVertexType> {
public:
    typedef Edge<WeightType, Vertex> type;
    typedef typename Where<Vertex, IsVertexType>::type VertexType;
    typedef std::pair<VertexType&, VertexType&> VerticesPair;
    typedef WeightType WeightType;
private:
    WeightType value;
    VertexType first;
    VertexType second;
public:
    Edge() = delete;
    explicit Edge(WeightType value, VertexType& vertex1, VertexType& vertex2) {
        this->value = value;
        this->first = VertexType(vertex1);
        this->second = VertexType(vertex2);
    }
    explicit Edge(WeightType value, std::tuple<VertexType&, VertexType&>& vertices) {
        this->value = value;
        this->first = std::get<0>(vertices);
        this->second = std::get<1>(vertices);
    }
    VerticesPair vertices() {
        return VerticesPair(this->first, this->second);
    }
    VertexType& get_vertex(const VertexType& vertex) {
        if(this->first == vertex)
            return this->first;
        else if (this->second == vertex)
            return this->second;
    }
    const WeightType& get_value() const {
        return this->value;
    }
    bool operator==(const Edge& rhs) {
        return rhs.value == this->value;
    }
    inline friend std::ostream& operator<<(std::ostream& out_stream, const Edge& rhs) noexcept {
        return out_stream << "< Edge: " << &rhs << "(value:," << rhs.value
                          << ", " << &(rhs.first) << ", " << &(rhs.second) << " )>";
    }
};

#endif //GRAPITO_EDGE_H
