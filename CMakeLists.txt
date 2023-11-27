cmake_minimum_required(VERSION 3.17)
project(server)

set(CMAKE_CXX_STANDARD 11)


find_package(Boost REQUIRED COMPONENTS system)
add_executable(server main.cpp)

target_link_libraries(server Boost::system)