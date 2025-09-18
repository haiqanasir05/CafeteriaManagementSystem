cmake_minimum_required(VERSION 3.16)
project(QtProject LANGUAGES CXX)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(QtProject main.cpp)
target_link_libraries(QtProject PRIVATE Qt6::Widgets)

