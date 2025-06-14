//
// Created by ����Դ on 24-10-13.
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
            // ���鼯���캯��
            explicit DSU(int n) :parent(n),rank(n,1){
                // TODO: ����ɲ��鼯�Ĺ��캯��
                for (int i = 0; i < n; ++i) {
                    parent[i] = i; // �ֶ���ʼ�� parent ����
                    }

            }

            // ���Ҹ��ڵ㲢·��ѹ��
            int find(int x)  {
                // TODO: ����Ԫ�صĸ��ڵ㣬�����·��ѹ��

                if(parent[x] != x)
                {
                    parent[x] = find(parent[x]);
                }
                return parent[x];

            }

            // �ϲ���������
            void unite(int x, int y) {
                // TODO: �ϲ�����

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

            // ��������ڵ��Ƿ�����ͬһ����
            bool same(int x, int y)  {
                // TODO: ��������ڵ��Ƿ�����ͬһ������

                return find(x) == find(y);
            }
        };

        std::list<Vertex> EulerCircle(const LGraph& graph); //����ŷ����·
        bool HaveEulerCircle(const LGraph& graph); //�ж��Ƿ����ŷ����·
        bool IsConnected(const LGraph& graph); //�ж�ͼ�Ƿ���ͨ
        int GetShortestPath(const LGraph& graph, const std::string& vertex_name_x,
            const std::string& vertex_name_y); //���㵥Դ���·��
        int TopologicalShortestPath(const LGraph& graph, std::vector<std::string> path); //�����������޵����·��
        std::vector<EdgeNode> MinimumSpanningTree(const LGraph& graph); //������С������

        bool HaveEulerCircle(const LGraph& graph);


        //����
        bool HaveEulerPath(const LGraph& graph); // �ж��Ƿ����ŷ��·��
        std::list<Vertex> GetAdjacentList(const LGraph& graph, Vertex vertex); // ��ȡ����ڽӱ�

        std::string RecommendTourRoute(const LGraph& graph, const std::string& start);

    }
}
#endif //CAMPUSNAVIGATION_ALGORITHM_H
