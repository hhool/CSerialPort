#***************************************************************************
# File: CMakeLists.txt
# Author: hhool
# Blog: https://github.com/hhool
#***************************************************************************

cmake_minimum_required(VERSION 2.8.12)

project(crc16_test)

set(CMAKE_CXX_STANDARD 11) # C++11

include_directories(.)

add_executable(${PROJECT_NAME} crc16.cpp crtc16_test.cpp)

add_dependencies(gtest get_gtest)

target_link_libraries( ${PROJECT_NAME} gtest)

if (WIN32)
    target_link_libraries( ${PROJECT_NAME} setupapi)
elseif(APPLE)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(FOUNDATION_LIBRARY Foundation)
    target_link_libraries( ${PROJECT_NAME} ${FOUNDATION_LIBRARY} ${IOKIT_LIBRARY})
elseif(UNIX)
    target_link_libraries( ${PROJECT_NAME} pthread)
endif ()