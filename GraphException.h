//
// Created by ����Դ on 24-10-13.
//

#ifndef CAMPUSNAVIGATION_GRAPHEXCEPTION_H
#define CAMPUSNAVIGATION_GRAPHEXCEPTION_H

#include <exception>
#include <string>

namespace Graph {
    class GraphException : public std::exception {
    private:
        std::string message;  // �Զ��������Ϣ
    public:
        // ���캯������һ��������Ϣ
        explicit GraphException(const std::string& msg) : message(msg) {}

        // ���� what() ���������ش�����Ϣ
        const char* what() const noexcept {
            return message.c_str();
        }
    };

} // Graph

#endif //CAMPUSNAVIGATION_GRAPHEXCEPTION_H
