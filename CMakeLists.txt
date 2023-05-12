cmake_minimum_required(VERSION 3.5)

project(tulloc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tulloc STATIC "${CMAKE_CURRENT_SOURCE_DIR}/internal/bucket.cpp")

add_subdirectory(test)

install(TARGETS tulloc
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
