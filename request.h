//
// Created by ch'y on 2021/3/17.
//

#ifndef UNTITLED_REQUEST_H
#define UNTITLED_REQUEST_H
#include<string>
using std::string;
struct request {
    string instr_type;
    string vm_info_type;
    int vm_info_id;

    request(string string1, string string2, int id) :
            instr_type(string1), vm_info_type(std::move(string2)), vm_info_id(id) {};
};
#endif //UNTITLED_REQUEST_H
