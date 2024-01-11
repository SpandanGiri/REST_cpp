cmake_minimum_required(VERSION 3.10)

project(REST VERSION 1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

#set flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

#add_subdirectory(dependencies/cpp_redis)

include_directories(/usr/local/lib/libboost)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/crow/include)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cpp_redis/includes)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dependencies/cpp_redis/tacopie)

link_directories(/usr/local/lib/libboost)

add_executable(REST main.cpp)

target_link_libraries(REST boost_system)
target_link_libraries(REST pthread)
#target_link_libraries(REST cpp_redis)


