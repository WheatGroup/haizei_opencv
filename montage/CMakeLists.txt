# cmake 的最低版本要求
cmake_minimum_required(VERSION 3.1)

project(montage)

find_package(OpenCV 4 REQUIRED)

add_executable(montage montage.cpp)
target_link_libraries(montage ${OpenCV_LIBS}) 