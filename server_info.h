//
// Created by ch'y on 2021/3/17.
//

#ifndef UNTITLED_SERVER_INFO_H
#define UNTITLED_SERVER_INFO_H
#include <string>
using std::string;
struct server_info {
    string name;
    int cpu;
    int mem;
    int hard_cost;
    int day_cost;

    server_info(string Iname, int Icpu, int Imem, int Ihard_cost, int Iday_cost) :
            name(Iname), cpu(Icpu), mem(Imem), hard_cost(Ihard_cost), day_cost(Iday_cost) {};
};

#endif //UNTITLED_SERVER_INFO_H
