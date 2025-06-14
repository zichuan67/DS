//
// Created by 刘凯源 on 24-10-13.
//

#ifndef CAMPUSNAVIGATION_ALGORITHM_H
#define CAMPUSNAVIGATION_ALGORITHM_H

#include "LGraph.h"

#include<queue>
#include<stack>
#include<iterator>
#include<algorithm>

namespace Graph {
    namespace Algorithm {
        class DSU {
        private:
            std::vector<int> parent, rank;
        public:
            // 并查集构造函数
            explicit DSU(int n) :parent(n),rank(n,1){
                // TODO: 请完成并查集的构造函数
                for (int i = 0; i < n; ++i) {
                    parent[i] = i; // 手动初始化 parent 数组
                    }

            }

            // 查找根节点并路径压缩
            int find(int x)  {
                // TODO: 查找元素的根节点，并完成路径压缩

                if(parent[x] != x)
                {
                    parent[x] = find(parent[x]);
                }
                return parent[x];

            }

            // 合并两个集合
            void unite(int x, int y) {
                // TODO: 合并集合

                int x_root = find(x);
                int y_root = find(y);
                if(x_root == y_root)
                    return;
                if(rank[x_root] < rank[y_root])
                {
                    parent[x_root] = y_root;
                }
                else
                {
                    parent[y_root] = x_root;
                    if(rank[x_root] <rank[y_root])
                    {
                        rank[x_root]++;
                    }
                }
            }

            // 检查两个节点是否属于同一集合
            bool same(int x, int y)  {
                // TODO: 检查两个节点是否属于同一个集合

                return find(x) == find(y);
            }
        };

        std::list<Vertex> EulerCircle(const LGraph& graph); //计算欧拉回路
        bool HaveEulerCircle(const LGraph& graph); //判断是否存在欧拉回路
        bool IsConnected(const LGraph& graph); //判断图是否联通
        int GetShortestPath(const LGraph& graph, const std::string& vertex_name_x,
            const std::string& vertex_name_y); //计算单源最短路径
        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path); //计算拓扑受限的最短路径
        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph); //计算最小生成树

        bool HaveEulerCircle(const LGraph& graph);


        //新增
        bool HaveEulerPath(const LGraph& graph); // 判断是否存在欧拉路径
        std::list<Vertex> GetAdjacentList(const LGraph& graph, Vertex vertex); // 获取点的邻接表

        std::string RecommendTourRoute(const LGraph& graph, const std::string& start);

    }
}
#endif //CAMPUSNAVIGATION_ALGORITHM_H
