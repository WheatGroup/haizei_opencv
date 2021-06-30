# cmake 的最低版本要求
cmake_minimum_required(VERSION 3.1)

project(pic_make)

find_package(OpenCV 4 REQUIRED)

add_executable(pic_make pic_make.cpp)
target_link_libraries(pic_make ${OpenCV_LIBS}) 