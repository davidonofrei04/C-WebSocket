cmake_minimum_required(VERSION 3.17)
project(MyBoostProject)

set(CMAKE_CXX_STANDARD 11)


find_package(Boost REQUIRED COMPONENTS system)

add_executable(MyBoostProject main.cpp
        WebSocketServer.cpp
        WebSocketServer.h
        HTTPServer.cpp
        HTTPServer.h
        DataStream.cpp
        DataStream.h)

target_link_libraries(MyBoostProject Boost::system)
