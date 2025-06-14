//
// Created by ����Դ on 24-5-16.
//

#include "LGraph.h"

namespace Graph {
    LGraph::LGraph(bool directed)
        : n_verts(0), m_edges(0), directed(directed), ver_list(std::vector<HeadNode>()) {}

    bool LGraph::exist_vertex(const std::string& name) const {
        //TODO:�ж��Ƿ����name���ƵĽڵ�

        return vertex_map.find(name) != vertex_map.end();
    }

    bool LGraph::exist_edge(const std::string& vertex_x_name, const std::string& vertex_y_name) const {
        //TODO:�ж��Ƿ����x-y�ı�
        auto x_it = vertex_map.find(vertex_x_name);
        auto y_it = vertex_map.find(vertex_y_name);
        if(x_it == vertex_map.end() || y_it == vertex_map.end())
                return false;
        Vertex x = x_it->second;//��ȡ����ID
        Vertex y = y_it->second;
        for(const auto& edge : ver_list[x].adj)
        {
            if(edge.dest == y)
                return true;
        }

        if(!directed)//���������ͼ�����ҷ�����Ƿ����
        {
            for(const auto& edge : ver_list[y].adj)
            {
                if(edge.dest == x)
                    return true;
            }
        }

        return false;
    }

    void LGraph::InsertVertex(const LocationInfo& vertex_info) {
        //TODO:����ڵ㣬�ڵ���Ϣ��LocationInfo�����

        if (exist_vertex(vertex_info.name)) {
                throw GraphException("�����Ѵ���");
            }
            vertex_map[vertex_info.name] = n_verts;
            ver_list.emplace_back(HeadNode(vertex_info));
            n_verts += 1;
    }

    void LGraph::DeleteVertex(const LocationInfo& vertex_info) {
        //TODO:ɾ���ڵ㣬�ڵ���Ϣ��LocationInfo�����
        //std::cerr << "LGraph::DeleteVertex(const LocationInfo &vertex_info) ��ûʵ��" << std::endl;

        auto it = vertex_map.find(vertex_info.name);
        if(it == vertex_map.end())
        {
            throw GraphException("���㲻����");
        }
        Vertex index = it->second;

        for(auto& node: ver_list[index].adj)
        {
            if(directed)
            {
                ver_list[node.dest].adj.remove_if([node](const EdgeNode& e)
                {
                    return e.from == node.from;
                    });
            }
            else
            {
                ver_list[node.dest].adj.remove_if([node](const EdgeNode& e)
                {
                    return e.from == node.from || e.from == node.dest;
                    });
            }
        }

        ver_list[index].adj.clear();
        ver_list[index].data = vertex_info;
        deleted.insert(vertex_info.name);
        vertex_map.erase(vertex_info.name);

    }

    void LGraph::UpdateVertex(const LocationInfo& old_info, LocationInfo& new_info) {
        //TODO:���½ڵ㣬��/�ɽڵ����Ϣ��LocationInfo�����
        //std::cerr << "LGraph::UpdateVertex(const LocationInfo &old_info, LocationInfo &new_info) ��ûʵ��" << std::endl;
        if(!exist_vertex(old_info.name))
        {
            throw GraphException("���㲻����");
        }
        auto it = vertex_map.find(old_info.name);
        Vertex index = it->second;
        ver_list[index].data = new_info;

    }

    VertInfo LGraph::GetVertex(const std::string& name) const {
        //TODO:��ȡ�ڵ㣬�ɽڵ�����ѯ�ڵ���Ϣ

        auto it = vertex_map.find(name);
        if (it == vertex_map.end()) {
            throw GraphException("���㲻����");
        }
        return ver_list[it->second].data;

    }

    VertInfo LGraph::GetVertex(const Vertex vertex) const {
        //TODO:��ȡ�ڵ㣬�ɽڵ��ID��ѯ
        if(vertex >= n_verts || vertex <0)
        {
            throw GraphException("��������������Χ");
        }
        return ver_list[vertex].data;
    }

    void LGraph::InsertEdge(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet weight) {
        //TODO:�����
        //std::cerr << "LGraph::InsertEdge(const std::string &vertex_x_name, const std::string &vertex_y_name, GElemSet weight) ��ûʵ��" << std::endl;

        if(!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name))
           {
               throw GraphException("���㲻����!!");
           }


        auto x = vertex_map.find(vertex_x_name);
        auto y = vertex_map.find(vertex_y_name);
        Vertex x_index = x->second;
        Vertex y_index = y->second;

        EdgeNode edge(x_index,y_index,weight);
        ver_list[x_index].adj.push_back(edge);
        if(!directed)
        {
            EdgeNode reverse_edge(y_index,x_index,weight);
            ver_list[y_index].adj.push_back(reverse_edge);
        }
        m_edges +=1;

    }

    void LGraph::DeleteEdge(const std::string& vertex_x_name, const std::string& vertex_y_name) {
        //TODO:ɾ���ߣ��������ڵ���ȷ��һ����
        //std::cerr << "LGraph::DeleteEdge(const std::string &vertex_x_name, const std::string &vertex_y_name) ��ûʵ��" << std::endl;

        if(!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name))
        {
            throw GraphException("���㲻����");
        }
        auto x = vertex_map.find(vertex_x_name);
        auto y = vertex_map.find(vertex_y_name);
        Vertex x_index = x->second;
        Vertex y_index = y->second;
        auto& x_adj = ver_list[x_index].adj;
        x_adj.remove_if([y_index](const EdgeNode& e)
                        {
                            return e.dest == y_index;
                        });
        if(!directed)
        {
            auto& y_adj = ver_list[y_index].adj;
            y_adj.remove_if([x_index](const EdgeNode& e)
                            {
                                return e.dest == x_index;
                            });
        }
        m_edges -= 1;

    }

    void LGraph::DeleteEdge(Vertex vertex_x, Vertex vertex_y) {
        //TODO:ɾ���ߣ��������ڵ�IDȷ��һ����
        //std::cerr << "LGraph::DeleteEdge(Vertex vertex_x, Vertex vertex_y) ��ûʵ��" << std::endl;
        if(vertex_x >=  n_verts || vertex_x <0 || vertex_y >= n_verts || vertex_y <0)
        {
            throw GraphException("��������������Χ");
        }
        auto& adj_list = ver_list[vertex_x].adj;
        adj_list.remove_if([vertex_y](const EdgeNode& e)
                           {
                               return e.dest == vertex_y;
                           });
        if(!directed)
        {
            auto& reverse_adj_list = ver_list[vertex_y].adj;
            reverse_adj_list.remove_if([vertex_x](const EdgeNode& e)
                                       {
                                           return e.dest == vertex_x;
                                       });
        }
        m_edges -=1;
    }


    void LGraph::UpdateEdge(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet new_weight) {
        //TODO:���±ߣ��������ڵ���ȷ��һ����
        //std::cerr << "LGraph::UpdateEdge(const std::string &vertex_x_name, const std::string &vertex_y_name, GElemSet new_weight) ��ûʵ��" << std::endl;
        if(!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name))
        {
            throw GraphException("���㲻����");
        }
        auto x = vertex_map.find(vertex_x_name);
        auto y = vertex_map.find(vertex_y_name);
        Vertex x_index = x->second;
        Vertex y_index = y->second;
        for(auto& edge : ver_list[x_index].adj)
        {
            if(edge.dest == y_index)
            {
                edge.weight = new_weight;
                break;
            }
        }
        if(!directed)
        {
            for(auto& edge: ver_list[y_index].adj)
            {
                if(edge.dest == x_index)
                {
                    edge.weight = new_weight;
                    break;
                }
            }
        }
    }

    GElemSet LGraph::GetEdge(const std::string& vertex_x_name, const std::string& vertex_y_name) const {
        //TODO:��ȡ�ߵ���Ϣ
        //std::cerr << "LGraph::GetEdge(const std::string &vertex_x_name, const std::string &vertex_y_name) ��ûʵ��" << std::endl;

        if(!exist_vertex(vertex_x_name) || !exist_vertex(vertex_y_name))
        {
            throw GraphException("���㲻����");
        }
        auto x = vertex_map.find(vertex_x_name);
        auto y = vertex_map.find(vertex_y_name);
        Vertex x_index = x->second;
        Vertex y_index = y->second;
        for(const auto& e : ver_list[x_index].adj)
        {
            if(e.dest == y_index)
            {

                return e.weight;
            }
        }
        throw GraphException("�߲�����");

    }

    std::vector<EdgeNode> LGraph::SortedEdges(std::function<bool(const GElemSet&, const GElemSet&)> cmp) const {
        //TODO:��ȡ����Ȩ�͸���������������б�
        //std::cerr << "LGraph::SortedEdges(std::function<bool(const GElemSet &, const GElemSet &)> cmp) ��ûʵ��" << std::endl;
        std::vector<EdgeNode>edges;
        for(size_t i=0;i<ver_list.size();i++)
        {
            for(const auto& edge : ver_list[i].adj)
            {
                if(directed || edge.dest > i || (edge.dest == i && edge.from <i))
                {
                    edges.push_back(edge);
                }
            }
        }
        std::sort(edges.begin(),edges.end(),[cmp](const EdgeNode& a,const EdgeNode& b)
                  {
                      return cmp(a.weight,b.weight);
                  });

        return edges;
    }



void LGraph::GetAdjacentList(const std::string& vertex_name) const {
    auto it = vertex_map.find(vertex_name);
    if (it == vertex_map.end()) {
        throw GraphException("���㲻����");
    }
    Vertex vertex = it->second;

    std::cout << "���ڶ�������, �߳���" << std::endl;
    for (const auto& edge : ver_list[vertex].adj) {
        std::string adjacent_vertex_name = ver_list[edge.dest].data.name;
        int edge_weight = edge.weight;
        std::cout << adjacent_vertex_name << ", " << edge_weight << std::endl;
    }
}


std::vector<std::string> LGraph::GetVerticesByType(const std::string& type) const {
    std::vector<std::string> vertices;
    for (const auto& node : ver_list) {
        if (node.data.type == type) {
            vertices.push_back(node.data.name);
        }
    }
    return vertices;
}


void LGraph::UpdateEdgeLength(const std::string& vertex_x_name, const std::string& vertex_y_name, GElemSet new_length) {
    auto x = vertex_map.find(vertex_x_name);
    auto y = vertex_map.find(vertex_y_name);
    if (x == vertex_map.end() || y == vertex_map.end()) {
        throw GraphException("���㲻����");
    }
    Vertex x_index = x->second;
    Vertex y_index = y->second;

    for (auto& edge : ver_list[x_index].adj) {
        if (edge.dest == y_index) {
            edge.weight = new_length;
            break;
        }
    }

    if (!directed) {
        for (auto& edge : ver_list[y_index].adj) {
            if (edge.dest == x_index) {
                edge.weight = new_length;
                break;
            }
        }
    }
}




}
