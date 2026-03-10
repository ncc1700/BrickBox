cmake_minimum_required(VERSION 3.10)

project(BrickBox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(BrickBox src/main.cpp
                src/network/Connection.cpp
                src/network/Packet.cpp
                src/network/NetworkTools.cpp
                src/network/protocol/1.21.11/MCProtocol.cpp)