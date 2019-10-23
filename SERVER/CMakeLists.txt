cmake_minimum_required(VERSION 3.13)
project(PROGETTO)

set(CMAKE_CXX_STANDARD 17)

add_executable(PROGETTO main.cpp CRDT.cpp CRDT.h Char.cpp Char.h)