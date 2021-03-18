//
// Created by ch'y on 2021/3/17.
//

#ifndef UNTITLED_SERVER_INSTANCE_H
#define UNTITLED_SERVER_INSTANCE_H

#include<vector>

#include "server_info.h"
#include "vm_info.h"

using namespace std;
typedef pair<int, vm_info> vm_with_id;

struct server_instance {
    int ID;
    server_info server;
    int type;// if type=1,it indicate this server instance save in one node mode;

    int cpu_used_a;
    int mem_used_a;
    vector<vm_with_id> vm_info_id_a;

    int cpu_used_b;
    int mem_used_b;
    vector<vm_with_id> vm_info_id_b;

    vector<int> load_status;

    server_instance(int id, server_info server_info, int type)
            :
            ID(id), server(server_info), type(type), cpu_used_a(0), mem_used_a(0), cpu_used_b(0),
            mem_used_b(0),
            load_status((4,0)) {
    }

    bool insert_vm_instance(vm_info &vmInfo, const int &id);

    bool del_vm_instance(const int &id);

private:
    bool update_load_status();
};

#endif //UNTITLED_SERVER_INSTANCE_H
