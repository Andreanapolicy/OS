cmake_minimum_required(VERSION 3.23)
project(GrammarToDSM)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(GrammarToDSM main.cpp src/Common/GrammarSide.h src/GrammarParser/GrammarParser.cpp src/GrammarParser/GrammarParser.h src/MachineSaver/MachineSaver.cpp src/MachineSaver/MachineSaver.h src/Machine/Machine.h src/Converter/DSMConverter.cpp src/Converter/DSMConverter.h src/Common/Utils.h src/Common/Lettering.h)
