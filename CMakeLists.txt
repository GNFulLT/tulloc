cmake_minimum_required(VERSION 3.5)

project(tulloc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tulloc STATIC )

install(TARGETS tulloc
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
