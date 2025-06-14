//
// Created by ����Դ on 24-10-13.
//

#ifndef CAMPUSNAVIGATION_LOCATIONINFO_H
#define CAMPUSNAVIGATION_LOCATIONINFO_H

#include <string>
#include <iostream>

namespace Graph {
    struct LocationInfo {
        std::string name;         // �ص�����
        int visitTime;       // ����ι���ʱ����λ�����ӣ�
        std::string type;   // �ص�����
        LocationInfo() = default;
        LocationInfo(const std::string& name_, const int visitTime_, const std::string& type_)
            : name(name_), visitTime(visitTime_), type(type_) {}
    };
} // Graph

#endif //CAMPUSNAVIGATION_LOCATIONINFO_H
