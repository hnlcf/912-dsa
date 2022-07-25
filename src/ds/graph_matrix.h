#ifndef INC_912_DSA_DS_GRAPH_MATRIX_H_
#define INC_912_DSA_DS_GRAPH_MATRIX_H_

#include "autoheader.h"
#include "graph.h"
#include "vector.h"

namespace dsa {
template <class V>
struct Vertex {
  V m_data;
  int64_t m_inDegree;   // Number of other vertices it points to
  int64_t m_outDegree;  // Number of other vertices it is pointed to

  /* The following fields serve the Graph Traversal Algorithms */
  VertexStatus m_status;
  int64_t m_dTime;     // Moment the GetVertex was found
  int64_t m_fTime;     // Moment when the GetVertex has been visited
  size_type m_parent;  // GetParent GetVertex in traversal tree
  int64_t m_priority;  // GetPriority in traversal tree of algorithms based
                       // GetPriority

  explicit Vertex(V const& d)
      : m_data(d),
        m_inDegree(0),
        m_outDegree(0),
        m_status(VertexStatus::Undiscovered),
        m_dTime(-1),
        m_fTime(-1),
        m_parent(-1),
        m_priority(INT64_MAX) {}
};

template <class E>
struct Edge {
  E m_data;
  int64_t m_weight;
  EdgeStatus m_status;

  Edge(E const& d, int64_t w)
      : m_data(d), m_weight(w), m_status(EdgeStatus::Undetermined) {}
};

template <class V, class E>
class GraphMatrix : public Graph<V, E> {
 private:
  Vector<Vertex<V>> m_vertices;      // GetVertex Set
  Vector<Vector<Edge<E>*>> m_edges;  // GetEdge Set

 public:
  GraphMatrix() {
    this->m_vertexNum = 0;
    this->m_edgeNum = 0;
  }

  ~GraphMatrix() {
    for (size_type i = 0; i < this->m_vertexNum; ++i) {
      for (size_type j = 0; j < this->m_edgeNum; ++j) {
        delete m_edges[i][j];
      }
    }
  }

  /// @brief
  size_type InsertVertex(const V& v) override {
    // append a column for original matrix
    for (size_type i = 0; i < this->m_vertexNum; ++i) {
      m_edges[i].PushBack(nullptr);
    }
    this->m_vertexNum++;
    // construct a row and append it to new matrix
    m_edges.PushBack(
        Vector<Edge<E>*>(this->m_vertexNum, this->m_vertexNum, nullptr));

    m_vertices.PushBack(Vertex<V>(v));
    return this->m_vertexNum - 1;
  }

  /// @brief
  V RemoveVertex(size_type v) override {
    // delete all out-degree edges
    for (size_type i = 0; i < this->m_vertexNum; ++i) {
      if (ExistsEdge(v, i)) {
        delete m_edges[v][i];
        m_vertices[i].m_inDegree--;
      }
    }
    // delete the `v` row
    m_edges.Remove(v);
    this->m_vertexNum--;

    // delete all in-degree edges and the `v` column
    for (size_type i = 0; i < this->m_vertexNum; ++i) {
      if (ExistsEdge(i, v)) {
        delete m_edges[i].Remove(v);
        m_vertices[i].m_outDegree--;
      }
    }
    // store data of vertex
    auto ans = GetVertex(v);

    // delete the vertex `v`
    m_vertices.Remove(v);

    return ans;
  }

  /// @brief
  V& GetVertex(size_type v) override { return m_vertices[v].m_data; }

  /// @brief
  int64_t GetInDegree(size_type v) override { return m_vertices[v].m_inDegree; }

  /// @brief
  int64_t GetOutDegree(size_type v) override {
    return m_vertices[v].m_outDegree;
  }

  /// @brief
  VertexStatus& GetVertexStatus(size_type v) override {
    return m_vertices[v].m_status;
  }

  /// @brief
  int64_t& GetDTime(size_type v) override { return m_vertices[v].m_dTime; }

  /// @brief
  int64_t& GetFTime(size_type v) override { return m_vertices[v].m_fTime; }

  /// @brief
  size_type& GetParent(size_type v) override { return m_vertices[v].m_parent; }

  /// @brief
  int64_t& GetPriority(size_type v) override {
    return m_vertices[v].m_priority;
  }

  /// @brief
  size_type FirstNeighbor(size_type v) override {
    return NextNeighbor(v, this->m_vertexNum);
  }

  /// @brief
  size_type NextNeighbor(size_type v, size_type i) override {
    i -= 1;
    while ((i > -1) && (!Graph<V, E>::ExistsEdge(v, i))) {
      i--;
    }
    return i;
  }

  /// @brief
  bool ExistsEdge(size_type u, size_type v) override {
    return (0 <= u) && (u < this->m_vertexNum) && (0 <= v) &&
           (v < this->m_vertexNum) && (m_edges[u][v] != nullptr);
  }

  /// @brief
  void InsertEdge(const E& e, int64_t w, size_type u, size_type v) override {
    if (ExistsEdge(u, v)) {
      return;
    }
    m_edges[u][v] = new Edge<E>(e, w);

    // update edges' number
    this->m_edgeNum++;
    // update in-degree/out-degree of `v` / `u`
    m_vertices[u].m_outDegree++;
    m_vertices[v].m_inDegree++;
  }

  /// @brief
  E RemoveEdge(size_type u, size_type v) override {
    auto ans = GetEdge(u, v);
    delete m_edges[u][v];
    m_edges[u][v] = nullptr;

    this->m_edgeNum--;
    m_vertices[u].m_outDegree--;
    m_vertices[v].m_inDegree--;
    return ans;
  }

  /// @brief
  EdgeStatus& GetEdgeStatus(size_type u, size_type v) override {
    return m_edges[u][v]->m_status;
  }

  /// @brief
  E& GetEdge(size_type u, size_type v) override {
    return m_edges[u][v]->m_data;
  }

  /// @brief
  int64_t& GetWeight(size_type u, size_type v) override {
    return m_edges[u][v]->m_weight;
  }
};
}  // namespace dsa

#endif
