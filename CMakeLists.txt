cmake_minimum_required(VERSION 3.20)
project(tsu_multithreading_2)

set(CMAKE_CXX_STANDARD 17)

add_executable(tsu_multithreading_2 main.cpp Worker.cpp Worker.h WorkerThread.cpp WorkerThread.h)
