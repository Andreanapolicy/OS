cmake_minimum_required(VERSION 3.23)
project(NotDSMToDSM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(NotDSMToDSM main.cpp src/MachineSaver/MachineSaver.cpp src/MachineSaver/MachineSaver.h)
