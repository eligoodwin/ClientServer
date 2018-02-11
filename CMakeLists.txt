cmake_minimum_required(VERSION 3.9)
project(ClientServer)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)

add_executable(ClientServer main.cpp ClientManager.cpp ClientManager.h Helper.cpp Helper.h Colors.h)