//
// Created by 刘凯源 on 24-10-13.
//
#include "Algorithm.h"
#include"LGraph.h"
#include<queue>
#include<stack>
#include<iterator>
#include<algorithm>
#include <sstream>
#include<vector>
#include<set>
#include<limits>

namespace Graph {
    namespace Algorithm {

        std::list<Vertex> GetCircuit(LGraph& graph, Vertex start) {
            //TODO:从给定点出发获得一条回路
            //std::cerr << "GetCircuit 还没实现" << std::endl;
            //return {};


            std::list<Vertex> circuit;
            std::vector<bool> visited(graph.VertexCount(), false);
            std::stack<Vertex> stack;
            stack.push(start);

            while (!stack.empty()) {
                Vertex current = stack.top();
                stack.pop();

                if (!visited[current]) {
                    visited[current] = true;
                    circuit.push_back(current);

                    for (const auto& edge : graph.List()[current].adj) {
                        Vertex neighbor = edge.dest;
                        if (!visited[neighbor]) {
                            stack.push(neighbor);
                        }
                    }
                }
            }

            return circuit;


        }




        bool IsConnected(const LGraph& graph) {
            //TODO:判断图是否联通
            //std::cerr << "IsConnected 还没实现" << std::endl;
            //return false;

            if (graph.VertexCount() == 0) return false;

            DSU dsu(graph.VertexCount());

            for (const auto& headNode : graph.List()) {
                for (const auto& edge : headNode.adj) {
                    dsu.unite(edge.from, edge.dest);
                }
            }

            for (size_t i = 1; i < graph.VertexCount(); ++i) {
                if (dsu.find(0) != dsu.find(i)) {
                    return false;
                }
            }

            return true;




        }





        bool HaveEulerCircle(const LGraph& graph) {
            //TODO:判断是否有欧拉回路
            //std::cerr << "HaveEulerCircle 还没实现" << std::endl;


            if (!IsConnected(graph)) {
        return false;
    }

    for (const auto& headNode : graph.List()) {
        if (headNode.adj.size() % 2 != 0) {
            return false;
        }
    }

    return true;




            //return false;
        }




        std::list<Vertex> EulerCircle(const LGraph& graph) {
            //TODO:获取欧拉回路,你可以使用GetCircuit函数
            //std::cerr << "EulerCircle 还没实现" << std::endl;


            std::list<Vertex> result;
            if (!HaveEulerCircle(graph)) {
                return result;
            }

            // 获取所有顶点
            std::vector<Vertex> vertices;
            for (const auto& entry : graph.Map()) {
                vertices.push_back(entry.second);
            }

            if (vertices.empty()) {
                return result;
            }

            Vertex start = vertices[0];
            std::stack<std::pair<Vertex, EdgeNode>> st;
            st.push({ start, EdgeNode(start, start, 0) });

            while (!st.empty()) {
                Vertex from = st.top().first;

                bool found = false;
                // 获取邻接表
                const auto& adjList = graph.List()[from].adj;

                for (auto it = adjList.begin(); it != adjList.end(); ++it) {
                    if (it->from == from) {
                        st.push({ it->dest, *it });
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    result.push_front(st.top().second.from);
                    st.pop();
                }
            }

            return result;



            //return {};
        }


        void BFSv(LGraph& graph, Vertex v, std::vector<bool>& visited) {
            //TODO:广度优先搜索整个图
            //std::cerr << "BFSv 还没实现" << std::endl;



            std::queue<Vertex> q;
    q.push(v);
    visited[v] = true;

    while (!q.empty()) {
        Vertex current = q.front();
        q.pop();

        for (const auto& edge : graph.List()[current].adj) {
            Vertex neighbor = edge.dest;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }






        }

        int GetShortestPath(const LGraph& graph, const std::string& vertex_name_x, const std::string& vertex_name_y) {
            //TODO:获取两点之间的最短路径
            //std::cerr << "GetShortestPath 还没实现" << std::endl;
            //return -1;
            auto startIt = graph.Map().find(vertex_name_x);
    auto endIt = graph.Map().find(vertex_name_y);

    if (startIt == graph.Map().end() || endIt == graph.Map().end()) {
        throw GraphException("One or both vertices do not exist!");
    }

    Vertex start = startIt->second;
    Vertex end = endIt->second;

    // 使用Dijkstra算法找寻最短路径
    struct DistInfo {
        int distance;
        int prev; // 前驱顶点的索引
    };
    // 存储每个顶点的最短距离和前驱顶点索引
    std::vector<DistInfo> dist(graph.VertexCount(), {std::numeric_limits<int>::max(), -1});
    std::priority_queue<std::pair<int, Vertex>, std::vector<std::pair<int, Vertex>>, std::greater<std::pair<int, Vertex>>> pq;

    dist[start].distance = 0;
    dist[start].prev = -1; // 起点的前驱不存在
    pq.push({0, start});

    while (!pq.empty()) {
        Vertex current = pq.top().second;
        pq.pop();

        if (current == end) {
            // 找到终点，重建路径
            std::vector<Vertex> pathIndices;
            for (Vertex v = end; v != -1; v = dist[v].prev) {
                pathIndices.push_back(v);
            }
            // 反转路径，因为是从终点往前追溯
            std::reverse(pathIndices.begin(), pathIndices.end());

            // 输出途经顶点名称
            for (size_t i = 0; i < pathIndices.size(); ++i) {
                std::cout << graph.List()[pathIndices[i]].data.name;
                if (i != pathIndices.size() - 1) {
                    std::cout << " -> ";
                }
            }
            std::cout << std::endl;

            return dist[end].distance;
        }

        for (const auto& edge : graph.List()[current].adj) {
            Vertex neighbor = edge.dest;
            int weight = edge.weight;

            if (dist[current].distance + weight < dist[neighbor].distance) {
                dist[neighbor].distance = dist[current].distance + weight;
                dist[neighbor].prev = current;
                pq.push({dist[neighbor].distance, neighbor});
            }
        }
    }

    throw GraphException("No path found between the vertices!");
}




        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path) {
            //TODO:获取拓扑受限的最短路径，拓扑序由path给出
            //std::cerr << "TopologicalShortestPath 还没实现" << std::endl;
            //return -1;
            int totalDistance = 0;
            for (size_t i = 0; i < path.size() - 1; ++i) {
            const std::string& from = path[i];
            const std::string& to = path[i + 1];
            if (!graph.exist_vertex(from) || !graph.exist_vertex(to)) {
                throw GraphException("路径中的地点不存在");
            }

            totalDistance += GetShortestPath(graph, from, to);
            }
            return totalDistance;
        }



        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph) {
            //TODO:计算最小生成树，并返回树上的边
            //std::cerr << "MinimumSpanningTree 还没实现" << std::endl;
            //return {};


            std::vector<EdgeNode> mst;
            DSU dsu(graph.VertexCount());

            auto edges = graph.SortedEdges();
            for (const auto& edge : edges) {
                if (dsu.find(edge.from) != dsu.find(edge.dest)) {
                    dsu.unite(edge.from, edge.dest);
                    mst.push_back(edge);
                }
            }

            return mst;


        }



        bool HaveEulerPath(const LGraph& graph) {
    if (!IsConnected(graph)) {
        return false;
    }

    int odd_degree_count = 0;
    for (const auto& headNode : graph.List()) {
        if (headNode.adj.size() % 2 != 0) {
            odd_degree_count++;
        }
    }

    return odd_degree_count == 0 || odd_degree_count == 2;
}

std::list<Vertex> GetAdjacentList(const LGraph& graph, Vertex vertex) {
    std::list<Vertex> adjacent_vertices;
    for (const auto& edge : graph.List()[vertex].adj) {
        adjacent_vertices.push_back(edge.dest);
    }
    return adjacent_vertices;
}


std::string RecommendTourRoute(const LGraph& graph, const std::string& start) {
    if (!graph.exist_vertex(start)) {
        throw GraphException("起点不存在");
    }

    // 使用深度优先搜索遍历图，生成游览路线
    std::stack<std::string> stack;
    std::set<std::string> visited;
    std::ostringstream route;
    int totalTime = 0; // 总游览耗时
    int totalDistance = 0; // 总路径长度
    std::string previousVertex;

    stack.push(start);
    visited.insert(start);

    while (!stack.empty()) {
        std::string current = stack.top();
        stack.pop();

        // 获取当前顶点信息
        VertInfo currentInfo = graph.GetVertex(current);

        // 添加到路线中
        if (visited.size() == 1) {
            route << current << " (参观 " << currentInfo.visitTime << " 分钟)";
        } else {
            // 检查路径是否存在并累加距离
            if (!previousVertex.empty() && graph.exist_edge(previousVertex, current)) {
                int distance = graph.GetEdge(previousVertex, current);
                totalDistance += distance;
                route << " -> " << current << " (距离 " << distance << " 米, 参观 " << currentInfo.visitTime << " 分钟)";
            } else {
                route << " -> " << current << " (参观 " << currentInfo.visitTime << " 分钟)";
            }
        }

        totalTime += currentInfo.visitTime; // 累加游览时间
        previousVertex = current;

        // 获取当前顶点的所有邻接顶点
        auto currentVertexIndex = graph.Map().at(current);
        const auto& adjList = graph.List()[currentVertexIndex].adj;

        // 查找并访问所有未访问的相邻顶点
        for (const auto& edge : adjList) {
            std::string adjacentVertexName = graph.List()[edge.dest].data.name;
            if (!visited.count(adjacentVertexName)) {
                stack.push(adjacentVertexName);
                visited.insert(adjacentVertexName);
            }
        }
    }

    // 添加总游览耗时和总路径长度
    route << "\n总游览耗时: " << totalTime << " 单位时间";
    route << "\n总路径长度: " << totalDistance << " 单位长度";

    return route.str();
}




    }

}
