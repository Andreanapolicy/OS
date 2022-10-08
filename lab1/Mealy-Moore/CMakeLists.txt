cmake_minimum_required(VERSION 3.23)
project(Mealy_Moore)

set(CMAKE_CXX_STANDARD 20)

add_executable(Mealy_Moore main.cpp src/TextParser/ITextParser.h src/TextParser/CSVTextParser.h src/Common/Automat.h)
