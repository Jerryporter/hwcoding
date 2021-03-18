//
// Created by ch'y on 2021/3/17.
//
#include <iostream>
#include <functional>
#include "server_instance.h"
#include "server_info.h"
#include "vm_info.h"

using namespace std;

bool equalImpl(const vm_with_id &lhs, const int &id) {
    return lhs.first == id;
}

bool server_instance::insert_vm_instance(vm_info &vmInfo, const int &id) {
    try {
        if (type == 1) {
            bool insert_node_in_a = true;
            if (insert_node_in_a) {
                vm_info_id_a.emplace_back(id, vmInfo);
                cpu_used_a += vmInfo.cpu;
                mem_used_a += vmInfo.mem;
            } else {
                vm_info_id_b.emplace_back(id, vmInfo);
                cpu_used_b += vmInfo.cpu;
                mem_used_b += vmInfo.mem;
            }
        } else {
            vm_info_id_a.emplace_back(id, vmInfo);
            cpu_used_a += vmInfo.cpu / 2;
            mem_used_a += vmInfo.mem / 2;

            vm_info_id_b.emplace_back(id, vmInfo);
            cpu_used_b += vmInfo.cpu / 2;
            mem_used_b += vmInfo.mem / 2;
        }
        update_load_status();
        return true;
    } catch (exception &e) {
        cerr << "server_instance create error!" << endl;
        return false;
    }
}

bool server_instance::del_vm_instance(const int &id) {
    auto ita = find_if(vm_info_id_a.begin(), vm_info_id_a.end(), bind(equalImpl, std::placeholders::_1, id));
    auto itb = find_if(vm_info_id_b.begin(), vm_info_id_b.end(), bind(equalImpl, std::placeholders::_1, id));
    if (type == 1) {
        if (ita != vm_info_id_a.end()) {
            cpu_used_a -= ita->second.cpu;
            mem_used_a -= ita->second.mem;
            vm_info_id_a.erase(ita);
        } else {
            if (itb != vm_info_id_b.end()) {
                cpu_used_b -= ita->second.cpu;
                mem_used_b -= ita->second.mem;
                vm_info_id_b.erase(itb);
            } else {
                std::cerr << "server id is" << this->ID << "del operation fail" << endl;
                return false;
            }
        }
    } else {
        if (ita != vm_info_id_a.end() && itb != vm_info_id_b.end()) {
            cpu_used_a -= ita->second.cpu / 2;
            mem_used_a -= ita->second.mem / 2;
            vm_info_id_a.erase(ita);
            cpu_used_b -= itb->second.cpu / 2;
            mem_used_b -= itb->second.mem / 2;
            vm_info_id_b.erase(itb);
        } else {
            cerr << "server id is" << this->ID << "del operation fail" << endl;
            return false;
        }
    }
    update_load_status();
    return true;
}

bool server_instance::update_load_status() {
    load_status[0] = server.mem - mem_used_a;
    load_status[2] = server.cpu - cpu_used_a;
    load_status[1] = server.mem - mem_used_b;
    load_status[3] = server.cpu - cpu_used_b;
    return true;
}
