//main.cpp
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>
#include<string>

using namespace std;


struct server {
    string name;
    int cpu;
    int mem;
    int hard_cost;
    int day_cost;

    server(string Iname, int Icpu, int Imem, int Ihard_cost, int Iday_cost) :
            name(Iname), cpu(Icpu), mem(Imem), hard_cost(Ihard_cost), day_cost(Iday_cost) {};
};

struct vm {
    string name;
    int cpu;
    int mem;
    int setting;

    vm(string Iname, int Icpu, int Imem, int Isetting) :
            name(std::move(Iname)), cpu(Icpu), mem(Imem), setting(Isetting) {};
};


struct instruction {
    string instr_type;
    string vm_type;
    int vm_id;

    instruction(string string1, string string2, int id) :
            instr_type(std::move(string1)), vm_type(std::move(string2)), vm_id(id) {};
};


vector<server> server_vector;
vector<vm> vm_vector;
vector<instruction> instr_vector;
vector<vector<instruction>> instruction_assemble;

int all_day = 0;
int day_instr_num = 0;


server produceServer(string &string1) {
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
    return server(name, cpu, mem, hard_cost, day_cost);
}

vm producevm(string &string1) {
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

    return vm(name, cpu, mem, setting);
}

instruction produceInstruction(string &string1) {
    int left_bound = 1;
    int right_bound = 1;

    right_bound = string1.find(',');
    string instr_name = string1.substr(left_bound, right_bound - left_bound);
    left_bound = right_bound + 1;


    string vm_type;
    if (instr_name != "del") {
        right_bound = string1.find(',', left_bound);
        vm_type = string1.substr(left_bound, right_bound - left_bound);
        left_bound = right_bound + 1;
    }


    right_bound = string1.find(',', left_bound);
    int vm_id = stoi(string1.substr(left_bound, right_bound - left_bound));
    left_bound = right_bound + 1;


    return instruction(instr_name, vm_type, vm_id);
}

int main() {

    ifstream train_file;
    train_file.open("../training-1.txt");

    if (train_file) {

        if (!train_file.eof()) {
            string read_line;
            getline(train_file, read_line);
            int count = stoi(read_line);
            server_vector.reserve(count);

            for (int i = 0; i < count; i++) {
                getline(train_file, read_line);
//                cout << read_line;
                server_vector.push_back(produceServer(read_line));
            }

            getline(train_file, read_line);
            count = stoi(read_line);
            vm_vector.reserve(count);
            for (int i = 0; i < count; i++) {
                getline(train_file, read_line);
//                cout << read_line;
                vm_vector.push_back(producevm(read_line));
            }


            getline(train_file, read_line);
            all_day = stoi(read_line);
            instruction_assemble.reserve(all_day);

            for (int i = 0; i < all_day; i++) {
                getline(train_file, read_line);
                day_instr_num = stoi(read_line);
                instr_vector.reserve(day_instr_num);
                for (int j = 0; j < day_instr_num; j++) {
                    getline(train_file, read_line);
//                    cout << read_line;
                    instr_vector.push_back(produceInstruction(read_line));
                }
                instruction_assemble.push_back(instr_vector);
                instr_vector.clear();
            }

        }
    }

    system("pause");
    return 0;
}