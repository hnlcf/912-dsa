#pragma once

#include "AutoHeader.hpp"
#include "Queue.hpp"
#include "Stack.hpp"

namespace dsa {
    enum class VertexStatus { Undiscovered, Discovered, Visited };
    enum class EdgeStatus { Undetermined, Tree, Cross, Forward, Backward };

    template<class V, class E>
    class Graph {
    private:
        /// Reset all fields both vertex and edge
        void reset() {
            // reset all vertices
            for (size_type i = 0; i < m_vertexNum; i++) {
                vertexStatus(i) = VertexStatus::Undiscovered;
                dTime(i) = -1;
                fTime(i) = -1;
                parent(i) = -1;
                priority(i) = INT64_MAX;

                // reset all edges
                for (size_type j = 0; j < m_vertexNum; j++)
                    if (existsEdge(i, j))
                        edgeStatus(i, j) = EdgeStatus::Undetermined;  // 类型
            }
        }

        /// 广度优先搜索算法（连通域）
        void BFS(size_type v, int64_t &clock) {
            Queue<size_type> q;
            vertexStatus(v) = VertexStatus::Discovered;
            q.enqueue(v);

            while (!q.isEmpty()) {
                // take out the head vertex of queue
                auto tmp = q.dequeue();

                // record time of starting to visit
                clock += 1;
                dTime(tmp) = clock;

                // enumerate all neighbors of `tmp`
                for (auto u = firstNeighbor(tmp); u > -1; u = nextNeighbor(tmp, u)) {
                    if (vertexStatus(u) == VertexStatus::Undiscovered) {
                        // modify status
                        vertexStatus(u) == VertexStatus::Discovered;
                        q.enqueue(u);

                        // mark the status of edge in traversal tree
                        edgeStatus(tmp, u) = EdgeStatus::Tree;
                        parent(u) = tmp;
                    } else {
                        edgeStatus(tmp, u) = EdgeStatus::Cross;
                    }
                }

                vertexStatus(tmp) = VertexStatus::Visited;
            }
        };

        /// （连通域）深度优先搜索算法
        void DFS(size_type, int64_t &){};

        /// （连通域）基于DFS的双连通分量分解算法
        void BCC(size_type, int64_t &, Stack<size_type> &){};

        /// （连通域）基于DFS的拓扑排序算法
        bool TSort(size_type, int64_t &, Stack<V> *) {
            return true;
        };

        /// （连通域）优先级搜索框架
        template<class PU>
        void PFS(size_type, PU){};

    public:
        size_type m_vertexNum;  // total number of vertices
        size_type m_edgeNum;    // total number of edges

        /**
         * Vertex's operation
         */

        /// 插入顶点，返回编号
        virtual size_type insertVertex(V const &v) = 0;

        /// 删除顶点及其关联边，返回该顶点信息
        virtual V removeVertex(size_type v) = 0;

        /// 顶点的数据（该顶点的确存在）
        virtual V &vertex(size_type v) = 0;

        /// Return vertex's `m_inDegree` (the in-degree of vertex) if existsEdge
        virtual int64_t inDegree(size_type v) = 0;

        /// Return vertex's `m_outDegree` (the out-degree of vertex) if existsEdge
        virtual int64_t outDegree(size_type v) = 0;

        /// Return vertex's first adjacent vertex
        virtual size_type firstNeighbor(size_type v) = 0;

        /// Return vertex's next adjacent vertex(relative to the current adjacent vertex `j`)
        virtual size_type nextNeighbor(size_type v, size_type i) = 0;

        /// Return the reference vertex's `m_status` (the vertexStatus of vertex)
        virtual VertexStatus &vertexStatus(size_type v) = 0;

        /// Return the reference vertex's `m_dTime` (the moment the vertex was found)
        virtual int64_t &dTime(size_type v) = 0;

        /// Return the reference vertex's `m_fTime` (the moment the vertex has been visited)
        virtual int64_t &fTime(size_type v) = 0;

        /// Return the reference vertex's `m_parent` (the parent vertex in traversal tree)
        virtual size_type &parent(size_type v) = 0;

        /// Return the reference vertex's `m_priority` (the priority in traversal tree of algorithms based priority)
        virtual int64_t &priority(size_type v) = 0;

        /**
         * Edge's operation
         * 边：这里约定，无向边均统一转化为方向互逆的一对有向边，从而将无向图视作有向图的特例
         */

        /// Return true if the edge between `u` and `v` exists
        virtual bool existsEdge(size_type u, size_type v) = 0;

        /// Insert a edge with specific weight between two vertices
        virtual void insertEdge(E const &e, int64_t w, size_type u, size_type v) = 0;

        /// Delete the edge between a pair of vertices and return it
        virtual E removeEdge(size_type u, size_type v) = 0;

        /// Return the reference of status of the edge between `u` and `v`
        virtual EdgeStatus &edgeStatus(size_type u, size_type v) = 0;

        /// Return the reference of edge between `u` and `v` if exists
        virtual E &edge(size_type u, size_type v) = 0;

        /// Return the reference of weight of the edge between `u` and `v`
        virtual int64_t &weight(size_type u, size_type v) = 0;

        /* Algorithms */

        /// 广度优先搜索算法
        void bfs(size_type){};

        /// 深度优先搜索算法
        void dfs(size_type){};

        /// 基于DFS的双连通分量分解算法
        void bcc(size_type){};

        /// 基于DFS的拓扑排序算法
        Stack<V> *tSort(size_type) {
            return nullptr;
        };

        /// 最小支撑树Prim算法
        void prim(size_type){};

        /// 最短路径Dijkstra算法
        void dijkstra(size_type){};

        /// 优先级搜索框架
        template<class PU>
        void pfs(size_type, PU){};
    };
}
