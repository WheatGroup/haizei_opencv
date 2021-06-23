# cmake 的最低版本要求
cmake_minimum_required(VERSION 3.1)

project(concat_pic)

find_package(OpenCV 4 REQUIRED)

add_executable(demo concat_pic.cpp)
target_link_libraries(demo ${OpenCV_LIBS}) 