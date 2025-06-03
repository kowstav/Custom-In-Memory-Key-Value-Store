# Minimum CMake version required.
cmake_minimum_required(VERSION 3.14)

# Project name.
project(CustomKeyValueStore)

# Set C++ standard to C++17.
set(CMAKE_CXX_STANDARD 17)
# Enforce C++17 standard.
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Enable extensions if needed for certain libraries, though generally prefer standard code.
set(CMAKE_CXX_EXTENSIONS OFF)

# Add include directory for header files.
include_directories(include)

# List of source files for the kv_store_lib.
set(KV_STORE_LIB_SOURCES
    src/utils.cpp
    src/hash_map.cpp
    src/trie.cpp
    src/lru_cache.cpp
    src/bloom_filter.cpp
    src/kv_store.cpp
)
# Add the library target.
add_library(kv_store_lib STATIC ${KV_STORE_LIB_SOURCES})
# Target include directories for the library itself (if it has internal includes not in global path).
target_include_directories(kv_store_lib PUBLIC include)


# Add executable for the main CLI application.
add_executable(kv_store_cli src/main.cpp)
# Link the main CLI executable against the kv_store_lib.
target_link_libraries(kv_store_cli PRIVATE kv_store_lib)


# Option to enable building tests (default ON).
option(BUILD_TESTS "Build unit tests" ON)

# If building tests is enabled.
if(BUILD_TESTS)
    # Enable CTest testing framework.
    enable_testing()

    # List of all test source files.
    set(TEST_FILES
        tests/test_hash_map.cpp
        tests/test_trie.cpp
        tests/test_lru_cache.cpp
        tests/test_bloom_filter.cpp
        tests/test_kv_store.cpp
    )

    # Iterate over each test file to create an executable and a CTest test.
    foreach(TEST_FILE ${TEST_FILES})
        # Get the base name of the test file (e.g., test_hash_map).
        get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)
        # Add an executable for the current test.
        add_executable(${TEST_NAME} ${TEST_FILE})
        # Link the test executable against the kv_store_lib.
        target_link_libraries(${TEST_NAME} PRIVATE kv_store_lib)
        # Add this executable to CTest.
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endforeach()
    # Print message indicating tests will be built.
    message(STATUS "Tests will be built.")
else()
    # Print message indicating tests will be skipped.
    message(STATUS "Tests will NOT be built.")
endif()