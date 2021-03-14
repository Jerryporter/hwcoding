//main.cpp
#include <fstream>
#include <utility>
#include <vector>
#include <iostream>
#include<string>

using namespace std;

//数据类型定义,一共有3种数据类型:
//服务器,虚拟机,指令
//其中,指令类型为2合1,目前没有想好如何区分add和del指令.所以将add和del指令统一存到instruction结构中
struct server {
    string name;
    int cpu;
    int mem;
    int hard_cost;
    int day_cost;

    server(string Iname, int Icpu, int Imem, int Ihard_cost, int Iday_cost) :
            name(std::move(Iname)), cpu(Icpu), mem(Imem), hard_cost(Ihard_cost), day_cost(Iday_cost) {};
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

//这里定义了3个暂存读入数据的vector
vector<server> server_vector;
vector<vm> vm_vector;
vector<instruction> instr_vector;

//下面3个函数功能是字符串分割功能,使用读入的字符串创建对应的结构
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

instruction read_instruction(string &string1) {
    int left_bound = 1;
    int right_bound = 1;

    right_bound = string1.find(',');
    string instr_name = string1.substr(left_bound, right_bound - left_bound);
    left_bound = right_bound + 1;

    //对于del指令,选择将其vm_type部分置空.
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
    //打开数据集文件
    ifstream train_file;
    train_file.open("../training-1.txt");
    //判断数据文件是否成功打开
    if (train_file) {
        //判断数据文件是否读完
        if (!train_file.eof()) {
            string read_line;
            getline(train_file, read_line);
            int count = stoi(read_line);
            //此循环测试了是否可以正确读入服务器类型
            for (int i = 0; i < count; i++) {
                getline(train_file, read_line);
                cout << read_line;
                server_vector.push_back(produceServer(read_line));
            }

            //此部分测试是否正确读入了虚拟机类型
            getline(train_file, read_line);
            count = stoi(read_line);
            for (int i = 0; i < count; i++) {
                getline(train_file, read_line);
                cout << read_line;
                vm_vector.push_back(producevm(read_line));
            }


        }
    }

    system("pause");
    return 0;
}