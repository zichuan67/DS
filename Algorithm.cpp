//
// Created by ����Դ on 24-10-13.
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
            //TODO:�Ӹ�����������һ����·
            //std::cerr << "GetCircuit ��ûʵ��" << std::endl;
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
            //TODO:�ж�ͼ�Ƿ���ͨ
            //std::cerr << "IsConnected ��ûʵ��" << std::endl;
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
            //TODO:�ж��Ƿ���ŷ����·
            //std::cerr << "HaveEulerCircle ��ûʵ��" << std::endl;


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
            //TODO:��ȡŷ����·,�����ʹ��GetCircuit����
            //std::cerr << "EulerCircle ��ûʵ��" << std::endl;


            std::list<Vertex> result;
            if (!HaveEulerCircle(graph)) {
                return result;
            }

            // ��ȡ���ж���
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
                // ��ȡ�ڽӱ�
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
            //TODO:���������������ͼ
            //std::cerr << "BFSv ��ûʵ��" << std::endl;



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
            //TODO:��ȡ����֮������·��
            //std::cerr << "GetShortestPath ��ûʵ��" << std::endl;
            //return -1;
            auto startIt = graph.Map().find(vertex_name_x);
    auto endIt = graph.Map().find(vertex_name_y);

    if (startIt == graph.Map().end() || endIt == graph.Map().end()) {
        throw GraphException("One or both vertices do not exist!");
    }

    Vertex start = startIt->second;
    Vertex end = endIt->second;

    // ʹ��Dijkstra�㷨��Ѱ���·��
    struct DistInfo {
        int distance;
        int prev; // ǰ�����������
    };
    // �洢ÿ���������̾����ǰ����������
    std::vector<DistInfo> dist(graph.VertexCount(), {std::numeric_limits<int>::max(), -1});
    std::priority_queue<std::pair<int, Vertex>, std::vector<std::pair<int, Vertex>>, std::greater<std::pair<int, Vertex>>> pq;

    dist[start].distance = 0;
    dist[start].prev = -1; // ����ǰ��������
    pq.push({0, start});

    while (!pq.empty()) {
        Vertex current = pq.top().second;
        pq.pop();

        if (current == end) {
            // �ҵ��յ㣬�ؽ�·��
            std::vector<Vertex> pathIndices;
            for (Vertex v = end; v != -1; v = dist[v].prev) {
                pathIndices.push_back(v);
            }
            // ��ת·������Ϊ�Ǵ��յ���ǰ׷��
            std::reverse(pathIndices.begin(), pathIndices.end());

            // ���;����������
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
            //TODO:��ȡ�������޵����·������������path����
            //std::cerr << "TopologicalShortestPath ��ûʵ��" << std::endl;
            //return -1;
            int totalDistance = 0;
            for (size_t i = 0; i < path.size() - 1; ++i) {
            const std::string& from = path[i];
            const std::string& to = path[i + 1];
            if (!graph.exist_vertex(from) || !graph.exist_vertex(to)) {
                throw GraphException("·���еĵص㲻����");
            }

            totalDistance += GetShortestPath(graph, from, to);
            }
            return totalDistance;
        }



        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph) {
            //TODO:������С�����������������ϵı�
            //std::cerr << "MinimumSpanningTree ��ûʵ��" << std::endl;
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
        throw GraphException("��㲻����");
    }

    // ʹ�����������������ͼ����������·��
    std::stack<std::string> stack;
    std::set<std::string> visited;
    std::ostringstream route;
    int totalTime = 0; // ��������ʱ
    int totalDistance = 0; // ��·������
    std::string previousVertex;

    stack.push(start);
    visited.insert(start);

    while (!stack.empty()) {
        std::string current = stack.top();
        stack.pop();

        // ��ȡ��ǰ������Ϣ
        VertInfo currentInfo = graph.GetVertex(current);

        // ��ӵ�·����
        if (visited.size() == 1) {
            route << current << " (�ι� " << currentInfo.visitTime << " ����)";
        } else {
            // ���·���Ƿ���ڲ��ۼӾ���
            if (!previousVertex.empty() && graph.exist_edge(previousVertex, current)) {
                int distance = graph.GetEdge(previousVertex, current);
                totalDistance += distance;
                route << " -> " << current << " (���� " << distance << " ��, �ι� " << currentInfo.visitTime << " ����)";
            } else {
                route << " -> " << current << " (�ι� " << currentInfo.visitTime << " ����)";
            }
        }

        totalTime += currentInfo.visitTime; // �ۼ�����ʱ��
        previousVertex = current;

        // ��ȡ��ǰ����������ڽӶ���
        auto currentVertexIndex = graph.Map().at(current);
        const auto& adjList = graph.List()[currentVertexIndex].adj;

        // ���Ҳ���������δ���ʵ����ڶ���
        for (const auto& edge : adjList) {
            std::string adjacentVertexName = graph.List()[edge.dest].data.name;
            if (!visited.count(adjacentVertexName)) {
                stack.push(adjacentVertexName);
                visited.insert(adjacentVertexName);
            }
        }
    }

    // �����������ʱ����·������
    route << "\n��������ʱ: " << totalTime << " ��λʱ��";
    route << "\n��·������: " << totalDistance << " ��λ����";

    return route.str();
}




    }

}
