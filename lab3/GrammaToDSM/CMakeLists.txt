cmake_minimum_required(VERSION 3.23)
project(GrammaToDSM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(GrammaToDSM main.cpp)
