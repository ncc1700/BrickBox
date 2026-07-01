cmake_minimum_required(VERSION 3.10)

project(BrickBox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_executable(BrickBox src/main.cpp
                        src/core/Channel.cpp
                        src/network/Packet.cpp
                        src/network/Connection.cpp
                        src/network/CSPackets.cpp)
                
target_include_directories(BrickBox PRIVATE include)
target_include_directories(BrickBox PRIVATE bbnet/includes)

target_link_libraries(BrickBox)
