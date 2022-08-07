#ifndef INC_912_DSA_DS_GRAPH_H_
#define INC_912_DSA_DS_GRAPH_H_

#include <ds/autoheader.h>
#include <ds/queue.h>
#include <ds/stack.h>

namespace dsa {
enum class VertexStatus { Undiscovered, Discovered, Visited };
enum class EdgeStatus { Undetermined, Tree, Cross, Forward, Backward };

template <class VertexType, class EdgeType>
class Graph {
 private:
  /// @brief reset all fields both getVertex and getEdge
  void reset() {
    // reset all vertices
    for (size_type i = 0; i < m_numVertex; i++) {
      getVertexStatus(i) = VertexStatus::Undiscovered;
      getDTime(i)        = -1;
      getFTime(i)        = -1;
      getParent(i)       = -1;
      getPriority(i)     = INT64_MAX;

      // reset all edges
      for (size_type j = 0; j < m_numVertex; j++)
        if (existsEdge(i, j))
          getEdgeStatus(i, j) = EdgeStatus::Undetermined;  // 类型
    }
  }

  /// @brief 广度优先搜索算法（连通域）
  void bfs(size_type v, int64_t& clock) {
    Queue<size_type> q;
    getVertexStatus(v) = VertexStatus::Discovered;
    q.enqueue(v);

    while (!q.isEmpty()) {
      // take out the head getVertex of queue
      auto tmp = q.dequeue();

      // record time of starting to visit
      clock += 1;
      getDTime(tmp) = clock;

      // enumerate all neighbors of `tmp`
      for (auto u = firstNeighbor(tmp); u > -1; u = nextNeighbor(tmp, u)) {
        if (getVertexStatus(u) == VertexStatus::Undiscovered) {
          // modify status
          getVertexStatus(u) == VertexStatus::Discovered;
          q.enqueue(u);

          // mark the status of getEdge in traversal tree
          getEdgeStatus(tmp, u) = EdgeStatus::Tree;
          getParent(u)          = tmp;
        } else {
          getEdgeStatus(tmp, u) = EdgeStatus::Cross;
        }
      }

      getVertexStatus(tmp) = VertexStatus::Visited;
    }
  };

  /// @brief （连通域）深度优先搜索算法
  void dfs(size_type, int64_t&) {}

  /// @brief （连通域）基于DFS的双连通分量分解算法
  void bcc(size_type, int64_t&, Stack<size_type>&) {}

  /// @brief （连通域）基于DFS的拓扑排序算法
  bool tSort(size_type, int64_t&, Stack<VertexType>*) { return true; };

  /// @brief （连通域）优先级搜索框架
  template <class PU>
  void pfs(size_type, PU) {}

 public:
  size_type m_numVertex;  // total number of vertices
  size_type m_numEdge;    // total number of edges

  /**
   * getVertex's operation
   */

  /// @brief 插入顶点，返回编号
  virtual size_type insertVertex(VertexType const& v) = 0;

  /// @brief 删除顶点及其关联边，返回该顶点信息
  virtual VertexType removeVertex(size_type v) = 0;

  /// @brief 顶点的数据（该顶点的确存在）
  virtual VertexType& getVertex(size_type v) = 0;

  /// @brief Return vertex's `m_inDegree` (the in-degree of vertex) if
  /// existsEdge
  virtual int64_t getInDegree(size_type v) = 0;

  /// @brief Return vertex's `m_outDegree` (the out-degree of vertex) if
  /// existsEdge
  virtual int64_t getOutDegree(size_type v) = 0;

  /// @brief Return vertex's first adjacent vertex
  virtual size_type firstNeighbor(size_type v) = 0;

  /// @brief Return vertex's next adjacent vertex(relative to the current
  /// adjacent vertex `j`)
  virtual size_type nextNeighbor(size_type v, size_type i) = 0;

  /// @brief Return the reference vertex's `m_status` (the vertexStatus of
  /// vertex)
  virtual VertexStatus& getVertexStatus(size_type v) = 0;

  /// @brief Return the reference vertex's `m_dTime` (the moment the vertex was
  /// found)
  virtual int64_t& getDTime(size_type v) = 0;

  /// @brief Return the reference vertex's `m_fTime` (the moment the vertex has
  /// been visited)
  virtual int64_t& getFTime(size_type v) = 0;

  /// @brief Return the reference vertex's `m_parent` (the parent vertex in
  /// traversal tree)
  virtual size_type& getParent(size_type v) = 0;

  /// @brief Return the reference vertex's `m_priority` (the priority in
  /// traversal tree of algorithms based priority)
  virtual int64_t& getPriority(size_type v) = 0;

  /**
   * Edge's operation
   * 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
   */

  /// @brief Return true if the edge between `u` and `v` exists
  virtual bool existsEdge(size_type u, size_type v) = 0;

  /// @brief Insert a edge with specific weight between two vertices
  virtual void insertEdge(EdgeType const& e, int64_t w, size_type u,
                          size_type v) = 0;

  /// @brief Delete the edge between a pair of vertices and return it
  virtual EdgeType removeEdge(size_type u, size_type v) = 0;

  /// @brief Return the reference of status of the edge between `u` and `v`
  virtual EdgeStatus& getEdgeStatus(size_type u, size_type v) = 0;

  /// @brief Return the reference of edge between `u` and `v` if exists
  virtual EdgeType& getEdge(size_type u, size_type v) = 0;

  /// @brief Return the reference of weight of the edge between `u` and `v`
  virtual int64_t& getWeight(size_type u, size_type v) = 0;

  /// @brief 广度优先搜索算法
  void bfs(size_type s) {
    reset();
    size_type v     = s;
    int64_t   clock = 0;

    do {
      if (getVertexStatus(v) == VertexStatus::Undiscovered) {
        bfs(v, clock);
      }
      v = ++v % m_numVertex;
    } while (s != v);
  }

  /// @brief 深度优先搜索算法
  void dfs(size_type) {}

  /// @brief 基于DFS的双连通分量分解算法
  void bcc(size_type) {}

  /// @brief 基于DFS的拓扑排序算法
  Stack<VertexType>* tSort(size_type) { return nullptr; }

  /// @brief 最小支撑树Prim算法
  void prim(size_type) {}

  /// @brief 最短路径Dijkstra算法
  void dijkstra(size_type) {}

  /// @brief 优先级搜索框架
  template <class PU>
  void Pfs(size_type, PU) {}
};
}  // namespace dsa

#endif
