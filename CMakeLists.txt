cmake_minimum_required(VERSION 3.5)

project(tulloc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(tulloc STATIC "${CMAKE_SOURCE_DIR}/internal/bucket.cpp" "${CMAKE_SOURCE_DIR}/src/tustring.cpp"
"${CMAKE_SOURCE_DIR}/src/dynamic_mh_pool.cpp" "${CMAKE_SOURCE_DIR}/src/singleton_mh_pool.cpp" "${CMAKE_SOURCE_DIR}/src/string_pool.cpp")

target_include_directories(tulloc PUBLIC "${CMAKE_SOURCE_DIR}/include/")

add_subdirectory(test)

install(TARGETS tulloc
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
