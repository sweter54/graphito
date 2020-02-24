//
// Created by 21927 on 12.12.2019.
//

#ifndef GRAPITO_VERTEX_H
#define GRAPITO_VERTEX_H

#include <utility>
#include "graph.h"
#include "utils.h"


template <typename GenericType>
struct IsVertexType {
    static_assert(
            is_base_of_template_t<Vertex, GenericType>::value,
            "Provided Type must be subclass of Graph's Vertex type"
    );
    typedef typename GenericType::type type;
};


template <class T>
class Vertex {
public:
    typedef Vertex<T> type;
protected:
    friend class Graph<Vertex>;
    template <class ValueType>
    struct HashVertex {
        using VertexType = const Vertex<ValueType>&;
        inline std::size_t operator()(VertexType key) const {
            return std::hash<decltype(key.value)>{}(key.get_value());
        }
    };
    using VertexHash = HashVertex<T>;
private:
    T value;
public:
    Vertex(): value(T()){}
    explicit Vertex(T value): value(value){}
    Vertex(const Vertex& vertex): value(vertex.value) {}
    Vertex(Vertex&& vertex) noexcept : value(vertex.value) {}

    inline T get_value() const { return this->value; }
    inline void set_vertex(T value) { this->value = value; }
    inline friend bool operator ==(const Vertex& lhs, const Vertex& rhs) {
        return lhs.value == rhs.value;
    }
    inline friend bool operator<(const Vertex& lhs, const Vertex& rhs) {
        return lhs.value < rhs.value;
    }
    Vertex& operator=(Vertex const& rhs) {
        std::cout << "ASSIGNED VERTEX" << std::endl;
        if (this->value == rhs.value) {
            return *this;
        }
        else {
            this->value = rhs.value;
            return *this;
        }
    }
};


#endif //GRAPITO_VERTEX_H
