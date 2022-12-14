# Top-level CMake project file, do global configuration

cmake_minimum_required(VERSION 3.15)

project (Blockout VERSION 1.0)

#add_executable(${PROJECT_NAME})

add_subdirectory(external)
add_subdirectory(src)
