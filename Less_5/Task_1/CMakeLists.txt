cmake_minimum_required(VERSION 3.19)
project(Task_1)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpqxx -lpq")
set(PQXX /usr/local/include/pqxx)
find_library(PQXX_LIB pqxx)
find_library(PQ_LIB pq)

add_executable(Task_1 main.cpp SQL.cpp SQL.h)
target_link_libraries(Task_1  PRIVATE pqxx)