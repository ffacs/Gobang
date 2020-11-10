cmake_minimum_required(VERSION 3.17)
project(GoBang)

set(CMAKE_CXX_STANDARD 14)

add_executable(GoBang main.cpp src/StateJudge.h src/dfs.h)