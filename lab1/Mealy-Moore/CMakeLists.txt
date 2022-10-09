cmake_minimum_required(VERSION 3.23)
project(Mealy_Moore)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(Mealy_Moore main.cpp src/TextParser/CSVTextParser.h src/Common/Automat.h src/Converter/MachineConverter.h src/MachineSaver/MachineSaver.h src/Common/LetterRandomizer.h)
