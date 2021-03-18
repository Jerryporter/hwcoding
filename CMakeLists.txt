cmake_minimum_required(VERSION 3.17)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp server_info.h vm_info.h request.h server_instance.cpp server_instance.h server_allocator.cpp server_allocator.h)