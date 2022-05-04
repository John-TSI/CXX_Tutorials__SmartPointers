cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SmartPointers VERSION 1.0.0)

set(SRC_FILES src/obj.cpp)
add_executable(${PROJECT_NAME} src/main.cpp ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC inc)
