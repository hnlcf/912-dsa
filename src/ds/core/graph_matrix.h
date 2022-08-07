#ifndef INC_912_DSA_DS_GRAPH_MATRIX_H_
#define INC_912_DSA_DS_GRAPH_MATRIX_H_

#include <ds/utils/autoheader.h>
#include <ds/core/graph.h>
#include <ds/core/vector.h>

namespace dsa {
template <class T>
struct Vertex {
  T         m_data;
  int64_t   m_inDegree;   // Number of other vertices it points to
  int64_t   m_outDegree;  // Number of other vertices it is pointed to

  /* The following fields serve the Graph Traversal Algorithms */
  VertexStatus m_status;
  int64_t      m_dTime;     // Moment the getVertex was found
  int64_t      m_fTime;     // Moment when the getVertex has been visited
  size_type    m_parent;    // getParent getVertex in traversal tree
  int64_t      m_priority;  // getPriority in traversal tree of algorithms based
                            // getPriority

  explicit Vertex(T const& d)
      : m_data(d),
        m_inDegree(0),
        m_outDegree(0),
        m_status(VertexStatus::Undiscovered),
        m_dTime(-1),
        m_fTime(-1),
        m_parent(-1),
        m_priority(INT64_MAX) {}
};

template <class ValueType>
struct Edge {
  ValueType  m_data;
  int64_t    m_weight;
  EdgeStatus m_status;

  Edge(ValueType const& d, int64_t w)
      : m_data(d), m_weight(w), m_status(EdgeStatus::Undetermined) {}
};

template <class VertexType, class EdgeType>
class GraphMatrix : public Graph<VertexType, EdgeType> {
 private:
  Vector<Vertex<VertexType>>      m_vertices;  // getVertex set
  Vector<Vector<Edge<EdgeType>*>> m_edges;     // getEdge set

 public:
  GraphMatrix() {
    this->m_numVertex = 0;
    this->m_numEdge   = 0;
  }

  ~GraphMatrix() {
    for (size_type i = 0; i < this->m_numVertex; ++i) {
      for (size_type j = 0; j < this->m_numEdge; ++j) {
        delete m_edges[i][j];
      }
    }
  }

  /// @brief
  size_type insertVertex(const VertexType& v) override {
    // append a column for original matrix
    for (size_type i = 0; i < this->m_numVertex; ++i) {
      m_edges[i].PushBack(nullptr);
    }
    this->m_numVertex++;
    // construct a row and append it to new matrix
    m_edges.pushBack(
        Vector<Edge<EdgeType>*>(this->m_numVertex, this->m_numVertex, nullptr));

    m_vertices.pushBack(Vertex<VertexType>(v));
    return this->m_numVertex - 1;
  }

  /// @brief
  VertexType removeVertex(size_type v) override {
    // delete all out-degree edges
    for (size_type i = 0; i < this->m_numVertex; ++i) {
      if (existsEdge(v, i)) {
        delete m_edges[v][i];
        m_vertices[i].m_inDegree--;
      }
    }
    // delete the `v` row
    m_edges.remove(v);
    this->m_numVertex--;

    // delete all in-degree edges and the `v` column
    for (size_type i = 0; i < this->m_numVertex; ++i) {
      if (existsEdge(i, v)) {
        delete m_edges[i].remove(v);
        m_vertices[i].m_outDegree--;
      }
    }
    // store data of vertex
    auto ans = getVertex(v);

    // delete the vertex `v`
    m_vertices.remove(v);

    return ans;
  }

  /// @brief
  VertexType& getVertex(size_type v) override { return m_vertices[v].m_data; }

  /// @brief
  int64_t getInDegree(size_type v) override { return m_vertices[v].m_inDegree; }

  /// @brief
  int64_t getOutDegree(size_type v) override {
    return m_vertices[v].m_outDegree;
  }

  /// @brief
  VertexStatus& getVertexStatus(size_type v) override {
    return m_vertices[v].m_status;
  }

  /// @brief
  int64_t& getDTime(size_type v) override { return m_vertices[v].m_dTime; }

  /// @brief
  int64_t& getFTime(size_type v) override { return m_vertices[v].m_fTime; }

  /// @brief
  size_type& getParent(size_type v) override { return m_vertices[v].m_parent; }

  /// @brief
  int64_t& getPriority(size_type v) override {
    return m_vertices[v].m_priority;
  }

  /// @brief
  size_type firstNeighbor(size_type v) override {
    return nextNeighbor(v, this->m_numVertex);
  }

  /// @brief
  size_type nextNeighbor(size_type v, size_type i) override {
    i -= 1;
    while ((i > -1) && (!Graph<VertexType, EdgeType>::existsEdge(v, i))) {
      i--;
    }
    return i;
  }

  /// @brief
  bool existsEdge(size_type u, size_type v) override {
    return (0 <= u) && (u < this->m_numVertex) && (0 <= v) &&
           (v < this->m_numVertex) && (m_edges[u][v] != nullptr);
  }

  /// @brief
  void insertEdge(const EdgeType& e, int64_t w, size_type u,
                  size_type v) override {
    if (existsEdge(u, v)) {
      return;
    }
    m_edges[u][v] = new Edge<EdgeType>(e, w);

    // update edges' number
    this->m_numEdge++;
    // update in-degree/out-degree of `v` / `u`
    m_vertices[u].m_outDegree++;
    m_vertices[v].m_inDegree++;
  }

  /// @brief
  EdgeType removeEdge(size_type u, size_type v) override {
    auto ans = getEdge(u, v);
    delete m_edges[u][v];
    m_edges[u][v] = nullptr;

    this->m_numEdge--;
    m_vertices[u].m_outDegree--;
    m_vertices[v].m_inDegree--;
    return ans;
  }

  /// @brief
  EdgeStatus& getEdgeStatus(size_type u, size_type v) override {
    return m_edges[u][v]->m_status;
  }

  /// @brief
  EdgeType& getEdge(size_type u, size_type v) override {
    return m_edges[u][v]->m_data;
  }

  /// @brief
  int64_t& getWeight(size_type u, size_type v) override {
    return m_edges[u][v]->m_weight;
  }
};
}  // namespace dsa

#endif
