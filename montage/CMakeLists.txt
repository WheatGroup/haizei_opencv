# cmake 的最低版本要求
cmake_minimum_required(VERSION 3.1)

project(transition_pic)

find_package(OpenCV 4 REQUIRED)

add_executable(transition_pic transition_pic.cpp)
target_link_libraries(transition_pic ${OpenCV_LIBS}) 