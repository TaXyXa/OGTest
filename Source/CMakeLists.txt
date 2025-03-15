cmake_minimum_required(VERSION 3.10)

project(SlotMachine)

set(SOURCE main.cpp)
set(CMAKE_CXX_STANDART 17)
set(CMAKE_CXX_STANDART_REQUIRED True)

set(CMAKE_CXX_COMPILER g++)

add_executable(SlotMachine ${SOURCE})