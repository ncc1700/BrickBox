cmake_minimum_required(VERSION 3.10)

project(BrickBox)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(BrickBox src/main.cpp
                src/network/Connection.cpp
                src/network/Packet.cpp
                src/network/NetworkTools.cpp
                src/network/PacketReceiver.cpp
                src/network/PacketSender.cpp
                src/network/protocol/1.21.11/ProtCallbacks.cpp
                src/network/protocol/MCProtocol.cpp
                src/network/protocol/1.21.11/client/CInitPackets.cpp
                src/network/protocol/1.21.11/client/CConfigPackets.cpp
                src/network/protocol/1.21.11/client/CSyncPackets.cpp
                src/network/protocol/1.21.11/server/SInitPackets.cpp
                src/network/protocol/1.21.11/server/SConfigPackets.cpp
                src/network/protocol/1.21.11/server/SSyncPackets.cpp
                src/network/protocol/1.21.11/server/SEventPackets.cpp
                src/network/protocol/1.21.11/server/SMiscPackets.cpp

                src/network/AbstractFormat.cpp)