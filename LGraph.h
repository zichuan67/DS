//
// Created by ����Դ on 24-5-16.
//

#ifndef LGRAPH_LGRAPH_H
#define LGRAPH_LGRAPH_H

#include <map>
#include <set>
#include <list>
#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include "LocationInfo.h"
#include "GraphException.h"

namespace Graph {
    typedef size_t Vertex;    /* ����ID���ͣ�����ʹ��size_t���� */
    typedef int GElemSet;  /* ��Ȩ���ͣ�����ʹ��int���� */
    typedef LocationInfo VertInfo; /* ������Ϣ���ͣ�����ʹ��LocationInfo */
    constexpr int NIL = -1;         /* ���㲻����ʱ�ķ���ֵ */

    struct EdgeNode {
        Vertex from, dest;     /* �ߵ���һ�˵��� */
        GElemSet weight; /* Ȩ�� */
        EdgeNode(Vertex from, Vertex dest, GElemSet weight)
            : from(from), dest(dest), weight(weight) {}
    };

    struct HeadNode {
        VertInfo data;           /* �洢������Ϣ */
        std::list<EdgeNode> adj; /* �ڽӱ�ʹ��STL������listʵ�� */

        HeadNode() = default;

        explicit HeadNode(const VertInfo& data_)
            : data(data_), adj(std::list<EdgeNode>()) {}
    };

    class LGraph {
    private:
        int n_verts;   // ������
        int m_edges;   // ����
        bool directed; // trueΪ����ͼ��falseΪ����ͼ
        std::vector<HeadNode> ver_list; // �ڽӱ�
        std::map<std::string, Vertex> vertex_map; // �ص����͵ص�IDӳ�䣬ID��0��ʼ
        std::set<std::string> deleted; // �Ѿ�ɾ���ĵص�
    public:
        bool exist_vertex(const std::string& name) const; // ��ѯ�ڵ��Ƿ���ڣ����ڷ���true
        bool exist_edge(const std::string& vertex_x_name, const std::string& vertex_y_name) const; // ��ѯ���Ƿ���ڣ����ڷ���true
        explicit LGraph(bool directed = false);
        const int& VertexCount() const { return n_verts; } // ��ȡ������
        const int& EdgesCount() const { return m_edges; } // ��ȡ����
        const std::vector<HeadNode>& List() const { return ver_list; } // ��ȡ�ڽӱ�
        const std::map<std::string, Vertex>& Map() const { return vertex_map; } //��ȡӳ���

        void InsertVertex(const LocationInfo& vertex_info); // �����
        void DeleteVertex(const LocationInfo& vertex_info); // ɾ���㣬ͬʱɾ�����ڱ�
        void UpdateVertex(const LocationInfo& old_info, LocationInfo& new_info); //�޸ĵ���Ϣ
        VertInfo GetVertex(const std::string& name) const; // ͨ���ص��� ��ѯ��
        VertInfo GetVertex(Vertex vertex) const; // ͨ����ID��ѯ��

        void InsertEdge(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet weight);// �����
        void DeleteEdge(const std::string& vertex_x_name, const std::string& vertex_y_name); // ɾ����
        void DeleteEdge(Vertex vertex_x, Vertex vertex_y); // ɾ����
        void UpdateEdge(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet new_weight); // �޸ı�
        GElemSet GetEdge(const std::string& vertex_x_name, const std::string& vertex_y_name) const; // ��ѯ��
        std::vector<EdgeNode> SortedEdges(
            std::function<bool(const GElemSet&, const GElemSet&)> cmp = std::less<>()
        ) const; // ���ر�Ȩ��ֵ����Ľ��(��С����)


        void GetAdjacentList(const std::string& vertex_name) const; // ��ȡ����ڽӱ�
        std::vector<std::string> GetVerticesByType(const std::string& type) const; // �������ͻ�ȡ��������
        void UpdateEdgeLength(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet new_length); // ���±ߵĳ���

    };
}
#endif  // LGRAPH_LGRAPH_H
