cmake_minimum_required(VERSION 3.8.2d)
project(ClientServer)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS "-lncurses")

add_executable(ClientServer main.cpp RingBuffer.h RingBuffer.cpp WindowManager.cpp WindowManager.h)