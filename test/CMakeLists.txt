cmake_minimum_required(VERSION 3.19)
project(test)

set(CMAKE_CXX_STANDARD 98)

add_executable(test main.cpp FamilyMart.cpp FamilyMart.h Commodity.cpp Commodity.h CommoditySold.cpp CommoditySold.h Bint.cpp Bint.h)