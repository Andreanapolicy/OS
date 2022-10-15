cmake_minimum_required(VERSION 3.23)
project(Minimization)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Minimization main.cpp src/Args/Args.h src/Args/ArgsParser.h src/Machine/Machine.h src/MachineSaver/MachineSaver.h src/TextParser/CSVTextParser.h src/MachineMinimizator/MachineMinimizator.h)
