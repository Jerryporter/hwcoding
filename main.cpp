//main.cpp
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <chrono>
#include "server_info.h"
#include "vm_info.h"
#include "request.h"

using namespace std;


vector<server_info> server_info_vector;
vector<vm_info> vm_info_vector;
vector<request> instr_vector;
vector<vector<request>> request_assemble;

int all_day = 0;
int day_instr_num = 0;


server_info produceserver_info(string &string1) {
    int left_bound = 1;
    int right_bound = 1;

    right_bound = string1.find(',');
    string name = string1.substr(left_bound, right_bound - left_bound);
    left_bound = right_bound + 1;

    right_bound = string1.find(',', left_bound);
    int cpu = stoi(string1.substr(left_bound, right_bound - left_bound));
    left_bound = right_bound + 1;

    right_bound = string1.find(',', left_bound);
    int mem = stoi(string1.substr(left_bound, right_bound - left_bound));
    left_bound = right_bound + 1;

    right_bound = string1.find(',', left_bound);
    int hard_cost = stoi(string1.substr(left_bound, right_bound - left_bound));
    left_bound = right_bound + 1;

    right_bound = string1.find(')', left_bound);
    int day_cost = stoi(string1.substr(left_bound, right_bound - left_bound));
    return server_info(name, cpu, mem, hard_cost, day_cost);
}

vm_info producevm_info(string &string1) {
    int left_bound = 1;
    int right_bound = 1;

    right_bound = string1.find(',');
    string name = string1.substr(left_bound, right_bound - left_bound);
    left_bound = right_bound + 1;

    right_bound = string1.find(',', left_bound);
    int cpu = stoi(string1.substr(left_bound, right_bound - left_bound));
    left_bound = right_bound + 1;

    right_bound = string1.find(',', left_bound);
    int mem = stoi(string1.substr(left_bound, right_bound - left_bound));
    left_bound = right_bound + 1;

    right_bound = string1.find(',', left_bound);
    int setting = stoi(string1.substr(left_bound, right_bound - left_bound));
    left_bound = right_bound + 1;

    return vm_info(name, cpu, mem, setting);
}

request producerequest(string &string1) {
    int left_bound = 1;
    int right_bound = 1;

    right_bound = string1.find(',');
    string instr_name = string1.substr(left_bound, right_bound - left_bound);
    left_bound = right_bound + 1;


    string vm_info_type;
    if (instr_name != "del") {
        right_bound = string1.find(',', left_bound);
        vm_info_type = string1.substr(left_bound, right_bound - left_bound);
        left_bound = right_bound + 1;
    }


    right_bound = string1.find(',', left_bound);
    int vm_info_id = stoi(string1.substr(left_bound, right_bound - left_bound));
    left_bound = right_bound + 1;


    return request(instr_name, vm_info_type, vm_info_id);
}

int main() {

    auto start_time = chrono::system_clock::now();
    ifstream train_file;
    train_file.open("../training-1.txt");

    if (train_file) {

        if (!train_file.eof()) {
            string read_line;
            getline(train_file, read_line);
            int count = stoi(read_line);
            server_info_vector.reserve(count);

            for (int i = 0; i < count; i++) {
                getline(train_file, read_line);
//                cout << read_line;
                server_info_vector.push_back(produceserver_info(read_line));
            }

            getline(train_file, read_line);
            count = stoi(read_line);
            vm_info_vector.reserve(count);
            for (int i = 0; i < count; i++) {
                getline(train_file, read_line);
//                cout << read_line;
                vm_info_vector.push_back(producevm_info(read_line));
            }


            getline(train_file, read_line);
            all_day = stoi(read_line);
            request_assemble.reserve(all_day);

            for (int i = 0; i < all_day; i++) {
                getline(train_file, read_line);
                day_instr_num = stoi(read_line);
                instr_vector.reserve(day_instr_num);
                for (int j = 0; j < day_instr_num; j++) {
                    getline(train_file, read_line);
//                    cout << read_line;
                    instr_vector.push_back(producerequest(read_line));
                }
                request_assemble.push_back(instr_vector);
                instr_vector.clear();
            }

        }
    }

    auto end_time = chrono::system_clock::now();
    auto time_duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);
    cout<<static_cast<double>(time_duration.count());
    system("pause");
    return 0;
}