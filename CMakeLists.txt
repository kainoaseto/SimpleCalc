cmake_minimum_required(VERSION 3.6)
project(SimpleCalc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")

set(SOURCE_FILES
    CGrammer.h
    CScanner.cpp
    CScanner.h
    Main.cpp
    pch.h)

add_executable(SimpleCalc ${SOURCE_FILES})