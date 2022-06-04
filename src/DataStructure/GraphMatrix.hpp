#pragma once

#include "AutoHeader.hpp"
#include "Graph.hpp"
#include "Vector.hpp"

namespace dsa {
    template<class V>
    struct Vertex {
        V       m_data;
        int64_t m_inDegree;   // Number of other vertices it points to
        int64_t m_outDegree;  // Number of other vertices it is pointed to

        /* The following fields serve the Graph Traversal Algorithms */
        VertexStatus m_status;
        int64_t      m_dTime;     // Moment the vertex was found
        int64_t      m_fTime;     // Moment when the vertex has been visited
        size_type    m_parent;    // Parent vertex in traversal tree
        int64_t      m_priority;  // Priority in traversal tree of algorithms based priority

        explicit Vertex(V const &d)
          : m_data(d), m_inDegree(0), m_outDegree(0), m_status(VertexStatus::Undiscovered),
            m_dTime(-1), m_fTime(-1), m_parent(-1), m_priority(INT64_MAX) {
        }
    };

    template<class E>
    struct Edge {
        E          m_data;
        int64_t    m_weight;
        EdgeStatus m_status;

        Edge(E const &d, int64_t w) : m_data(d), m_weight(w), m_status(EdgeStatus::Undetermined) {
        }
    };
}
