enable_testing()

# Define the test executable and link with the library
add_executable(tulloc_test "${CMAKE_CURRENT_SOURCE_DIR}/bucket_test.cpp")
target_link_libraries(tulloc_test tulloc)

target_include_directories(tulloc_test PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../internal")

# Add a test case
add_test(NAME bucket_test COMMAND bucket_test)