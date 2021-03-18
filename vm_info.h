//
// Created by ch'y on 2021/3/17.
//

#ifndef UNTITLED_VM_INFO_H
#define UNTITLED_VM_INFO_H

#include <string>

using std::string;

struct vm_info {
    string name;
    int cpu;
    int mem;
    int setting;

    vm_info(string Iname, int Icpu, int Imem, int Isetting) :
            name(Iname), cpu(Icpu), mem(Imem), setting(Isetting) {};
};

#endif //UNTITLED_VM_INFO_H
