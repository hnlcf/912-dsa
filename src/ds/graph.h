#ifndef INC_912_DSA_DS_GRAPH_H_
#define INC_912_DSA_DS_GRAPH_H_

#include "autoheader.h"
#include "queue.h"
#include "stack.h"

namespace dsa {
enum class VertexStatus { Undiscovered, Discovered, Visited };
enum class EdgeStatus { Undetermined, Tree, Cross, Forward, Backward };

template <class V, class E>
class Graph {
 private:
  /// @brief Reset all fields both GetVertex and GetEdge
  void Reset() {
    // Reset all vertices
    for (size_type i = 0; i < m_vertexNum; i++) {
      GetVertexStatus(i) = VertexStatus::Undiscovered;
      GetDTime(i) = -1;
      GetFTime(i) = -1;
      GetParent(i) = -1;
      GetPriority(i) = INT64_MAX;

      // Reset all edges
      for (size_type j = 0; j < m_vertexNum; j++)
        if (ExistsEdge(i, j))
          GetEdgeStatus(i, j) = EdgeStatus::Undetermined;  // 类型
    }
  }

  /// @brief 广度优先搜索算法（连通域）
  void BFS(size_type v, int64_t& clock) {
    Queue<size_type> q;
    GetVertexStatus(v) = VertexStatus::Discovered;
    q.Enqueue(v);

    while (!q.IsEmpty()) {
      // take out the head GetVertex of queue
      auto tmp = q.Dequeue();

      // record time of starting to visit
      clock += 1;
      GetDTime(tmp) = clock;

      // enumerate all neighbors of `tmp`
      for (auto u = FirstNeighbor(tmp); u > -1; u = NextNeighbor(tmp, u)) {
        if (GetVertexStatus(u) == VertexStatus::Undiscovered) {
          // modify status
          GetVertexStatus(u) == VertexStatus::Discovered;
          q.Enqueue(u);

          // mark the status of GetEdge in traversal tree
          GetEdgeStatus(tmp, u) = EdgeStatus::Tree;
          GetParent(u) = tmp;
        } else {
          GetEdgeStatus(tmp, u) = EdgeStatus::Cross;
        }
      }

      GetVertexStatus(tmp) = VertexStatus::Visited;
    }
  };

  /// @brief （连通域）深度优先搜索算法
  void DFS(size_type, int64_t&) {}

  /// @brief （连通域）基于DFS的双连通分量分解算法
  void BCC(size_type, int64_t&, Stack<size_type>&) {}

  /// @brief （连通域）基于DFS的拓扑排序算法
  bool TSort(size_type, int64_t&, Stack<V>*) { return true; };

  /// @brief （连通域）优先级搜索框架
  template <class PU>
  void PFS(size_type, PU) {}

 public:
  size_type m_vertexNum;  // total number of vertices
  size_type m_edgeNum;    // total number of edges

  /**
   * GetVertex's operation
   */

  /// @brief 插入顶点，返回编号
  virtual size_type InsertVertex(V const& v) = 0;

  /// @brief 删除顶点及其关联边，返回该顶点信息
  virtual V RemoveVertex(size_type v) = 0;

  /// @brief 顶点的数据（该顶点的确存在）
  virtual V& GetVertex(size_type v) = 0;

  /// @brief Return vertex's `m_inDegree` (the in-degree of vertex) if
  /// existsEdge
  virtual int64_t GetInDegree(size_type v) = 0;

  /// @brief Return vertex's `m_outDegree` (the out-degree of vertex) if
  /// existsEdge
  virtual int64_t GetOutDegree(size_type v) = 0;

  /// @brief Return vertex's first adjacent vertex
  virtual size_type FirstNeighbor(size_type v) = 0;

  /// @brief Return vertex's next adjacent vertex(relative to the current
  /// adjacent vertex `j`)
  virtual size_type NextNeighbor(size_type v, size_type i) = 0;

  /// @brief Return the reference vertex's `m_status` (the vertexStatus of
  /// vertex)
  virtual VertexStatus& GetVertexStatus(size_type v) = 0;

  /// @brief Return the reference vertex's `m_dTime` (the moment the vertex was
  /// found)
  virtual int64_t& GetDTime(size_type v) = 0;

  /// @brief Return the reference vertex's `m_fTime` (the moment the vertex has
  /// been visited)
  virtual int64_t& GetFTime(size_type v) = 0;

  /// @brief Return the reference vertex's `m_parent` (the parent vertex in
  /// traversal tree)
  virtual size_type& GetParent(size_type v) = 0;

  /// @brief Return the reference vertex's `m_priority` (the priority in
  /// traversal tree of algorithms based priority)
  virtual int64_t& GetPriority(size_type v) = 0;

  /**
   * Edge's operation
   * 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
   */

  /// @brief Return true if the edge between `u` and `v` exists
  virtual bool ExistsEdge(size_type u, size_type v) = 0;

  /// @brief Insert a edge with specific weight between two vertices
  virtual void InsertEdge(E const& e, int64_t w, size_type u, size_type v) = 0;

  /// @brief Delete the edge between a pair of vertices and return it
  virtual E RemoveEdge(size_type u, size_type v) = 0;

  /// @brief Return the reference of status of the edge between `u` and `v`
  virtual EdgeStatus& GetEdgeStatus(size_type u, size_type v) = 0;

  /// @brief Return the reference of edge between `u` and `v` if exists
  virtual E& GetEdge(size_type u, size_type v) = 0;

  /// @brief Return the reference of weight of the edge between `u` and `v`
  virtual int64_t& GetWeight(size_type u, size_type v) = 0;

  /// @brief 广度优先搜索算法
  void BFS(size_type s) {
    Reset();
    size_type v = s;
    int64_t clock = 0;

    do {
      if (GetVertexStatus(v) == VertexStatus::Undiscovered) {
        BFS(v, clock);
      }
      v = ++v % m_vertexNum;
    } while (s != v);
  }

  /// @brief 深度优先搜索算法
  void DFS(size_type) {}

  /// @brief 基于DFS的双连通分量分解算法
  void BCC(size_type) {}

  /// @brief 基于DFS的拓扑排序算法
  Stack<V>* TSort(size_type) { return nullptr; }

  /// @brief 最小支撑树Prim算法
  void Prim(size_type) {}

  /// @brief 最短路径Dijkstra算法
  void Dijkstra(size_type) {}

  /// @brief 优先级搜索框架
  template <class PU>
  void Pfs(size_type, PU) {}
};
}  // namespace dsa

#endif
