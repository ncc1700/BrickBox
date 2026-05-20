cmake_minimum_required(VERSION 3.10)

project(BrickBox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(BrickBox bbnet/includes/)
add_executable(BrickBox src/main.cpp
                
                bbnet/src/core/bytestream.c
                bbnet/src/core/storage.c
                bbnet/src/core/tools.c
                bbnet/src/network/client/client.c)

target_link_libraries(BrickBox z uv)