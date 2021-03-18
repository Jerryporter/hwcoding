//
// Created by ch'y on 2021/3/18.
//

#ifndef UNTITLED_SERVER_ALLOCATOR_H
#define UNTITLED_SERVER_ALLOCATOR_H
#include <vector>
#include <memory>
#include <string>

#include "server_instance.h"

using namespace std;
typedef pair<int,server_instance> server_and_id;
class server_allocator{
public:

private:
    vector<server_and_id> server_list;
};
#endif //UNTITLED_SERVER_ALLOCATOR_H
