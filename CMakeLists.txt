cmake_minimum_required(VERSION 3.21)
project(testc C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(testc main.c)
target_link_libraries(testc mhash)