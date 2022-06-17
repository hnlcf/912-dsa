#pragma once

#include <AutoHeader.hpp>
#include <Graph.hpp>
#include <Vector.hpp>

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
      : m_data(d), m_inDegree(0), m_outDegree(0), m_status(VertexStatus::Undiscovered), m_dTime(-1),
        m_fTime(-1), m_parent(-1), m_priority(INT64_MAX) {
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

  template<class V, class E>
  class GraphMatrix : public Graph<V, E> {
private:
    Vector<Vertex<V>>         m_vertices;  // vertex set
    Vector<Vector<Edge<E> *>> m_edges;     // edge set

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

    size_type insertVertex(const V &v) override {
      // append a column for original matrix
      for (size_type i = 0; i < this->m_vertexNum; ++i) {
        m_edges[i].push_back(nullptr);
      }
      this->m_vertexNum++;
      // construct a row and append it to new matrix
      m_edges.push_back(Vector<Edge<E> *>(this->m_vertexNum, this->m_vertexNum, nullptr));

      m_vertices.push_back(Vertex<V>(v));
      return this->m_vertexNum - 1;
    }

    V removeVertex(size_type v) override {
      // delete all out-degree edges
      for (size_type i = 0; i < this->m_vertexNum; ++i) {
        if (existsEdge(v, i)) {
          delete m_edges[v][i];
          m_vertices[i].m_inDegree--;
        }
      }
      // delete the `v` row
      m_edges.remove(v);
      this->m_vertexNum--;

      // delete all in-degree edges and the `v` column
      for (size_type i = 0; i < this->m_vertexNum; ++i) {
        if (existsEdge(i, v)) {
          delete m_edges[i].remove(v);
          m_vertices[i].m_outDegree--;
        }
      }
      // store data of vertex
      auto ans = vertex(v);

      // delete the vertex `v`
      m_vertices.remove(v);

      return ans;
    }

    V &vertex(size_type v) {
      return m_vertices[v].m_data;
    }

    int64_t inDegree(size_type v) override {
      return m_vertices[v].m_inDegree;
    }

    int64_t outDegree(size_type v) override {
      return m_vertices[v].m_outDegree;
    }

    VertexStatus &vertexStatus(size_type v) override {
      return m_vertices[v].m_status;
    }

    int64_t &dTime(size_type v) override {
      return m_vertices[v].m_dTime;
    }

    int64_t &fTime(size_type v) override {
      return m_vertices[v].m_fTime;
    }

    size_type &parent(size_type v) override {
      return m_vertices[v].m_parent;
    }

    int64_t &priority(size_type v) override {
      return m_vertices[v].m_priority;
    }

    size_type firstNeighbor(size_type v) override {
      return nextNeighbor(v, this->m_vertexNum);
    }

    size_type nextNeighbor(size_type v, size_type i) override {
      i -= 1;
      while ((i > -1) && (!Graph<V, E>::existsEdge(v, i))) {
        i--;
      }
      return i;
    }

    bool existsEdge(size_type u, size_type v) override {
      return (0 <= u) && (u < this->m_vertexNum) && (0 <= v) && (v < this->m_vertexNum) &&
             (m_edges[u][v] != nullptr);
    }

    void insertEdge(const E &e, int64_t w, size_type u, size_type v) override {
      if (existsEdge(u, v)) {
        return;
      }
      m_edges[u][v] = new Edge<E>(e, w);

      // update edges' number
      this->m_edgeNum++;
      // update in-degree/out-degree of `v` / `u`
      m_vertices[u].m_outDegree++;
      m_vertices[v].m_inDegree++;
    }

    E removeEdge(size_type u, size_type v) override {
      auto ans = edge(u, v);
      delete m_edges[u][v];
      m_edges[u][v] = nullptr;

      this->m_edgeNum--;
      m_vertices[u].m_outDegree--;
      m_vertices[v].m_inDegree--;
      return ans;
    }

    EdgeStatus &edgeStatus(size_type u, size_type v) override {
      return m_edges[u][v]->m_status;
    }

    E &edge(size_type u, size_type v) override {
      return m_edges[u][v]->m_data;
    }

    int64_t &weight(size_type u, size_type v) override {
      return m_edges[u][v]->m_weight;
    }
  };
}
